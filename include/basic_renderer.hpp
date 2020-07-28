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
 * @file basic_renderer.hpp
 *
 * @brief Provides the `basic_renderer` class, the base implementation of
 * renderers.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_RENDERER_BASE_HEADER
#define CENTURION_RENDERER_BASE_HEADER

#include <algorithm>
#include <memory>
#include <utility>

#include "area.hpp"
#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "color.hpp"
#include "font_cache.hpp"
#include "log.hpp"
#include "point.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/**
 * @class basic_renderer
 *
 * @ingroup graphics
 *
 * @brief Provides the base implementation of renderers.
 *
 * @details This class provides the general API for hardware-accelerated
 * rendering.
 *
 * @tparam Derived the type of the derived renderer.
 *
 * @since 5.0.0
 *
 * @see `renderer`
 * @see `renderer_handle`
 *
 * @headerfile basic_renderer.hpp
 */
template <class Derived>
class basic_renderer {
 public:
  /**
   * @brief Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  void clear() noexcept;

  /**
   * @brief Clears the rendering target with the specified color.
   *
   * @note This method doesn't change the currently selected color.
   *
   * @param color the color that will be used to clear the rendering target.
   *
   * @since 5.0.0
   */
  void clear_with(const color& color) noexcept;

  /**
   * @brief Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  void present() noexcept;

  /**
   * @name Primitive rendering
   * Methods for rendering rectangles and lines.
   */
  ///@{

  /**
   * @brief Renders the outline of a rectangle in the currently selected color.
   *
   * @tparam Traits the traits used by the rectangle.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void draw_rect(const basic_rect<Traits>& rect) noexcept;

  /**
   * @brief Renders a filled rectangle in the currently selected color.
   *
   * @tparam Traits the traits used by the rectangle.
   *
   * @param rect the rectangle that will be rendered.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void fill_rect(const basic_rect<Traits>& rect) noexcept;

  /**
   * @brief Renders a line between the supplied points, in the currently
   * selected color.
   *
   * @tparam Traits The traits used by the points.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void draw_line(const basic_point<Traits>& start,
                 const basic_point<Traits>& end) noexcept;

  /**
   * @brief Renders a collection of lines.
   *
   * @details This method requires the the `Container` type provides the
   * public member `value_type` and subsequently, that the `value_type`
   * in turn provides a `value_type` member. The former would correspond to
   * the actual point type, and the latter corresponds to either `int` or
   * `float`.
   *
   * @warning `Container` *must* be a collection that stores its data
   * contiguously! The behaviour of this method is undefined if this condition
   * isn't met.
   *
   * @tparam Container the container type. Must store its elements
   * contiguously, such as `std::vector` or `std::array`.
   *
   * @param container the container that holds the points that will be used
   * to render the line.
   *
   * @since 5.0.0
   */
  template <typename Container>
  void draw_lines(const Container& container) noexcept;

  ///@}  // end of primitive rendering

  /**
   * @name Text rendering
   * Methods for rendering text encoded in UTF-8, LATIN-1 or UNICODE.
   */
  ///@{

  /**
   * @brief Creates and returns a texture of blended UTF-8 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * @param str the UTF-8 text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUTF8_Blended`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_utf8(nn_czstring str, const font& font)
      -> texture;

  /**
   * @brief Creates and returns a texture of blended and wrapped UTF-8 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This method will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * @param str the UTF-8 text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * @param font the font that the text will be rendered in.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUTF8_Blended_Wrapped`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_utf8(nn_czstring str,
                                                 const font& font,
                                                 u32 wrap) -> texture;

  /**
   * @brief Creates and returns a texture of shaded UTF-8 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * method when you want nice text, and can live with a box around it.
   *
   * @param str the UTF-8 text that will be rendered.
   * @param font the font that the text will be rendered in.
   * @param background the background color used for the box.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUTF8_Shaded`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_shaded_utf8(nn_czstring str,
                                        const font& font,
                                        const color& background) -> texture;

  /**
   * @brief Creates and returns a texture of solid UTF-8 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the UTF-8 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
   * when quality isn't as big of a concern and speed is important.
   *
   * @param str the UTF-8 text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderText_Solid`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_solid_utf8(nn_czstring str, const font& font)
      -> texture;

  /**
   * @brief Creates and returns a texture of blended Latin-1 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * @param str the Latin-1 text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderText_Blended`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_latin1(nn_czstring str, const font& font)
      -> texture;

  /**
   * @brief Creates and returns a texture of blended and wrapped Latin-1 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This method will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * @param str the Latin-1 text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * @param font the font that the text will be rendered in.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderText_Blended_Wrapped`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_latin1(nn_czstring str,
                                                   const font& font,
                                                   u32 wrap) -> texture;

  /**
   * @brief Creates and returns a texture of shaded Latin-1 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the Latin-1 text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * method when you want nice text, and can live with a box around it.
   *
   * @param str the Latin-1 text that will be rendered.
   * @param font the font that the text will be rendered in.
   * @param background the background color used for the box.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderText_Shaded`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_shaded_latin1(nn_czstring str,
                                          const font& font,
                                          const color& background) -> texture;

  /**
   * @brief Creates and returns a texture of solid Latin-1 text.
   *
   * @pre `str` can't be null.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
   * when quality isn't as big of a concern and speed is important.
   *
   * @param str the Latin-1 text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderText_Solid`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_solid_latin1(nn_czstring str, const font& font)
      -> texture;

  /**
   * @brief Creates and returns a texture of blended Unicode text.
   *
   * @details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * @param str the Unicode text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUNICODE_Blended`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_unicode(const unicode_string& str,
                                            const font& font) -> texture;

  /**
   * @brief Creates and returns a texture of blended and wrapped Unicode text.
   *
   * @details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This method will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired
   * breakpoints.
   *
   * @param str the Unicode text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints.
   * @param font the font that the text will be rendered in.
   * @param wrap the width in pixels after which the text will be wrapped.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUNICODE_Blended_Wrapped`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_blended_wrapped_unicode(const unicode_string& str,
                                                    const font& font,
                                                    u32 wrap) -> texture;

  /**
   * @brief Creates and returns a texture of shaded Unicode text.
   *
   * @details Attempts to render the Unicode text in the supplied font using
   * the currently selected color and returns a texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * method when you want nice text, and can live with a box around it.
   *
   * @param str the Unicode text that will be rendered.
   * @param font the font that the text will be rendered in.
   * @param background the background color used for the box.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUNICODE_Shaded`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_shaded_unicode(const unicode_string& str,
                                           const font& font,
                                           const color& background) -> texture;

  /**
   * @brief Creates and returns a texture of solid Unicode text.
   *
   * @details Attempts to render the specified text in the supplied font using
   * the currently selected color and return the texture that contains the
   * result. Use the returned texture to actually render the text to the
   * screen.
   *
   * This method is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
   * when quality isn't as big of a concern and speed is important.
   *
   * @param str the Unicode text that will be rendered.
   * @param font the font that the text will be rendered in.
   *
   * @return a texture that contains the rendered text.
   *
   * @see `TTF_RenderUNICODE_Solid`
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto render_solid_unicode(const unicode_string& str,
                                          const font& font) -> texture;

  /**
   * @brief Renders a glyph at the specified position.
   *
   * @pre the specified glyph **must** have been cached.
   *
   * @tparam T the font key type that the renderer uses.
   *
   * @param cache the font cache that will be used.
   * @param glyph the glyph, in unicode, that will be rendered.
   * @param position the position of the rendered glyph.
   *
   * @return the x-coordinate of the next glyph to be rendered after the
   * current glyph.
   *
   * @since 5.0.0
   */
  auto render_glyph(const font_cache& cache,
                    unicode glyph,
                    const ipoint& position) -> int;

  /**
   * @brief Renders a string.
   *
   * @details This method will not apply any clever conversions on the
   * supplied string. The string is literally iterated,
   * character-by-character, and each character is rendered using
   * the `render_glyph` function.
   *
   * @pre Every character in the string must correspond to a valid Unicode
   * glyph.
   * @pre Every character must have been previously cached.
   *
   * @note This method is sensitive to newline-characters, and will render
   * strings that contain such characters appropriately.
   *
   * @tparam String the type of the string, must be iterable and provide
   * `unicode` characters.
   *
   * @param cache the font cache that will be used.
   * @param str the string that will be rendered.
   * @param position the position of the rendered text.
   *
   * @since 5.0.0
   */
  template <typename String>
  void render_text(const font_cache& cache, const String& str, ipoint position);

  ///@}  // end of text rendering

  /**
   * @name Texture rendering
   * Methods for rendering hardware-accelerated textures.
   */
  ///@{

  /**
   * @brief Renders a texture at the specified position.
   *
   * @tparam Traits the traits used by the point.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void render(const texture& texture,
              const basic_point<Traits>& position) noexcept;

  /**
   * @brief Renders a texture according to the specified rectangle.
   *
   * @tparam Traits the traits used by the rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void render(const texture& texture,
              const basic_rect<Traits>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @remarks This should be your preferred method of rendering textures. This
   * method is efficient and simple.
   *
   * @tparam Traits the traits used by the destination rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void render(const texture& texture,
              const irect& source,
              const basic_rect<Traits>& destination) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam Traits the traits used by the destination rectangle.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   *
   * @since 4.0.0
   */
  template <typename Traits>
  void render(const texture& texture,
              const irect& source,
              const basic_rect<Traits>& destination,
              double angle) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam RectTraits the traits used by the destination rectangle.
   * @tparam PointTraits the traits used by the center point.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will
   * be rotated.
   *
   * @since 4.0.0
   */
  template <typename RectTraits, typename PointTraits>
  void render(const texture& texture,
              const irect& source,
              const basic_rect<RectTraits>& destination,
              double angle,
              const basic_point<PointTraits>& center) noexcept;

  /**
   * @brief Renders a texture.
   *
   * @tparam RectTraits the traits used by the destination rectangle.
   * @tparam PointTraits the traits used by the center point.
   *
   * @param texture the texture that will be rendered.
   * @param source the cutout out of the texture that will be rendered.
   * @param destination the position and size of the rendered texture.
   * @param angle the clockwise angle, in degrees, with which the rendered
   * texture will be rotated.
   * @param center specifies the point around which the rendered texture will be
   * rotated.
   * @param flip specifies how the rendered texture will be flipped.
   *
   * @since 4.0.0
   */
  template <typename RectTraits, typename PointTraits>
  void render(const texture& texture,
              const irect& source,
              const basic_rect<RectTraits>& destination,
              double angle,
              const basic_point<PointTraits>& center,
              SDL_RendererFlip flip) noexcept;

  ///@}  // end of texture rendering

  /**
   * @brief Sets the color that will be used by the renderer.
   *
   * @param color the color that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_color(const color& color) noexcept;

  /**
   * @brief Sets the clipping area rectangle.
   *
   * @details Clipping is disabled by default.
   *
   * @param area the clip area rectangle; or `nothing` to disable clipping.
   *
   * @since 3.0.0
   */
  void set_clip(std::optional<irect> area) noexcept;

  /**
   * @brief Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_viewport(const irect& viewport) noexcept;

  /**
   * @brief Sets the blend mode that will be used by the renderer.
   *
   * @param mode the blend mode that will be used by the renderer.
   *
   * @since 3.0.0
   */
  void set_blend_mode(blend_mode mode) noexcept;

  /**
   * @brief Sets the rendering target of the renderer.
   *
   * @details The supplied texture must support being a render target.
   * Otherwise, this method will reset the render target.
   *
   * @param target a pointer to the new target texture; `nullptr` indicates
   * that the default rendering target should be used.
   *
   * @since 3.0.0
   */
  void set_target(const texture* target) noexcept;

  /**
   * @brief Sets the rendering scale.
   *
   * @note This method has no effect if any of the arguments aren't
   * greater than zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   *
   * @since 3.0.0
   */
  void set_scale(float xScale, float yScale) noexcept;

  /**
   * @brief Sets the logical size used by the renderer.
   *
   * @details This method is useful for resolution-independent rendering.
   *
   * @remarks This is also known as *virtual size* in other frameworks.
   *
   * @note This method has no effect if either of the supplied dimensions
   * aren't greater than zero.
   *
   * @param size the logical width and height that will be used.
   *
   * @since 3.0.0
   */
  void set_logical_size(const iarea& size) noexcept;

  /**
   * @brief Sets whether or not to force integer scaling for the logical
   * viewport.
   *
   * @details By default, this property is set to false. This method can be
   * useful to combat visual artefacts when doing floating-point rendering.
   *
   * @param enabled `true` if integer scaling should be used; `false` otherwise.
   *
   * @since 3.0.0
   */
  void set_logical_integer_scale(bool enabled) noexcept;

  /**
   * @brief Returns the logical width that the renderer uses.
   *
   * @details By default, this property is set to 0.
   *
   * @return the logical width that the renderer uses.
   *
   * @see renderer::logical_size
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int;

  /**
   * @brief Returns the logical height that the renderer uses.
   *
   * @details By default, this property is set to 0.
   *
   * @return the logical height that the renderer uses.
   *
   * @see renderer::logical_size
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int;

  /**
   * @brief Returns the size of the logical (virtual) viewport.
   *
   * @note calling this method once is faster than calling both
   * `logical_width` and `logical_height` for obtaining the size.
   *
   * @return the size of the logical (virtual) viewport.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto logical_size() const noexcept -> iarea;

  /**
   * @brief Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto x_scale() const noexcept -> float;

  /**
   * @brief Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto y_scale() const noexcept -> float;

  /**
   * @brief Returns the x- and y-scale used by the renderer.
   *
   * @note calling this method once is faster than calling both `x_scale`
   * and `y_scale` for obtaining the scale.
   *
   * @return the x- and y-scale used by the renderer.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto scale() const noexcept -> std::pair<float, float>;

  /**
   * @brief Returns the current clipping rectangle, if there is one active.
   *
   * @return the current clipping rectangle; or `nothing` if there is none.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> std::optional<irect>;

  /**
   * @brief Returns information about the renderer.
   *
   * @return information about the renderer; `nothing` if something went
   * wrong.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto info() const noexcept -> std::optional<SDL_RendererInfo>;

  /**
   * @brief Returns the output width of the renderer.
   *
   * @return the output width of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_width() const noexcept -> int;

  /**
   * @brief Returns the output height of the renderer.
   *
   * @return the output height of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_height() const noexcept -> int;

  /**
   * @brief Returns the output size of the renderer.
   *
   * @note calling this method once is faster than calling `output_width`
   * and `output_height` for obtaining the output size.
   *
   * @return the current output size of the renderer.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto output_size() const noexcept -> iarea;

  /**
   * @brief Returns the blend mode that is being used by the renderer.
   *
   * @return the blend mode that is being used.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode;

  /**
   * @name Flag-related queries.
   *
   * @brief Methods for obtaining information about the window flags.
   */
  ///@{

  /**
   * @brief Returns a bit mask of the current renderer flags.
   *
   * @note There are multiple other methods for checking if a flag is set,
   * such as `is_vsync_enabled` or `is_accelerated`, that are nicer to use than
   * this method.
   *
   * @return a bit mask of the current renderer flags.
   *
   * @see `SDL_RendererFlags`
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto flags() const noexcept -> u32;

  /**
   * @brief Indicates whether or not the `present` method is synced with
   * the refresh rate of the screen.
   *
   * @return `true` if vsync is enabled; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_vsync_enabled() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer is hardware accelerated.
   *
   * @return `true` if the renderer is hardware accelerated; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_accelerated() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer is using software rendering.
   *
   * @return `true` if the renderer is software-based; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_software_based() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the renderer supports rendering to a
   * target texture.
   *
   * @return `true` if the renderer supports target texture rendering; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto supports_target_textures() const noexcept -> bool;

  ///@} // end of flag queries

  /**
   * @brief Indicates whether or not the renderer uses integer scaling values
   * for logical viewports.
   *
   * @details By default, this property is set to false.
   *
   * @return `true` if the renderer uses integer scaling for logical
   * viewports; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_using_integer_logical_scaling() const noexcept -> bool;

  /**
   * @brief Indicates whether or not clipping is enabled.
   *
   * @details This is disabled by default.
   *
   * @return `true` if clipping is enabled; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_clipping_enabled() const noexcept -> bool;

  /**
   * @brief Returns the currently selected rendering color.
   *
   * @details The default color is black.
   *
   * @return the currently selected rendering color.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get_color() const noexcept -> color;

  /**
   * @brief Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto viewport() const noexcept -> irect;

 protected:
  basic_renderer() noexcept = default;

 private:
  [[nodiscard]] auto render_text(owner<SDL_Surface*> s) -> texture;

  [[nodiscard]] auto ptr() noexcept -> SDL_Renderer*;

  [[nodiscard]] auto ptr() const noexcept -> SDL_Renderer*;
};

/**
 * @brief Returns the number of available rendering drivers.
 *
 * @note Usually there is only one available rendering driver.
 *
 * @return the number of available rendering drivers.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto num_render_drivers() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

/**
 * @brief Returns the number of available video drivers compiled into SDL.
 *
 * @return the number of available video drivers compiled into SDL.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto num_video_drivers() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

/**
 * @brief Returns the information associated with a rendering driver.
 *
 * @param index the index of the rendering driver to query.
 *
 * @return information about the specified rendering driver; `nothing` if
 * something went wrong.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto get_render_driver_info(int index) noexcept
    -> std::optional<SDL_RendererInfo>;

}  // namespace centurion

#include "basic_renderer.ipp"

#endif  // CENTURION_RENDERER_BASE_HEADER