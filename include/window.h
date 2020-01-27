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
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <gsl>
#include <SDL.h>
#include "centurion_api.h"

namespace centurion {

class IWindowListener;

/**
 * The Window class is a wrapper around an SDL_Window instance. Window instances can't be copied.
 * Instances of the Window class can be implicitly converted to SDL_Window*.
 *
 * @see IWindowListener
 * @since 3.0.0
 */
class CENTURION_API Window final {
 private:
  SDL_Window* window = nullptr;
  std::vector<IWindowListener*> windowListeners;

  /**
   * Notifies all registered window listeners that the window has been updated.
   *
   * @since 3.0.0
   */
  CENTURION_API void notify_window_listeners() noexcept;

 public:
  /**
   * Creates a window instance. The window will be hidden by default. When a window is being
   * created, it will look for a file called "centurion_icon.png", which it will attempt to use
   * as the default icon. However, the window can be created without any problem with the file
   * missing.
   *
   * @param title the title of thw window.
   * @param width the width of the window, must be greater than zero.
   * @param height the height of the window, must be greater than zero.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  CENTURION_API explicit Window(const std::string& title, int width, int height);

  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param width the width of the window, must be greater than zero.
   * @param height the height of the window, must be greater than zero.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  CENTURION_API explicit Window(int width, int height);

  /**
   * Creates a 800x600 window with the specified title.
   *
   * @param title the title of the window.
   * @since 3.0.0
   */
  CENTURION_API explicit Window(const std::string& title);

  /**
   * Creates a 800x600 window. The window will be hidden by default.
   *
   * @since 3.0.0
   */
  CENTURION_API Window();

  /**
   * Creates a window by moving the contents of the supplied window into the new window.
   *
   * @param other the window that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Window(Window&& other) noexcept;

  Window(const Window&) noexcept = delete;

  CENTURION_API ~Window();

  Window& operator=(const Window&) noexcept = delete;

  /**
   * Moves the contents of the supplied window into this window.
   *
   * @param other the window whose contents will be moved.
   * @return the changed window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API Window& operator=(Window&& other) noexcept;

  /**
   * Creates and returns a unique pointer to a window instance.
   *
   * @param title the title of the window.
   * @param width the width of the window.
   * @param height the height of the window.
   * @return a unique pointer to a window instance.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Window> unique(const std::string& title,
                                                      int width,
                                                      int height);

  /**
   * Creates and returns a unique pointer to a window instance.
   *
   * @param width the width of the window.
   * @param height the height of the window.
   * @return a unique pointer to a window instance.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Window> unique(int width, int height);

  /**
   * Creates and returns a unique pointer to a window instance.
   *
   * @param title the title of the window.
   * @return a unique pointer to a window instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Window> unique(const std::string& title);

  /**
   * Creates and returns a unique pointer to a Window instance.
   *
   * @return a unique pointer to a Window instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Window> unique();

  /**
   * Creates and returns a shared pointer to a window instance.
   *
   * @param title the title of the window.
   * @param width the width of the window.
   * @param height the height of the window.
   * @return a shared pointer to a window instance.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Window> shared(const std::string& title,
                                                      int width,
                                                      int height);

  /**
   * Creates and returns a shared pointer to a window instance.
   *
   * @param width the width of the window.
   * @param height the height of the window.
   * @return a shared pointer to a window instance.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Window> shared(int width, int height);

  /**
   * Creates and returns a shared pointer to a window instance.
   *
   * @param title the title of the window.
   * @return a shared pointer to a window instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Window> shared(const std::string& title);

  /**
   * Creates and returns a shared pointer to a Window instance.
   *
   * @return a shared pointer to a Window instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Window> shared();

  /**
   * Makes the window visible. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  CENTURION_API void show() noexcept;

  /**
   * Makes the window invisible. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  CENTURION_API void hide() noexcept;

  /**
   * Centers the window position relative to the screen. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  CENTURION_API void center() noexcept;

  /**
   * Raises this window above other windows and requests focus. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  CENTURION_API void raise() noexcept;

  /**
   * Adds a window listener to the window. Null listener are always silently ignored. The window
   * takes no ownership of supplied pointers.
   *
   * @param listener a window listener, may be null.
   * @since 3.0.0
   */
  CENTURION_API void add_window_listener(IWindowListener* listener) noexcept;

  /**
   * Sets whether or not the window is in fullscreen mode. Triggers a window listener update.
   *
   * @param fullscreen true if the window should enable fullscreen mode; false
   * otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_fullscreen(bool fullscreen) noexcept;

  /**
   * Sets whether or not the window is decorated. Triggers a window listener update. This property
   * is enabled by default.
   *
   * @param decorated true if the window should be decorated; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_decorated(bool decorated) noexcept;

  /**
   * Sets whether or not the window should be resizable. Triggers a window listener update.
   *
   * @param isResizable true if the window should be resizable; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_resizable(bool isResizable) noexcept;

  /**
   * Sets the width of the window. Triggers a window listener update.
   *
   * @param width the new width of the window.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_width(int width);

  /**
   * Sets the height of the window. Triggers a window listener update.
   *
   * @param height the new height of the window.
   * @throws invalid_argument if the supplied height isn't greater than
   * zero.
   * @since 3.0.0
   */
  CENTURION_API void set_height(int height);

  /**
   * Sets the icon that will be used by the window. Triggers a window listener update. The
   * supplied pointer should be freed by the caller.
   *
   * @param icon a pointer to the surface that will serve as the icon of the window.
   * @since 3.0.0
   */
  CENTURION_API void set_icon(gsl::not_null<SDL_Surface*> icon) noexcept;

  /**
   * Sets the title of the window. Triggers a window listener update.
   *
   * @param title the title of the window.
   * @since 3.0.0
   */
  CENTURION_API void set_title(const std::string& title) noexcept;

  /**
   * Sets the gamma brightness of the window. This operation is only supported if the window is
   * in fullscreen mode. This property will be reset every time the fullscreen mode is exited.
   * Triggers a window listener update.
   *
   * @param gamma the brightness value, in the range [0, 1].
   * @since 3.0.0
   */
  CENTURION_API void set_gamma(float gamma) noexcept;

  /**
   * Sets the opacity of the window. Triggers a window listener update.
   *
   * @param opacity the opacity, in the range [0, 1]. This value will be clamped to a value in
   * the legal range internally.
   * @since 3.0.0
   */
  CENTURION_API void set_opacity(float opacity) noexcept;

  /**
   * Sets the minimum size of the window. Triggers a window listener update.
   *
   * @param width the minimum width of the window, must be greater than zero.
   * @param height the minimum height of the window, must be greater than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_min_size(int width, int height) noexcept;

  /**
   * Sets the maximum size of the window. Triggers a window listener update.
   *
   * @param width the maximum width of the window, must be greater than zero.
   * @param height the maximum height of the window, must be greater than zero.
   * @since 3.0.0
   */
  CENTURION_API void set_max_size(int width, int height) noexcept;

  /**
   * Sets the position of the window. Note, it's possible to use SDL_WINDOWPOS_CENTERED or
   * SDL_WINDOWPOS_UNDEFINED as any of the arguments. Triggers a window listener update.
   *
   * @param x the screen x-coordinate that the window will adapt.
   * @param y the screen y-coordinate that the window will adapt.
   * @since 3.0.0
   */
  CENTURION_API void set_position(int x, int y) noexcept;

  /**
   * Sets whether or not the mouse should be confined within the window. This property is disabled
   * by default. Triggers a window listener update.
   *
   * @param grabMouse true if the mouse should be confined within the window; false otherwise.
   * @since 3.0.0
   */
  CENTURION_API void set_grab_mouse(bool grabMouse) noexcept;

  /**
   * Sets the overall brightness of the window. Triggers a window listener update.
   *
   * @param brightness the brightness value, in the range [0, 1]. A value outside this range will
   * be clamped to the closest valid value.
   * @since 3.0.0
   */
  CENTURION_API void set_brightness(float brightness) noexcept;

  /**
   * Indicates whether or not the window is decorated. The window is decorated by default.
   *
   * @return true if the window is decorated; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_decorated() const noexcept;

  /**
   * Indicates whether or not the window is currently grabbing the mouse input.
   *
   * @return true if the window is grabbing the mouse; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_grabbing_mouse() const noexcept;

  /**
   * Indicates whether or not the window is resizable.
   *
   * @return true if the window is resizable; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_resizable() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen mode.
   *
   * @return true if the window is in fullscreen mode; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_fullscreen() const noexcept;

  /**
   * Indicates whether or not the window is visible.
   *
   * @return true if the window is visible; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_visible() const noexcept;

  /**
   * Returns the current brightness value of the window. The default value of this property is 1.
   *
   * @return the current brightness of the window, in the range [0, 1].
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_brightness() const noexcept;

  /**
   * Returns the opacity of the window.
   *
   * @return the opacity of the window, in the range [0, 1].
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_opacity() const noexcept;

  /**
   * Returns the x-coordinate of the window position.
   *
   * @return the x-coordinate of the window position.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_x() const noexcept;

  /**
   * Returns the y-coordinate of the window position.
   *
   * @return the y-coordinate of the window position.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_y() const noexcept;

  /**
   * Returns a numerical ID of the window.
   *
   * @return a numerical ID of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_id() const noexcept;

  /**
   * Returns the current position of the window.
   *
   * @return the current position of the window, in the format (x, y).
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::pair<int, int> get_position() const noexcept;

  /**
   * Returns the minimum size of the window.
   *
   * @return the minimum size of the window, in the format (width, height).
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::pair<int, int> get_min_size() const noexcept;

  /**
   * Returns the maximum size of the window.
   *
   * @return the maximum size of the window, in the format (width, height).
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::pair<int, int> get_max_size() const noexcept;

  /**
   * Returns the current width of the window.
   *
   * @return the current width of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_width() const noexcept;

  /**
   * Returns the current height of the window.
   *
   * @return the current height of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_height() const noexcept;

  /**
   * Returns any renderer that is associated with this window. Note! If no renderer is associated
   * with the window, then a null pointer is returned. Please don't take ownership of the
   * returned renderer.
   *
   * @return a pointer to the renderer that is associated with this window; null if no such
   * renderer exists.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API SDL_Renderer* get_renderer() const noexcept;

  /**
   * Returns the pixel format of the window.
   *
   * @return the pixel format of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_pixel_format() const noexcept;

  /**
   * Returns the title of the window.
   *
   * @return the title of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string get_title() const noexcept;

  /**
   * Returns a textual representation of the window.
   *
   * @return a textual representation of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Implicit conversion to raw SDL_Window pointer.
   *
   * @return a pointer to the SDL_Window representation of the window.
   * @since 3.0.0
   */
  CENTURION_API /*implicit*/ operator SDL_Window*() const noexcept;
};

}