/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_FONT_HEADER
#define CENTURION_FONT_HEADER

#include <SDL_ttf.h>

#include <cassert>   // assert
#include <memory>    // unique_ptr
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string

#include "area.hpp"
#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/to_string.hpp"
#include "exception.hpp"
#include "not_null.hpp"
#include "unicode_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

/**
 * \struct glyph_metrics
 *
 * \brief Provides metrics about a glyph in a font.
 *
 * \since 4.0.0
 *
 * \headerfile font.hpp
 */
struct glyph_metrics final
{
  int minX;     ///< The minimum X-offset.
  int minY;     ///< The minimum Y-offset.
  int maxX;     ///< The maximum X-offset.
  int maxY;     ///< The maximum Y-offset.
  int advance;  ///< The advance offset.
};

/**
 * \class font
 *
 * \brief Represents a True Type font.
 *
 * \see `TTF_Font`
 *
 * \since 3.0.0
 *
 * \headerfile font.hpp
 */
class font final
{
 public:
  /**
   * \enum hint
   *
   * \brief Provides different possible TrueType font hint values.
   *
   * \since 3.1.0
   *
   * \todo Centurion 6: Make this a normal enum?
   *
   * \headerfile font.hpp
   */
  enum class hint
  {
    normal = TTF_HINTING_NORMAL,
    light = TTF_HINTING_LIGHT,
    mono = TTF_HINTING_MONO,
    none = TTF_HINTING_NONE
  };

  /**
   * \brief Creates a font based on the `.ttf`-file at the specified path.
   *
   * \param file the file path of the TrueType font file, mustn't be null.
   * \param size the font size, must be greater than zero.
   *
   * \throws exception if the supplied size is <= 0.
   * \throws ttf_error if the font cannot be loaded.
   *
   * \since 3.0.0
   */
  font(not_null<czstring> file, const int size) : m_size{size}
  {
    assert(file);

    if (size <= 0) {
      throw exception{"Bad font size!"};
    }

    m_font.reset(TTF_OpenFont(file, size));
    if (!m_font) {
      throw ttf_error{};
    }

    m_style = TTF_GetFontStyle(m_font.get());
  }

  /**
   * \brief Resets the style of the font.
   *
   * \since 3.0.0
   */
  void reset() noexcept
  {
    m_style = TTF_STYLE_NORMAL;
    TTF_SetFontStyle(m_font.get(), m_style);
  }

  /**
   * \brief Sets whether the font is bold.
   *
   * \param bold `true` if the font should be bold; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_bold(const bool bold) noexcept
  {
    if (bold) {
      add_style(TTF_STYLE_BOLD);
    } else {
      remove_style(TTF_STYLE_BOLD);
    }
  }

  /**
   * \brief Sets whether the font is italic.
   *
   * \param italic `true` if the font should be italic; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_italic(const bool italic) noexcept
  {
    if (italic) {
      add_style(TTF_STYLE_ITALIC);
    } else {
      remove_style(TTF_STYLE_ITALIC);
    }
  }

  /**
   * \brief Sets whether the font is underlined.
   *
   * \param underlined `true` if the font should be underlined; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  void set_underlined(const bool underlined) noexcept
  {
    if (underlined) {
      add_style(TTF_STYLE_UNDERLINE);
    } else {
      remove_style(TTF_STYLE_UNDERLINE);
    }
  }

  /**
   * \brief Sets whether the font is strikethrough.
   *
   * \param strikethrough `true` if the font should be strikethrough; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  void set_strikethrough(const bool strikethrough) noexcept
  {
    if (strikethrough) {
      add_style(TTF_STYLE_STRIKETHROUGH);
    } else {
      remove_style(TTF_STYLE_STRIKETHROUGH);
    }
  }

  /**
   * \brief Sets the outline size of the font.
   *
   * \param outline the outline size, in pixels; `0` is used to disable
   * outlining.
   *
   * \since 5.0.0
   */
  void set_outline(const int outline) noexcept
  {
    TTF_SetFontOutline(m_font.get(), outline);
  }

  /**
   * \brief Sets the TrueType font hint of the font.
   *
   * \param hint the font hinting that will be used.
   *
   * \since 3.1.0
   */
  void set_font_hinting(const hint hint) noexcept
  {
    TTF_SetFontHinting(m_font.get(), static_cast<int>(hint));
  }

  /**
   * \brief Sets whether or not font kerning is allowed.
   *
   * \details Kerning is the process of adjusting the spacing between certain
   * characters in order to improve the appearance of a font.
   *
   * \param kerning `true` if kerning should be allowed; `false` otherwise.
   *
   * \since 4.0.0
   */
  void set_kerning(const bool kerning) noexcept
  {
    TTF_SetFontKerning(m_font.get(), kerning ? 1 : 0);
  }

  /**
   * \brief Returns the maximum height of a character in this font.
   *
   * \details This is usually the same as the point size.
   *
   * \return the maximum height of a character in this font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return TTF_FontHeight(m_font.get());
  }

  /**
   * \brief Returns the offset from the baseline to the bottom of the font
   * characters.
   *
   * \details The returned value is negative, relative to the baseline.
   *
   * \return the offset from the baseline to the bottom of the font characters.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto descent() const noexcept -> int
  {
    return TTF_FontDescent(m_font.get());
  }

  /**
   * \brief Returns the offset from the baseline to the top of the font
   * characters.
   *
   * \details The returned value is positive, relative to the baseline.
   *
   * \return the offset from the baseline to the top of the font characters.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto ascent() const noexcept -> int
  {
    return TTF_FontAscent(m_font.get());
  }

  /**
   * \brief Returns the recommended pixel height of rendered text in the font.
   *
   * \details The returned value is usually larger than the height of the font.
   *
   * \return Returns the recommended pixel height of rendered text in the font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto line_skip() const noexcept -> int
  {
    return TTF_FontLineSkip(m_font.get());
  }

  /**
   * \brief Returns the number of available font faces in the font.
   *
   * \return the number of available font faces in the font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto font_faces() const noexcept -> int
  {
    return static_cast<int>(TTF_FontFaces(m_font.get()));
  }

  /**
   * \brief Returns the TrueType font hinting of the font.
   *
   * \details This property is set to `Normal` by default.
   *
   * \return the TrueType font hinting of the font.
   *
   * \since 3.1.0
   */
  [[nodiscard]] auto font_hinting() const noexcept -> hint
  {
    return static_cast<font::hint>(TTF_GetFontHinting(m_font.get()));
  }

  /**
   * \brief Indicates whether or not kerning is being used.
   *
   * \return `true` if kerning is being used by the font; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `has_kerning()` instead.
   *
   * \since 4.0.0
   */
  [[nodiscard, deprecated]] auto kerning() const noexcept -> bool
  {
    return has_kerning();
  }

  /**
   * \brief Indicates whether or not kerning is being used.
   *
   * \return `true` if kerning is being used by the font; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto has_kerning() const noexcept -> bool
  {
    return TTF_GetFontKerning(m_font.get());
  }

  /**
   * \brief Indicates whether or not the font is bold.
   *
   * \return `true` if the font is bold; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `is_bold()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto bold() const noexcept -> bool
  {
    return is_bold();
  }

  /**
   * \brief Indicates whether or not the font is bold.
   *
   * \return `true` if the font is bold; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_bold() const noexcept -> bool
  {
    return m_style & TTF_STYLE_BOLD;
  }

  /**
   * \brief Indicates whether or not the font is italic.
   *
   * \return `true` if the font is italic; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `is_italic()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto italic() const noexcept -> bool
  {
    return is_italic();
  }

  /**
   * \brief Indicates whether or not the font is italic.
   *
   * \return `true` if the font is italic; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_italic() const noexcept -> bool
  {
    return m_style & TTF_STYLE_ITALIC;
  }

  /**
   * \brief Indicates whether or not the font is underlined.
   *
   * \return `true` if the font is underlined; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `is_underlined()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto underlined() const noexcept -> bool
  {
    return is_underlined();
  }

  /**
   * \brief Indicates whether or not the font is underlined.
   *
   * \return `true` if the font is underlined; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_underlined() const noexcept -> bool
  {
    return m_style & TTF_STYLE_UNDERLINE;
  }

  /**
   * \brief Indicates whether or not the font is a strikethrough font.
   *
   * \return `true` if the font is a strikethrough font; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `is_strikethrough()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto strikethrough() const noexcept -> bool
  {
    return is_strikethrough();
  }

  /**
   * \brief Indicates whether or not the font is a strikethrough font.
   *
   * \return `true` if the font is a strikethrough font; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_strikethrough() const noexcept -> bool
  {
    return m_style & TTF_STYLE_STRIKETHROUGH;
  }

  /**
   * \brief Indicates whether or not the font is outlined.
   *
   * \return `true` if the font is outlined; `false` otherwise.
   *
   * \deprecated Since 5.1.0, use `is_outlined()` instead.
   *
   * \since 3.0.0
   */
  [[nodiscard, deprecated]] auto outlined() const noexcept -> bool
  {
    return is_outlined();
  }

  /**
   * \brief Indicates whether or not the font is outlined.
   *
   * \return `true` if the font is outlined; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_outlined() const noexcept -> bool
  {
    return TTF_GetFontOutline(m_font.get()) != 0;
  }

  /**
   * \brief Indicates whether or not the font is fixed width.
   *
   * \return `true` if the font is fixed width; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_fixed_width() const noexcept -> bool
  {
    return TTF_FontFaceIsFixedWidth(m_font.get());
  }

  /**
   * \brief Returns the size of the outline of the font.
   *
   * \return the current outline size, in pixels.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto outline() const noexcept -> int
  {
    return TTF_GetFontOutline(m_font.get());
  }

  /**
   * \brief Returns the kerning amount between two glyphs in the font, if
   * kerning would be enabled.
   *
   * \details In other words, you can use this method to obtain the
   * kerning amount between, for instance, the characters 'a' and 'V' if they
   * were to be rendered next to each other.
   *
   * \param firstGlyph the first glyph.
   * \param secondGlyph the second glyph.
   *
   * \return the kerning amount between to glyphs in the font.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto kerning_amount(const unicode firstGlyph,
                                    const unicode secondGlyph) const noexcept
      -> int
  {
    const auto amount =
        TTF_GetFontKerningSizeGlyphs(m_font.get(), firstGlyph, secondGlyph);
    return amount;
  }

  /**
   * \brief Indicates whether or not the specified glyph is available in the
   * font.
   *
   * \param glyph the unicode glyph that will be checked.
   *
   * \return `true` if the glyph is available in the font; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_glyph_provided(const unicode glyph) const noexcept
      -> bool
  {
    return TTF_GlyphIsProvided(m_font.get(), glyph);
  }

  /**
   * \brief Returns the metrics of the specified glyph in this font.
   *
   * \param glyph the glyph to obtain the metrics of.
   *
   * \return the metrics of the specified glyph; std::nullopt if the metrics
   * couldn't be obtained.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get_metrics(const unicode glyph) const noexcept
      -> std::optional<glyph_metrics>
  {
    glyph_metrics metrics{};
    const auto result = TTF_GlyphMetrics(m_font.get(),
                                         glyph,
                                         &metrics.minX,
                                         &metrics.maxX,
                                         &metrics.minY,
                                         &metrics.maxY,
                                         &metrics.advance);
    if (result != -1) {
      return metrics;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the family name of the font.
   *
   * \return the family name of the font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto family_name() const noexcept -> czstring
  {
    return TTF_FontFaceFamilyName(m_font.get());
  }

  /**
   * \brief Returns the font face style name of the font.
   *
   * \note This information may not be available.
   *
   * \return the font face style name of the font; `nullptr` if it isn't
   * available.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto style_name() const noexcept -> czstring
  {
    return TTF_FontFaceStyleName(m_font.get());
  }

  /**
   * \brief Returns the width of the supplied string, if it was rendered using
   * the font.
   *
   * \param str the string to determine the width of, can't be null.
   *
   * \return the width of the supplied string, if it was rendered using the
   * font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto string_width(not_null<czstring> str) const noexcept -> int
  {
    assert(str);
    int width{};
    TTF_SizeText(m_font.get(), str, &width, nullptr);
    return width;
  }

  /**
   * \brief Returns the height of the supplied string, if it was rendered
   * using the font.
   *
   * \param str the string to determine the height of, can't be null.
   *
   * \return the height of the supplied string, if it was rendered using the
   * font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto string_height(not_null<czstring> str) const noexcept -> int
  {
    assert(str);
    int height{};
    TTF_SizeText(m_font.get(), str, nullptr, &height);
    return height;
  }

  /**
   * \brief Returns the size of the supplied string, if it was rendered using
   * the font.
   *
   * \param str the string to determine the size of, can't be null.
   *
   * \return the size of the string, if it was rendered using the font.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto string_size(not_null<czstring> str) const noexcept -> iarea
  {
    assert(str);
    int width{};
    int height{};
    TTF_SizeText(m_font.get(), str, &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the size of the font.
   *
   * \return the size of the font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto size() const noexcept -> int
  {
    return m_size;
  }

  /**
   * \brief Returns a pointer to the associated `TTF_Font`.
   *
   * \warning Use of this method is not recommended. However, it's useful since
   * many SDL calls use non-const pointers even when no change will be applied.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated `TTF_Font`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> TTF_Font*
  {
    return m_font.get();
  }

  /**
   * \brief Converts to `TTF_Font*`.
   *
   * \return a pointer to the associated `TTF_Font` instance.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator TTF_Font*() noexcept
  {
    return m_font.get();
  }

  /**
   * \brief Converts to `const TTF_Font*`.
   *
   * \return a pointer to the associated `TTF_Font` instance.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator const TTF_Font*() const noexcept
  {
    return m_font.get();
  }

 private:
  struct deleter final
  {
    void operator()(TTF_Font* font) noexcept
    {
      TTF_CloseFont(font);
    }
  };

  std::unique_ptr<TTF_Font, deleter> m_font;
  int m_style{};
  int m_size{};

  /**
   * \brief Enables the font style associated with the supplied bit mask.
   *
   * \details The possible values are `TTF_STYLE_BOLD`, `TTF_STYLE_ITALIC`,
   * `TTF_STYLE_UNDERLINE` and `TTF_STYLE_STRIKETHROUGH`.
   *
   * \param mask the bit mask of the font style to enable.
   *
   * \since 3.0.0
   */
  void add_style(const int mask) noexcept
  {
    m_style |= mask;
    TTF_SetFontStyle(m_font.get(), m_style);
  }

  /**
   * \brief Removes the font style associated with the supplied bit mask.
   *
   * \details The possible values are `TTF_STYLE_BOLD`, `TTF_STYLE_ITALIC`,
   * `TTF_STYLE_UNDERLINE` and `TTF_STYLE_STRIKETHROUGH`.
   *
   * \param mask the bit mask of the font style to disable.
   *
   * \since 3.0.0
   */
  void remove_style(const int mask) noexcept
  {
    m_style &= ~mask;
    TTF_SetFontStyle(m_font.get(), m_style);
  }
};

/**
 * \brief Returns a textual representation of a font instance.
 *
 * \return a textual representation of the font instance.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const font& font) -> std::string
{
  return "[font | data: " + detail::address_of(font.get()) +
         ", name: " + std::string{font.family_name()} +
         ", size: " + detail::to_string(font.size()).value() + "]";
}

/**
 * \brief Prints a textual representation of a font.
 *
 * \param stream the stream that will be used.
 * \param font the font instance that will be printed.
 *
 * \return the stream that was used.
 *
 * \since 5.0.0
 */
inline auto operator<<(std::ostream& stream, const font& font) -> std::ostream&
{
  stream << to_string(font);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_FONT_HEADER