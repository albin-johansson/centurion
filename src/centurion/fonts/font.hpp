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

#ifndef CENTURION_FONTS_FONT_HPP_
#define CENTURION_FONTS_FONT_HPP_

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string, to_string

#include "../common.hpp"
#include "../detail/stdlib.hpp"
#include "../features.hpp"
#include "../surface.hpp"
#include "../unicode.hpp"
#include "../color.hpp"
#include "../version.hpp"
#include "font_direction.hpp"
#include "font_hint.hpp"
#include "wrap_alignment.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

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

    return TTF_SetFontSize(get(), mSize) >= 0;
  }

  auto set_size(const int size, const font_dpi& dpi) noexcept -> result
  {
    if (size <= 0) {
      return failure;
    }

    mSize = size;

    return TTF_SetFontSizeDPI(get(), size, dpi.horizontal, dpi.vertical) == 0;
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

  void reset_style() noexcept { TTF_SetFontStyle(get(), TTF_STYLE_NORMAL); }

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

  void set_kerning(const bool kerning) noexcept { TTF_SetFontKerning(get(), kerning ? 1 : 0); }

  void set_outline(const int outline) noexcept
  {
    TTF_SetFontOutline(get(), detail::max(outline, 0));
  }

  void set_hinting(const font_hint hint) noexcept
  {
    TTF_SetFontHinting(get(), to_underlying(hint));
  }

#if SDL_TTF_VERSION_ATLEAST(2, 20, 0)

  auto set_direction(const font_direction dir) -> result
  {
    return TTF_SetFontDirection(get(), static_cast<TTF_Direction>(dir)) == 0;
  }

  auto set_script(const char* script) -> result
  {
    return TTF_SetFontScriptName(get(), script) == 0;
  }

#endif  // SDL_TTF_VERSION_ATLEAST(2, 20, 0)

  [[nodiscard]] auto is_bold() const noexcept -> bool
  {
    return TTF_GetFontStyle(get()) & TTF_STYLE_BOLD;
  }

  [[nodiscard]] auto is_italic() const noexcept -> bool
  {
    return TTF_GetFontStyle(get()) & TTF_STYLE_ITALIC;
  }

  [[nodiscard]] auto is_underlined() const noexcept -> bool
  {
    return TTF_GetFontStyle(get()) & TTF_STYLE_UNDERLINE;
  }

  [[nodiscard]] auto is_strikethrough() const noexcept -> bool
  {
    return TTF_GetFontStyle(get()) & TTF_STYLE_STRIKETHROUGH;
  }

  [[nodiscard]] auto is_outlined() const noexcept -> bool { return outline() != 0; }

  [[nodiscard]] auto has_kerning() const noexcept -> bool { return TTF_GetFontKerning(get()); }

  [[nodiscard]] auto outline() const noexcept -> int { return TTF_GetFontOutline(get()); }

  [[nodiscard]] auto hinting() const noexcept -> font_hint
  {
    return static_cast<font_hint>(TTF_GetFontHinting(get()));
  }

  [[nodiscard]] auto is_fixed_width() const noexcept -> bool
  {
    return TTF_FontFaceIsFixedWidth(get());
  }

  [[nodiscard]] auto height() const noexcept -> int { return TTF_FontHeight(get()); }

  [[nodiscard]] auto descent() const noexcept -> int { return TTF_FontDescent(get()); }

  [[nodiscard]] auto ascent() const noexcept -> int { return TTF_FontAscent(get()); }

  [[nodiscard]] auto line_skip() const noexcept -> int { return TTF_FontLineSkip(get()); }

  [[nodiscard]] auto face_count() const noexcept -> int
  {
    return static_cast<int>(TTF_FontFaces(get()));
  }

  [[nodiscard]] auto family_name() const noexcept -> const char*
  {
    return TTF_FontFaceFamilyName(get());
  }

  [[nodiscard]] auto style_name() const noexcept -> const char*
  {
    return TTF_FontFaceStyleName(get());
  }

  [[nodiscard]] auto size() const noexcept -> int { return mSize; }

  [[nodiscard]] auto get_kerning(const unicode_t previous,
                                 const unicode_t current) const noexcept -> int
  {
    return TTF_GetFontKerningSizeGlyphs(get(), previous, current);
  }

  [[nodiscard]] auto is_glyph_provided(const unicode_t glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided(get(), glyph);
  }

  [[nodiscard]] auto get_metrics(const unicode_t glyph) const noexcept -> maybe<glyph_metrics>
  {
    glyph_metrics metrics;
    if (TTF_GlyphMetrics(get(),
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
    return TTF_GetFontKerningSizeGlyphs32(get(), previous, current);
  }

  [[nodiscard]] auto is_glyph_provided_w(const unicode32_t glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided32(get(), glyph);
  }

  [[nodiscard]] auto get_metrics_w(const unicode32_t glyph) const noexcept
      -> maybe<glyph_metrics>
  {
    glyph_metrics metrics;
    if (TTF_GlyphMetrics32(get(),
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
    return TTF_SetFontSDF(get(), enable ? SDL_TRUE : SDL_FALSE) == 0;
  }

  [[nodiscard]] auto sdf_enabled() const noexcept -> bool
  {
    return TTF_GetFontSDF(get()) == SDL_TRUE;
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
    if (TTF_SizeText(get(), str, &size.width, &size.height) != -1) {
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
    if (TTF_MeasureText(get(), str, width, &result.extent, &result.count) < 0) {
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
    if (TTF_MeasureUTF8(get(), str, width, &result.extent, &result.count) < 0) {
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
    if (TTF_MeasureUNICODE(get(), str.data(), width, &result.extent, &result.count) < 0) {
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
    const auto style = TTF_GetFontStyle(get());
    TTF_SetFontStyle(get(), style | mask);
  }

  void remove_style(const int mask) noexcept
  {
    const auto style = TTF_GetFontStyle(get());
    TTF_SetFontStyle(get(), style & ~mask);
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

#if SDL_TTF_VERSION_ATLEAST(2, 0, 18)

[[deprecated("Use font::set_script instead")]] inline auto ttf_set_script(
    const int script) noexcept -> result
{
  return TTF_SetScript(script) == 0;
}

[[deprecated("Use font::set_direction instead")]] inline auto ttf_set_direction(
    const int direction) noexcept -> result
{
  return TTF_SetDirection(direction) == 0;
}

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

#endif  // SDL_TTF_VERSION_ATLEAST(2, 0, 18)

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONTS_FONT_HPP_