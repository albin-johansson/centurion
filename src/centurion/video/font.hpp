#ifndef CENTURION_FONT_HEADER
#define CENTURION_FONT_HEADER

#ifndef CENTURION_NO_SDL_TTF

#include <SDL_ttf.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/not_null.hpp"
#include "../core/str.hpp"
#include "../core/to_underlying.hpp"
#include "../detail/address_of.hpp"
#include "../math/area.hpp"
#include "unicode_string.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \struct glyph_metrics
 *
 * \brief Provides metrics about a glyph in a font.
 *
 * \since 4.0.0
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
 * \enum font_hint
 *
 * \brief Provides different possible TrueType font hint values.
 *
 * \since 3.1.0
 */
enum class font_hint : int
{
  normal = TTF_HINTING_NORMAL,
  light = TTF_HINTING_LIGHT,
  mono = TTF_HINTING_MONO,
  none = TTF_HINTING_NONE
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied font hint.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(font_hint::light) == "light"`.
 *
 * \param hint the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const font_hint hint) -> std::string_view
{
  switch (hint) {
    case font_hint::normal:
      return "normal";

    case font_hint::light:
      return "light";

    case font_hint::mono:
      return "mono";

    case font_hint::none:
      return "none";

    default:
      throw cen_error{"Did not recognize font hint!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a font hint enumerator.
 *
 * \param stream the output stream that will be used.
 * \param hint the enumerator that will be printed.
 *
 * \see `to_string(font_hint)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const font_hint hint) -> std::ostream&
{
  return stream << to_string(hint);
}

/// \} End of streaming

/**
 * \class font
 *
 * \brief Represents a TrueType font.
 *
 * \details This class provides information about a TrueType font, but it can also be used
 * for text rendering and obtaining information about the size of rendered strings, etc.
 *
 * \see `TTF_Font`
 *
 * \since 3.0.0
 */
class font final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a font based on the `.ttf`-file at the specified path.
   *
   * \param file the file path of the TrueType font file, mustn't be null.
   * \param size the font size, must be greater than zero.
   *
   * \throws cen_error if the supplied size is not greater than zero.
   * \throws ttf_error if the font cannot be loaded.
   *
   * \since 3.0.0
   */
  font(const not_null<str> file, const int size) : m_size{size}
  {
    assert(file);

    if (size <= 0) {
      throw cen_error{"Bad font size!"};
    }

    m_font.reset(TTF_OpenFont(file, size));
    if (!m_font) {
      throw ttf_error{};
    }
  }

  /**
   * \brief Creates a font based on the `.ttf`-file at the specified path.
   *
   * \param file the file path of the TrueType font file.
   * \param size the font size, must be greater than zero.
   *
   * \throws cen_error if the supplied size is not greater than zero.
   * \throws ttf_error if the font cannot be loaded.
   *
   * \since 5.3.0
   */
  font(const std::string& file, const int size) : font{file.c_str(), size}
  {}

  /// \} End of construction

  /// \name Style functions
  /// \{

  /**
   * \brief Resets the style of the font.
   *
   * \since 3.0.0
   */
  void reset() noexcept
  {
    TTF_SetFontStyle(m_font.get(), TTF_STYLE_NORMAL);
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
    }
    else {
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
    }
    else {
      remove_style(TTF_STYLE_ITALIC);
    }
  }

  /**
   * \brief Sets whether the font is underlined.
   *
   * \param underlined `true` if the font should be underlined; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_underlined(const bool underlined) noexcept
  {
    if (underlined) {
      add_style(TTF_STYLE_UNDERLINE);
    }
    else {
      remove_style(TTF_STYLE_UNDERLINE);
    }
  }

  /**
   * \brief Sets whether the font is strikethrough.
   *
   * \param strikethrough `true` if the font should be strikethrough; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_strikethrough(const bool strikethrough) noexcept
  {
    if (strikethrough) {
      add_style(TTF_STYLE_STRIKETHROUGH);
    }
    else {
      remove_style(TTF_STYLE_STRIKETHROUGH);
    }
  }

  /**
   * \brief Sets the outline size of the font.
   *
   * \param outline the outline size, in pixels; `0` is used to disable outlining.
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
  void set_font_hinting(const font_hint hint) noexcept
  {
    TTF_SetFontHinting(m_font.get(), to_underlying(hint));
  }

  /**
   * \brief Sets whether or not font kerning is allowed.
   *
   * \details Kerning is the process of adjusting the spacing between certain characters
   * in order to improve the appearance of a font.
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
   * \brief Indicates whether or not the font is bold.
   *
   * \return `true` if the font is bold; `false` otherwise.
   *
   * \since 5.1.0
   */
  [[nodiscard]] auto is_bold() const noexcept -> bool
  {
    return TTF_GetFontStyle(m_font.get()) & TTF_STYLE_BOLD;
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
    return TTF_GetFontStyle(m_font.get()) & TTF_STYLE_ITALIC;
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
    return TTF_GetFontStyle(m_font.get()) & TTF_STYLE_UNDERLINE;
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
    return TTF_GetFontStyle(m_font.get()) & TTF_STYLE_STRIKETHROUGH;
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
   * \brief Returns the TrueType font hinting of the font.
   *
   * \details This property is set to `Normal` by default.
   *
   * \return the TrueType font hinting of the font.
   *
   * \since 3.1.0
   */
  [[nodiscard]] auto font_hinting() const noexcept -> font_hint
  {
    return static_cast<font_hint>(TTF_GetFontHinting(m_font.get()));
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

  /// \} End of style functions

  /// \name Queries
  /// \{

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
   * \brief Returns the offset from the baseline to the bottom of the font characters.
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
   * \brief Returns the offset from the baseline to the top of the font characters.
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
   * \brief Returns the family name of the font.
   *
   * \return the family name of the font.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto family_name() const noexcept -> str
  {
    return TTF_FontFaceFamilyName(m_font.get());
  }

  /**
   * \brief Returns the font face style name of the font.
   *
   * \note This information may not be available.
   *
   * \return the font face style name of the font; `nullptr` if it isn't available.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto style_name() const noexcept -> str
  {
    return TTF_FontFaceStyleName(m_font.get());
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

  /// \} End of queries

  /// \name Glyph information
  /// \{

  /**
   * \brief Returns the kerning amount between two glyphs in the font, if kerning would be
   * enabled.
   *
   * \details In other words, you can use this function to obtain the kerning amount
   * between, for instance, the characters 'a' and 'V' if they were to be rendered next to
   * each other.
   *
   * \param firstGlyph the first glyph.
   * \param secondGlyph the second glyph.
   *
   * \return the kerning amount between to glyphs in the font.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto kerning_amount(const unicode firstGlyph,
                                    const unicode secondGlyph) const noexcept -> int
  {
    return TTF_GetFontKerningSizeGlyphs(m_font.get(), firstGlyph, secondGlyph);
  }

  /**
   * \brief Indicates whether or not the specified glyph is available in the font.
   *
   * \param glyph the unicode glyph that will be checked.
   *
   * \return `true` if the glyph is available in the font; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_glyph_provided(const unicode glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided(m_font.get(), glyph);
  }

  /**
   * \brief Returns the metrics of the specified glyph in this font.
   *
   * \param glyph the glyph to obtain the metrics of.
   *
   * \return the metrics of the specified glyph; std::nullopt if the metrics couldn't be
   * obtained.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get_metrics(const unicode glyph) const noexcept
      -> std::optional<glyph_metrics>
  {
    glyph_metrics metrics{};
    if (TTF_GlyphMetrics(m_font.get(),
                         glyph,
                         &metrics.minX,
                         &metrics.maxX,
                         &metrics.minY,
                         &metrics.maxY,
                         &metrics.advance) != -1)
    {
      return metrics;
    }
    else {
      return std::nullopt;
    }
  }

  /// \} End of glyph information

  /// \name Rendered string size functions
  /// \{

  /**
   * \brief Returns the size of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the size of, can't be null.
   *
   * \return the size of the string, if it was rendered using the font; `std::nullopt` if
   * something goes wrong.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto string_size(const not_null<str> str) const noexcept
      -> std::optional<iarea>
  {
    assert(str);

    iarea size{};
    if (TTF_SizeText(m_font.get(), str, &size.width, &size.height) != -1) {
      return size;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the size of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the size of.
   *
   * \return the size of the string, if it was rendered using the font; `std::nullopt` if
   * something goes wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto string_size(const std::string& str) const noexcept -> std::optional<iarea>
  {
    return string_size(str.c_str());
  }

  /**
   * \brief Returns the width of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the width of, can't be null.
   *
   * \return the width of the supplied string, if it was rendered using the font;
   * `std::nullopt` if something goes wrong.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto string_width(const not_null<str> str) const noexcept -> std::optional<int>
  {
    if (const auto size = string_size(str)) {
      return size->width;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the width of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the width of.
   *
   * \return the width of the supplied string, if it was rendered using the font;
   * `std::nullopt` if something goes wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto string_width(const std::string& str) const noexcept -> std::optional<int>
  {
    return string_width(str.c_str());
  }

  /**
   * \brief Returns the height of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the height of, can't be null.
   *
   * \return the height of the supplied string, if it was rendered using the font;
   * `std::nullopt` if something goes wrong.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto string_height(const not_null<str> str) const noexcept
      -> std::optional<int>
  {
    if (const auto size = string_size(str)) {
      return size->height;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the height of the supplied string, if it was rendered using the font.
   *
   * \param str the string to determine the height of.
   *
   * \return the height of the supplied string, if it was rendered using the font;
   * `std::nullopt` if something goes wrong.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto string_height(const std::string& str) const noexcept -> std::optional<int>
  {
    return string_height(str.c_str());
  }

  /// \} End of rendered string size functions

  /// \name Conversions
  /// \{

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

  /// \} End of conversions

  /**
   * \brief Returns a pointer to the associated `TTF_Font`.
   *
   * \warning Use of this function is not recommended. However, it's useful since many SDL
   * calls use non-const pointers even when no change will be applied.
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

 private:
  struct deleter final
  {
    void operator()(TTF_Font* font) noexcept
    {
      TTF_CloseFont(font);
    }
  };

  std::unique_ptr<TTF_Font, deleter> m_font;
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
    const auto style = TTF_GetFontStyle(m_font.get());
    TTF_SetFontStyle(m_font.get(), style | mask);
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
    const auto style = TTF_GetFontStyle(m_font.get());
    TTF_SetFontStyle(m_font.get(), style & ~mask);
  }
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a font instance.
 *
 * \return a textual representation of the font instance.
 *
 * \since 5.0.0
 */
[[nodiscard]] inline auto to_string(const font& font) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("font{{data: {}, name: {}, size: {}}}",
                     detail::address_of(font.get()),
                     font.family_name(),
                     font.size());
#else
  return "font{data: " + detail::address_of(font.get()) +
         ", name: " + std::string{font.family_name()} +
         ", size: " + std::to_string(font.size()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

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
  return stream << to_string(font);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONT_HEADER