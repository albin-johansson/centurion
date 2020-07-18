/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file font_cache.hpp
 *
 * @brief Provides the `font_cache` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_FONT_CACHE_HEADER
#define CENTURION_FONT_CACHE_HEADER

#include <SDL_ttf.h>

#include <algorithm>
#include <array>
#include <hashed_string.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "colors.hpp"
#include "font.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "surface.hpp"
#include "unicode_string.hpp"

namespace centurion::experimental {

/**
 * @class font_cache
 *
 * @ingroup graphics
 *
 * @brief Provides an efficient font rendering API.
 *
 * @details This class provides two different optimizations.
 *
 * First of, this class will, if told, cache glyph textures that can be used
 * to render strings by simply looking up the individual glyphs and rendering
 * existing textures. It should be noted that the glyph-based rendering will
 * not feature accurate kerning. However, this might not be noticeable and/or
 * worth the performance boost. This type of rendering is *very* efficient for
 * rendering pieces of text that frequently changes, since other approaches
 * would require dynamic allocation and de-allocation for every new rendered
 * string.
 *
 * Secondly, it's also possible to tell instances of this class to cache full
 * strings and associate them with a user-provided identifier. Using this
 * approach, the strings will be rendered using accurate kerning. The problem
 * is, as you probably know, is that it's often hard to know what exact
 * strings you will render at compile-time. Use this option if you know that
 * you're going to render some specific string a lot.
 *
 * @since 5.0.0
 *
 * @headerfile font_cache.hpp
 */
class font_cache final {
 public:
  /**
   * @brief Creates an empty font cache instance.
   *
   * @note You have to explicitly state what glyphs that you want to be cached.
   *
   * @param font the font that will be used.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit font_cache(font&& font) noexcept;

  /**
   * @brief Creates an empty font cache, and creates the associated font
   * in-place.
   *
   * @tparam Args the types of the arguments forwarded to the font constructor.
   *
   * @param args the arguments that will be forwarded to the font constructor.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  explicit font_cache(Args&&... args) : m_font{std::forward<Args>(args)...}
  {}

  CENTURION_QUERY
  static auto unique(font&& font) -> std::unique_ptr<font_cache>;

  /**
   * @name Text rendering
   * Methods for rendering glyphs and strings using cached textures.
   */
  /**@{*/

  /**
   * @brief Renders a glyph at the specified position.
   *
   * @details Invoking this function with a glyph that hasn't been cached
   * will cause an exception to be thrown.
   *
   * @pre the specified glyph **must** have been cached.
   *
   * @tparam T the font key type that the renderer uses.
   *
   * @param renderer the renderer that will be used.
   * @param glyph the glyph, in unicode, that will be rendered.
   * @param position the position of the rendered glyph.
   *
   * @return the x-coordinate of the next glyph to be rendered after the
   * current glyph.
   *
   * @since 5.0.0
   */
  CENTURION_API
  auto render_glyph(renderer_ptr renderer,
                    unicode glyph,
                    const point_i& position) -> int;

  /**
   * @brief Renders a string.
   *
   * @details This method will not apply any clever conversions on the
   * supplied string. The string is literally iterated,
   * character-by-character, and each character is rendered using
   * the `render_glyph`. In other words, be sure that each `char` in your
   * strings represent a single glyph.
   *
   * @pre Every character in the string must correspond to a valid Unicode
   * glyph **and** must have been previously cached.
   *
   * @note This method is sensitive to newline-characters, and will render
   * strings that contain such characters appropriately.
   *
   * @param renderer the renderer that will be used.
   * @param str the string that will be rendered.
   * @param position the position of the rendered text.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void render(renderer_ptr renderer, std::string_view str, point_i position);

  /**
   * @brief Renders a Unicode string.
   *
   * @details This method will try to use previously cached glyphs to render
   * the supplied string.
   *
   * @param renderer the renderer that will be used.
   * @param str the Unicode string that will be rendered.
   * @param position the position of the rendered text.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void render_unicode(renderer_ptr renderer,
                      const unicode_string& str,
                      point_i position);

  /**@}*/  // end of text rendering

  /**
   * @name String caching
   * Methods for caching strings encoded in UTF-8, Latin-1 or Unicode.
   */
  /**@{*/

  /**
   * @brief Caches the supplied Unicode string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_unicode`.
   *
   * @note This method respects the kerning of the font.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Unicode string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_unicode(renderer_ptr renderer,
                             entt::id_type id,
                             const unicode_string& str);

  /**
   * @brief Caches the supplied Latin-1 string as a texture.
   *
   * @details The texture is created using
   * `renderer_base::render_blended_latin1`.
   *
   * @note This method respects the kerning of the font.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the Latin-1 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_latin1(renderer_ptr renderer,
                            entt::id_type id,
                            std::string_view str);

  /**
   * @brief Caches the supplied UTF-8 string as a texture.
   *
   * @details The texture is created using `renderer_base::render_blended_utf8`.
   *
   * @note This method respects the kerning of the font.
   *
   * @param renderer the renderer that will be used.
   * @param id the key that will be associated with the texture.
   * @param str the UTF-8 string that will be cached.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_blended_utf8(renderer_ptr renderer,
                          entt::id_type id,
                          std::string_view str);

  /**@}*/  // end of string caching

  /**
   * @name Glyph caching
   * Methods for caching Unicode glyph textures.
   */
  /**@{*/

  CENTURION_API
  void add_glyph(renderer& renderer, unicode glyph);

  /**
   * @brief Caches the glyphs in the specified range.
   *
   * @details The range is interpreted as [min, max), i.e. the the `min`
   * value is included, and `max` is excluded.
   *
   * @remark For an overview of the various Unicode blocks, see <a
   * href="https://unicode-table.com/en/blocks/">this</a>.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   * @param begin the first glyph that will be included.
   * @param end the "end" glyph in the range, will not be included.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_range(renderer& renderer, unicode begin, unicode end);

  /**
   * @brief Attempts to cache all printable basic latin characters.
   *
   * @details The basic latin set provides the most common characters, such as
   * upper- and lower-case latin letters, numbers and symbols. This method
   * might throw if something goes wrong when creating the textures.
   *
   * @param renderer the renderer that will be used to create the glyph
   * textures.
   *
   * @since 5.0.0
   */
  CENTURION_API
  void cache_basic_latin(renderer& renderer);

  CENTURION_API
  void cache_latin1_supplement(renderer& renderer);

  CENTURION_API
  void cache_latin1(renderer& renderer);

  /**@}*/  // end of glyph caching

  /**
   * @brief Indicates whether or not the specified glyph has been cached.
   *
   * @param glyph the glyph to check.
   *
   * @return `true` if the specified glyph has been cached; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto has(unicode glyph) const noexcept -> bool
  {
    return m_glyphs.count(glyph);
  }

  /**
   * @brief Returns the cached texture associated with the specified glyph.
   *
   * @pre `glyph` **must** have been previously cached.
   *
   * @param glyph the desired glyph to lookup the texture for.
   *
   * @return the cached texture associated with the glyph.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto at(unicode glyph) const -> const texture&
  {
    return m_glyphs.at(glyph);
  }

  /**
   * @brief Returns a pointer to the texture associated with the specified key.
   *
   * @note The returned pointer is not suitable for storing for longer than
   * absolutely necessary, as it might get invalidated by modifications of
   * the font cache.
   *
   * @param id the key of the desired texture.
   *
   * @return a pointer to the texture associated with the specified key;
   * `nullptr` if no texture is found.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto try_cached(entt::id_type id) const noexcept -> const texture*;

  /**
   * @brief Returns the cached texture associated with the specified ID.
   *
   * @pre `id` **must** be associated with a cached string texture.
   *
   * @param id the key of the cached texture to obtain.
   *
   * @return the cached texture associated with the key.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto cached(entt::id_type id) const -> const texture&
  {
    return m_strings.at(id);
  }

  [[nodiscard]] auto metrics(unicode glyph) -> glyph_metrics&
  {
    return m_metrics.at(glyph);
  }

  [[nodiscard]] auto metrics(unicode glyph) const -> const glyph_metrics&
  {
    return m_metrics.at(glyph);
  }

  [[nodiscard]] auto get() noexcept -> font& { return m_font; }

  [[nodiscard]] auto get() const noexcept -> const font& { return m_font; }

 private:
  font m_font;

  struct glyph_data {
    texture cached;
    glyph_metrics metrics;
  };

  std::unordered_map<unicode, texture> m_glyphs;
  std::unordered_map<unicode, glyph_metrics> m_metrics;

  std::unordered_map<entt::id_type, texture> m_strings;

  [[nodiscard]] auto create_glyph_texture(renderer& renderer, unicode glyph)
      -> texture;
};

}  // namespace centurion::experimental

#ifdef CENTURION_HEADER_ONLY
#include "font_cache.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_FONT_CACHE_HEADER