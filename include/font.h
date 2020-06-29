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

#ifndef CENTURION_FONT_HEADER
#define CENTURION_FONT_HEADER

#include <SDL_ttf.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "area.h"
#include "centurion_api.h"
#include "centurion_exception.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The GlyphMetrics struct provides metrics about a glyph in a font.
 *
 * @since 4.0.0
 */
struct GlyphMetrics final {
  int minX;
  int minY;
  int maxX;
  int maxY;
  int advance;
};

/**
 * The Font class represents a TrueType font.
 *
 * @since 3.0.0
 */
class Font final {
 public:
  /**
   * The Hint enum class represents different possible TrueType font hint
   * values.
   *
   * @since 3.1.0
   */
  enum class Hint {
    Normal = TTF_HINTING_NORMAL,
    Light = TTF_HINTING_LIGHT,
    Mono = TTF_HINTING_MONO,
    None = TTF_HINTING_NONE
  };

  /**
   * Creates a Font based on the .ttf-file at the specified path.
   *
   * @param file the file path of the TrueType font file.
   * @param size the font size, must be greater than zero.
   * @throws CenturionException if the font cannot be loaded or if the supplied
   * size isn't greater than zero.
   * @since 3.0.0
   */
  CENTURION_API Font(CZString file, int size);

  /**
   * The copy constructor is deleted for font instances.
   *
   * @since 3.0.0
   */
  Font(const Font&) noexcept = delete;

  /**
   * Creates a font by moving the supplied font.
   *
   * @param other the font that will have its fields moved.
   * @since 3.0.0
   */
  CENTURION_API Font(Font&& other) noexcept;

  CENTURION_API ~Font() noexcept;

  /**
   * The copy assignment operator is deleted for font instances.
   *
   * @since 3.0.0
   */
  Font& operator=(const Font&) noexcept = delete;

  /**
   * Moves the supplied font into this font.
   *
   * @param other the font that will have its fields moved.
   * @return the created font.
   * @since 3.0.0
   */
  CENTURION_API Font& operator=(Font&& other) noexcept;

  /**
   * Creates and returns a unique pointer to a font instance.
   *
   * @param file the file path of the TrueType font file.
   * @param size the font size, must be greater than zero.
   * @return a unique pointer to a font instance.
   * @throws CenturionException if the font cannot be loaded or if the supplied
   * size isn't greater than zero.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Font> unique(CZString file, int size);

  /**
   * Creates and returns a shared pointer to a font instance.
   *
   * @param file the file path of the TrueType font file.
   * @param size the font size, must be greater than zero.
   * @return a shared pointer to a font instance.
   * @throws CenturionException if the font cannot be loaded or if the supplied
   * size isn't greater than zero.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Font> shared(CZString file, int size);

  /**
   * Resets the style of the font.
   *
   * @since 3.0.0
   */
  CENTURION_API void reset() noexcept;

  /**
   * Sets the bold property of the font.
   *
   * @param bold true if the font should be bold; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_bold(bool bold) noexcept;

  /**
   * Sets the italic property of the font.
   *
   * @param italic true if the font should be italic; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_italic(bool italic) noexcept;

  /**
   * Sets the underlined property of the font.
   *
   * @param underlined true if the font should be underlined; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_underlined(bool underlined) noexcept;

  /**
   * Sets the strikethrough property of the font.
   *
   * @param strikethrough true if the font should be strikethrough; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_strikethrough(bool strikethrough) noexcept;

  /**
   * Sets the outlined property of the font.
   *
   * @param outlined true if the font should be outlined; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_outlined(bool outlined) noexcept;

  /**
   * Sets the TrueType font hinting.
   *
   * @param hint the font hinting that will be used.
   * @since 3.1.0
   */
  CENTURION_API void set_font_hinting(Hint hint) noexcept;

  /**
   * Sets whether or not font kerning is allowed. Kerning is the process of
   * adjusting the spacing between certain characters in order to improve the
   * appearance of a font.
   *
   * @param kerning true if kerning should be allowed; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API void set_kerning(bool kerning) noexcept;

  /**
   * Returns the maximum height of a character in this font. This is usually the
   * same as the point size.
   *
   * @return the maximum height of a character in this font.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int height() const noexcept;

  /**
   * Returns the offset from the baseline to the bottom of the font characters.
   * The returned value is negative, relative to the baseline.
   *
   * @return the offset from the baseline to the bottom of the font characters.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int descent() const noexcept;

  /**
   * Returns the offset from the baseline to the top of the font characters. The
   * returned value is positive, relative to the baseline.
   *
   * @return the offset from the baseline to the top of the font characters.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int ascent() const noexcept;

  /**
   * Returns the recommended pixel height of rendered text in the font. The
   * returned value is usually larger than the height of the font.
   *
   * @return Returns the recommended pixel height of rendered text in the font.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int line_skip() const noexcept;

  /**
   * Returns the number of available font faces in the font.
   *
   * @return the number of available font faces in the font.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int font_faces() const noexcept;

  /**
   * Returns the TrueType font hinting of the font. Set to FontHint::Normal by
   * default.
   *
   * @return the TrueType font hinting of the font.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API Hint font_hinting() const noexcept;

  /**
   * Indicates whether or not kerning is being used.
   *
   * @return true if kerning is being used by the font; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool kerning() const noexcept;

  /**
   * Indicates whether or not the font is bold.
   *
   * @return true if the font is bold; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool bold() const noexcept;

  /**
   * Indicates whether or not the font is italic.
   *
   * @return true if the font is italic; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool italic() const noexcept;

  /**
   * Indicates whether or not the font is underlined.
   *
   * @return true if the font is underlined; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool underlined() const noexcept;

  /**
   * Indicates whether or not the font is a strikethrough font.
   *
   * @return true if the font is a strikethrough font; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool strikethrough() const noexcept;

  /**
   * Indicates whether or not the font is outlined.
   *
   * @return true if the font is outlined; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool outlined() const noexcept;

  /**
   * Indicates whether or not the font is fixed width.
   *
   * @return true if the font is fixed width; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_fixed_width() const noexcept;

  /**
   * Returns the kerning amount between two glyphs in the font, if kerning
   * would be enabled. In other words, you can use this method to obtain the
   * kerning amount between, for instance, the characters 'a' and 'V' if they
   * were to be rendered next to each other.
   *
   * @param firstGlyph the first glyph.
   * @param secondGlyph the second glyph.
   * @return the kerning amount between to glyphs in the font.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int kerning_amount(Uint16 firstGlyph,
                                   Uint16 secondGlyph) const noexcept;

  /**
   * Indicates whether or not the specified glyph is available in the font.
   *
   * @param glyph the unicode glyph that will be checked.
   * @return true if the glyph is available in the font; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_glyph_provided(Uint16 glyph) const noexcept;

  /**
   * Returns the metrics of the specified glyph in this font.
   *
   * @param glyph the glyph to obtain the metrics of.
   * @return the metrics of the specified glyph; nothing if the metrics
   * couldn't be obtained.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<GlyphMetrics> glyph_metrics(Uint16 glyph) const noexcept;

  /**
   * Returns the family name of the font.
   *
   * @return the family name of the font.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API CZString family_name() const noexcept;

  /**
   * Returns the font face style name of the font. This information may not be
   * available.
   *
   * @return the font face style name of the font; null if there is none
   * available.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API CZString style_name() const noexcept;

  /**
   * Returns the width of the supplied string, if it was rendered using the
   * font.
   *
   * @param s the string to determine the width of.
   * @return the width of the supplied string, if it was rendered using the
   * font. The returned value is 0 if the string is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int string_width(CZString s) const noexcept;

  /**
   * Returns the height of the supplied string, if it was rendered using the
   * font.
   *
   * @param s the string to determine the height of.
   * @return the height of the supplied string, if it was rendered using the
   * font. The returned value is 0 if the string is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int string_height(CZString s) const noexcept;

  /**
   * Returns the size of the supplied string, if it was rendered using the font.
   *
   * @param s the string to determine the size of.
   * @return the size of the string, if it was rendered using the font. The
   * returned size is 0x0 if the supplied string is null.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IArea string_size(CZString s) const noexcept;

  /**
   * Returns the compile-time version of SDL2_ttf that is being used.
   *
   * @return the compile-time version of SDL2_ttf that is being used.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SDL_version ttf_version() noexcept;

  /**
   * Returns a textual representation of the font instance.
   *
   * @return a textual representation of the font instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Returns the size of the font.
   *
   * @return the size of the font.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  int size() const noexcept { return m_size; }

  /**
   * Returns a pointer to the internal TTF_Font. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied.
   *
   * @return a pointer to the internal TTF_Font.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  TTF_Font* get() const noexcept { return m_font; }

  /**
   * Converts to TTF_Font*.
   *
   * @return a pointer to the internal TTF_Font instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator TTF_Font*() noexcept { return m_font; }

  /**
   * Converts to TTF_Font*.
   *
   * @return a pointer to the internal TTF_Font instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator const TTF_Font*() const noexcept { return m_font; }

 private:
  TTF_Font* m_font = nullptr;
  int m_style = 0;
  int m_size = 0;

  /**
   * Destroys the resources associated with the font.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied font instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Font&& other) noexcept;

  /**
   * Enables the font style associated with the supplied bit mask. The possible
   * values are TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and
   * TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to enable.
   * @since 3.0.0
   */
  void add_style(int mask) noexcept;

  /**
   * Removes the font style associated with the supplied bit mask. The possible
   * values are TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and
   * TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to disable.
   * @since 3.0.0
   */
  void remove_style(int mask) noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Font>::value, "Font isn't final!");
#endif

static_assert(std::is_nothrow_move_constructible<Font>::value,
              "Font isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Font>::value,
              "Font isn't nothrow move assignable!");

static_assert(!std::is_copy_constructible<Font>::value,
              "Font is copy constructible!");

static_assert(!std::is_copy_assignable<Font>::value,
              "Font is copy assignable!");

static_assert(std::is_convertible<Font, TTF_Font*>::value,
              "Font isn't convertible to TTF_Font*!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "font.cpp"
#endif

#endif  // CENTURION_FONT_HEADER