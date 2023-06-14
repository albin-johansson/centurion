/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_FONTS_FONT_CACHE_HPP_
#define CENTURION_FONTS_FONT_CACHE_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <ostream>        // ostream
#include <string>         // string
#include <unordered_map>  // unordered_map
#include <utility>        // move

#include "../common.hpp"
#include "../features.hpp"
#include "../video/renderer.hpp"
#include "../video/texture.hpp"
#include "font.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * Provides efficient font rendering.
 *
 * This class can be used to cache individual glyphs as textures that can subsequently be
 * rendered one-by-one to form strings. Note, this approach will not result in accurate
 * kerning. However, this might not be noticeable, and simply worth the performance boost. This
 * approach is very efficient for rendering pieces of text that frequently changes, since other
 * approaches would require dynamic allocation and de-allocation for every new rendered string.
 *
 * Furthermore, it is possible to cache rendered strings and associate them with integer
 * identifiers. In contrast with the first approach, this will result in accurate kerning. The
 * only problem is that it is hard to know the exact strings you will render at compile-time.
 * Use this option if you know that you are going to render some specific string a lot.
 *
 * Note, instances of this class are initially empty, i.e. they hold no cached glyphs or
 * strings. It is up to you to explicitly specify what you want to cache.
 *
 * \see font
 * \see font_bundle
 */
class font_cache final {
 public:
  using id_type = usize;
  using size_type = usize;

  struct glyph_data final {
    texture glyph;          ///< The cached texture of the glyph.
    glyph_metrics metrics;  ///< The metrics associate with the glyph.
  };

  /**
   * Creates a font cache based on the font at the specified file path.
   *
   * \param file the file path of the font.
   * \param size the size of the font.
   */
  font_cache(const char* file, const int size) : mFont {file, size} {}

  font_cache(const std::string& file, const int size) : mFont {file, size} {}

  explicit font_cache(font&& font) noexcept : mFont {std::move(font)} {}

  /// Renders a glyph, returning the x-coordinate for the next glyph.
  template <typename T>
  auto render_glyph(basic_renderer<T>& renderer, const unicode_t glyph, const ipoint& position)
      -> int
  {
    if (const auto* data = find_glyph(glyph)) {
      const auto& [texture, metrics] = *data;
      const auto outline = mFont.outline();

      /* SDL_ttf handles the y-axis alignment */
      const auto x = position.x() + metrics.min_x - outline;
      const auto y = position.y() - outline;

      renderer.render(texture, ipoint {x, y});

      return x + metrics.advance;
    }
    else {
      return position.x();
    }
  }

  /**
   * Renders a string as a series of glyphs.
   *
   * You can provide null-characters in the string to indicate line breaks. This function will
   * not output rendered text with accurate kerning.
   *
   * \tparam String the type of the string-like object, storing Unicode glyphs.
   *
   * \param renderer the renderer that will be used.
   * \param str the source of the Unicode glyphs.
   * \param position the position of the rendered string.
   */
  template <typename T, typename String>
  void render_text(basic_renderer<T>& renderer, const String& str, ipoint position)
  {
    const auto originalX = position.x();
    const auto lineSkip = mFont.line_skip();

    for (const unicode_t glyph : str) {
      if (glyph == '\n') {
        position.set_x(originalX);
        position.set_y(position.y() + lineSkip);
      }
      else {
        const auto x = render_glyph(renderer, glyph, position);
        position.set_x(x);
      }
    }
  }

  /**
   * Caches a rendered string as a texture.
   *
   * Whilst this function takes any surface as input, it is intended to be used in
   * collaboration with the text rendering functions provided by the font class. As a result,
   * the related functions use "string" in their names, e.g. find_string and has_string.
   *
   * \param renderer the associated renderer.
   * \param surface the surface obtained through one of the `font` rendering functions.
   *
   * \return the identifier assigned to the cached string.
   *
   * \see find_string
   * \see has_string
   * \see get_string
   */
  template <typename T>
  auto store(basic_renderer<T>& renderer, const surface& surface) -> id_type
  {
    const auto id = mNextStringId;
    assert(mStrings.find(id) == mStrings.end());

    mStrings.try_emplace(id, renderer.make_texture(surface));
    ++mNextStringId;

    return id;
  }

  /// Returns the cached string texture for an identifier, if there is one.
  [[nodiscard]] auto find_string(const id_type id) const -> const texture*
  {
    if (const auto iter = mStrings.find(id); iter != mStrings.end()) {
      return &iter->second;
    }
    else {
      return nullptr;
    }
  }

  /// Indicates whether there is a cached string associated with a specific identifier.
  [[nodiscard]] auto has_string(const id_type id) const -> bool
  {
    return find_string(id) != nullptr;
  }

  /// Returns the cached rendered string associated with an identifier.
  [[nodiscard]] auto get_string(const id_type id) const -> const texture&
  {
    if (const auto* ptr = find_string(id)) {
      return *ptr;
    }
    else {
      throw exception {"Invalid font cache string identifier!"};
    }
  }

  /**
   * Renders a glyph to a texture and caches it.
   *
   * This function has no effect if the glyph has already been cached, or if the glyph is not
   * provided by the underlying font.
   *
   * \param renderer the renderer that will be used.
   * \param glyph the glyph that will be cached.
   */
  template <typename T>
  void store_glyph(basic_renderer<T>& renderer, const unicode_t glyph)
  {
    if (has_glyph(glyph) || !mFont.is_glyph_provided(glyph)) {
      return;
    }

    glyph_data data {make_glyph_texture(renderer, glyph), mFont.get_metrics(glyph).value()};
    mGlyphs.try_emplace(glyph, std::move(data));
  }

  /**
   * Renders a range of glyphs to individual textures and caches them.
   *
   * The glyphs that will be cached are in the range [begin, end).
   *
   * \param renderer the renderer that will be used.
   * \param begin the first glyph that will be cached.
   * \param end the range terminator (will not be cached).
   *
   * \see https://unicode-table.com/en/blocks/
   */
  template <typename T>
  void store_glyphs(basic_renderer<T>& renderer, const unicode_t begin, const unicode_t end)
  {
    for (auto glyph = begin; glyph < end; ++glyph) {
      store_glyph(renderer, glyph);
    }
  }

  /// Stores the glyphs provided in the basic latin character range.
  template <typename T>
  void store_basic_latin_glyphs(basic_renderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/basic-latin/ */
    store_glyphs(renderer, 0x20, 0x7F);
  }

  /// Stores the glyphs provided in the Latin-1 supplement character range.
  template <typename T>
  void store_latin1_supplement_glyphs(basic_renderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/latin-1-supplement/ */
    store_glyphs(renderer, 0xA0, 0xFF + 0x1);
  }

  /// Stores the glyphs provided in the Latin-1 character range.
  template <typename T>
  void store_latin1_glyphs(basic_renderer<T>& renderer)
  {
    store_basic_latin_glyphs(renderer);
    store_latin1_supplement_glyphs(renderer);
  }

  /// Returns the cached information associated with a glyph, if there is any.
  [[nodiscard]] auto find_glyph(const unicode_t glyph) const -> const glyph_data*
  {
    if (const auto it = mGlyphs.find(glyph); it != mGlyphs.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }

  /// Indicates whether a glyph has been cached.
  [[nodiscard]] auto has_glyph(const unicode_t glyph) const noexcept -> bool
  {
    return find_glyph(glyph) != nullptr;
  }

  /// Returns the previously cached information associated with a glyph.
  [[nodiscard]] auto get_glyph(const unicode_t glyph) const -> const glyph_data&
  {
    if (const auto* ptr = find_glyph(glyph)) {
      return *ptr;
    }
    else {
      throw exception {"Invalid font cache glyph!"};
    }
  }

  /// Returns the underlying font instance.
  [[nodiscard]] auto get_font() noexcept -> font& { return mFont; }
  [[nodiscard]] auto get_font() const noexcept -> const font& { return mFont; }

 private:
  font mFont;
  std::unordered_map<unicode_t, glyph_data> mGlyphs;
  std::unordered_map<id_type, texture> mStrings;
  id_type mNextStringId {1};

  template <typename T>
  [[nodiscard]] auto make_glyph_texture(basic_renderer<T>& renderer, const unicode_t glyph)
      -> texture
  {
    return renderer.make_texture(mFont.render_blended_glyph(glyph, renderer.get_color()));
  }
};

[[nodiscard]] inline auto to_string(const font_cache& cache) -> std::string
{
  const auto& font = cache.get_font();

  const auto* name = str_or_na(font.family_name());
  const auto size = font.size();

#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font_cache(font: '{}', size: {})", name, size);
#else
  using namespace std::string_literals;
  return "font_cache(font: '"s + name + "', size: " + std::to_string(size) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const font_cache& cache) -> std::ostream&
{
  return stream << to_string(cache);
}

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_FONT_CACHE_HPP_
