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

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

enum class font_hint {
  normal = TTF_HINTING_NORMAL,
  light = TTF_HINTING_LIGHT,
  mono = TTF_HINTING_MONO,
  none = TTF_HINTING_NONE
};

/// \name Font hint functions
/// \{

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
      throw exception{"Did not recognize font hint!"};
  }
}

inline auto operator<<(std::ostream& stream, const font_hint hint) -> std::ostream&
{
  return stream << to_string(hint);
}

/// \} End of font hint functions

struct glyph_metrics final {
  int min_x{};    ///< The minimum X-offset.
  int min_y{};    ///< The minimum Y-offset.
  int max_x{};    ///< The maximum X-offset.
  int max_y{};    ///< The maximum Y-offset.
  int advance{};  ///< The advance offset.
};

/**
 * \brief Represents a TrueType font.
 *
 * \details This class provides information about TrueType fonts, and can also be used
 * for rendering glyphs and strings. There are also various utility classes related to dealing
 * with fonts, in order to easily deal with fonts of different sizes and more efficient text
 * rendering.
 *
 * \see `font_cache`
 * \see `font_bundle`
 */
class font final {
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a font based on the TTF-font at the specified path.
   *
   * \param file the file path of the font file.
   * \param size the size of the font.
   *
   * \throws exception if the font size is not greater than zero.
   * \throws ttf_error if the font cannot be opened.
   */
  font(const char* file, const int size) : mSize{size}
  {
    assert(file);

    if (size <= 0) {
      throw exception{"Bad font size!"};
    }

    mFont.reset(TTF_OpenFont(file, size));
    if (!mFont) {
      throw ttf_error{};
    }
  }

  /// \copydoc font(const char*, int)
  font(const std::string& file, const int size) : font{file.c_str(), size} {}

  /// \} End of construction

  /// \name Style functions
  /// \{

  /**
   * \brief Resets the style of the font.
   */
  void reset_style() noexcept { TTF_SetFontStyle(mFont.get(), TTF_STYLE_NORMAL); }

  /**
   * \brief Sets whether the font is bold.
   *
   * \param bold `true` if the font should be bold; `false` otherwise.
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
   * \brief Sets whether the font can make use of kerning.
   *
   * \param kerning `true` if kerning is allowed; `false` otherwise.
   */
  void set_kerning(const bool kerning) noexcept
  {
    TTF_SetFontKerning(mFont.get(), kerning ? 1 : 0);
  }

  /**
   * \brief Sets the outline size of the font.
   *
   * \param outline the outline size; use zero to disable the outline.
   */
  void set_outline(const int outline) noexcept
  {
    TTF_SetFontOutline(mFont.get(), detail::max(outline, 0));
  }

  /**
   * \brief Sets the hint used by the font.
   *
   * \param hint the hint that will be used.
   */
  void set_font_hinting(const font_hint hint) noexcept
  {
    TTF_SetFontHinting(mFont.get(), ToUnderlying(hint));
  }

  /**
   * \brief Indicates whether the font is bold.
   *
   * \return `true` if the font is bold; `false` otherwise.
   */
  [[nodiscard]] auto is_bold() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_BOLD;
  }

  /**
   * \brief Indicates whether the font is italic.
   *
   * \return `true` if the font is italic; `false` otherwise.
   */
  [[nodiscard]] auto is_italic() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_ITALIC;
  }

  /**
   * \brief Indicates whether the font is underlined.
   *
   * \return `true` if the font is underlined; `false` otherwise.
   */
  [[nodiscard]] auto is_underlined() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_UNDERLINE;
  }

  /**
   * \brief Indicates whether the font is strikethrough.
   *
   * \return `true` if the font is strikethrough; `false` otherwise.
   */
  [[nodiscard]] auto is_strikethrough() const noexcept -> bool
  {
    return TTF_GetFontStyle(mFont.get()) & TTF_STYLE_STRIKETHROUGH;
  }

  /**
   * \brief Indicates whether the font is outlined.
   *
   * \return `true` if the font is outlined; `false` otherwise.
   */
  [[nodiscard]] auto is_outlined() const noexcept -> bool { return outline() != 0; }

  /**
   * \brief Indicates whether the font can make use of kerning.
   *
   * \return `true` if the kerning is allowed; `false` otherwise.
   */
  [[nodiscard]] auto has_kerning() const noexcept -> bool
  {
    return TTF_GetFontKerning(mFont.get());
  }

  /**
   * \brief Returns the size of the font outline.
   *
   * \return the outline size.
   */
  [[nodiscard]] auto outline() const noexcept -> int
  {
    return TTF_GetFontOutline(mFont.get());
  }

  /**
   * \brief Returns the font hinting.
   *
   * \return the current font hint.
   */
  [[nodiscard]] auto font_hinting() const noexcept -> font_hint
  {
    return static_cast<font_hint>(TTF_GetFontHinting(mFont.get()));
  }

  /// \} End of style functions

  /// \name Query functions
  /// \{

  /**
   * \brief Indicates whether the font is fixed width.
   *
   * \return `true` if the font is fixed width; `false` otherwise.
   */
  [[nodiscard]] auto is_fixed_width() const noexcept -> bool
  {
    return TTF_FontFaceIsFixedWidth(mFont.get());
  }

  /**
   * \brief Returns the maximum height of a character in the font.
   *
   * \return the maximum character height.
   */
  [[nodiscard]] auto height() const noexcept -> int { return TTF_FontHeight(mFont.get()); }

  /**
   * \brief Returns the offset from the baseline to the bottom of the font characters.
   *
   * \return the "descent" value of the font.
   */
  [[nodiscard]] auto descent() const noexcept -> int { return TTF_FontDescent(mFont.get()); }

  /**
   * \brief Returns the offset from the baseline to the top of the font characters.
   *
   * \return the "ascent" value of the font.
   */
  [[nodiscard]] auto ascent() const noexcept -> int { return TTF_FontAscent(mFont.get()); }

  /**
   * \brief Returns the suggested vertical spacing between lines of rendered text in the font.
   *
   * \return the vertical spacing between lines of text in the font.
   */
  [[nodiscard]] auto line_skip() const noexcept -> int
  {
    return TTF_FontLineSkip(mFont.get());
  }

  /**
   * \brief Returns the number of available font faces.
   *
   * \return the amount of font faces.
   */
  [[nodiscard]] auto font_face_count() const noexcept -> int
  {
    return static_cast<int>(TTF_FontFaces(mFont.get()));
  }

  /**
   * \brief Returns the name of the font family.
   *
   * \return the font family name; a null string is returned if something goes wrong.
   */
  [[nodiscard]] auto family_name() const noexcept -> const char*
  {
    return TTF_FontFaceFamilyName(mFont.get());
  }

  /**
   * \brief Returns the name of the font face style.
   *
   * \return the font face style name; a null string is returned if it is not available.
   */
  [[nodiscard]] auto style_name() const noexcept -> const char*
  {
    return TTF_FontFaceStyleName(mFont.get());
  }

  /**
   * \brief Returns the size of the font.
   *
   * \return the size of the font.
   */
  [[nodiscard]] auto size() const noexcept -> int { return mSize; }

  /// \} End of query functions

  /// \name Glyph information functions
  /// \{

  /**
   * \brief Returns the kerning amount between two glyphs.
   *
   * \param previous the previous glyph.
   * \param current the current glyph.
   *
   * \return the kerning amount between the two glyphs.
   */
  [[nodiscard]] auto get_kerning(const unicode_t previous,
                                 const unicode_t current) const noexcept -> int
  {
    return TTF_GetFontKerningSizeGlyphs(mFont.get(), previous, current);
  }

  /**
   * \brief Indicates whether a glyph is provided by the font.
   *
   * \param glyph the glyph that will be checked.
   *
   * \return `true` if the glyph is provided; `false` otherwise.
   */
  [[nodiscard]] auto is_glyph_provided(const unicode_t glyph) const noexcept -> bool
  {
    return TTF_GlyphIsProvided(mFont.get(), glyph);
  }

  /**
   * \brief Returns the metrics of a specific glyph.
   *
   * \param glyph the glyph that will be queried.
   *
   * \return the metrics of the glyph; an empty optional is returned if it is unavailable.
   */
  [[nodiscard]] auto get_metrics(const unicode_t glyph) const noexcept
      -> std::optional<glyph_metrics>
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
      return std::nullopt;
    }
  }

  /// \} End of glyph information functions

  /// \name Glyph rendering functions
  /// \{

  [[nodiscard]] auto render_solid_glyph(const unicode_t glyph, const color& fg) const
      -> Surface
  {
    return Surface{TTF_RenderGlyph_Solid(get(), glyph, fg.get())};
  }

  [[nodiscard]] auto render_shaded_glyph(const unicode_t glyph,
                                         const color& fg,
                                         const color& bg) const -> Surface
  {
    return Surface{TTF_RenderGlyph_Shaded(get(), glyph, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_blended_glyph(const unicode_t glyph, const color& fg) const
      -> Surface
  {
    return Surface{TTF_RenderGlyph_Blended(get(), glyph, fg.get())};
  }

  /// \} End of glyph rendering functions

  /// \name String rendering functions
  /// \{

  /**
   * \brief Returns the size of a string if it was rendered using the font.
   *
   * \param str the string that will be measured.
   *
   * \return the size of the string if it was rendered; an empty optional is returned if
   * something goes wrong.
   */
  [[nodiscard]] auto calc_size(const char* str) const noexcept -> std::optional<Area>
  {
    assert(str);

    Area size{};
    if (TTF_SizeText(mFont.get(), str, &size.width, &size.height) != -1) {
      return size;
    }
    else {
      return std::nullopt;
    }
  }

  /// \copydoc calc_size()
  [[nodiscard]] auto calc_size(const std::string& str) const noexcept -> std::optional<Area>
  {
    return calc_size(str.c_str());
  }

  [[nodiscard]] auto render_solid(const char* str, const color& fg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Solid(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_solid(const std::string& str, const color& fg) const -> Surface
  {
    return render_solid(str.c_str(), fg);
  }

  [[nodiscard]] auto render_shaded(const char* str, const color& fg, const color& bg) const
      -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_shaded(const std::string& str,
                                   const color& fg,
                                   const color& bg) const -> Surface
  {
    return render_shaded(str.c_str(), fg, bg);
  }

  [[nodiscard]] auto render_blended(const char* str, const color& fg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Blended(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_blended(const std::string& str, const color& fg) const -> Surface
  {
    return render_blended(str.c_str(), fg);
  }

  [[nodiscard]] auto render_wrapped(const char* str, const color& fg, const Uint32 wrap) const
      -> Surface
  {
    assert(str);
    return Surface{TTF_RenderUTF8_Blended_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_wrapped(const std::string& str,
                                    const color& fg,
                                    const Uint32 wrap) const -> Surface
  {
    return render_wrapped(str.c_str(), fg, wrap);
  }

  [[nodiscard]] auto render_solid_latin1(const char* str, const color& fg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Solid(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_solid_latin1(const std::string& str, const color& fg) const
      -> Surface
  {
    return render_solid_latin1(str.c_str(), fg);
  }

  [[nodiscard]] auto render_shaded_latin1(const char* str,
                                          const color& fg,
                                          const color& bg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Shaded(get(), str, fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_shaded_latin1(const std::string& str,
                                          const color& fg,
                                          const color& bg) const -> Surface
  {
    return render_shaded_latin1(str.c_str(), fg, bg);
  }

  [[nodiscard]] auto render_blended_latin1(const char* str, const color& fg) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Blended(get(), str, fg.get())};
  }

  [[nodiscard]] auto render_blended_latin1(const std::string& str, const color& fg) const
      -> Surface
  {
    return render_blended_latin1(str.c_str(), fg);
  }

  [[nodiscard]] auto render_wrapped_latin1(const char* str,
                                           const color& fg,
                                           const Uint32 wrap) const -> Surface
  {
    assert(str);
    return Surface{TTF_RenderText_Blended_Wrapped(get(), str, fg.get(), wrap)};
  }

  [[nodiscard]] auto render_wrapped_latin1(const std::string& str,
                                           const color& fg,
                                           const Uint32 wrap) const -> Surface
  {
    return render_wrapped_latin1(str.c_str(), fg, wrap);
  }

  [[nodiscard]] auto render_solid_unicode(const UnicodeString& str, const color& fg) const
      -> Surface
  {
    return Surface{TTF_RenderUNICODE_Solid(get(), str.data(), fg.get())};
  }

  [[nodiscard]] auto render_shaded_unicode(const UnicodeString& str,
                                           const color& fg,
                                           const color& bg) const -> Surface
  {
    return Surface{TTF_RenderUNICODE_Shaded(get(), str.data(), fg.get(), bg.get())};
  }

  [[nodiscard]] auto render_blended_unicode(const UnicodeString& str, const color& fg) const
      -> Surface
  {
    return Surface{TTF_RenderUNICODE_Blended(get(), str.data(), fg.get())};
  }

  [[nodiscard]] auto render_wrapped_unicode(const UnicodeString& str,
                                            const color& fg,
                                            const Uint32 wrap) const -> Surface
  {
    return Surface{TTF_RenderUNICODE_Blended_Wrapped(get(), str.data(), fg.get(), wrap)};
  }

  /// \} End of string rendering functions

  [[nodiscard]] auto get() const noexcept -> TTF_Font* { return mFont.get(); }

 private:
  Managed<TTF_Font> mFont;
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
};

/// \name Font functions
/// \{

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

/// \} End of font functions

/**
 * \brief Provides efficient font rendering.
 *
 * \details This class can be used to cache individual glyphs as textures that can
 * subsequently be rendered one-by-one to form strings. Note, this approach will not result in
 * accurate kerning. However, this might not be noticeable, and simply worth the performance
 * boost. This approach is very efficient for rendering pieces of text that frequently changes,
 * since other approaches would require dynamic allocation and de-allocation for every new
 * rendered string.
 *
 * \details Furthermore, it is possible to cache rendered strings and associate them with
 * integer identifiers. In contrast with the first approach, this will result in accurate
 * kerning. The only problem is that it is hard to know the exact strings you will render at
 * compile-time. Use this option if you know that you are going to render some specific string
 * a lot.
 *
 * \note Instances of this class are initially empty, i.e. they hold no cached glyphs or
 * strings. It is up to you to explicitly specify what you want to cache.
 *
 * \see `font`
 * \see `font_bundle`
 */
class font_cache final {
 public:
  using id_type = std::size_t;
  using size_type = std::size_t;

  /**
   * \brief Provides cached information about a glyph in a font.
   */
  struct glyph_data final {
    Texture texture;        ///< The cached texture of the glyph.
    glyph_metrics metrics;  ///< The metrics associate with the glyph.
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates a font cache based on the font at the specified file path.
   *
   * \param file the file path of the font.
   * \param size the size of the font.
   */
  font_cache(const char* file, const int size) : mFont{file, size} {}

  /// \copydoc font_cache(const char*, int)
  font_cache(const std::string& file, const int size) : mFont{file, size} {}

  /**
   * \brief Creates a font cache based on an existing font.
   *
   * \param font the font that will be used.
   */
  explicit font_cache(font&& font) noexcept : mFont{std::move(font)} {}

  /// \} End of construction

  /// \name Glyph-based rendering functions
  /// \{

  /**
   * \brief Renders a glyph, returning the x-coordinate for the next glyph.
   *
   * \param renderer the renderer that will be used.
   * \param glyph the Unicode glyph that will be rendered.
   * \param position the position of the rendered glyph.
   *
   * \return the x-coordinate intended to be used by a consecutive glyph.
   */
  template <typename T>
  auto render_glyph(BasicRenderer<T>& renderer, const unicode_t glyph, const Point& position)
      -> int
  {
    if (const auto* data = find_glyph(glyph)) {
      const auto& [texture, metrics] = *data;
      const auto outline = mFont.outline();

      /* SDL_ttf handles the y-axis alignment */
      const auto x = position.GetX() + metrics.min_x - outline;
      const auto y = position.GetY() - outline;

      renderer.Render(texture, Point{x, y});

      return x + metrics.advance;
    }
    else {
      return position.GetX();
    }
  }

  /**
   * \brief Renders a string as a series of glyphs.
   *
   * \details You can provide null-characters in the string to indicate line breaks which this
   * function will respect.
   *
   * \note This function will not output rendered text with accurate kerning.
   *
   * \tparam String the type of the string-like object, storing Unicode glyphs.
   *
   * \param renderer the renderer that will be used.
   * \param str the source of the Unicode glyphs.
   * \param position the position of the rendered string.
   *
   * \see `render_glyph()`
   */
  template <typename T, typename String>
  void render_text(BasicRenderer<T>& renderer, const String& str, Point position)
  {
    const auto originalX = position.GetX();
    const auto lineSkip = mFont.line_skip();

    for (const unicode_t glyph : str) {
      if (glyph == '\n') {
        position.SetX(originalX);
        position.SetY(position.GetY() + lineSkip);
      }
      else {
        const auto x = render_glyph(renderer, glyph, position);
        position.SetX(x);
      }
    }
  }

  /// \} End of glyph-based rendering functions

  /// \name String caching functions
  /// \{

  /**
   * \brief Renders a UTF-8 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_solid()`
   */
  template <typename T>
  auto store_solid(BasicRenderer<T>& renderer, const char* str, const color& fg) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_solid(str, fg));
  }

  /// \copydoc store_solid()
  template <typename T>
  auto store_solid(BasicRenderer<T>& renderer, const std::string& str, const color& fg)
      -> id_type
  {
    return store_solid(renderer, str.c_str(), fg);
  }

  /**
   * \brief Renders a UTF-8 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the foreground color of the rendered text.
   * \param bg the background color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_shaded()`
   */
  template <typename T>
  auto store_shaded(BasicRenderer<T>& renderer,
                    const char* str,
                    const color& fg,
                    const color& bg) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_shaded(str, fg, bg));
  }

  /// \copydoc store_shaded()
  template <typename T>
  auto store_shaded(BasicRenderer<T>& renderer,
                    const std::string& str,
                    const color& fg,
                    const color& bg) -> id_type
  {
    return store_shaded(renderer, str.c_str(), fg, bg);
  }

  /**
   * \brief Renders a UTF-8 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_blended()`
   */
  template <typename T>
  auto store_blended(BasicRenderer<T>& renderer, const char* str, const color& fg) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_blended(str, fg));
  }

  /// \copydoc store_blended()
  template <typename T>
  auto store_blended(BasicRenderer<T>& renderer, const std::string& str, const color& fg)
      -> id_type
  {
    return store_blended(renderer, str.c_str(), fg);
  }

  /**
   * \brief Renders a UTF-8 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_wrapped()`
   */
  template <typename T>
  auto store_wrapped(BasicRenderer<T>& renderer,
                     const char* str,
                     const color& fg,
                     const Uint32 wrap) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_wrapped(str, fg, wrap));
  }

  /// \copydoc store_wrapped()
  template <typename T>
  auto store_wrapped(BasicRenderer<T>& renderer,
                     const std::string& str,
                     const color& fg,
                     const Uint32 wrap) -> id_type
  {
    return store_wrapped(renderer, str.c_str(), fg, wrap);
  }

  /**
   * \brief Renders a Latin-1 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_solid_latin1()`
   */
  template <typename T>
  auto store_solid_latin1(BasicRenderer<T>& renderer, const char* str, const color& fg)
      -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_solid_latin1(str, fg));
  }

  /// \copydoc store_solid_latin1()
  template <typename T>
  auto store_solid_latin1(BasicRenderer<T>& renderer, const std::string& str, const color& fg)
      -> id_type
  {
    return store_solid_latin1(renderer, str.c_str(), fg);
  }

  /**
   * \brief Renders a Latin-1 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the foreground color of the rendered text.
   * \param bg the background color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_shaded_latin1()`
   */
  template <typename T>
  auto store_shaded_latin1(BasicRenderer<T>& renderer,
                           const char* str,
                           const color& fg,
                           const color& bg) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_shaded_latin1(str, fg, bg));
  }

  /// \copydoc store_shaded_latin1()
  template <typename T>
  auto store_shaded_latin1(BasicRenderer<T>& renderer,
                           const std::string& str,
                           const color& fg,
                           const color& bg) -> id_type
  {
    return store_shaded_latin1(renderer, str.c_str(), fg, bg);
  }

  /**
   * \brief Renders a Latin-1 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_blended_latin1()`
   */
  template <typename T>
  auto store_blended_latin1(BasicRenderer<T>& renderer, const char* str, const color& fg)
      -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_blended_latin1(str, fg));
  }

  /// \copydoc store_blended_latin1()
  template <typename T>
  auto store_blended_latin1(BasicRenderer<T>& renderer,
                            const std::string& str,
                            const color& fg) -> id_type
  {
    return store_blended_latin1(renderer, str.c_str(), fg);
  }

  /**
   * \brief Renders a Latin-1 string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_wrapped_latin1()`
   */
  template <typename T>
  auto store_wrapped_latin1(BasicRenderer<T>& renderer,
                            const char* str,
                            const color& fg,
                            const Uint32 wrap) -> id_type
  {
    assert(str);
    return store(renderer, mFont.render_wrapped_latin1(str, fg, wrap));
  }

  /// \copydoc store_wrapped_latin1()
  template <typename T>
  auto store_wrapped_latin1(BasicRenderer<T>& renderer,
                            const std::string& str,
                            const color& fg,
                            const Uint32 wrap) -> id_type
  {
    return store_wrapped_latin1(renderer, str.c_str(), fg, wrap);
  }

  /**
   * \brief Renders a Unicode string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_solid_unicode()`
   */
  template <typename T>
  auto store_solid_unicode(BasicRenderer<T>& renderer,
                           const UnicodeString& str,
                           const color& fg) -> id_type
  {
    return store(renderer, mFont.render_solid_unicode(str, fg));
  }

  /**
   * \brief Renders a Unicode string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the foreground color of the rendered text.
   * \param bg the background color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_shaded_unicode()`
   */
  template <typename T>
  auto store_shaded_unicode(BasicRenderer<T>& renderer,
                            const UnicodeString& str,
                            const color& fg,
                            const color& bg) -> id_type
  {
    return store(renderer, mFont.render_shaded_unicode(str, fg, bg));
  }

  /**
   * \brief Renders a Unicode string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_blended_unicode()`
   */
  template <typename T>
  auto store_blended_unicode(BasicRenderer<T>& renderer,
                             const UnicodeString& str,
                             const color& fg) -> id_type
  {
    return store(renderer, mFont.render_blended_unicode(str, fg));
  }

  /**
   * \brief Renders a Unicode string to a texture and caches it.
   *
   * \param renderer the renderer that will be used to create the string texture.
   * \param str the string that will be rendered and cached.
   * \param fg the color of the rendered text.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return the identifier assigned to the texture.
   *
   * \see `font::render_wrapped_unicode()`
   */
  template <typename T>
  auto store_wrapped_unicode(BasicRenderer<T>& renderer,
                             const UnicodeString& str,
                             const color& fg,
                             const Uint32 wrap) -> id_type
  {
    return store(renderer, mFont.render_wrapped_unicode(str, fg, wrap));
  }

  /// \} End of string caching functions

  /// \name String cache query functions
  /// \{

  /**
   * \brief Returns the cached string texture for an identifier, if there is one.
   *
   * \param id the identifier of the cached string.
   *
   * \return the cached string texture; a null pointer is returned if no match was found.
   */
  [[nodiscard]] auto find_string(const id_type id) const -> const Texture*
  {
    if (const auto iter = mStrings.find(id); iter != mStrings.end()) {
      return &iter->second;
    }
    else {
      return nullptr;
    }
  }

  /**
   * \brief Indicates whether there is a cached string associated with a specific identifier.
   *
   * \param id the identifier that will be checked.
   *
   * \return `true` if there is a cached string associated with the ID; `false` otherwise.
   */
  [[nodiscard]] auto has_string(const id_type id) const -> bool
  {
    return find_string(id) != nullptr;
  }

  /**
   * \brief Returns the cached rendered string associated with an identifier.
   *
   * \param id the identifier associated with the desired rendered string.
   *
   * \return the cached string texture.
   *
   * \throws exception if there is no cached string for the supplied identifier.
   *
   * \see `find_string()`
   */
  [[nodiscard]] auto get_string(const id_type id) const -> const Texture&
  {
    if (const auto* ptr = find_string(id)) {
      return *ptr;
    }
    else {
      throw exception{"Invalid font cache string identifier!"};
    }
  }

  /// \} End of string cache query functions

  /// \name Glyph caching functions
  /// \{

  /**
   * \brief Renders a glyph to a texture and caches it.
   *
   * \details This function has no effect if the glyph has already been cached, or if the glyph
   * is not provided by the underlying font.
   *
   * \param renderer the renderer that will be used.
   * \param glyph the glyph that will be cached.
   */
  template <typename T>
  void store_glyph(BasicRenderer<T>& renderer, const unicode_t glyph)
  {
    if (has_glyph(glyph) || !mFont.is_glyph_provided(glyph)) {
      return;
    }

    glyph_data data{make_glyph_texture(renderer, glyph), mFont.get_metrics(glyph).value()};
    mGlyphs.try_emplace(glyph, std::move(data));
  }

  /**
   * \brief Renders a range of glyphs to individual textures and caches them.
   *
   * \details The glyphs that will be cached are in the range [begin, end).
   *
   * \param renderer the renderer that will be used.
   * \param begin the first glyph that will be cached.
   * \param end the range terminator (will not be cached).
   *
   * \see `store_glyph()`
   * \see https://unicode-table.com/en/blocks/
   */
  template <typename T>
  void store_glyphs(BasicRenderer<T>& renderer, const unicode_t begin, const unicode_t end)
  {
    for (auto glyph = begin; glyph < end; ++glyph) {
      store_glyph(renderer, glyph);
    }
  }

  /**
   * \brief Stores the glyphs provided in the basic latin character range.
   *
   * \note The control characters are excluded.
   *
   * \param renderer the renderer that will be used.
   *
   * \see `store_glyphs()`
   */
  template <typename T>
  void store_basic_latin_glyphs(BasicRenderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/basic-latin/ */
    store_glyphs(renderer, 0x20, 0x7F);
  }

  /**
   * \brief Stores the glyphs provided in the Latin-1 supplement character range.
   *
   * \note The control characters are excluded.
   *
   * \param renderer the renderer that will be used.
   *
   * \see `store_glyphs()`
   */
  template <typename T>
  void store_latin1_supplement_glyphs(BasicRenderer<T>& renderer)
  {
    /* https://unicode-table.com/en/blocks/latin-1-supplement/ */
    store_glyphs(renderer, 0xA0, 0xFF + 0x1);
  }

  /**
   * \brief Stores the glyphs provided in the Latin-1 character range.
   *
   * \param renderer the renderer that will be used.
   *
   * \see `store_basic_latin_glyphs()`
   * \see `store_latin1_supplement_glyphs()`
   */
  template <typename T>
  void store_latin1_glyphs(BasicRenderer<T>& renderer)
  {
    store_basic_latin_glyphs(renderer);
    store_latin1_supplement_glyphs(renderer);
  }

  /// \} End of glyph caching functions

  /// \name Glyph cache query functions
  /// \{

  /**
   * \brief Returns the cached information associated with a glyph, if there is any.
   *
   * \param glyph the glyph that will be queried.
   *
   * \return the found glyph data; a null pointer is returned if no data was found.
   */
  [[nodiscard]] auto find_glyph(const unicode_t glyph) const -> const glyph_data*
  {
    if (const auto it = mGlyphs.find(glyph); it != mGlyphs.end()) {
      return &it->second;
    }
    else {
      return nullptr;
    }
  }

  /**
   * \brief Indicates whether a glyph has been cached.
   *
   * \param glyph the glyph that will be checked.
   *
   * \return `true` if the glyph has been cached; `false` otherwise.
   */
  [[nodiscard]] auto has_glyph(const unicode_t glyph) const noexcept -> bool
  {
    return find_glyph(glyph) != nullptr;
  }

  /**
   * \brief Returns the previously cached information associated with a glyph.
   *
   * \param glyph the glyph that will be queried.
   *
   * \return the cached glyph data.
   *
   * \throws exception if there is no data stored for the glyph.
   *
   * \see `find_glyph()`
   */
  [[nodiscard]] auto get_glyph(const unicode_t glyph) const -> const glyph_data&
  {
    if (const auto* ptr = find_glyph(glyph)) {
      return *ptr;
    }
    else {
      throw exception{"Invalid font cache glyph!"};
    }
  }

  /// \} End of glyph cache query functions

  /**
   * \brief Returns the underlying font instance.
   *
   * \return the associated font.
   */
  [[nodiscard]] auto get_font() noexcept -> font& { return mFont; }

  /// \copydoc get_font()
  [[nodiscard]] auto get_font() const noexcept -> const font& { return mFont; }

 private:
  font mFont;
  std::unordered_map<unicode_t, glyph_data> mGlyphs;
  std::unordered_map<id_type, Texture> mStrings;
  id_type mNextStringId{1};

  template <typename T>
  [[nodiscard]] auto make_glyph_texture(BasicRenderer<T>& renderer, const unicode_t glyph)
      -> Texture
  {
    return renderer.ToTexture(mFont.render_blended_glyph(glyph, renderer.GetColor()));
  }

  template <typename T>
  auto store(BasicRenderer<T>& renderer, Surface&& surface) -> id_type
  {
    const auto id = mNextStringId;
    assert(mStrings.find(id) == mStrings.end());

    mStrings.try_emplace(id, renderer.ToTexture(surface));
    ++mNextStringId;

    return id;
  }
};

/// \name Font cache functions
/// \{

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

/// \} End of font cache functions

/**
 * \brief Utility for handling fonts of various sizes.
 *
 * \details The main motivation behind this utility is the fact that it is common to load the
 * same font family in several different sizes. This class provides a simple API for
 * efficiently managing such pools of fonts.
 *
 * \details This class works by organizing different pools of fonts based on their file paths.
 * Which means that the same font, loaded from different file paths, will be put into different
 * pools.
 *
 * \note Despite the name, this class actually stores `font_cache` instances. However, you can
 * still simply extract the underlying `font` instances if you do not need the extra features
 * provided by the `font_cache` class.
 *
 * \see `font`
 * \see `font_cache`
 */
class font_bundle final {
 public:
  using id_type = std::size_t;
  using size_type = std::size_t;

  /**
   * \brief Loads a font in a specific size.
   *
   * \details It is safe to load a font that has already been previously loaded. Furthermore,
   * this function has no effect if there is already a font of the specified size stored in the
   * pool for the font family.
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

  /**
   * \brief Indicates whether or not there is a font pool associated with an ID.
   *
   * \param id the pool ID that will be checked.
   *
   * \return `true` if there is a font pool associated with the ID; `false` otherwise.
   */
  [[nodiscard]] auto contains(const id_type id) const -> bool
  {
    return mPools.find(id) != mPools.end();
  }

  /**
   * \brief Indicates whether there is a pool for the specified file path.
   *
   * \param path the file path that will be checked.
   *
   * \return `true` if a pool is found; `false` otherwise.
   */
  [[nodiscard]] auto contains(const std::string_view path) const -> bool
  {
    return get_id(path).has_value();
  }

  /**
   * \brief Indicates whether there is a font of a specific size in a pool.
   *
   * \details This function returns `false` if an invalid pool identifier is used.
   *
   * \param id the identifier associated with the pool that will be checked.
   * \param size the font size to look for.
   *
   * \return `true` if there is a font of the specific size in the pool; `false` otherwise.
   */
  [[nodiscard]] auto contains(const id_type id, const int size) const -> bool
  {
    if (const auto pack = mPools.find(id); pack != mPools.end()) {
      return pack->second.caches.find(size) != pack->second.caches.end();
    }
    else {
      return false;
    }
  }

  /**
   * \brief Returns a previously loaded font of a particular size from a pool.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font cache.
   *
   * \throws exception if the identifier is invalid or if there is no font of the specified
   * size.
   */
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

  /// \copydoc at()
  [[nodiscard]] auto at(const id_type id, const int size) const -> const font_cache&
  {
    return mPools.at(id).caches.at(size);
  }

  /**
   * \brief Returns a previously loaded font of a particular size from a pool.
   *
   * \note This function is provided as a shorthand, and simply calls `at()` and extracts the
   * font from the found font cache.
   *
   * \param id the identifier of the pool to query.
   * \param size the size of the desired font.
   *
   * \return the found font.
   *
   * \throws exception if the identifier is invalid or if there is no font of the specified
   * size.
   *
   * \see `at()`
   */
  [[nodiscard]] auto get_font(const id_type id, const int size) -> font&
  {
    return at(id, size).get_font();
  }

  /// \copydoc get_font()
  [[nodiscard]] auto get_font(const id_type id, const int size) const -> const font&
  {
    return at(id, size).get_font();
  }

  /**
   * \brief Returns the amount of fonts that have been loaded (including different sizes).
   *
   * \return the total amount of loaded individual fonts.
   *
   * \see `pool_count()`
   */
  [[nodiscard]] auto font_count() const noexcept -> size_type
  {
    size_type count = 0;

    for (const auto& [id, pack] : mPools) {
      count += pack.caches.size();
    }

    return count;
  }

  /**
   * \brief Returns the amount of loaded font pools, i.e. font faces irrespective of sizes.
   *
   * \return the number of font pools.
   *
   * \see `font_count()`
   */
  [[nodiscard]] auto pool_count() const -> size_type { return mPools.size(); }

 private:
  struct font_pool final {
    std::string path;
    std::unordered_map<int, font_cache> caches;  ///< Size -> Cache
  };

  std::unordered_map<id_type, font_pool> mPools;
  id_type mNextFontId{1};

  [[nodiscard]] auto get_id(const std::string_view path) const -> std::optional<id_type>
  {
    for (const auto& [id, pack] : mPools) {
      if (!pack.caches.empty()) {
        if (pack.path == path) {
          return id;
        }
      }
    }

    return std::nullopt;
  }
};

/// \name Font bundle functions
/// \{

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

/// \} End of font bundle functions

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_NO_SDL_TTF
#endif  // CENTURION_FONT_HPP_