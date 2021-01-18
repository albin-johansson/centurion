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

#ifndef CENTURION_RENDERER_HEADER
#define CENTURION_RENDERER_HEADER

#include <SDL.h>

#include <cassert>        // assert
#include <cstddef>        // size_t
#include <memory>         // unique_ptr
#include <optional>       // optional
#include <ostream>        // ostream
#include <string>         // string
#include <type_traits>    // enable_if_t, true_type, false_type, conditional_t
#include <unordered_map>  // unordered_map
#include <utility>        // move, forward, pair

#include "blend_mode.hpp"
#include "centurion_cfg.hpp"
#include "color.hpp"
#include "colors.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/convert_bool.hpp"
#include "detail/owner_handle_api.hpp"
#include "font.hpp"
#include "font_cache.hpp"
#include "integers.hpp"
#include "not_null.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

template <typename B>
class basic_renderer;

/**
 * \typedef renderer
 *
 * \brief Represents an owning renderer.
 *
 * \since 5.0.0
 */
using renderer = basic_renderer<std::true_type>;

/**
 * \typedef renderer_handle
 *
 * \brief Represents a non-owning renderer.
 *
 * \since 5.0.0
 */
using renderer_handle = basic_renderer<std::false_type>;

/**
 * \class basic_renderer
 *
 * \brief Provides hardware-accelerated 2D-rendering.
 *
 * \tparam B `std::true_type` for owning renderers; `std::false_type` for
 * non-owning renderers.
 *
 * \since 5.0.0
 *
 * \see `renderer`
 * \see `renderer_handle`
 *
 * \headerfile renderer.hpp
 */
template <typename B>
class basic_renderer final
{
  [[nodiscard]] constexpr static auto default_flags() noexcept
      -> SDL_RendererFlags
  {
    return static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
                                          SDL_RENDERER_PRESENTVSYNC);
  }

 public:
  // clang-format off
  /**
   * \brief Creates a renderer based on a pointer to an SDL renderer.
   *
   * \note The supplied pointer will be claimed by the renderer if the created
   * renderer is owning.
   *
   * \param renderer a pointer to the associated SDL renderer.
   *
   * \since 3.0.0
   */
  explicit basic_renderer(SDL_Renderer* renderer) noexcept(!detail::is_owning<B>())
      : m_renderer{renderer}
  {
    if constexpr (detail::is_owning<B>()) {
      if (!get()) {
        throw exception{"Cannot create renderer from null pointer!"};
      }
    }
  }
  // clang-format on

  /**
   * \brief Creates an owning renderer based on the supplied window.
   *
   * \param window the associated window instance.
   * \param flags the renderer flags that will be used.
   *
   * \throws sdl_error if something goes wrong when creating the renderer.
   *
   * \since 4.0.0
   */
  template <typename Window, typename BB = B, detail::is_owner<BB> = true>
  explicit basic_renderer(const Window& window,
                          const SDL_RendererFlags flags = default_flags())
      : m_renderer{SDL_CreateRenderer(window.get(), -1, flags)}
  {
    if (!get()) {
      throw sdl_error{};
    }

    set_blend_mode(blend_mode::blend);
    set_color(colors::black);
    set_logical_integer_scale(false);
  }

  template <typename BB = B, detail::is_handle<BB> = true>
  explicit basic_renderer(const renderer& owner) noexcept
      : m_renderer{owner.get()}
  {}

  /**
   * \brief Clears the rendering target with the currently selected color.
   *
   * \since 3.0.0
   */
  void clear() noexcept
  {
    SDL_RenderClear(get());
  }

  /**
   * \brief Clears the rendering target with the specified color.
   *
   * \note This function doesn't change the currently selected color.
   *
   * \param color the color that will be used to clear the rendering target.
   *
   * \since 5.0.0
   */
  void clear_with(const color& color) noexcept
  {
    const auto oldColor = get_color();

    set_color(color);
    clear();

    set_color(oldColor);
  }

  /**
   * \brief Applies the previous rendering calls to the rendering target.
   *
   * \since 3.0.0
   */
  void present() noexcept
  {
    SDL_RenderPresent(get());
  }

  /**
   * \name Primitive rendering
   * Methods for rendering rectangles and lines.
   */
  ///\{

  /**
   * \brief Renders the outline of a rectangle in the currently selected color.
   *
   * \tparam U the representation type used by the rectangle.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \since 4.0.0
   */
  template <typename U>
  void draw_rect(const basic_rect<U>& rect) noexcept
  {
    if constexpr (basic_rect<U>::isIntegral) {
      SDL_RenderDrawRect(get(), rect.data());
    } else {
      SDL_RenderDrawRectF(get(), rect.data());
    }
  }

  /**
   * \brief Renders a filled rectangle in the currently selected color.
   *
   * \tparam U the representation type used by the rectangle.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \since 4.0.0
   */
  template <typename U>
  void fill_rect(const basic_rect<U>& rect) noexcept
  {
    if constexpr (basic_rect<U>::isIntegral) {
      SDL_RenderFillRect(get(), rect.data());
    } else {
      SDL_RenderFillRectF(get(), rect.data());
    }
  }

  /**
   * \brief Fills the entire rendering target with the currently selected color.
   *
   * \details This function is different from `clear()` and `clear_with()` in
   * that it can be used as an intermediate rendering command (just like all
   * rendering functions). An example of a use case of this function could be
   * for rendering a transparent background for game menus.
   *
   * \since 5.1.0
   */
  void fill() noexcept
  {
    fill_rect<int>({{}, output_size()});
  }

  /**
   * \brief Fills the entire rendering target with the specified color.
   *
   * \note This function does not affect the currently set color.
   *
   * \copydetails fill()
   */
  void fill_with(const color& color) noexcept
  {
    const auto oldColor = get_color();

    set_color(color);
    fill();

    set_color(oldColor);
  }

  /**
   * \brief Renders a line between the supplied points, in the currently
   * selected color.
   *
   * \tparam U The representation type used by the points.
   *
   * \param start the start point of the line.
   * \param end the end point of the line.
   *
   * \since 4.0.0
   */
  template <typename U>
  void draw_line(const basic_point<U>& start,
                 const basic_point<U>& end) noexcept
  {
    if constexpr (basic_point<U>::isIntegral) {
      SDL_RenderDrawLine(get(), start.x(), start.y(), end.x(), end.y());
    } else {
      SDL_RenderDrawLineF(get(), start.x(), start.y(), end.x(), end.y());
    }
  }

  /**
   * \brief Renders a collection of lines.
   *
   * \details This function requires the the `Container` type provides the
   * public member `value_type` and subsequently, that the `value_type`
   * in turn provides a `value_type` member. The former would correspond to
   * the actual point type, and the latter corresponds to either `int` or
   * `float`.
   *
   * \warning `Container` *must* be a collection that stores its data
   * contiguously! The behaviour of this function is undefined if this condition
   * isn't met.
   *
   * \tparam Container the container type. Must store its elements
   * contiguously, such as `std::vector` or `std::array`.
   *
   * \param container the container that holds the points that will be used
   * to render the line.
   *
   * \since 5.0.0
   */
  template <typename Container>
  void draw_lines(const Container& container) noexcept
  {
    using point_t = typename Container::value_type;  // a point of int or float
    using value_t = typename point_t::value_type;    // either int or float

    if (!container.empty()) {
      const auto& front = container.front();
      const auto* first = front.data();
      const auto count = static_cast<int>(container.size());

      if constexpr (std::is_same_v<value_t, int>) {
        SDL_RenderDrawLines(get(), first, count);
      } else {
        SDL_RenderDrawLinesF(get(), first, count);
      }
    }
  }

  ///\}  // end of primitive rendering

  /**
   * \name Text rendering
   * Methods for rendering text encoded in UTF-8, LATIN-1 or UNICODE.
   */
  ///\{

  /**
   * \brief Creates and returns a texture of blended UTF-8 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * \param str the UTF-8 text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUTF8_Blended`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_utf8(not_null<czstring> str,
                                         const font& font) -> texture
  {
    assert(str);
    return render_text(
        TTF_RenderUTF8_Blended(font.get(), str, get_color().get()));
  }

  /**
   * \brief Creates and returns a texture of blended and wrapped UTF-8 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This function will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * \param str the UTF-8 text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * \param font the font that the text will be rendered in.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUTF8_Blended_Wrapped`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_utf8(not_null<czstring> str,
                                                 const font& font,
                                                 const u32 wrap) -> texture
  {
    assert(str);
    return render_text(TTF_RenderUTF8_Blended_Wrapped(font.get(),
                                                      str,
                                                      get_color().get(),
                                                      wrap));
  }

  /**
   * \brief Creates and returns a texture of shaded UTF-8 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * function when you want nice text, and can live with a box around it.
   *
   * \param str the UTF-8 text that will be rendered.
   * \param font the font that the text will be rendered in.
   * \param background the background color used for the box.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUTF8_Shaded`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_shaded_utf8(not_null<czstring> str,
                                        const font& font,
                                        const color& background) -> texture
  {
    assert(str);
    return render_text(TTF_RenderUTF8_Shaded(font.get(),
                                             str,
                                             get_color().get(),
                                             background.get()));
  }

  /**
   * \brief Creates and returns a texture of solid UTF-8 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this function
   * when quality isn't as big of a concern and speed is important.
   *
   * \param str the UTF-8 text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderText_Solid`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_solid_utf8(not_null<czstring> str, const font& font)
      -> texture
  {
    assert(str);
    return render_text(
        TTF_RenderUTF8_Solid(font.get(), str, get_color().get()));
  }

  /**
   * \brief Creates and returns a texture of blended Latin-1 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * \param str the Latin-1 text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderText_Blended`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_latin1(not_null<czstring> str,
                                           const font& font) -> texture
  {
    assert(str);
    return render_text(
        TTF_RenderText_Blended(font.get(), str, get_color().get()));
  }

  /**
   * \brief Creates and returns a texture of blended and wrapped Latin-1 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This function will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * \param str the Latin-1 text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * \param font the font that the text will be rendered in.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderText_Blended_Wrapped`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_latin1(not_null<czstring> str,
                                                   const font& font,
                                                   const u32 wrap) -> texture
  {
    assert(str);
    return render_text(TTF_RenderText_Blended_Wrapped(font.get(),
                                                      str,
                                                      get_color().get(),
                                                      wrap));
  }

  /**
   * \brief Creates and returns a texture of shaded Latin-1 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * function when you want nice text, and can live with a box around it.
   *
   * \param str the Latin-1 text that will be rendered.
   * \param font the font that the text will be rendered in.
   * \param background the background color used for the box.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderText_Shaded`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_shaded_latin1(not_null<czstring> str,
                                          const font& font,
                                          const color& background) -> texture
  {
    assert(str);
    return render_text(TTF_RenderText_Shaded(font.get(),
                                             str,
                                             get_color().get(),
                                             background.get()));
  }

  /**
   * \brief Creates and returns a texture of solid Latin-1 text.
   *
   * \pre `str` can't be null.
   *
   * \details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this function
   * when quality isn't as big of a concern and speed is important.
   *
   * \param str the Latin-1 text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderText_Solid`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_solid_latin1(not_null<czstring> str,
                                         const font& font) -> texture
  {
    assert(str);
    return render_text(
        TTF_RenderText_Solid(font.get(), str, get_color().get()));
  }

  /**
   * \brief Creates and returns a texture of blended Unicode text.
   *
   * \details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * \param str the Unicode text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUNICODE_Blended`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_unicode(const unicode_string& str,
                                            const font& font) -> texture
  {
    return render_text(
        TTF_RenderUNICODE_Blended(font.get(), str.data(), get_color().get()));
  }

  /**
   * \brief Creates and returns a texture of blended and wrapped Unicode text.
   *
   * \details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This function will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * \param str the Unicode text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * \param font the font that the text will be rendered in.
   * \param wrap the width in pixels after which the text will be wrapped.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUNICODE_Blended_Wrapped`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_unicode(const unicode_string& str,
                                                    const font& font,
                                                    const u32 wrap) -> texture
  {
    return render_text(TTF_RenderUNICODE_Blended_Wrapped(font.get(),
                                                         str.data(),
                                                         get_color().get(),
                                                         wrap));
  }

  /**
   * \brief Creates and returns a texture of shaded Unicode text.
   *
   * \details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * function when you want nice text, and can live with a box around it.
   *
   * \param str the Unicode text that will be rendered.
   * \param font the font that the text will be rendered in.
   * \param background the background color used for the box.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUNICODE_Shaded`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_shaded_unicode(const unicode_string& str,
                                           const font& font,
                                           const color& background) -> texture
  {
    return render_text(TTF_RenderUNICODE_Shaded(font.get(),
                                                str.data(),
                                                get_color().get(),
                                                background.get()));
  }

  /**
   * \brief Creates and returns a texture of solid Unicode text.
   *
   * \details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This function is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this function
   * when quality isn't as big of a concern and speed is important.
   *
   * \param str the Unicode text that will be rendered.
   * \param font the font that the text will be rendered in.
   *
   * \return a texture that contains the rendered text.
   *
   * \see `TTF_RenderUNICODE_Solid`
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto render_solid_unicode(const unicode_string& str,
                                          const font& font) -> texture
  {
    return render_text(
        TTF_RenderUNICODE_Solid(font.get(), str.data(), get_color().get()));
  }

  /**
   * \brief Renders a glyph at the specified position.
   *
   * \note This function has no effect if the glyph doesn't exist in the cache.
   *
   * \param cache the font cache that will be used.
   * \param glyph the glyph, in unicode, that will be rendered.
   * \param position the position of the rendered glyph.
   *
   * \return the x-coordinate of the next glyph to be rendered after the
   * current glyph, or the same x-coordinate if no glyph was rendered.
   *
   * \since 5.0.0
   */
  auto render_glyph(const font_cache& cache,
                    const unicode glyph,
                    const ipoint& position) -> int
  {
    if (const auto* data = cache.try_at(glyph)) {
      const auto& [texture, metrics] = *data;

      const auto outline = cache.get_font().outline();

      // SDL_ttf handles the y-axis alignment
      const auto x = position.x() + metrics.minX - outline;
      const auto y = position.y() - outline;

      render(texture, ipoint{x, y});

      return x + metrics.advance;
    } else {
      return position.x();
    }
  }

  /**
   * \brief Renders a string.
   *
   * \details This function will not apply any clever conversions on the
   * supplied string. The string is literally iterated, character-by-character,
   * and each character is rendered using the `render_glyph` function.
   *
   * \pre Every character in the string must correspond to a valid Unicode
   * glyph.
   *
   * \note This function is sensitive to newline-characters, and will render
   * strings that contain such characters appropriately.
   *
   * \tparam String the type of the string, must be iterable and provide
   * `unicode` characters.
   *
   * \param cache the font cache that will be used.
   * \param str the string that will be rendered.
   * \param position the position of the rendered text.
   *
   * \since 5.0.0
   */
  template <typename String>
  void render_text(const font_cache& cache, const String& str, ipoint position)
  {
    const auto& font = cache.get_font();

    const auto originalX = position.x();
    const auto lineSkip = font.line_skip();

    for (const unicode glyph : str) {
      if (glyph == '\n') {
        position.set_x(originalX);
        position.set_y(position.y() + lineSkip);
      } else {
        const auto x = render_glyph(cache, glyph, position);
        position.set_x(x);
      }
    }
  }

  ///\}  // end of text rendering

  /**
   * \name Texture rendering
   * Methods for rendering hardware-accelerated textures.
   */
  ///\{

  /**
   * \brief Renders a texture at the specified position.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the point.
   *
   * \param texture the texture that will be rendered.
   * \param position the position of the rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P, typename U>
  void render(const basic_texture<U>& texture,
              const basic_point<P>& position) noexcept
  {
    if constexpr (basic_point<P>::isFloating) {
      const auto size = cast<cen::farea>(texture.size());
      const SDL_FRect dst{position.x(), position.y(), size.width, size.height};
      SDL_RenderCopyF(get(), texture.get(), nullptr, &dst);
    } else {
      const SDL_Rect dst{position.x(),
                         position.y(),
                         texture.width(),
                         texture.height()};
      SDL_RenderCopy(get(), texture.get(), nullptr, &dst);
    }
  }

  /**
   * \brief Renders a texture according to the specified rectangle.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param destination the position and size of the rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P, typename U>
  void render(const basic_texture<U>& texture,
              const basic_rect<P>& destination) noexcept
  {
    if constexpr (basic_rect<P>::isFloating) {
      SDL_RenderCopyF(get(), texture.get(), nullptr, destination.data());
    } else {
      SDL_RenderCopy(get(), texture.get(), nullptr, destination.data());
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \remarks This should be your preferred function of rendering textures. This
   * function is efficient and simple.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position and size of the rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P, typename U>
  void render(const basic_texture<U>& texture,
              const irect& source,
              const basic_rect<P>& destination) noexcept
  {
    if constexpr (basic_rect<P>::isFloating) {
      SDL_RenderCopyF(get(), texture.get(), source.data(), destination.data());
    } else {
      SDL_RenderCopy(get(), texture.get(), source.data(), destination.data());
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position and size of the rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   *
   * \since 4.0.0
   */
  template <typename P, typename U>
  void render(const basic_texture<U>& texture,
              const irect& source,
              const basic_rect<P>& destination,
              const double angle) noexcept
  {
    if constexpr (basic_rect<P>::isFloating) {
      SDL_RenderCopyExF(get(),
                        texture.get(),
                        source.data(),
                        destination.data(),
                        angle,
                        nullptr,
                        SDL_FLIP_NONE);
    } else {
      SDL_RenderCopyEx(get(),
                       texture.get(),
                       source.data(),
                       destination.data(),
                       angle,
                       nullptr,
                       SDL_FLIP_NONE);
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam R the representation type used by the destination rectangle.
   * \tparam P the representation type used by the center point.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position and size of the rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * \param center specifies the point around which the rendered texture will
   * be rotated.
   *
   * \since 4.0.0
   */
  template <typename R, typename P, typename U>
  void render(const basic_texture<U>& texture,
              const irect& source,
              const basic_rect<R>& destination,
              const double angle,
              const basic_point<P>& center) noexcept
  {
    static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                                 typename basic_point<P>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<R>::isFloating) {
      SDL_RenderCopyExF(get(),
                        texture.get(),
                        source.data(),
                        destination.data(),
                        angle,
                        center.data(),
                        SDL_FLIP_NONE);
    } else {
      SDL_RenderCopyEx(get(),
                       texture.get(),
                       source.data(),
                       destination.data(),
                       angle,
                       center.data(),
                       SDL_FLIP_NONE);
    }
  }

  /**
   * \brief Renders a texture.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam R the representation type used by the destination rectangle.
   * \tparam P the representation type used by the center point.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position and size of the rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * \param center specifies the point around which the rendered texture will be
   * rotated.
   * \param flip specifies how the rendered texture will be flipped.
   *
   * \since 4.0.0
   */
  template <typename R, typename P, typename U>
  void render(const basic_texture<U>& texture,
              const irect& source,
              const basic_rect<R>& destination,
              const double angle,
              const basic_point<P>& center,
              const SDL_RendererFlip flip) noexcept
  {
    static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                                 typename basic_point<P>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<R>::isFloating) {
      SDL_RenderCopyExF(get(),
                        texture.get(),
                        source.data(),
                        destination.data(),
                        angle,
                        center.data(),
                        flip);
    } else {
      SDL_RenderCopyEx(get(),
                       texture.get(),
                       source.data(),
                       destination.data(),
                       angle,
                       center.data(),
                       flip);
    }
  }

  ///\}  // end of texture rendering

  /**
   * \name Translated rendering
   * \brief Translated rendering API, only available for owning renderers.
   */
  ///\{

  /**
   * \brief Sets the translation viewport that will be used by the renderer.
   *
   * \details This function should be called before calling any of the `_t`
   * rendering methods, for automatic translation.
   *
   * \param viewport the rectangle that will be used as the translation
   * viewport.
   *
   * \since 3.0.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  void set_translation_viewport(const frect& viewport) noexcept
  {
    m_renderer.translation = viewport;
  }

  /**
   * \brief Returns the translation viewport that is currently being used.
   *
   * \details Set to (0, 0, 0, 0) by default.
   *
   * \return the translation viewport that is currently being used.
   *
   * \since 3.0.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto translation_viewport() const noexcept -> const frect&
  {
    return m_renderer.translation;
  }

  /**
   * \brief Renders an outlined rectangle in the currently selected color.
   *
   * \details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * \tparam R the representation type used by the rectangle.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \since 4.1.0
   */
  template <typename R, typename BB = B, detail::is_owner<BB> = true>
  void draw_rect_t(const basic_rect<R>& rect) noexcept
  {
    draw_rect(translate(rect));
  }

  /**
   * \brief Renders a filled rectangle in the currently selected color.
   *
   * \details The rendered rectangle will be translated using the current
   * translation viewport.
   *
   * \tparam R the representation type used by the rectangle.
   *
   * \param rect the rectangle that will be rendered.
   *
   * \since 4.1.0
   */
  template <typename R, typename BB = B, detail::is_owner<BB> = true>
  void fill_rect_t(const basic_rect<R>& rect) noexcept
  {
    fill_rect(translate(rect));
  }

  /**
   * \brief Renders a texture at the specified position.
   *
   * \details The rendered texture will be translated using the translation
   * viewport.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P The representation type used by the point.
   *
   * \param texture the texture that will be rendered.
   * \param position the position (pre-translation) of the rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const basic_point<P>& position) noexcept
  {
    render(texture, translate(position));
  }

  /**
   * \brief Renders a texture according to the specified rectangle.
   *
   * \details The rendered texture will be translated using the translation
   * viewport.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the destination rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param destination the position (pre-translation) and size of the
   * rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const basic_rect<P>& destination) noexcept
  {
    render(texture, translate(destination));
  }

  /**
   * \brief Renders a texture.
   *
   * \details The rendered texture will be translated using the translation
   * viewport.
   *
   * \remarks This should be your preferred function of rendering textures. This
   * function is efficient and simple.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the destination rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position (pre-translation) and size of the
   * rendered texture.
   *
   * \since 4.0.0
   */
  template <typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const irect& source,
                const basic_rect<P>& destination) noexcept
  {
    render(texture, source, translate(destination));
  }

  /**
   * \brief Renders a texture.
   *
   * \details The rendered texture will be translated using the translation
   * viewport.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam P the representation type used by the destination rectangle.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position (pre-translation) and size of the
   * rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   *
   * \since 4.0.0
   */
  template <typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const irect& source,
                const basic_rect<P>& destination,
                const double angle) noexcept
  {
    render(texture, source, translate(destination), angle);
  }

  /**
   * \brief Renders a texture.
   *
   * \details The rendered texture will be translated using the translation
   * viewport.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam R the representation type used by the destination rectangle.
   * \tparam P the representation type used by the center-of-rotation point.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position (pre-translation) and size of the
   * rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * \param center specifies the point around which the rendered texture will
   * be rotated.
   *
   * \since 4.0.0
   */
  template <typename R,
            typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const irect& source,
                const basic_rect<R>& destination,
                const double angle,
                const basic_point<P>& center) noexcept
  {
    render(texture, source, translate(destination), angle, center);
  }

  /**
   * \brief Renders a texture.
   *
   * \tparam U the ownership tag of the texture.
   * \tparam R the representation type used by the destination rectangle.
   * \tparam P the representation type used by the center-of-rotation point.
   *
   * \param texture the texture that will be rendered.
   * \param source the cutout out of the texture that will be rendered.
   * \param destination the position (pre-translation) and size of the
   * rendered texture.
   * \param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * \param center specifies the point around which the rendered texture will
   * be rotated.
   * \param flip specifies how the rendered texture will be flipped.
   *
   * \since 4.0.0
   */
  template <typename R,
            typename P,
            typename U,
            typename BB = B,
            detail::is_owner<BB> = true>
  void render_t(const basic_texture<U>& texture,
                const irect& source,
                const basic_rect<R>& destination,
                const double angle,
                const basic_point<P>& center,
                const SDL_RendererFlip flip) noexcept
  {
    render(texture, source, translate(destination), angle, center, flip);
  }

  ///\} // end of translated rendering

  /**
   * \name Font handling
   * \brief Font handling API, only available for owning renderers.
   */
  ///\{

  /**
   * \brief Adds a font to the renderer.
   *
   * \note This function overwrites any previously stored font associated
   * with the specified ID.
   *
   * \param id the key that will be associated with the font.
   * \param font the font that will be added.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  void add_font(const std::size_t id, font&& font)
  {
    auto& fonts = m_renderer.fonts;
    if (fonts.find(id) != fonts.end()) {
      remove_font(id);
    }
    fonts.emplace(id, std::move(font));
  }

  /**
   * \brief Creates a font and adds it to the renderer.
   *
   * \note This function overwrites any previously stored font associated
   * with the specified ID.
   *
   * \tparam Args the types of the arguments that will be forwarded.
   *
   * \param id the key that will be associated with the font.
   * \param args the arguments that will be forwarded to the `font` constructor.
   *
   * \since 5.0.0
   */
  template <typename... Args, typename BB = B, detail::is_owner<BB> = true>
  void emplace_font(const std::size_t id, Args&&... args)
  {
    auto& fonts = m_renderer.fonts;
    if (fonts.find(id) != fonts.end()) {
      remove_font(id);
    }
    fonts.try_emplace(id, std::forward<Args>(args)...);
  }

  /**
   * \brief Removes the font associated with the specified key.
   *
   * \details This function has no effect if there is no font associated with
   * the specified key.
   *
   * \param id the key associated with the font that will be removed.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  void remove_font(const std::size_t id)
  {
    m_renderer.fonts.erase(id);
  }

  /**
   * \brief Returns the font associated with the specified name.
   *
   * \pre There must be a font associated with the specified ID.
   *
   * \param id the key associated with the desired font.
   *
   * \return the font associated with the specified name.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto get_font(const std::size_t id) -> font&
  {
    return m_renderer.fonts.at(id);
  }

  /**
   * \copydoc get_font
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto get_font(const std::size_t id) const -> const font&
  {
    return m_renderer.fonts.at(id);
  }

  /**
   * \brief Indicates whether or not the renderer has a font associated with
   * the specified key.
   *
   * \param id the key that will be checked.
   *
   * \return `true` if the renderer has a font associated with the key;
   * `false` otherwise.
   *
   * \since 4.1.0
   */
  template <typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto has_font(const std::size_t id) const noexcept -> bool
  {
    return static_cast<bool>(m_renderer.fonts.count(id));
  }

  ///\} // end of font handling

  /**
   * \brief Sets the color that will be used by the renderer.
   *
   * \param color the color that will be used by the renderer.
   *
   * \since 3.0.0
   */
  void set_color(const color& color) noexcept
  {
    SDL_SetRenderDrawColor(get(),
                           color.red(),
                           color.green(),
                           color.blue(),
                           color.alpha());
  }

  /**
   * \brief Sets the clipping area rectangle.
   *
   * \details Clipping is disabled by default.
   *
   * \param area the clip area rectangle; or `std::nullopt` to disable clipping.
   *
   * \since 3.0.0
   */
  void set_clip(const std::optional<irect> area) noexcept
  {
    if (area) {
      SDL_RenderSetClipRect(get(), area->data());
    } else {
      SDL_RenderSetClipRect(get(), nullptr);
    }
  }

  /**
   * \brief Sets the viewport that will be used by the renderer.
   *
   * \param viewport the viewport that will be used by the renderer.
   *
   * \since 3.0.0
   */
  void set_viewport(const irect& viewport) noexcept
  {
    SDL_RenderSetViewport(get(), viewport.data());
  }

  /**
   * \brief Sets the blend mode that will be used by the renderer.
   *
   * \param mode the blend mode that will be used by the renderer.
   *
   * \since 3.0.0
   */
  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetRenderDrawBlendMode(get(), static_cast<SDL_BlendMode>(mode));
  }

  /**
   * \brief Sets the rendering target of the renderer.
   *
   * \details The supplied texture must support being a render target.
   * Otherwise, this function will reset the render target.
   *
   * \param target a pointer to the new target texture; `nullptr` indicates
   * that the default rendering target should be used.
   *
   * \since 3.0.0
   */
  void set_target(const texture* target) noexcept
  {
    if (target && target->is_target()) {
      SDL_SetRenderTarget(get(), target->get());
    } else {
      SDL_SetRenderTarget(get(), nullptr);
    }
  }

  /**
   * \brief Sets the rendering scale.
   *
   * \note This function has no effect if any of the arguments aren't
   * greater than zero.
   *
   * \param xScale the x-axis scale that will be used.
   * \param yScale the y-axis scale that will be used.
   *
   * \since 3.0.0
   */
  void set_scale(const float xScale, const float yScale) noexcept
  {
    if ((xScale > 0) && (yScale > 0)) {
      SDL_RenderSetScale(get(), xScale, yScale);
    }
  }

  /**
   * \brief Sets the logical size used by the renderer.
   *
   * \details This function is useful for resolution-independent rendering.
   *
   * \remarks This is also known as *virtual size* in other frameworks.
   *
   * \note This function has no effect if either of the supplied dimensions
   * aren't greater than zero.
   *
   * \param size the logical width and height that will be used.
   *
   * \since 3.0.0
   */
  void set_logical_size(const iarea& size) noexcept
  {
    if ((size.width >= 0) && (size.height >= 0)) {
      SDL_RenderSetLogicalSize(get(), size.width, size.height);
    }
  }

  /**
   * \brief Sets whether or not to force integer scaling for the logical
   * viewport.
   *
   * \details By default, this property is set to false. This function can be
   * useful to combat visual artefacts when doing floating-point rendering.
   *
   * \param enabled `true` if integer scaling should be used; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_logical_integer_scale(const bool enabled) noexcept
  {
    SDL_RenderSetIntegerScale(get(), detail::convert_bool(enabled));
  }

  /**
   * \brief Returns a handle to the current render target.
   *
   * \return a handle to the current render target; empty if using the default
   * target.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_render_target() noexcept -> texture_handle
  {
    return texture_handle{SDL_GetRenderTarget(get())};
  }

  /**
   * \brief Returns the logical width that the renderer uses.
   *
   * \details By default, this property is set to 0.
   *
   * \return the logical width that the renderer uses.
   *
   * \see renderer::logical_size
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int
  {
    int width{};
    SDL_RenderGetLogicalSize(get(), &width, nullptr);
    return width;
  }

  /**
   * \brief Returns the logical height that the renderer uses.
   *
   * \details By default, this property is set to 0.
   *
   * \return the logical height that the renderer uses.
   *
   * \see renderer::logical_size
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int
  {
    int height{};
    SDL_RenderGetLogicalSize(get(), nullptr, &height);
    return height;
  }

  /**
   * \brief Returns the size of the logical (virtual) viewport.
   *
   * \note calling this function once is faster than calling both
   * `logical_width` and `logical_height` for obtaining the size.
   *
   * \return the size of the logical (virtual) viewport.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto logical_size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_RenderGetLogicalSize(get(), &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the x-axis scale that the renderer uses.
   *
   * \return the x-axis scale that the renderer uses.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto x_scale() const noexcept -> float
  {
    float xScale{};
    SDL_RenderGetScale(get(), &xScale, nullptr);
    return xScale;
  }

  /**
   * \brief Returns the y-axis scale that the renderer uses.
   *
   * \return the y-axis scale that the renderer uses.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto y_scale() const noexcept -> float
  {
    float yScale{};
    SDL_RenderGetScale(get(), nullptr, &yScale);
    return yScale;
  }

  /**
   * \brief Returns the x- and y-scale used by the renderer.
   *
   * \note calling this function once is faster than calling both `x_scale`
   * and `y_scale` for obtaining the scale.
   *
   * \return the x- and y-scale used by the renderer.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto scale() const noexcept -> std::pair<float, float>
  {
    float xScale{};
    float yScale{};
    SDL_RenderGetScale(get(), &xScale, &yScale);
    return {xScale, yScale};
  }

  /**
   * \brief Returns the current clipping rectangle, if there is one active.
   *
   * \return the current clipping rectangle; or `std::nullopt` if there is none.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> std::optional<irect>
  {
    irect rect{};
    SDL_RenderGetClipRect(get(), rect.data());
    if (!rect.has_area()) {
      return std::nullopt;
    } else {
      return rect;
    }
  }

  /**
   * \brief Returns information about the renderer.
   *
   * \return information about the renderer; `std::nullopt` if something went
   * wrong.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto info() const noexcept -> std::optional<SDL_RendererInfo>
  {
    SDL_RendererInfo info{};
    const auto result = SDL_GetRendererInfo(get(), &info);
    if (result == 0) {
      return info;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the output width of the renderer.
   *
   * \return the output width of the renderer.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto output_width() const noexcept -> int
  {
    int width{};
    SDL_GetRendererOutputSize(get(), &width, nullptr);
    return width;
  }

  /**
   * \brief Returns the output height of the renderer.
   *
   * \return the output height of the renderer.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto output_height() const noexcept -> int
  {
    int height{};
    SDL_GetRendererOutputSize(get(), nullptr, &height);
    return height;
  }

  /**
   * \brief Returns the output size of the renderer.
   *
   * \note calling this function once is faster than calling `output_width`
   * and `output_height` for obtaining the output size.
   *
   * \return the current output size of the renderer.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto output_size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_GetRendererOutputSize(get(), &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the blend mode that is being used by the renderer.
   *
   * \return the blend mode that is being used.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetRenderDrawBlendMode(get(), &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * \name Flag-related queries.
   *
   * \brief Methods for obtaining information about the window flags.
   */
  ///\{

  /**
   * \brief Returns a bit mask of the current renderer flags.
   *
   * \note There are multiple other methods for checking if a flag is set,
   * such as `is_vsync_enabled` or `is_accelerated`, that are nicer to use than
   * this function.
   *
   * \return a bit mask of the current renderer flags.
   *
   * \see `SDL_RendererFlags`
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto flags() const noexcept -> u32
  {
    SDL_RendererInfo info{};
    SDL_GetRendererInfo(get(), &info);
    return info.flags;
  }

  /**
   * \brief Indicates whether or not the `present` function is synced with
   * the refresh rate of the screen.
   *
   * \return `true` if vsync is enabled; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_vsync_enabled() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_RENDERER_PRESENTVSYNC);
  }

  /**
   * \brief Indicates whether or not the renderer is hardware accelerated.
   *
   * \return `true` if the renderer is hardware accelerated; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_accelerated() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_RENDERER_ACCELERATED);
  }

  /**
   * \brief Indicates whether or not the renderer is using software rendering.
   *
   * \return `true` if the renderer is software-based; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_software_based() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_RENDERER_SOFTWARE);
  }

  /**
   * \brief Indicates whether or not the renderer supports rendering to a
   * target texture.
   *
   * \return `true` if the renderer supports target texture rendering; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto supports_target_textures() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_RENDERER_TARGETTEXTURE);
  }

  ///\} // end of flag queries

  /**
   * \brief Indicates whether or not the renderer uses integer scaling values
   * for logical viewports.
   *
   * \details By default, this property is set to false.
   *
   * \return `true` if the renderer uses integer scaling for logical
   * viewports; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_using_integer_logical_scaling() const noexcept -> bool
  {
    return SDL_RenderGetIntegerScale(get());
  }

  /**
   * \brief Indicates whether or not clipping is enabled.
   *
   * \details This is disabled by default.
   *
   * \return `true` if clipping is enabled; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_clipping_enabled() const noexcept -> bool
  {
    return SDL_RenderIsClipEnabled(get());
  }

  /**
   * \brief Returns the currently selected rendering color.
   *
   * \details The default color is black.
   *
   * \return the currently selected rendering color.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto get_color() const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    u8 alpha{};
    SDL_GetRenderDrawColor(get(), &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  /**
   * \brief Returns the viewport that the renderer uses.
   *
   * \return the viewport that the renderer uses.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto viewport() const noexcept -> irect
  {
    irect viewport{};
    SDL_RenderGetViewport(get(), viewport.data());
    return viewport;
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \warning It's undefined behaviour to invoke other member functions that
   * use the internal pointer if this function returns `false`.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename BB = B, detail::is_handle<BB> = true>
  explicit operator bool() const noexcept
  {
    return m_renderer != nullptr;
  }

  /**
   * \brief Returns a pointer to the associated SDL renderer.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL_Renderer.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Renderer*
  {
    if constexpr (detail::is_owning<B>()) {
      return m_renderer.ptr.get();
    } else {
      return m_renderer;
    }
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Renderer* renderer) noexcept
    {
      SDL_DestroyRenderer(renderer);
    }
  };

  struct owning_data final
  {
    /*implicit*/ owning_data(SDL_Renderer* r) : ptr{r}
    {}

    std::unique_ptr<SDL_Renderer, deleter> ptr;
    frect translation{};
    std::unordered_map<std::size_t, font> fonts{};
  };

  using rep_t = std::conditional_t<B::value, owning_data, SDL_Renderer*>;

  rep_t m_renderer;

  [[nodiscard]] auto render_text(owner<SDL_Surface*> s) -> texture
  {
    surface surface{s};
    texture texture{SDL_CreateTextureFromSurface(get(), surface.get())};
    return texture;
  }

  template <typename T, typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto translate(const basic_point<T>& point) const noexcept
      -> basic_point<T>
  {
    using value_type = typename basic_point<T>::value_type;

    const auto& translation = m_renderer.translation;
    const auto x = point.x() - static_cast<value_type>(translation.x());
    const auto y = point.y() - static_cast<value_type>(translation.y());

    return basic_point<T>{x, y};
  }

  template <typename T, typename BB = B, detail::is_owner<BB> = true>
  [[nodiscard]] auto translate(const basic_rect<T>& rect) const noexcept
      -> basic_rect<T>
  {
    return basic_rect<T>{translate(rect.position()), rect.size()};
  }
};

template <typename B>
[[nodiscard]] auto to_string(const basic_renderer<B>& renderer) -> std::string
{
  return "[renderer | data: " + detail::address_of(renderer.get()) + "]";
}

template <typename B>
auto operator<<(std::ostream& stream, const basic_renderer<B>& renderer)
    -> std::ostream&
{
  stream << to_string(renderer);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_RENDERER_HEADER
