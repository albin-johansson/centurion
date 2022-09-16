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

#ifndef CENTURION_FONT_HPP_
#define CENTURION_FONT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL.h>
#include <SDL_ttf.h>

#include <cassert>        // assert
#include <cstddef>        // size_t
#include <cstring>        // strcmp
#include <filesystem>     // path
#include <memory>         // unique_ptr
#include <optional>       // optional
#include <ostream>        // ostream
#include <string>         // string, to_string
#include <string_view>    // string_view
#include <unordered_map>  // unordered_map
#include <utility>        // move, forward

#include "color.hpp"
#include "common.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "memory.hpp"
#include "render.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode.hpp"
#include "version.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

[[nodiscard]] inline auto ttf_free_type_version() noexcept -> version
{
  version ver;
  TTF_GetFreeTypeVersion(&ver.major, &ver.minor, &ver.patch);
  return ver;
}

[[nodiscard]] inline auto ttf_harf_buzz_version() noexcept -> version
{
  version ver;
  TTF_GetHarfBuzzVersion(&ver.major, &ver.minor, &ver.patch);
  return ver;
}

inline auto ttf_set_script(const int script) noexcept -> result
{
  return TTF_SetScript(script) == 0;
}

inline auto ttf_set_direction(const int direction) noexcept -> result
{
  return TTF_SetDirection(direction) == 0;
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

enum class font_hint
{
  normal = TTF_HINTING_NORMAL,
  light = TTF_HINTING_LIGHT,

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)
  light_subpixel = TTF_HINTING_LIGHT_SUBPIXEL,
#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  mono = TTF_HINTING_MONO,
  none = TTF_HINTING_NONE
};

[[nodiscard]] constexpr auto to_string(const font_hint hint) -> std::string_view
{
  switch (hint) {
    case font_hint::normal:
      return "normal";

    case font_hint::light:
      return "light";

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

    case font_hint::light_subpixel:
      return "light_subpixel";

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

    case font_hint::mono:
      return "mono";

    case font_hint::none:
      return "none";

    default:
      throw exception{"Did not recognize font hint!"};
  }
}

inline auto operator<<(std::ostream& stream, const font_hint hint) -> std::ostream&
{
  return stream << to_string(hint);
}

struct glyph_metrics final
{
  int min_x{};    ///< The minimum X-offset.
  int min_y{};    ///< The minimum Y-offset.
  int max_x{};    ///< The maximum X-offset.
  int max_y{};    ///< The maximum Y-offset.
  int advance{};  ///< The advance offset.
};

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

struct font_dpi final
{
  uint horizontal{};
  uint vertical{};
};

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

enum class wrap_alignment
{
  left = TTF_WRAPPED_ALIGN_LEFT,
  center = TTF_WRAPPED_ALIGN_CENTER,
  right = TTF_WRAPPED_ALIGN_RIGHT,
};

[[nodiscard]] inline auto to_string(const wrap_alignment align) -> std::string_view
{
  switch (align) {
    case wrap_alignment::left:
      return "left";

    case wrap_alignment::center:
      return "center";

    case wrap_alignment::right:
      return "right";

    default:
      throw exception{"Invalid alignment!"};
  }
}

inline auto operator<<(std::ostream& stream, const wrap_alignment align) -> std::ostream&
{
  return stream << to_string(align);
}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)

/**
 * Represents a TrueType font.
 *
 * This class provides information about TrueType fonts, and can also be used for rendering
 * glyphs and strings. There are also various utility classes related to dealing with fonts, in
 * order to easily deal with fonts of different sizes and more efficient text rendering.
 *
 * \see font_cache
 * \see font_bundle
 */
class font final
{
 public:
  font(const char* file, const int size) : mSize{size}
  {
    assert(file);

    if (mSize <= 0) {
      throw exception{"Bad font size!"};
    }

    mFont.reset(TTF_OpenFont(file, mSize));
    if (!mFont) {
      throw ttf_error{};
    }
  }

  font(const std::string& file, const int size) : font{file.c_str(), size} {}

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  font(const char* file, const int size, const font_dpi& dpi) : mSize{size}
  {
    assert(file);

    if (mSize <= 0) {
      throw exception{"Bad font size!"};
    }

    mFont.reset(TTF_OpenFontDPI(file, mSize, dpi.horizontal, dpi.vertical));
    if (!mFont) {
      throw ttf_error{};
    }
  }

  font(const std::string& file, const int size, const font_dpi& dpi)
      : font{file.c_str(), size, dpi}
  {}

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  auto set_size(const int size) noexcept -> result
  {
    if (size <= 0) {
      return failure;
    }

    mSize = size;

    return TTF_SetFontSize(mFont.get(), mSize) >= 0;
  }

  auto set_size(const int size, const font_dpi& dpi) noexcept -> result
  {
    if (size <= 0) {
      return failure;
    }

    mSize = size;

    return TTF_SetFontSizeDPI(mFont.get(), size, dpi.horizontal, dpi.vertical) == 0;
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  void reset_style() noexcept { TTF_SetFontStyle(mFont.get(), TTF_STYLE_NORMAL); }

  void set_bold(const bool bold) noexcept
  {
    if (bold) {
      add_style(TTF_STYLE_BOLD);
    }
    else {
      remove_style(TTF_STYLE_BOLD);
    }
  }

  void set_italic(const bool italic) noexcept
  {
    if (italic) {
      add_style(TTF_STYLE_ITALIC);
    }
    else {
      remove_style(TTF_STYLE_ITALIC);
    }
  }

  void set_underlined(const bool underlined) noexcept
  {
    if (underlined) {
      add_style(TTF_STYLE_UNDERLINE);
    }
    else {
      remove_style(TTF_STYLE_UNDERLINE);
    }
  }

  void set_strikethrough(const bool strikethrough) noexcept
  {
    if (strikethrough) {
      add_style(TTF_STYLE_STRIKETHROUGH);
    }
    else {
      remove_style(TTF_STYLE_STRIKETHROUGH);
    }
  }

  void set_kerning(const bool kerning) noexcept
  {
    TTF_SetFontKerning(mFont.get(), kerning ? 1 : 0);
  }

  void set_outline(const int outline) noexcept
  {
    TTF_SetFontOutline(mFont.get(), detail::max(outline, 0));
  }

  void set_hinting(const font_hint hint) noexcept
  {
    TTF_SetFontHinting(mFont.get(), to_underlying(hint));
  }

  [[nodiscard]] auto is_bold() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_BOLD;
  }

  [[nodiscard]] auto is_italic() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_ITALIC;
  }

  [[nodiscard]] auto is_underlined() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_UNDERLINE;
  }

  [[nodiscard]] auto is_strikethrough() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_STRIKETHROUGH;
  }

  [[nodiscard]] auto is_outlined() const noexcept -> bool { return outline() != 0; }

  [[nodiscard]] auto has_kerning() const noexcept -> bool
  {
    return TTF_GetFontKerning(mFont.get());
  }

  [[nodiscard]] auto outline() const noexcept -> int
  {
    return TTF_GetFontOutline(mFont.get());
  }

  [[nodiscard]] auto hinting() const noexcept -> font_hint
  {
    return static_cast<font_hint>(TTF_GetFontHinting(mFont.get()));
  }

  [[nodiscard]] auto is_fixed_width() const noexcept -> bool
  {
    return TTF_FontFaceIsFixedWidth(mFont.get());
  }

  [[nodiscard]] auto height() const noexcept -> int { return TTF_FontHeight(mFont.get()); }

  [[nodiscard]] auto descent() const noexcept -> int { return TTF_FontDescent(mFont.get()); }

  [[nodiscard]] auto ascent() const noexcept -> int { return TTF_FontAscent(mFont.get()); }

  [[nodiscard]] auto line_skip() const noexcept -> int
  {
    return TTF_FontLineSkip(mFont.get());
  }

  [[nodiscard]] auto face_count() const noexcept -> int
  {
    return static_cast<int>(TTF_FontFaces(mFont.get()));
  }

  [[nodiscard]] auto family_name() const noexcept -> const char*
  {
    return TTF_FontFaceFamilyName(mFont.get());
  }

  [[nodiscard]] auto style_name() const noexcept -> const char*
  {
    return TTF_FontFaceStyleName(mFont.get());
  }

  [[nodiscard]] auto size() const noexcept -> int { return mSize; }

  [[nodiscard]] auto get_kerning(const unicode_t previous,
                                 const unicode_t current) const noexcept -> int
  {
    return TTF_GetFontKerningSizeGlyphs(mFont.get(), previous, current);
  }

  [[nodiscard]] auto is_glyph_provided(const unicode_t glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided(mFont.get(), glyph);
  }

  [[nodiscard]] auto get_metrics(const unicode_t glyph) const noexcept -> maybe<glyph_metrics>
  {
    glyph_metrics metrics;
    if (TTF_GlyphMetrics(mFont.get(),
                         glyph,
                         &metrics.min_x,
                         &metrics.max_x,
                         &metrics.min_y,
                         &metrics.max_y,
                         &metrics.advance) != -1) {
      return metrics;
    }
    else {
      return nothing;
    }
  }

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto get_kerning_w(const unicode32_t previous,
                                   const unicode32_t current) const noexcept -> int
  {
    return TTF_GetFontKerningSizeGlyphs32(mFont.get(), previous, current);
  }

  [[nodiscard]] auto is_glyph_provided_w(const unicode32_t glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided32(mFont.get(), glyph);
  }

  [[nodiscard]] auto get_metrics_w(const unicode32_t glyph) const noexcept
      -> maybe<glyph_metrics>
  {
    glyph_metrics metrics;
    if (TTF_GlyphMetrics32(mFont.get(),
                           glyph,
                           &metrics.min_x,
                           &metrics.max_x,
                           &metrics.min_y,
                           &metrics.max_y,
                           &metrics.advance) != -1) {
      return metrics;
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  auto set_sdf_enabled(const bool enable) noexcept -> result
  {
    return TTF_SetFontSDF(mFont.get(), enable ? SDL_TRUE : SDL_FALSE) == 0;
  }

  [[nodiscard]] auto sdf_enabled() const noexcept -> bool
  {
    return TTF_GetFontSDF(mFont.get()) == SDL_TRUE;
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto render_solid_glyph(const unicode_t glyph, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderGlyph_Solid(get(), glyph, fg.get())};
  }

  [[nodiscard]] auto render_shaded_glyph(const unicode_t glyph,
                                         const color& fg,
                                         const color& bg) const -> surface
  {
    return surface{TTF_RenderGlyph_Shaded(get(), glyph, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_blended_glyph(const unicode_t glyph, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderGlyph_Blended(get(), glyph, fg.get())};
  }

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto render_solid_glyph_w(const unicode32_t glyph, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderGlyph32_Solid(get(), glyph, fg.get())};
  }

  [[nodiscard]] auto render_shaded_glyph_w(const unicode32_t glyph,
                                           const color& fg,
                                           const color& bg) const -> surface
  {
    return surface{TTF_RenderGlyph32_Shaded(get(), glyph, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_blended_glyph_w(const unicode32_t glyph, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderGlyph32_Blended(get(), glyph, fg.get())};
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

  void set_wrap_align(const wrap_alignment align) noexcept
  {
    TTF_SetFontWrappedAlign(get(), to_underlying(align));
  }

  [[nodiscard]] auto wrap_align() const noexcept -> wrap_alignment
  {
    return static_cast<wrap_alignment>(TTF_GetFontWrappedAlign(get()));
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)

  [[nodiscard]] auto calc_size(const char* str) const noexcept -> maybe<iarea>
  {
    assert(str);

    iarea size{};
    if (TTF_SizeText(mFont.get(), str, &size.width, &size.height) != -1) {
      return size;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto calc_size(const std::string& str) const noexcept -> maybe<iarea>
  {
    return calc_size(str.c_str());
  }

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  struct measure_result final
  {
    int count{};   ///< The amount of characters that can be rendered
    int extent{};  ///< The width of the characters that can be rendered
  };

  [[nodiscard]] auto measure_text(const char* str, const int width) const noexcept
      -> maybe<measure_result>
  {
    measure_result result;
    if (TTF_MeasureText(mFont.get(), str, width, &result.extent, &result.count) < 0) {
      return nothing;
    }
    else {
      return result;
    }
  }

  [[nodiscard]] auto measure_utf8(const char* str, const int width) const noexcept
      -> maybe<measure_result>
  {
    measure_result result;
    if (TTF_MeasureUTF8(mFont.get(), str, width, &result.extent, &result.count) < 0) {
      return nothing;
    }
    else {
      return result;
    }
  }

  [[nodiscard]] auto measure_unicode(const unicode_string& str, const int width) const noexcept
      -> maybe<measure_result>
  {
    measure_result result;
    if (TTF_MeasureUNICODE(mFont.get(), str.data(), width, &result.extent, &result.count) <
        0) {
      return nothing;
    }
    else {
      return result;
    }
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto render_blended(const char* str, const color& fg) const -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Blended(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_blended_utf8(const char* str, const color& fg) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Blended(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_blended_uni(const unicode_string& str, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderUNICODE_Blended(get(), str.data(), fg.get())};
  }

  [[nodiscard]] auto render_solid(const char* str, const color& fg) const -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Solid(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_solid_utf8(const char* str, const color& fg) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Solid(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_solid_uni(const unicode_string& str, const color& fg) const
      -> surface
  {
    return surface{TTF_RenderUNICODE_Solid(get(), str.data(), fg.get())};
  }

  [[nodiscard]] auto render_shaded(const char* str, const color& fg, const color& bg) const
      -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_shaded_utf8(const char* str,
                                        const color& fg,
                                        const color& bg) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_shaded_uni(const unicode_string& str,
                                       const color& fg,
                                       const color& bg) const -> surface
  {
    return surface{TTF_RenderUNICODE_Shaded(get(), str.data(), fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_blended_wrapped(const char* str,
                                            const color& fg,
                                            const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Blended_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_blended_wrapped_utf8(const char* str,
                                                 const color& fg,
                                                 const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Blended_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_blended_wrapped_uni(const unicode_string& str,
                                                const color& fg,
                                                const uint32 wrap) const -> surface
  {
    return surface{TTF_RenderUNICODE_Blended_Wrapped(get(), str.data(), fg.get(), wrap)};
  }

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto render_solid_wrapped(const char* str,
                                          const color& fg,
                                          const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Solid_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_solid_wrapped_utf8(const char* str,
                                               const color& fg,
                                               const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Solid_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_solid_wrapped_uni(const unicode_string& str,
                                              const color& fg,
                                              const uint32 wrap) const -> surface
  {
    return surface{TTF_RenderUNICODE_Solid_Wrapped(get(), str.data(), fg.get(), wrap)};
  }

  [[nodiscard]] auto render_shaded_wrapped(const char* str,
                                           const color& fg,
                                           const color& bg,
                                           const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderText_Shaded_Wrapped(get(), str, fg.get(), bg.get(), wrap)};
  }

  [[nodiscard]] auto render_shaded_wrapped_utf8(const char* str,
                                                const color& fg,
                                                const color& bg,
                                                const uint32 wrap) const -> surface
  {
    assert(str);
    return surface{TTF_RenderUTF8_Shaded_Wrapped(get(), str, fg.get(), bg.get(), wrap)};
  }

  [[nodiscard]] auto render_shaded_wrapped_uni(const unicode_string& str,
                                               const color& fg,
                                               const color& bg,
                                               const uint32 wrap) const -> surface
  {
    return surface{
        TTF_RenderUNICODE_Shaded_Wrapped(get(), str.data(), fg.get(), bg.get(), wrap)};
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto get() const noexcept -> TTF_Font* { return mFont.get(); }

 private:
  managed_ptr<TTF_Font> mFont;
  int mSize{};

  void add_style(const int mask) noexcept
  {
    const auto style = TTF_GetFontStyle(mFont.get());
    TTF_SetFontStyle(mFont.get(), style | mask);
  }

  void remove_style(const int mask) noexcept
  {
    const auto style = TTF_GetFontStyle(mFont.get());
    TTF_SetFontStyle(mFont.get(), style & ~mask);
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  font() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

[[nodiscard]] inline auto to_string(const font& font) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font(data: {}, name: '{}', size: {})",
                     detail::address_of(font.get()),
                     str_or_na(font.family_name()),
                     font.size());
#else
  return "font(data: " + detail::address_of(font.get()) + ", name: '" +
         str_or_na(font.family_name()) + "', size: " + std::to_string(font.size()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const font& font) -> std::ostream&
{
  return stream << to_string(font);
}

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
class font_cache final
{
 public:
  using id_type = usize;
  using size_type = usize;

  struct glyph_data final
  {
    texture glyph;          ///< The cached texture of the glyph.
    glyph_metrics metrics;  ///< The metrics associate with the glyph.
  };

  /**
   * Creates a font cache based on the font at the specified file path.
   *
   * \param file the file path of the font.
   * \param size the size of the font.
   */
  font_cache(const char* file, const int size) : mFont{file, size} {}

  font_cache(const std::string& file, const int size) : mFont{file, size} {}

  explicit font_cache(font&& font) noexcept : mFont{std::move(font)} {}

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

      renderer.render(texture, ipoint{x, y});

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
      throw exception{"Invalid font cache string identifier!"};
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

    glyph_data data{make_glyph_texture(renderer, glyph), mFont.get_metrics(glyph).value()};
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
      throw exception{"Invalid font cache glyph!"};
    }
  }

  /// Returns the underlying font instance.
  [[nodiscard]] auto get_font() noexcept -> font& { return mFont; }
  [[nodiscard]] auto get_font() const noexcept -> const font& { return mFont; }

 private:
  font mFont;
  std::unordered_map<unicode_t, glyph_data> mGlyphs;
  std::unordered_map<id_type, texture> mStrings;
  id_type mNextStringId{1};

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

namespace experimental {

/**
 * Utility for handling fonts of various sizes.
 *
 * The main motivation behind this utility is the fact that it is common to load the same font
 * family in several different sizes. This class provides a simple API for efficiently managing
 * such pools of fonts.
 *
 * This class works by organizing different pools of fonts based on their file paths. Which
 * means that the same font, loaded from different file paths, will be put into different
 * pools.
 *
 * Despite the name, this class actually stores font_cache instances. However, you can still
 * easily extract the underlying font instances if you do not need the extra features provided
 * by the `font_cache` class.
 *
 * \see font
 * \see font_cache
 */
class font_bundle final
{
 public:
  using id_type = usize;
  using size_type = usize;

  /**
   * Loads a font in a specific size.
   *
   * It is safe to load a font that has already been previously loaded. Furthermore, this
   * function has no effect if there is already a font of the specified size stored in the pool
   * for the font family.
   *
   * \param path the file path of the font.
   * \param size the size of the font.
   *
   * \return the identifier associated with the font.
   */
  auto load_font(const char* path, const int size) -> id_type
  {
    assert(path);
    if (const auto id = get_id(path)) {
      mPools[*id].caches.try_emplace(size, font{path, size});
      return *id;
    }
    else {
      const auto newId = mNextFontId;

      auto& pack = mPools[newId];
      pack.path = path;
      pack.caches.try_emplace(size, font{path, size});

      ++mNextFontId;

      return newId;
    }
  }

  /// Indicates whether there is a font pool associated with an ID.
  [[nodiscard]] auto contains(const id_type id) const -> bool
  {
    return mPools.find(id) != mPools.end();
  }

  /// Indicates whether there is a pool for the specified file path.
  [[nodiscard]] auto contains(const std::string_view path) const -> bool
  {
    return get_id(path).has_value();
  }

  /// Indicates whether there is a font of a specific size in a pool.
  [[nodiscard]] auto contains(const id_type id, const int size) const -> bool
  {
    if (const auto pack = mPools.find(id); pack != mPools.end()) {
      return pack->second.caches.find(size) != pack->second.caches.end();
    }
    else {
      return false;
    }
  }

  /// Returns a previously loaded font of a particular size from a pool.
  [[nodiscard]] auto at(const id_type id, const int size) -> font_cache&
  {
    if (const auto pool = mPools.find(id); pool != mPools.end()) {
      auto& caches = pool->second.caches;
      if (const auto cache = caches.find(size); cache != caches.end()) {
        return cache->second;
      }
      else {
        throw exception{"No loaded font of the requested size!"};
      }
    }
    else {
      throw exception{"Invalid font pool identifier!"};
    }
  }

  [[nodiscard]] auto at(const id_type id, const int size) const -> const font_cache&
  {
    return mPools.at(id).caches.at(size);
  }

  /**
   * Returns a previously loaded font of a particular size from a pool.
   *
   * This function is provided as a shorthand, and simply calls at() and extracts the font
   * from the found font cache.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font.
   */
  [[nodiscard]] auto get_font(const id_type id, const int size) -> font&
  {
    return at(id, size).get_font();
  }

  [[nodiscard]] auto get_font(const id_type id, const int size) const -> const font&
  {
    return at(id, size).get_font();
  }

  /// Returns the amount of fonts that have been loaded (including different sizes).
  [[nodiscard]] auto font_count() const noexcept -> size_type
  {
    size_type count = 0;

    for (const auto& [id, pack] : mPools) {
      count += pack.caches.size();
    }

    return count;
  }

  /// Returns the amount of loaded font pools, i.e. font faces irrespective of sizes.
  [[nodiscard]] auto pool_count() const -> size_type { return mPools.size(); }

 private:
  struct font_pool final
  {
    std::string path;
    std::unordered_map<int, font_cache> caches;  ///< Size -> Cache
  };

  std::unordered_map<id_type, font_pool> mPools;
  id_type mNextFontId{1};

  [[nodiscard]] auto get_id(const std::string_view path) const -> maybe<id_type>
  {
    for (const auto& [id, pack] : mPools) {
      if (!pack.caches.empty()) {
        if (pack.path == path) {
          return id;
        }
      }
    }

    return nothing;
  }
};

[[nodiscard]] inline auto to_string(const font_bundle& bundle) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font_bundle(#pools: {}, #fonts: {})",
                     bundle.pool_count(),
                     bundle.font_count());
#else
  return "font_bundle(#pools: " + std::to_string(bundle.pool_count()) +
         ", #fonts: " + std::to_string(bundle.font_count()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const font_bundle& bundle) -> std::ostream&
{
  return stream << to_string(bundle);
}

}  // namespace experimental
}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONT_HPP_