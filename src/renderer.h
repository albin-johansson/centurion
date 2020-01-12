#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <gsl>
#include <SDL.h>
#include <SDL_image.h>

namespace centurion {

class Image;
class Font;

/**
 * The Renderer class is a wrapper class for the SDL_Renderer struct. Rendering operations are
 * treated as const methods.
 *
 * @see SDL_Renderer
 * @since 3.0.0
 */
class Renderer {
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
   * @throws NullPointerException if the supplied pointer is null.
   * @since 3.0.0
   */
  explicit Renderer(gsl::owner<SDL_Renderer*> renderer);

  /**
   * Creates a renderer based on the supplied SDL_Window. The internal renderer will be created
   * using the SDL_RENDERER_ACCELERATED and SDL_RENDERER_PRESENTVSYNC flags.
   *
   * @param window a pointer to the SDL_Window that will be used to create the
   * renderer.
   * @param flags the SDL_RENDERER_x flags that will be used.
   * @see SDL_RendererFlags
   * @since 3.0.0
   */
  explicit Renderer(gsl::not_null<SDL_Window*> window,
                    uint32_t flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  Renderer(Renderer&& other) noexcept;

  Renderer(const Renderer&) noexcept = delete;

  Renderer& operator=(Renderer&& other) noexcept;

  Renderer& operator=(const Renderer&) noexcept = delete;

  virtual ~Renderer();

  /**
   * Clears the rendering target with the currently selected color.
   *
   * @since 3.0.0
   */
  void clear() const noexcept;

  /**
   * Applies the previous rendering calls to the rendering target.
   *
   * @since 3.0.0
   */
  void present() const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 3.0.0
   */
  void draw_image(const Image& texture, int x, int y) const noexcept;

  /**
   * Renders a texture.
   *
   * @param texture a reference to the texture that will be rendered.
   * @param x the x-coordinate of the rendered texture.
   * @param y the y-coordinate of the rendered texture.
   * @since 3.0.0
   */
  void draw_image(const Image& texture, float x, float y) const noexcept;

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
  void draw_image(const Image& texture, int x, int y, int width, int height) const noexcept;

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
  void draw_image(const Image& texture,
                  float x,
                  float y,
                  float width,
                  float height) const noexcept;

  void draw_image(const Image& texture,
                  const SDL_Rect& source,
                  const SDL_FRect& destination) const noexcept;

  void draw_image_translated(const Image& texture,
                             const SDL_Rect& source,
                             const SDL_FRect& destination) const noexcept;

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
  void fill_rect(int x, int y, int width, int height) const noexcept;

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
  void fill_rect(float x, float y, float width, float height) const noexcept;

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
  void draw_rect(float x, float y, float width, float height) const noexcept;

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
  void draw_rect(int x, int y, int width, int height) const noexcept;

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
  void draw_text(const std::string& text, float x, float y, const Font& font) const;

  /**
   * Sets the color that will be used by the renderer. This method is considered a const-method,
   * even if it technically changes the state of the renderer.
   *
   * @param red the red component value, in the range [0, 255].
   * @param green the green component value, in the range [0, 255].
   * @param blue the blue component value, in the range [0, 255].
   * @param alpha the alpha component value, in the range [0, 255]. Set to 255 by default.
   * @since 3.0.0
   */
  void set_color(uint8_t red,
                 uint8_t green,
                 uint8_t blue,
                 uint8_t alpha = SDL_ALPHA_OPAQUE) const noexcept;

  void set_color(const SDL_Color& color) const noexcept;

  /**
   * Sets the viewport that will be used by the renderer.
   *
   * @param viewport the viewport that will be used by the renderer.
   * @since 3.0.0
   */
  void set_viewport(const SDL_Rect& viewport) noexcept;

  /**
   * Sets the translation viewport that will be used by the renderer. This method can be used in
   * order to be able to use the various X_translated-methods.
   *
   * @param viewport the rectangle that will be used as the translation viewport.
   * @since 3.0.0
   */
  void set_translation_viewport(const SDL_FRect& viewport) noexcept;

  /**
   * Sets the blend mode that will be used by the renderer.
   *
   * @param blendMode the blend mode that will be used by the renderer.
   * @since 3.0.0
   */
  void set_blend_mode(const SDL_BlendMode& blendMode) noexcept;

  /**
   * Sets the viewport that will be used by the renderer. This method has no effect if any of the
   * arguments are less than or equal to zero.
   *
   * @param xScale the x-axis scale that will be used.
   * @param yScale the y-axis scale that will be used.
   * @since 3.0.0
   */
  void set_scale(float xScale, float yScale) noexcept;

  /**
   * Sets the logical dimensions of the renderer, which is useful for achieving
   * resolution-independent rendering. This method has no effect if either of the supplied
   * dimensions aren't greater than zero.
   *
   * @param width the logical width that will be used.
   * @param height the logical height that will be used.
   * @since 3.0.0
   */
  void set_logical_size(int width, int height) noexcept;

  /**
   * Sets whether or not to force integer scaling for the logical viewport. By default, this
   * property is set to false.
   *
   * @param useLogicalIntegerScale true if integer scaling should be used; false otherwise.
   * @since 3.0.0
   */
  void set_logical_integer_scale(bool useLogicalIntegerScale) noexcept;

  /**
   * Returns the logical width that the renderer uses.
   *
   * @return the logical width that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_logical_width() const noexcept;

  /**
   * Returns the logical height that the renderer uses.
   *
   * @return the logical height that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_logical_height() const noexcept;

  /**
   * Returns the x-axis scale that the renderer uses.
   *
   * @return the x-axis scale that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  float get_x_scale() const noexcept;

  /**
   * Returns the y-axis scale that the renderer uses.
   *
   * @return the y-axis scale that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  float get_y_scale() const noexcept;

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
  uint32_t get_flags() const noexcept;

  /**
   * Indicates whether or not the <code>present()</code> method is synced with the
   * refresh rate of the screen.
   *
   * @return true if vsync is enabled; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_vsync_enabled() const noexcept;

  /**
   * Indicates whether or not the renderer is hardware accelerated.
   *
   * @return true if the renderer is hardware accelerated; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_accelerated() const noexcept;

  /**
   * Indicates whether or not the renderer is using software rendering.
   *
   * @return true if the renderer is software-based; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_software_based() const noexcept;

  /**
   * Indicates whether or not the renderer supports rendering to a target texture.
   *
   * @return true if the renderer supports target texture rendering; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_supporting_target_textures() const noexcept;

  /**
   * Indicates whether or not the renderer uses integer scaling values for logical viewports. By
   * default, this property is set to false.
   *
   * @return true if the renderer uses integer scaling for logical viewports; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_using_integer_logical_scaling() const noexcept;

  /**
   * Returns the currently selected rendering color.
   *
   * @return the currently selected rendering color.
   * @since 3.0.0
   */
  [[nodiscard]]
  SDL_Color get_color() const noexcept;

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
  std::unique_ptr<Image> create_image(const std::string& s, const Font& font) const;

  /**
   * Returns the viewport that the renderer uses.
   *
   * @return the viewport that the renderer uses.
   * @since 3.0.0
   */
  [[nodiscard]]
  SDL_Rect get_viewport() const noexcept;

  /**
   * Returns the translation viewport that is currently being used.
   *
   * @return the translation viewport that is currently being used.
   * @since 3.0.0
   */
  [[nodiscard]]
  const SDL_FRect& get_translation_viewport() const noexcept;

  /*implicit*/ operator SDL_Renderer*() const noexcept;
};

}