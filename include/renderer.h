/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <optional>
#include <gsl>
#include <SDL.h>
#include <SDL_image.h>
#include "centurion_api.h"
#include "color.h"

namespace centurion {

class Image;
class Font;
class Point;
class FPoint;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct. Rendering operations are
 * treated as const methods.
 *
 * @see SDL_Renderer
 * @since 3.0.0
 */
class CENTURION_API Renderer final {
 private:
  SDL_Renderer* renderer = nullptr;
  SDL_FRect translationViewport = {0, 0, 0, 0};

 public:
  // TODO a lot of rendering class would be prettier if there was a viewport-translated
  // alternative for all methods, ex: RenderTranslatedRect, RenderTranslatedImage, etc.

  /**
   * Creates a renderer based on the supplied SDL_Renderer.
   *
   * @param renderer a pointer to the SDL_Renderer that will be used by the
   * renderer.
   * @throws invalid_argument if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit Renderer(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates a renderer based on the supplied SDL_Window. By default, the internal renderer will be
   * created using the SDL_RENDERER_ACCELERATED and SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @param flags the SDL_RENDERER_x flags that will be used (OR'd together).
   * @see SDL_RendererFlags
   * @since 3.0.0
   */
  CENTURION_API explicit Renderer(gsl::not_null<SDL_Window*> window,
                                  uint32_t flags = SDL_RENDERER_ACCELERATED
                                      | SDL_RENDERER_PRESENTVSYNC);

  CENTURION_API Renderer(Renderer&& other) noexcept;

  Renderer(const Renderer&) noexcept = delete;

  CENTURION_API Renderer& operator=(Renderer&& other) noexcept;

  Renderer& operator=(const Renderer&) noexcept = delete;

  CENTURION_API ~Renderer();

  /**
   * Creates and returns a unique pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created renderer will be based
   * on, may not be null.
   * @return a unique pointer to a renderer.
   * @throws invalid_argument if the supplied renderer is null.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Renderer> unique(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a unique pointer to a renderer based on the supplied SDL_Window. By
   * default, the internal renderer will be created using the SDL_RENDERER_ACCELERATED and
   * SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @param flags the SDL_RENDERER_x flags that will be used (OR'd together).
   * @return a unique pointer to a renderer.
   * @see SDL_RendererFlags
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Renderer> unique(gsl::not_null<SDL_Window*> window,
                                                        uint32_t flags = SDL_RENDERER_ACCELERATED
                                                            | SDL_RENDERER_PRESENTVSYNC);

  /**
   * Creates and returns a shared pointer to a renderer.
   *
   * @param renderer a raw pointer to the SDL_Renderer that the created renderer will be based
   * on, may not be null.
   * @return a shared pointer to a renderer.
   * @throws invalid_argument if the supplied renderer is null.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Renderer> shared(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates and returns a shared pointer to a renderer based on the supplied SDL_Window. By
   * default, the internal renderer will be created using the SDL_RENDERER_ACCELERATED and
   * SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @param flags the SDL_RENDERER_x flags that will be used (OR'd together).
   * @return a shared pointer to a renderer.
   * @see SDL_RendererFlags
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Renderer> shared(gsl::not_null<SDL_Window*> window,
                                                        uint32_t flags = SDL_RENDERER_ACCELERATED
                                                            | SDL_RENDERER_PRESENTVSYNC);

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  CENTURION_API void clear() const noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  CENTURION_API void present() const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& texture, int x, int y) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& texture, float x, float y) const noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied width and/or height isn't
   * greater than zero.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& texture,
                                int x,
                                int y,
                                int width,
                                int height) const noexcept;

  /**
   * Renders a texture. This method has no effect if the supplied width and/or height isn't greater
   * than zero.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @param width the width of the rendered texture.
   * @param height the height of the rendered texture.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& texture,
                                float x,
                                float y,
                                float width,
                                float height) const noexcept;

  /**
   * Renders a part of an image at the specified destination.
   *
   * @param texture the source image.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& texture,
                                const SDL_Rect& source,
                                const SDL_FRect& destination) const noexcept;

  /**
   * Renders a part of an image at the specified destination. The position of the rendered image
   * is translated using the currently set translation viewport.
   *
   * @param texture the source image.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image_translated(const Image& texture,
                                           const SDL_Rect& source,
                                           const SDL_FRect& destination) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specified the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_Rect& destination,
                                double angle) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specified the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_FRect& destination,
                                double angle) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param center the rotation center point.
   * @param angle the angle of the image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_Rect& destination,
                                const Point& center,
                                double angle) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param center the rotation center point.
   * @param angle the angle of the image.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_FRect& destination,
                                const FPoint& center,
                                double angle) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @param flip the value that specifies whether or not the rendered image should be flipped.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_Rect& destination,
                                double angle,
                                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @param flip the value that specifies whether or not the rendered image should be flipped.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_FRect& destination,
                                double angle,
                                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @param center the rotation center point.
   * @param flip the value that specifies whether or not the rendered image should be flipped.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_Rect& destination,
                                double angle,
                                const Point& center,
                                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders an image.
   *
   * @param image the image that will be rendered.
   * @param source the rectangle that specifies the cutout of the source image.
   * @param destination the destination of the rendered image.
   * @param angle the angle of the image.
   * @param center the rotation center point.
   * @param flip the value that specifies whether or not the rendered image should be flipped.
   * @since 3.0.0
   */
  CENTURION_API void draw_image(const Image& image,
                                const SDL_Rect& source,
                                const SDL_FRect& destination,
                                double angle,
                                const FPoint& center,
                                SDL_RendererFlip flip) const noexcept;

  /**
   * Renders a filled rectangle with the currently selected color. This method has no effect if the
   * supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 3.0.0
   */
  CENTURION_API void fill_rect(int x, int y, int width, int height) const noexcept;

  /**
   * Renders a filled rectangle with the currently selected color. This method has no effect if the
   * supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 3.0.0
   */
  CENTURION_API void fill_rect(float x, float y, float width, float height) const noexcept;

  /**
   * Renders an outlined rectangle with the currently selected color. This method has no effect if
   * the supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 3.0.0
   */
  CENTURION_API void draw_rect(float x, float y, float width, float height) const noexcept;

  /**
   * Renders an outlined rectangle with the currently selected color. This method has no effect if
   * the supplied width and/or height isn't greater than zero.
   *
   * @param x the x-coordinate of the rendered rectangle.
   * @param y the y-coordinate of the rendered rectangle.
   * @param width the width of the rendered rectangle.
   * @param height the height of the rendered rectangle.
   * @since 3.0.0
   */
  CENTURION_API void draw_rect(int x, int y, int width, int height) const noexcept;

  /**
   * Renders a line in the currently selected color.
   *
   * @param start the start of the line.
   * @param end the end of the line.
   * @since 3.0.0
   */
  CENTURION_API void draw_line(const FPoint& start, const FPoint& end) const noexcept;

  /**
   * Renders a line in the currently selected color.
   *
   * @param start the start of the line.
   * @param end the end of the line.
   * @since 3.0.0
   */
  CENTURION_API void draw_line(const Point& start, const Point& end) const noexcept;

  /**
   * Renders a sequence of connected lines in the currently selected color.
   *
   * @param points the collection of points to draw the lines between.
   * @since 3.0.0
   */
  CENTURION_API void draw_lines(const std::vector<Point>& points) const noexcept;

  /**
   * Renders a string of text. Note that this method is rather inefficient, since it will
   * dynamically allocate a texture based on the supplied string for every call to this method.
   *
   * @param text the text that will be rendered in the supplied font.
   * @param x the x-coordinate of the rendered text.
   * @param y the y-coordinate of the rendered text.
   * @param font the font that will be used.
   * @since 3.0.0
   */
  CENTURION_API void draw_text(const std::string& text, float x, float y, const Font& font) const;

  /**
   * Sets the color that will be used by the renderer. This method is intentionally considered a
   * const-method, even if it technically changes the state of the renderer.
   *
   * @param red the red component value, in the range [0, 255].
   * @param green the green component value, in the range [0, 255].
   * @param blue the blue component value, in the range [0, 255].
   * @param alpha the alpha component value, in the range [0, 255]. Set to 255 by default.
   * @since 3.0.0
   */
  CENTURION_API void set_color(uint8_t red,
                               uint8_t green,
                               uint8_t blue,
                               uint8_t alpha = SDL_ALPHA_OPAQUE) const noexcept;

  /**
   * Sets the color that will be used by the renderer. This method is intentionally considered a
   * const-method, even if it technically changes the state of the renderer.
   *
   * @param color the color that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_color(const Color& color) const noexcept;

  /**
   * Sets the clipping area rectangle. Clipping is disabled by default.
   *
   * @param area the clip area rectangle; or std::nullopt to disable clipping.
   * @since 3.0.0
   */
  CENTURION_API void set_clip(std::optional<SDL_Rect> area) noexcept;

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_viewport(const SDL_Rect& viewport) noexcept;

  /**
   * Sets the translation viewport that will be used by the renderer. This method can be used in
   * order to be able to use the various X_translated-methods.
   *
   * @param viewport the rectangle that will be used as the translation viewport.
   * @since 3.0.0
   */
  CENTURION_API void set_translation_viewport(const SDL_FRect& viewport) noexcept;

  /**
   * Sets the blend mode that will be used by the renderer.
   *
   * @param blendMode the blend mode that will be used by the renderer.
   * @since 3.0.0
   */
  CENTURION_API void set_blend_mode(const SDL_BlendMode& blendMode) noexcept;

  /**
   * Sets the rendering target of the renderer. The supplied image must support being a render
   * target. Otherwise, this method will reset the render target.
   *
   * @param texture a pointer to the new target texture, can safely be null to indicate that the
   * default rendering target should be used.
   * @since 3.0.0
   */
  CENTURION_API void set_target(const Image* texture) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no effect if any of the
   * arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_scale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of the supplied
   * dimensions aren't greater than zero.
   *
   * @param width the logical width that will be used.
   * @param height the logical height that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_size(int width, int height) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By default, this
   * property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses. By default, this property is set to 0.
   *
   * @return the logical width that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_logical_width() const noexcept;

  /**
   * Returns the logical height that the renderer uses. By default, this property is set to 0.
   *
   * @return the logical height that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_logical_height() const noexcept;

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_x_scale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_y_scale() const noexcept;

  /**
   * Returns the current clipping rectangle, if there is one active.
   *
   * @return the current clipping rectangle; or std::nullopt if there is none.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::optional<SDL_Rect> get_clip() const noexcept;

  /**
   * Returns information about the renderer.
   *
   * @return information about the renderer.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API SDL_RendererInfo get_info() const noexcept;

  /**
   * Returns the output width of the renderer.
   *
   * @return the output width of the renderer.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_output_width() const noexcept;

  /**
   * Returns the output height of the renderer.
   *
   * @return the output height of the renderer.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_output_height() const noexcept;

  /**
   * Returns the output size of the renderer.
   *
   * @return the output size of the renderer, in the format (width, height).
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::pair<int, int> get_output_size() const noexcept;

  /**
   * Returns a bit mask that represents all of flags used when creating the renderer. The
   * possible values are
   * <ul>
   *   <li>a</li>
   * </ul>
   *
   * @return a bit mask that represents all of flags used when creating the renderer.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_flags() const noexcept;

  /**
   * Indicates whether or not the <code>present()</code> method is synced with the
   * refresh rate of the screen.
   *
   * @return true if vsync is enabled; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_vsync_enabled() const noexcept;

  /**
   * Indicates whether or not the renderer is hardware accelerated.
   *
   * @return true if the renderer is hardware accelerated; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_accelerated() const noexcept;

  /**
   * Indicates whether or not the renderer is using software rendering.
   *
   * @return true if the renderer is software-based; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_software_based() const noexcept;

  /**
   * Indicates whether or not the renderer supports rendering to a target texture.
   *
   * @return true if the renderer supports target texture rendering; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_supporting_target_textures() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for logical viewports. By
   * default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_using_integer_logical_scaling() const noexcept;

  /**
   * Indicates whether or not clipping is enabled. This is disabled by default.
   *
   * @return true if clipping is enabled; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_clipping_enabled() const noexcept;

  /**
   * Returns the currently selected rendering color. Set to black by default.
   *
   * @return the currently selected rendering color.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API Color get_color() const noexcept;

  /**
   * Attempts to create and return a pointer to an SDL_Texture instance that represents the
   * supplied string rendered with the supplied font. This method will not throw any
   * exception by itself, but dynamic memory allocation will occur behind-the-scenes.
   *
   * @param s the string that contains the content that will be rendered to a texture.
   * @param font a reference to the font that will be used.
   * @return a unique pointer to an image that represents the supplied string rendered with the
   * currently selected font; nullptr if the operation is unsuccessful.
   */
  [[nodiscard]]
  CENTURION_API std::unique_ptr<Image> create_image(const std::string& s, const Font& font) const;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API SDL_Rect get_viewport() const noexcept;

  /**
   * Returns the translation viewport that is currently being used. Set to (0, 0, 0, 0) by default.
   *
   * @return the translation viewport that is currently being used.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API const SDL_FRect& get_translation_viewport() const noexcept;

  /**
   * Returns a textual representation of the renderer.
   *
   * @return a textual representation of the renderer.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * @since 3.0.0
   */
  CENTURION_API /*implicit*/ operator SDL_Renderer*() const noexcept;
};

}