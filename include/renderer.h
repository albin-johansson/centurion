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

#ifndef CENTURION_RENDERER_HEADER
#define CENTURION_RENDERER_HEADER

#include <SDL.h>
#include <SDL_image.h>

#include <gsl-lite.hpp>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "blend_mode.h"
#include "centurion_api.h"
#include "centurion_utils.h"
#include "color.h"
#include "point.h"
#include "rectangle.h"

namespace centurion {
namespace video {

class Window;
class Texture;
class Font;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct. Rendering
 * operations are treated as const methods.
 *
 * @see SDL_Renderer
 * @since 3.0.0
 */
class Renderer final {
 private:
  SDL_Renderer* renderer = nullptr;
  math::FRect translationViewport = {0, 0, 0, 0};

  static constexpr SDL_RendererFlags defaultFlags =
      static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC);

  void destroy() noexcept;

 public:
  /**
   * Creates a renderer based on the supplied SDL_Renderer.
   *
   * @param renderer a pointer to the SDL_Renderer that will be used by the
   * renderer.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_API
  explicit Renderer(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates a renderer based on the supplied window. By default, the
   * internal renderer will be created using the SDL_RENDERER_ACCELERATED and
   * SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @since 4.0.0
   */
  CENTURION_API
  explicit Renderer(const Window& window,
                    SDL_RendererFlags flags = defaultFlags);

  CENTURION_API
  Renderer(Renderer&& other) noexcept;

  Renderer(const Renderer&) noexcept = delete;

  CENTURION_API
  Renderer& operator=(Renderer&& other) noexcept;

  Renderer& operator=(const Renderer&) noexcept = delete;

  CENTURION_API
  ~Renderer();

  /**
   * Creates and returns a unique pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created renderer
   * will be based on, may not be null.
   * @return a unique pointer to a renderer.
   * @throws invalid_argument if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Renderer> unique(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a unique pointer to a renderer instance.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @return a unique pointer to a renderer instance.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Renderer> unique(
      const Window& window, SDL_RendererFlags flags = defaultFlags);

  /**
   * Creates and returns a shared pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created
   * renderer will be based on, may not be null.
   * @return a shared pointer to a renderer.
   * @throws invalid_argument if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Renderer> shared(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a shared pointer to a renderer instance.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @return a shared pointer to a renderer instance.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Renderer> shared(
      const Window& window, SDL_RendererFlags flags = defaultFlags);

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void clear() const noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void present() const noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API
  void draw_rect(const math::IRect& rect) const noexcept;

  /**
   * Renders a filled rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API
  void fill_rect(const math::IRect& rect) const noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API
  void draw_rect_f(const math::FRect& rect) const noexcept;

  /**
   * Renders a filled rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API
  void fill_rect_f(const math::FRect& rect) const noexcept;

  /**
   * Draws a line in between the supplied points in the currently selected
   * color.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   * @since 4.0.0
   */
  CENTURION_API
  void draw_line(const math::IPoint& start,
                 const math::IPoint& end) const noexcept;

  /**
   * Renders a sequence of connected lines in the currently selected color.
   *
   * @param points the collection of points to draw the lines between.
   * @since 3.0.0
   */
  CENTURION_API
  void draw_lines(const std::vector<math::IPoint>& points) const noexcept;

  /**
   * Draws a line in between the supplied points in the currently selected
   * color.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   * @since 4.0.0
   */
  CENTURION_API
  void draw_line_f(const math::FPoint& start,
                   const math::FPoint& end) const noexcept;

  /**
   * Renders a texture at the specified position.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture, math::IPoint position) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position and size of the
   * rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture, const math::IRect& rect) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture,
              const math::IRect& src,
              const math::IRect& dst) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture,
              const math::IRect& src,
              const math::IRect& dst,
              double angle) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture,
              const math::IRect& src,
              const math::IRect& dst,
              double angle,
              math::IPoint center) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture,
              const math::IRect& src,
              const math::IRect& dst,
              SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render(const Texture& texture,
              const math::IRect& src,
              const math::IRect& dst,
              double angle,
              math::IPoint center,
              SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture, math::FPoint position) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param rect the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture, const math::FRect& rect) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture,
                const math::IRect& src,
                const math::FRect& dst) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture,
                const math::IRect& src,
                const math::FRect& dst,
                double angle) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture,
                const math::IRect& src,
                const math::FRect& dst,
                double angle,
                math::FPoint center) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture,
                const math::IRect& src,
                const math::FRect& dst,
                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture. The rotation is done clock-wise.
   *
   * @param texture the texture that will be rendered.
   * @param src the part of the texture that will be rendered.
   * @param dst the destination and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the center point of the rotation.
   * @param flip the value that indicates how the rendered texture should be
   * flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_f(const Texture& texture,
                const math::IRect& src,
                const math::FRect& dst,
                double angle,
                math::FPoint center,
                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture at the specified position. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture, math::IPoint position) const noexcept;

  /**
   * Renders a texture. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position (pre-translation) and
   * size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture, const math::IRect& rect) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture,
                const math::IRect& src,
                const math::IRect& dst) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture,
                const math::IRect& src,
                const math::IRect& dst,
                double angle) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture,
                const math::IRect& src,
                const math::IRect& dst,
                double angle,
                math::IPoint center) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture,
                const math::IRect& src,
                const math::IRect& dst,
                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_t(const Texture& texture,
                const math::IRect& src,
                const math::IRect& dst,
                double angle,
                math::IPoint center,
                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture at the specified position. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture, math::FPoint position) const noexcept;

  /**
   * Renders a texture. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position (pre-translation) and
   * size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::FRect& rect) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::IRect& src,
                 const math::FRect& dst) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::IRect& src,
                 const math::FRect& dst,
                 double angle) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::IRect& src,
                 const math::FRect& dst,
                 double angle,
                 math::FPoint center) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::IRect& src,
                 const math::FRect& dst,
                 SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @param center the rotation center point.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API
  void render_tf(const Texture& texture,
                 const math::IRect& src,
                 const math::FRect& dst,
                 double angle,
                 math::FPoint center,
                 SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a string of text. Note that this method is rather inefficient,
   * since it will dynamically allocate a texture based on the supplied
   * string for every call to this method. This method has no effect if the
   * supplied string is null.
   *
   * @param text the text that will be rendered in the supplied font.
   * @param pos the position of the rendered text.
   * @param font the font that will be used.
   * @since 4.0.0
   */
  CENTURION_API
  void render_text(const char* text, math::IRect pos, const Font& font) const;

  /**
   * Renders a string of text. Note that this method is rather inefficient,
   * since it will dynamically allocate a texture based on the supplied
   * string for every call to this method. This method has no effect if the
   * supplied string is null.
   *
   * @param text the text that will be rendered in the supplied font.
   * @param pos the position of the rendered text.
   * @param font the font that will be used.
   * @since 3.0.0
   */
  CENTURION_API
  void render_text_f(const char* text, math::FRect pos, const Font& font) const;

  /**
   * Sets the color that will be used by the renderer. This method is
   * intentionally considered a const-method, even if it technically changes the
   * state of the renderer.
   *
   * @param color the color that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API
  void set_color(const Color& color) const noexcept;

  /**
   * Sets the clipping area rectangle. Clipping is disabled by default.
   *
   * @param area the clip area rectangle; or nullopt to disable clipping.
   * @since 3.0.0
   */
  CENTURION_API
  void set_clip(Optional<math::IRect> area) noexcept;

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API
  void set_viewport(const math::IRect& viewport) noexcept;

  /**
   * Sets the translation viewport that will be used by the renderer. This
   * method can be used in order to be able to use the various
   * X_translated-methods.
   *
   * @param viewport the rectangle that will be used as the translation
   * viewport.
   * @since 3.0.0
   */
  CENTURION_API
  void set_translation_viewport(const math::FRect& viewport) noexcept;

  /**
   * Sets the blend mode that will be used by the renderer.
   *
   * @param mode the blend mode that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API
  void set_blend_mode(BlendMode mode) noexcept;

  /**
   * Sets the rendering target of the renderer. The supplied image must support
   * being a render target. Otherwise, this method will reset the render target.
   *
   * @param texture a pointer to the new target texture, can safely be null to
   * indicate that the default rendering target should be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_target(const Texture* texture) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no
   * effect if any of the arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_scale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of
   * the supplied dimensions aren't greater than zero.
   *
   * @param width the logical width that will be used.
   * @param height the logical height that will be used.
   * @since 3.0.0
   */
  CENTURION_API
  void set_logical_size(int width, int height) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By
   * default, this property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_API
  void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses. By default, this property
   * is set to 0.
   *
   * @return the logical width that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  int get_logical_width() const noexcept;

  /**
   * Returns the logical height that the renderer uses. By default, this
   * property is set to 0.
   *
   * @return the logical height that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  int get_logical_height() const noexcept;

  /* The only way of discovering the limits of the possible is to venture a
     little way past them into the impossible. */

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  float get_x_scale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  float get_y_scale() const noexcept;

  /**
   * Returns the current clipping rectangle, if there is one active.
   *
   * @return the current clipping rectangle; or nullopt if there is none.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<math::IRect> get_clip() const noexcept;

  /**
   * Returns information about the renderer.
   *
   * @return information about the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  SDL_RendererInfo get_info() const noexcept;

  /**
   * Returns the output width of the renderer.
   *
   * @return the output width of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  int get_output_width() const noexcept;

  /**
   * Returns the output height of the renderer.
   *
   * @return the output height of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  int get_output_height() const noexcept;

  /**
   * Returns the output size of the renderer.
   *
   * @return the output size of the renderer, in the format (width, height).
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::pair<int, int> get_output_size() const noexcept;

  /**
   * Returns the blend mode that is being used by the renderer.
   *
   * @return the blend mode that is being used.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  BlendMode get_blend_mode() const noexcept;

  /**
   * Returns a bit mask that represents all of flags used when creating the
   * renderer. The possible values are <ul> <li>a</li>
   * </ul>
   *
   * @return a bit mask that represents all of flags used when creating the
   * renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Uint32 get_flags() const noexcept;

  /**
   * Indicates whether or not the <code>present()</code> method is synced with
   * the refresh rate of the screen.
   *
   * @return true if vsync is enabled; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_vsync_enabled() const noexcept;

  /**
   * Indicates whether or not the renderer is hardware accelerated.
   *
   * @return true if the renderer is hardware accelerated; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_accelerated() const noexcept;

  /**
   * Indicates whether or not the renderer is using software rendering.
   *
   * @return true if the renderer is software-based; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_software_based() const noexcept;

  /**
   * Indicates whether or not the renderer supports rendering to a target
   * texture.
   *
   * @return true if the renderer supports target texture rendering; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_supporting_target_textures() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for
   * logical viewports. By default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports;
   * false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_using_integer_logical_scaling() const noexcept;

  /**
   * Indicates whether or not clipping is enabled. This is disabled by default.
   *
   * @return true if clipping is enabled; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  bool is_clipping_enabled() const noexcept;

  /**
   * Returns the currently selected rendering color. Set to black by default.
   *
   * @return the currently selected rendering color.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Color get_color() const noexcept;

  /**
   * Attempts to create and return a pointer to an SDL_Texture instance that
   * represents the supplied string rendered with the supplied font. This method
   * will not throw any exception by itself, but dynamic memory allocation will
   * occur behind-the-scenes.
   *
   * @param s the string that contains the content that will be rendered to a
   * texture.
   * @param font a reference to the font that will be used.
   * @return a unique pointer to an image that represents the supplied string
   * rendered with the currently selected font; nullptr if the operation is
   * unsuccessful.
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::unique_ptr<Texture> create_image(const std::string& s,
                                        const Font& font) const;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  math::IRect get_viewport() const noexcept;

  /**
   * Returns the translation viewport that is currently being used. Set to (0,
   * 0, 0, 0) by default.
   *
   * @return the translation viewport that is currently being used.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  const math::FRect& get_translation_viewport() const noexcept;

  /**
   * Returns a textual representation of the renderer.
   *
   * @return a textual representation of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::string to_string() const;

  CENTURION_NODISCARD
  CENTURION_API
  SDL_Renderer* get_internal() const noexcept;

  /**
   * @since 3.0.0
   */
  CENTURION_API
  operator SDL_Renderer*() const noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Renderer>::value, "Renderer isn't final!");
#endif

static_assert(std::is_nothrow_move_constructible<Renderer>::value,
              "Renderer isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Renderer>::value,
              "Renderer isn't nothrow move assignable!");

static_assert(!std::is_nothrow_copy_constructible<Renderer>::value,
              "Renderer is copyable!");

static_assert(!std::is_nothrow_copy_assignable<Renderer>::value,
              "Renderer is copy assignable!");

static_assert(std::is_convertible<Renderer, SDL_Renderer*>::value,
              "Renderer isn't convertible to SDL_Renderer*!");

}  // namespace video
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "renderer.cpp"
#endif

#endif  // CENTURION_RENDERER_HEADER