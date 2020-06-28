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

#include <unordered_map>
#include <vector>

#include "area.h"
#include "blend_mode.h"
#include "centurion_api.h"
#include "centurion_utils.h"
#include "color.h"
#include "point.h"
#include "rect.h"

namespace centurion {

class Window;
class Texture;
class Font;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct.
 *
 * @see SDL_Renderer
 * @since 3.0.0
 */
class Renderer final {
 public:
  /**
   * Creates a renderer based on the supplied SDL_Renderer.
   *
   * @param renderer a pointer to the SDL_Renderer that will be used by the
   * renderer.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit Renderer(Owner<SDL_Renderer*> renderer);

  /**
   * Creates a renderer based on the supplied window. By default, the
   * internal renderer will be created using the SDL_RENDERER_ACCELERATED and
   * SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @throws CenturionException if something goes wrong when creating the
   * Renderer.
   * @since 4.0.0
   */
  CENTURION_API explicit Renderer(const Window& window,
                                  SDL_RendererFlags flags = defaultFlags);

  CENTURION_API Renderer(Renderer&& other) noexcept;

  Renderer(const Renderer&) noexcept = delete;

  CENTURION_API Renderer& operator=(Renderer&& other) noexcept;

  Renderer& operator=(const Renderer&) noexcept = delete;

  CENTURION_API ~Renderer();

  /**
   * Creates and returns a unique pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created renderer
   * will be based on, may not be null.
   * @return a unique pointer to a renderer.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Renderer> unique(
      Owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a unique pointer to a renderer instance.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @return a unique pointer to a renderer instance.
   * @throws CenturionException if something goes wrong when creating the
   * Renderer.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Renderer> unique(
      const Window& window,
      SDL_RendererFlags flags = defaultFlags);

  /**
   * Creates and returns a shared pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created
   * renderer will be based on, may not be null.
   * @return a shared pointer to a renderer.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Renderer> shared(
      Owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a shared pointer to a renderer instance.
   *
   * @param window the associated window instance.
   * @param flags the renderer flags that will be used.
   * @return a shared pointer to a renderer instance.
   * @throws CenturionException if something goes wrong when creating the
   * Renderer.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Renderer> shared(
      const Window& window,
      SDL_RendererFlags flags = defaultFlags);

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  CENTURION_API void clear() noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  CENTURION_API void present() noexcept;

  /**
   * Adds a font to the renderer. This method has no effect if the specified
   * name is already taken or if the supplied font is null.
   *
   * @param name the name that will be associated with the font, should
   * preferably be quite short.
   * @param font the font that will be added, can safely be null.
   * @since 4.1.0
   */
  CENTURION_API void add_font(const std::string& name,
                              const SharedPtr<Font>& font) noexcept;

  /**
   * Adds a font to the renderer. This method has no effect if the name of
   * the font is already taken or if the supplied font is null. This method
   * will return the name that was associated with the font if adding the
   * font was successful.
   *
   * @param font the font that will be added, can safely be null.
   * @return the name associated with the supplied font if successful;
   * nothing otherwise.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  Optional<std::string> add_font(const SharedPtr<Font>& font) noexcept;

  /**
   * Removes the font associated with the specified name.
   *
   * @param name the name associated with the font that will be removed.
   * @since 4.1.0
   */
  CENTURION_API void remove_font(const std::string& name) noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API void draw_rect(const IRect& rect) noexcept;

  /**
   * Renders a filled rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API void fill_rect(const IRect& rect) noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API void draw_rect_f(const FRect& rect) noexcept;

  /**
   * Renders a filled rectangle in the currently selected color.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.0.0
   */
  CENTURION_API void fill_rect_f(const FRect& rect) noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color. The rendered
   * rectangle will be translated using the translation viewport.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.1.0
   */
  CENTURION_API void draw_rect_t(const IRect& rect) noexcept;

  /**
   * Renders an outlined rectangle in the currently selected color. The rendered
   * rectangle will be translated using the translation viewport.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.1.0
   */
  CENTURION_API void draw_rect_tf(const FRect& rect) noexcept;

  /**
   * Renders a filled rectangle in the currently selected color. The rendered
   * rectangle will be translated using the translation viewport.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.1.0
   */
  CENTURION_API void fill_rect_t(const IRect& rect) noexcept;

  /**
   * Renders a filled rectangle in the currently selected color. The rendered
   * rectangle will be translated using the translation viewport.
   *
   * @param rect the rectangle that will be rendered.
   * @since 4.1.0
   */
  CENTURION_API void fill_rect_tf(const FRect& rect) noexcept;

  /**
   * Draws a line in between the supplied points in the currently selected
   * color.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   * @since 4.0.0
   */
  CENTURION_API void draw_line(const IPoint& start, const IPoint& end) noexcept;

  /**
   * Renders a sequence of connected lines in the currently selected color.
   *
   * @param points the collection of points to draw the lines between.
   * @since 3.0.0
   */
  CENTURION_API void draw_lines(const std::vector<IPoint>& points) noexcept;

  /**
   * Draws a line in between the supplied points in the currently selected
   * color.
   *
   * @param start the start point of the line.
   * @param end the end point of the line.
   * @since 4.0.0
   */
  CENTURION_API void draw_line_f(const FPoint& start,
                                 const FPoint& end) noexcept;

  /**
   * Renders a texture at the specified position.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render(const Texture& texture, IPoint position) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position and size of the
   * rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render(const Texture& texture, const IRect& rect) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render(const Texture& texture,
                            const IRect& src,
                            const IRect& dst) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API void render(const Texture& texture,
                            const IRect& src,
                            const IRect& dst,
                            double angle) noexcept;

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
  CENTURION_API void render(const Texture& texture,
                            const IRect& src,
                            const IRect& dst,
                            double angle,
                            IPoint center) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API void render(const Texture& texture,
                            const IRect& src,
                            const IRect& dst,
                            SDL_RendererFlip flip) noexcept;

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
  CENTURION_API void render(const Texture& texture,
                            const IRect& src,
                            const IRect& dst,
                            double angle,
                            IPoint center,
                            SDL_RendererFlip flip) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param position the position of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_f(const Texture& texture, FPoint position) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param rect the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_f(const Texture& texture,
                              const FRect& rect) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_f(const Texture& texture,
                              const IRect& src,
                              const FRect& dst) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param angle the angle of the rendered texture, in degrees.
   * @since 4.0.0
   */
  CENTURION_API void render_f(const Texture& texture,
                              const IRect& src,
                              const FRect& dst,
                              double angle) noexcept;

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
  CENTURION_API void render_f(const Texture& texture,
                              const IRect& src,
                              const FRect& dst,
                              double angle,
                              FPoint center) noexcept;

  /**
   * Renders a texture.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API void render_f(const Texture& texture,
                              const IRect& src,
                              const FRect& dst,
                              SDL_RendererFlip flip) noexcept;

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
  CENTURION_API void render_f(const Texture& texture,
                              const IRect& src,
                              const FRect& dst,
                              double angle,
                              FPoint center,
                              SDL_RendererFlip flip) noexcept;

  /**
   * Renders a texture at the specified position. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_t(const Texture& texture, IPoint position) noexcept;

  /**
   * Renders a texture. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position (pre-translation) and
   * size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& rect) noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& src,
                              const IRect& dst) noexcept;

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
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& src,
                              const IRect& dst,
                              double angle) noexcept;

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
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& src,
                              const IRect& dst,
                              double angle,
                              IPoint center) noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& src,
                              const IRect& dst,
                              SDL_RendererFlip flip) noexcept;

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
  CENTURION_API void render_t(const Texture& texture,
                              const IRect& src,
                              const IRect& dst,
                              double angle,
                              IPoint center,
                              SDL_RendererFlip flip) noexcept;

  /**
   * Renders a texture at the specified position. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param position the position (pre-translation) of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_tf(const Texture& texture,
                               FPoint position) noexcept;

  /**
   * Renders a texture. The rendered texture will be
   * translated using the translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param rect the rectangle that provides the position (pre-translation) and
   * size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_tf(const Texture& texture,
                               const FRect& rect) noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the texture that will be rendered.
   * @param dst the position (pre-translation) and size of the rendered texture.
   * @since 4.0.0
   */
  CENTURION_API void render_tf(const Texture& texture,
                               const IRect& src,
                               const FRect& dst) noexcept;

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
  CENTURION_API void render_tf(const Texture& texture,
                               const IRect& src,
                               const FRect& dst,
                               double angle) noexcept;

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
  CENTURION_API void render_tf(const Texture& texture,
                               const IRect& src,
                               const FRect& dst,
                               double angle,
                               FPoint center) noexcept;

  /**
   * Renders a texture. The rendered texture will be translated using the
   * translation viewport.
   *
   * @param texture the texture that will be rendered.
   * @param src the section of the supplied texture that will be rendered.
   * @param dst the position and size of the rendered texture.
   * @param flip the hint for how the rendered texture should be flipped.
   * @since 4.0.0
   */
  CENTURION_API void render_tf(const Texture& texture,
                               const IRect& src,
                               const FRect& dst,
                               SDL_RendererFlip flip) noexcept;

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
  CENTURION_API void render_tf(const Texture& texture,
                               const IRect& src,
                               const FRect& dst,
                               double angle,
                               FPoint center,
                               SDL_RendererFlip flip) noexcept;

  /**
   * Sets the color that will be used by the renderer.
   *
   * @param color the color that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_color(const Color& color) noexcept;

  /**
   * Sets the clipping area rectangle. Clipping is disabled by default.
   *
   * @param area the clip area rectangle; or nothing to disable clipping.
   * @since 3.0.0
   */
  CENTURION_API void set_clip(Optional<IRect> area) noexcept;

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_viewport(const IRect& viewport) noexcept;

  /**
   * Sets the translation viewport that will be used by the renderer. This
   * method can be used in order to be able to use the various
   * X_translated-methods.
   *
   * @param viewport the rectangle that will be used as the translation
   * viewport.
   * @since 3.0.0
   */
  CENTURION_API void set_translation_viewport(const FRect& viewport) noexcept;

  /**
   * Sets the blend mode that will be used by the renderer.
   *
   * @param mode the blend mode that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_blend_mode(BlendMode mode) noexcept;

  /**
   * Sets the rendering target of the renderer. The supplied image must support
   * being a render target. Otherwise, this method will reset the render target.
   *
   * @param texture a pointer to the new target texture, can safely be null to
   * indicate that the default rendering target should be used.
   * @since 3.0.0
   */
  CENTURION_API void set_target(const Texture* texture) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no
   * effect if any of the arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_scale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of
   * the supplied dimensions aren't greater than zero.
   *
   * @param size the logical width and height that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_size(IArea size) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By
   * default, this property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_integer_scale(
      bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses. By default, this property
   * is set to 0.
   *
   * @return the logical width that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int logical_width() const noexcept;

  /**
   * Returns the logical height that the renderer uses. By default, this
   * property is set to 0.
   *
   * @return the logical height that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int logical_height() const noexcept;

  /* The only way of discovering the limits of the possible is to venture a
     little way past them into the impossible. */

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float x_scale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float y_scale() const noexcept;

  /**
   * Returns the current clipping rectangle, if there is one active.
   *
   * @return the current clipping rectangle; or nothing if there is none.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Optional<IRect> clip() const noexcept;

  /**
   * Returns information about the renderer.
   *
   * @return information about the renderer; nothing if something went wrong.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Optional<SDL_RendererInfo> info() const noexcept;

  /**
   * Returns the output width of the renderer.
   *
   * @return the output width of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int output_width() const noexcept;

  /**
   * Returns the output height of the renderer.
   *
   * @return the output height of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int output_height() const noexcept;

  /**
   * Returns the output size of the renderer.
   *
   * @return the output size of the renderer, in the format (width, height).
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IArea output_size() const noexcept;

  /**
   * Returns the blend mode that is being used by the renderer.
   *
   * @return the blend mode that is being used.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API BlendMode blend_mode() const noexcept;

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
  CENTURION_API Uint32 flags() const noexcept;

  /**
   * Indicates whether or not the <code>present()</code> method is synced with
   * the refresh rate of the screen.
   *
   * @return true if vsync is enabled; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool vsync_enabled() const noexcept;

  /**
   * Indicates whether or not the renderer is hardware accelerated.
   *
   * @return true if the renderer is hardware accelerated; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool accelerated() const noexcept;

  /**
   * Indicates whether or not the renderer is using software rendering.
   *
   * @return true if the renderer is software-based; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool software_based() const noexcept;

  /**
   * Indicates whether or not the renderer supports rendering to a target
   * texture.
   *
   * @return true if the renderer supports target texture rendering; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool supports_target_textures() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for
   * logical viewports. By default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports;
   * false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool using_integer_logical_scaling() const noexcept;

  /**
   * Indicates whether or not clipping is enabled. This is disabled by default.
   *
   * @return true if clipping is enabled; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool clipping_enabled() const noexcept;

  /**
   * Returns the currently selected rendering color. Set to black by default.
   *
   * @return the currently selected rendering color.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Color color() const noexcept;

  /**
   * Attempts to render the specified text in the supplied font using the
   * currently selected color and return the texture that contains the result.
   * Use the returned texture to actually render the text to the screen. This
   * method doesn't throw but might return null if something goes wrong.
   *
   * <p> This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param font the font that the text will be rendered in.
   * @return a unique pointer to a texture that contains the rendered text;
   * null if something went wrong.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  UniquePtr<Texture> text_blended(CZString text,
                                  const Font& font) const noexcept;

  /**
   * Attempts to render the specified text in the supplied font using the
   * currently selected color and return the texture that contains the result.
   * Use the returned texture to actually render the text to the screen. This
   * method doesn't throw but might return null if something goes wrong.
   *
   * <p> This method renders the text at the highest quality and uses
   * anti-aliasing. Use this when you want high quality text, but beware that
   * this is the slowest alternative. This method will wrap the supplied text
   * to fit the specified width. Furthermore, you can also manually control
   * the line breaks by inserting newline characters at the desired breakpoints.
   *
   * @param text the text that will be rendered. You can insert newline
   * characters in the string to indicate breakpoints, can safely be null.
   * @param wrap the width in pixels which marks the point that the text will
   * be wrapped after.
   * @param font the font that the text will be rendered in.
   * @return a unique pointer to a texture that contains the rendered text;
   * null if something went wrong.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  UniquePtr<Texture> text_blended_wrapped(CZString text,
                                          Uint32 wrap,
                                          const Font& font) const noexcept;

  /**
   * Attempts to render the specified text in the supplied font using the
   * currently selected color and return the texture that contains the result.
   * Use the returned texture to actually render the text to the screen. This
   * method doesn't throw but might return null if something goes wrong.
   *
   * <p> This method renders the text using anti-aliasing and with a box
   * behind the text. This alternative is probably a bit slower than
   * rendering solid text but about as fast as blended text. Use this
   * method when you want nice text, and can live with a box around it.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param bg the background color used for the box.
   * @param font the font that the text will be rendered in.
   * @return a unique pointer to a texture that contains the rendered text;
   * null if something went wrong.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  UniquePtr<Texture> text_shaded(CZString text,
                                 const Color& bg,
                                 const Font& font) const noexcept;

  /**
   * Attempts to render the specified text in the supplied font using the
   * currently selected color and return the texture that contains the result.
   * Use the returned texture to actually render the text to the screen. This
   * method doesn't throw but might return null if something goes wrong.
   *
   * <p> This method is the fastest at rendering text to a texture. It
   * doesn't use anti-aliasing so the text isn't very smooth. Use this method
   * when quality isn't as big of a concern and speed is important.
   *
   * @param text the text that will be rendered, can safely be null.
   * @param font the font that the text will be rendered in.
   * @return a unique pointer to a texture that contains the rendered text;
   * null if something went wrong.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  UniquePtr<Texture> text_solid(CZString text, const Font& font) const noexcept;

  /**
   * Returns the font associated with the specified name. This method returns
   * null if there is no font associated with the specified name.
   *
   * @param name the name associated with the desired font.
   * @return the font associated with the specified name; null if there is no
   * such font.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API SharedPtr<Font> font(const std::string& name) noexcept;

  /**
   * Indicates whether or not the renderer has a font associated with the
   * specified name.
   *
   * @param name the name that will be checked.
   * @return true if the renderer has a font associated with the specified
   * name; false otherwise.
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool has_font(const std::string& name) const noexcept;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IRect viewport() const noexcept;

  /**
   * Returns a textual representation of the renderer.
   *
   * @return a textual representation of the renderer.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Returns the number of available rendering drivers. Usually there is only
   * 1 available rendering driver.
   *
   * @return the number of available rendering drivers.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int render_drivers() noexcept;

  /**
   * Returns the number of available video drivers compiled into SDL.
   *
   * @return the number of available video drivers compiled into SDL.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static int video_drivers() noexcept;

  /**
   * Returns the information associated with a rendering driver.
   *
   * @param index the index of the rendering driver to query.
   * @return information about the specified rendering driver; nothing if
   * something went wrong.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static Optional<SDL_RendererInfo> driver_info(int index) noexcept;

  /**
   * Returns the translation viewport that is currently being used. Set to (0,
   * 0, 0, 0) by default.
   *
   * @return the translation viewport that is currently being used.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  const FRect& translation_viewport() const noexcept
  {
    return m_translationViewport;
  }

  /**
   * Returns a pointer to the internal SDL_Renderer. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied.
   *
   * @return a pointer to the internal SDL_Renderer.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Renderer* get() const noexcept { return m_renderer; }

  /**
   * Converts to SDL_Renderer*.
   *
   * @return a pointer to the internal SDL_Renderer instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Renderer*() noexcept { return m_renderer; }

  /**
   * Converts to SDL_Renderer*.
   *
   * @return a pointer to the internal SDL_Renderer instance.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator const SDL_Renderer*() const noexcept { return m_renderer; }

 private:
  SDL_Renderer* m_renderer = nullptr;
  FRect m_translationViewport = {{0, 0}, {0, 0}};
  std::unordered_map<std::string, SharedPtr<Font>> m_fonts;

  static constexpr SDL_RendererFlags defaultFlags =
      static_cast<SDL_RendererFlags>(SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC);

  /**
   * Destroys the resources associated with the renderer.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied renderer instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Renderer&& other) noexcept;

  /**
   * A helper method used by text rendering methods to create surfaces based
   * on the text and then convert it to fast textures.
   *
   * @param text the text that will be rendered.
   * @param render a lambda that creates a <code>SDL_Surface*</code> and
   * takes a <code>CZString</code> as its parameter.
   * @return a unique pointer to a texture; null if something went wrong.
   * @since 4.0.0
   */
  template <typename Lambda>
  CENTURION_NODISCARD UniquePtr<Texture> render_text(
      CZString text,
      Lambda&& render) const noexcept
  {
    if (!text) {
      return nullptr;
    }

    SDL_Surface* surface = render(text);
    if (!surface) {
      return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (texture) {
      return detail::make_unique<Texture>(texture);
    } else {
      return nullptr;
    }
  }

  /**
   * Returns the translated x-coordinate that corresponds to the supplied
   * x-coordinate.
   *
   * @param x the x-coordinate that will be translated.
   * @return the translated x-coordinate that corresponds to the supplied
   * x-coordinate.
   * @since 4.1.0
   */
  CENTURION_NODISCARD int tx(int x) const noexcept
  {
    return x - static_cast<int>(m_translationViewport.x());
  }

  /**
   * Returns the translated y-coordinate that corresponds to the supplied
   * y-coordinate.
   *
   * @param y the y-coordinate that will be translated.
   * @return the translated y-coordinate that corresponds to the supplied
   * y-coordinate.
   * @since 4.1.0
   */
  CENTURION_NODISCARD int ty(int y) const noexcept
  {
    return y - static_cast<int>(m_translationViewport.y());
  }

  /**
   * Returns the translated x-coordinate that corresponds to the supplied
   * x-coordinate.
   *
   * @param x the x-coordinate that will be translated.
   * @return the translated x-coordinate that corresponds to the supplied
   * x-coordinate.
   * @since 4.1.0
   */
  CENTURION_NODISCARD float tx(float x) const noexcept
  {
    return x - m_translationViewport.x();
  }

  /**
   * Returns the translated y-coordinate that corresponds to the supplied
   * y-coordinate.
   *
   * @param y the y-coordinate that will be translated.
   * @return the translated y-coordinate that corresponds to the supplied
   * y-coordinate.
   * @since 4.1.0
   */
  CENTURION_NODISCARD float ty(float y) const noexcept
  {
    return y - m_translationViewport.y();
  }
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

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "renderer.cpp"
#endif

#endif  // CENTURION_RENDERER_HEADER