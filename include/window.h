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
 * This header provides the @link centurion::Window @endlink class.
 *
 * @file window.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_WINDOW_HEADER
#define CENTURION_WINDOW_HEADER

#include <SDL.h>

#include "area.h"
#include "centurion_api.h"
#include "centurion_utils.h"
#include "pixel_format.h"
#include "point.h"

namespace centurion {

class Surface;

/**
 * The Window class is a wrapper around an SDL_Window instance. Window instances
 * can't be copied. Instances of the Window class can be implicitly converted to
 * SDL_Window*.
 *
 * @par General information
 * | Property              | Value                                |
 * | --------------------- | :----------------------------------- |
 * | Default constructible | Yes                                  |
 * | Movable               | Yes                                  |
 * | Copyable              | No                                   |
 * | Explicit conversions  | None                                 |
 * | Implicit conversions  | `SDL_Window*`, `const SDL_Window*`   |
 * | Overloaded operators  | None                                 |
 * | Namespace             | @link ::centurion @endlink           |
 *
 * @headerfile window.h <>
 * @since 3.0.0
 */
class Window final {
 public:
  /**
   * Creates a 800x600 window. The window will be hidden by default.
   *
   * @throws CenturionException if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_API Window();

  /**
   * Creates a window based on the supplied SDL_Window instance. The created
   * window will claim ownership of the supplied pointer.
   *
   * @param window a pointer to the SDL_Window that will be claimed.
   * @throws CenturionException if the supplied pointer is null.
   * @since 4.0.0
   */
  CENTURION_API explicit Window(Owner<SDL_Window*> window);

  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param title the title of the window, may be null. If null, the empty
   * string is used.
   * @param size the size of the window, components must be greater than
   * zero, defaults to 800x600.
   * @throws CenturionException if the supplied width or height isn't
   * greater than zero or if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_API explicit Window(CZString title, IArea size = {800, 600});

  /**
   * Creates a window by moving the contents of the supplied window into the new
   * window.
   *
   * @param other the window that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Window(Window&& other) noexcept;

  Window(const Window&) noexcept = delete;

  CENTURION_API ~Window() noexcept;

  Window& operator=(const Window&) noexcept = delete;

  /**
   * Moves the contents of the supplied window into this window.
   *
   * @param other the window whose contents will be moved.
   * @return the changed window.
   * @since 3.0.0
   */
  CENTURION_API Window& operator=(Window&& other) noexcept;

  /**
   * Creates and returns a unique pointer to a Window instance.
   *
   * @return a unique pointer to a Window instance.
   * @throws CenturionException if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Window> unique();

  /**
   * Creates and returns a unique pointer to a window instance. The created
   * window will claim ownership of the supplied pointer.
   *
   * @param window a pointer to the SDL_Window that will be claimed.
   * @return a unique pointer to a window instance.
   * @throws CenturionException if the supplied pointer is null or if the window
   * cannot be created.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Window> unique(Owner<SDL_Window*> window);

  /**
   * Creates and returns a unique pointer to a window instance.
   *
   * @param title the title of the window, may be null. If null, the empty
   * string is used.
   * @param size the size of the window, components must be greater than
   * zero, defaults to 800x600.
   * @return a unique pointer to a window instance.
   * @throws CenturionException if the supplied width or height values aren't
   * greater than zero or if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static UniquePtr<Window> unique(CZString title,
                                                IArea size = {800, 600});

  /**
   * Creates and returns a shared pointer to a Window instance.
   *
   * @return a shared pointer to a Window instance.
   * @throws CenturionException if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Window> shared();

  /**
   * Creates and returns a shared pointer to a window instance. The created
   * window will claim ownership of the supplied pointer.
   *
   * @param window a pointer to the SDL_Window that will be claimed.
   * @return a shared pointer to a window instance.
   * @throws CenturionException if the supplied pointer is null.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Window> shared(Owner<SDL_Window*> window);

  /**
   * Creates and returns a shared pointer to a window instance.
   *
   * @param title the title of the window, may be null. If null, the empty
   * string is used.
   * @param size the size of the window, components must be greater than zero,
   * defaults to 800x600.
   * @return a shared pointer to a window instance.
   * @throws CenturionException if the supplied width or height values aren't
   * greater than zero or if the window cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API static SharedPtr<Window> shared(CZString title,
                                                IArea size = {800, 600});

  /**
   * Makes the window visible.
   *
   * @since 3.0.0
   */
  CENTURION_API void show() noexcept;

  /**
   * Makes the window invisible.
   *
   * @since 3.0.0
   */
  CENTURION_API void hide() noexcept;

  /**
   * Centers the window position relative to the screen. Windows are centered by
   * default.
   *
   * @since 3.0.0
   */
  CENTURION_API void center() noexcept;

  /**
   * Raises this window above other windows and requests focus.
   *
   * @since 3.0.0
   */
  CENTURION_API void raise() noexcept;

  /**
   * Maximizes the window.
   *
   * @since 3.1.0
   */
  CENTURION_API void maximize() noexcept;

  /**
   * Minimizes the window.
   *
   * @since 3.1.0
   */
  CENTURION_API void minimize() noexcept;

  /**
   * Sets whether or not the window is in fullscreen mode.
   *
   * @param fullscreen true if the window should enable fullscreen mode; false
   * for windowed mode.
   * @since 3.0.0
   */
  CENTURION_API void set_fullscreen(bool fullscreen) noexcept;

  /**
   * Sets whether or not the window is in fullscreen desktop mode. This mode
   * is useful when you want to "fake" fullscreen mode.
   *
   * @param fullscreen true if the window should enable fullscreen desktop
   * mode; false for windowed mode.
   * @since 4.0.0
   */
  CENTURION_API void set_fullscreen_desktop(bool fullscreen) noexcept;

  /**
   * Sets whether or not the window is decorated. This property is enabled by
   * default.
   *
   * @param decorated true if the window should be decorated; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_decorated(bool decorated) noexcept;

  /**
   * Sets whether or not the window should be resizable.
   *
   * @param resizable true if the window should be resizable; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_resizable(bool resizable) noexcept;

  /**
   * Sets the width of the window. This method has no effect if the supplied
   * width isn't greater than zero.
   *
   * @param width the new width of the window, must be greater than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_width(int width) noexcept;

  /**
   * Sets the height of the window. This method has no effect if the supplied
   * height isn't greater than zero.
   *
   * @param height the new height of the window, must be greater than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_height(int height) noexcept;

  /**
   * Sets the icon that will be used by the window.
   *
   * @param icon the surface that will serve as the icon of the window.
   * @since 3.0.0
   */
  CENTURION_API void set_icon(const Surface& icon) noexcept;

  /**
   * Sets the title of the window. This method has no effect if the supplied
   * string is null.
   *
   * @param title the title of the window, can safely be null.
   * @since 3.0.0
   */
  CENTURION_API void set_title(CZString title) noexcept;

  /**
   * Sets the opacity of the window.
   *
   * @param opacity the opacity, in the range [0, 1]. This value will be clamped
   * to a value in the legal range internally.
   * @since 3.0.0
   */
  CENTURION_API void set_opacity(float opacity) noexcept;

  /**
   * Sets the minimum size of the window. This method has no effect if any of
   * the components aren't greater than zero.
   *
   * @param size the minimum size of the window, components must be greater
   * than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_min_size(IArea size) noexcept;

  /**
   * Sets the maximum size of the window. This method has no effect if any of
   * the components aren't greater than zero.
   *
   * @param size the maximum size of the window, components must be greater
   * than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_max_size(IArea size) noexcept;

  /**
   * Sets the position of the window. Note, it's possible to use
   * SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED as any of the arguments.
   *
   *
   * @param x the screen x-coordinate that the window will adapt.
   * @param y the screen y-coordinate that the window will adapt.
   * @since 3.0.0
   */
  CENTURION_API void set_position(int x, int y) noexcept;

  /**
   * Sets whether or not the mouse should be confined within the window. This
   * property is disabled by default.
   *
   * @param grabMouse true if the mouse should be confined within the window;
   * false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_grab_mouse(bool grabMouse) noexcept;

  /**
   * Sets the overall brightness of the window. This operation is only supported
   * if the window is in fullscreen mode. This property will be reset every time
   * the fullscreen mode is exited.
   *
   * @param brightness the brightness value, in the range [0, 1]. A value
   * outside this range will be clamped to the closest valid value.
   * @since 3.0.0
   */
  CENTURION_API void set_brightness(float brightness) noexcept;

  /**
   * Sets whether or not the mouse should be captured. The window might have
   * to be visible in order for the mouse to be captured.
   *
   * @param capturingMouse true if the mouse should be captured; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_API void set_capturing_mouse(bool capturingMouse) noexcept;

  /**
   * Indicates whether or not the window is decorated. The window is decorated
   * by default.
   *
   * @return true if the window is decorated; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool decorated() const noexcept;

  /**
   * Indicates whether or not the window is currently grabbing the mouse input.
   *
   * @return true if the window is grabbing the mouse; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool grabbing_mouse() const noexcept;

  /**
   * Indicates whether or not the window is resizable. By default, this
   * property is set to false.
   *
   * @return true if the window is resizable; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool resizable() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen mode.
   *
   * @return true if the window is in fullscreen mode; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool fullscreen() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen desktop mode.
   *
   * @return true if the window is in fullscreen desktop mode; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool fullscreen_desktop() const noexcept;

  /**
   * Indicates whether or not the window is visible.
   *
   * @return true if the window is visible; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool visible() const noexcept;

  /**
   * Returns the current brightness value of the window. The default value of
   * this property is 1.
   *
   * @return the current brightness of the window, in the range [0, 1].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float brightness() const noexcept;

  /**
   * Returns the opacity of the window.
   *
   * @return the opacity of the window, in the range [0, 1].
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API float opacity() const noexcept;

  /**
   * Returns the x-coordinate of the window position.
   *
   * @return the x-coordinate of the window position.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int x() const noexcept;

  /**
   * Returns the y-coordinate of the window position.
   *
   * @return the y-coordinate of the window position.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int y() const noexcept;

  /**
   * Returns a numerical ID of the window.
   *
   * @return a numerical ID of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 id() const noexcept;

  /**
   * Returns the display index associated with the window.
   *
   * @return the display index associated with the window; nothing if the
   * display index cannot be obtained.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API Optional<int> display_index() const noexcept;

  /**
   * Returns the current position of the window. Windows are centered by
   * default.
   *
   * @return the current position of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IPoint position() const noexcept;

  /**
   * Returns the minimum size of the window.
   *
   * @return the minimum size of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IArea min_size() const noexcept;

  /**
   * Returns the maximum size of the window.
   *
   * @return the maximum size of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API IArea max_size() const noexcept;

  /**
   * Returns the current width of the window.
   *
   * @return the current width of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int width() const noexcept;

  /**
   * Returns the current height of the window.
   *
   * @return the current height of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int height() const noexcept;

  /**
   * Indicates whether or not the window is usable with an OpenGL-context.
   *
   * @return true if the window is compatible with an OpenGL-context; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool opengl() const noexcept;

  /**
   * Indicates whether or not the window is usable as a Vulkan surface.
   *
   * @return true if the window is is usable as a Vulkan surface; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool vulkan() const noexcept;

  /**
   * Indicates whether or not the window has input focus. The window might
   * have to be visible for this to be true.
   *
   * @return true if the window has input focus; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool has_input_focus() const noexcept;

  /**
   * Indicates whether or not the window has mouse focus.
   *
   * @return true if the window has mouse focus; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool has_mouse_focus() const noexcept;

  /**
   * Indicates whether or not the window wasn't created by SDL.
   *
   * @return true if the window wasn't created by SDL; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_foreign() const noexcept;

  /**
   * Indicates whether or not the window is capturing the mouse.
   *
   * @return true if the window is capturing the mouse; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool capturing_mouse() const noexcept;

  /**
   * Indicates whether or not the window is set to be always on top of other
   * windows.
   *
   * @return true if the window is always on top of other windows; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool always_on_top() const noexcept;

  /**
   * Indicates whether or not the window is minimized.
   *
   * @return true if the window is minimized; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool minimized() const noexcept;

  /**
   * Indicates whether or not the window is maximized.
   *
   * @return true if the window is maximized; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool maximized() const noexcept;

  /**
   * Indicates whether or not a flag is set. Some of the use cases of this
   * method can be replaced by more explicit methods, e.g. <code>fullscreen()
   * </code> instead of <code>check_flag(SDL_WINDOW_FULLSCREEN)</code>.
   *
   * @param flag the flag that will be tested.
   * @return true if the flag is set; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool check_flag(SDL_WindowFlags flag) const noexcept;

  /**
   * Returns a mask that represents the flags associated with the window. You
   * can check the returned mask using the SDL_WindowFlags enum.
   *
   * @return a mask that represents the flags associated with the window.
   * @since 4.0.0
   * @see SDL_WindowFlags
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 flags() const noexcept;

  /**
   * Returns any renderer that is associated with this window. Note! If no
   * renderer is associated with the window, then a null pointer is returned.
   * Please don't take ownership of the returned renderer.
   *
   * @return a pointer to the renderer that is associated with this window; null
   * if no such renderer exists.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API const SDL_Renderer* renderer() const noexcept;

  /**
   * Returns the pixel format of the window.
   *
   * @return the pixel format of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API PixelFormat pixel_format() const noexcept;

  /**
   * Returns the title of the window.
   *
   * @return the title of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API CZString title() const noexcept;

  /**
   * Returns a textual representation of the window.
   *
   * @return a textual representation of the window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Returns a pointer to the internal SDL_Window. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied.
   *
   * @return a pointer to the internal SDL_Window.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Window* get() const noexcept { return m_window; }

  /**
   * Implicitly converts to a pointer to SDL_Window.
   *
   * @return a pointer to the internal SDL_Window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Window*() noexcept { return m_window; }

  /**
   * Implicitly converts to a pointer to SDL_Window.
   *
   * @return a pointer to the internal SDL_Window.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator const SDL_Window*() const noexcept { return m_window; }

 private:
  SDL_Window* m_window = nullptr;

  /**
   * Destroys the resources associated with the window.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied window instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Window&& other) noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Window>::value, "Window isn't final!");
#endif

static_assert(std::is_nothrow_move_assignable<Window>::value,
              "Window isn't nothrow move assignable!");

static_assert(std::is_nothrow_move_constructible<Window>::value,
              "Window isn't nothrow move constructible!");

static_assert(!std::is_copy_assignable<Window>::value,
              "Window is copy assignable!");

/* When a distinguished but elderly scientist states that something is
   possible, he is almost certainly right. When he states that something is
   impossible, he is very probably wrong. */

static_assert(!std::is_copy_constructible<Window>::value,
              "Window is copy constructible!");

static_assert(std::is_convertible<Window, SDL_Window*>::value,
              "Window isn't convertible to SDL_Window*!");

static_assert(std::is_default_constructible<Window>::value,
              "Window isn't default constructible!");

static_assert(std::is_nothrow_destructible<Window>::value,
              "Window isn't nothrow destructible!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "window.cpp"
#endif

#endif  // CENTURION_WINDOW_HEADER