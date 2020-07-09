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
 * @file window.hpp
 *
 * @brief Provides the windowing API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_WINDOW_HEADER
#define CENTURION_WINDOW_HEADER

#include <SDL.h>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "pixel_format.hpp"
#include "point.hpp"

namespace centurion {

class Surface;

/**
 * @class Window
 *
 * @brief The main class for dealing with windows in the library.
 *
 * @since 3.0.0
 *
 * @headerfile window.hpp
 */
class Window final {
 public:
  /**
   * @brief Creates a 800x600 window. The window will be hidden by default.
   *
   * @throws centurion_exception if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API Window();

  /**
   * @brief Creates a window based on the supplied SDL_Window instance.
   *
   * @details The created window will claim ownership of the supplied pointer.
   *
   * @param window a pointer to the window that will be claimed.
   *
   * @throws centurion_exception if the supplied pointer is null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit Window(owner<SDL_Window*> window);

  /**
   * @brief Creates a window instance.
   *
   * @details The window will be hidden by default.
   *
   * @param title the title of the window, may be null. If null, the empty
   * string is used.
   * @param size the size of the window, components must be greater than
   * zero, defaults to 800x600.
   *
   * @throws centurion_exception if the supplied width or height isn't
   * greater than zero or if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit Window(czstring title, area_i size = {800, 600});

  /**
   * @brief Creates a window by moving the supplied window.
   *
   * @param other the window that will be moved.
   *
   * @since 3.0.0
   */
  CENTURION_API
  Window(Window&& other) noexcept;

  Window(const Window&) noexcept = delete;

  CENTURION_API
  ~Window() noexcept;

  auto operator=(const Window&) noexcept -> Window& = delete;

  /**
   * @brief Moves the contents of the supplied window into this window.
   *
   * @param other the window whose contents will be moved.
   *
   * @return the window that absorbed the supplied window.
   *
   * @since 3.0.0
   */
  CENTURION_API
  auto operator=(Window&& other) noexcept -> Window&;

  /**
   * @copydoc Window()
   */
  CENTURION_QUERY
  static auto unique() -> std::unique_ptr<Window>;

  /**
   * @copydoc Window(owner<SDL_Window*>)
   */
  CENTURION_QUERY
  static auto unique(owner<SDL_Window*> window) -> std::unique_ptr<Window>;

  /**
   * @copydoc Window(czstring, area_i)
   */
  CENTURION_QUERY
  static auto unique(czstring title, area_i size = {800, 600})
      -> std::unique_ptr<Window>;

  /**
   * @copydoc Window()
   */
  CENTURION_QUERY
  static auto shared() -> std::shared_ptr<Window>;

  /**
   * @copydoc Window(owner<SDL_Window*>)
   */
  CENTURION_QUERY
  static auto shared(owner<SDL_Window*> window) -> std::shared_ptr<Window>;

  /**
   * @copydoc Window(czstring, area_i)
   */
  CENTURION_QUERY
  static auto shared(czstring title, area_i size = {800, 600})
      -> std::shared_ptr<Window>;

  /**
   * @brief Makes the window visible.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void show() noexcept;

  /**
   * @brief Makes the window invisible.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void hide() noexcept;

  /**
   * @brief Centers the window position relative to the screen.
   *
   * @note Windows are centered by default.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void center() noexcept;

  /**
   * @brief Raises this window above other windows and requests focus.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void raise() noexcept;

  /**
   * @brief Maximizes the window.
   *
   * @since 3.1.0
   */
  CENTURION_API
  void maximize() noexcept;

  /**
   * @brief Minimizes the window.
   *
   * @since 3.1.0
   */
  CENTURION_API
  void minimize() noexcept;

  /**
   * @brief Sets whether or not the window is in fullscreen mode.
   *
   * @param fullscreen `true` if the window should enable fullscreen mode;
   * `false` for windowed mode.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_fullscreen(bool fullscreen) noexcept;

  /**
   * @brief Sets whether or not the window is in fullscreen desktop mode.
   *
   * @details This mode is useful when you want to "fake" fullscreen mode.
   *
   * @param fullscreen `true` if the window should enable fullscreen desktop
   * mode; `false` for windowed mode.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_fullscreen_desktop(bool fullscreen) noexcept;

  /**
   * @brief Sets whether or not the window is decorated.
   *
   * @details This is enabled by default.
   *
   * @param decorated `true` if the window should be decorated; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_decorated(bool decorated) noexcept;

  /**
   * @brief Sets whether or not the window should be resizable.
   *
   * @param resizable `true` if the window should be resizable; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_resizable(bool resizable) noexcept;

  /**
   * @brief Sets the width of the window.
   *
   * @details This method has no effect if the supplied width isn't greater than
   * zero.
   *
   * @param width the new width of the window, must be greater than zero.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_width(int width) noexcept;

  /**
   * @brief Sets the height of the window.
   *
   * @details This method has no effect if the supplied height isn't greater
   * than zero.
   *
   * @param height the new height of the window, must be greater than zero.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_height(int height) noexcept;

  /**
   * @brief Sets the icon that will be used by the window.
   *
   * @param icon the surface that will serve as the icon of the window.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_icon(const Surface& icon) noexcept;

  /**
   * @brief Sets the title of the window.
   *
   * @details This method has no effect if the supplied string is null.
   *
   * @param title the title of the window, can safely be null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_title(czstring title) noexcept;

  /**
   * @brief Sets the opacity of the window.
   *
   * @details The supplied opacity will be clamped to a value in the legal
   * range.
   *
   * @param opacity the opacity, in the range [0, 1].
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_opacity(float opacity) noexcept;

  /**
   * @brief Sets the minimum size of the window.
   *
   * @details This method has no effect if any of the components aren't greater
   * than zero.
   *
   * @param size the minimum size of the window, components must be greater
   * than zero.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_min_size(area_i size) noexcept;

  /**
   * @brief Sets the maximum size of the window.
   *
   * @details This method has no effect if any of the components aren't greater
   * than zero.
   *
   * @param size the maximum size of the window, components must be greater
   * than zero.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_max_size(area_i size) noexcept;

  /**
   * @brief Sets the position of the window.
   *
   * @note It's possible to use `SDL_WINDOWPOS_CENTERED` or
   * `SDL_WINDOWPOS_UNDEFINED` as any of the arguments.
   *
   * @param x the new screen x-coordinate of the window.
   * @param y the new screen y-coordinate of the window.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_position(int x, int y) noexcept;

  /**
   * @brief Sets whether or not the mouse should be confined within the window.
   *
   * @brief This property is disabled by default.
   *
   * @param grabMouse `true` if the mouse should be confined within the window;
   * `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_grab_mouse(bool grabMouse) noexcept;

  /**
   * @brief Sets the overall brightness of the window.
   *
   * @details This operation is only supported if the window is in fullscreen
   * mode. This property will be reset every time the fullscreen mode is exited.
   *
   * @note A brightness value outside the legal range will be clamped to the
   * closest valid value.
   *
   * @param brightness the brightness value, in the range [0, 1].
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_brightness(float brightness) noexcept;

  /**
   * @brief Sets whether or not the mouse should be captured.
   *
   * @note The window might have to be visible in order for the mouse to be
   * captured.
   *
   * @param capturingMouse `true` if the mouse should be captured; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_capturing_mouse(bool capturingMouse) noexcept;

  /**
   * @brief Indicates whether or not the window is decorated.
   *
   * @details Windows are decorated by default.
   *
   * @return `true` if the window is decorated; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto decorated() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is currently grabbing the mouse
   * input.
   *
   * @return `true` if the window is grabbing the mouse; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto grabbing_mouse() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is resizable.
   *
   * @details By default, this property is set to false.
   *
   * @return `true` if the window is resizable; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto resizable() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is in fullscreen mode.
   *
   * @return `true` if the window is in fullscreen mode; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto fullscreen() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is in fullscreen desktop mode.
   *
   * @return `true` if the window is in fullscreen desktop mode;
   * `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto fullscreen_desktop() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is visible.
   *
   * @return `true` if the window is visible; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto visible() const noexcept -> bool;

  /**
   * @brief Returns the current brightness value of the window.
   *
   * @details The default value of this property is 1.
   *
   * @return the current brightness of the window, in the range [0, 1].
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto brightness() const noexcept -> float;

  /**
   * @brief Returns the opacity of the window.
   *
   * @return the opacity of the window, in the range [0, 1].
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto opacity() const noexcept -> float;

  /**
   * @brief Returns the x-coordinate of the window position.
   *
   * @return the x-coordinate of the window position.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto x() const noexcept -> int;

  /**
   * @brief Returns the y-coordinate of the window position.
   *
   * @return the y-coordinate of the window position.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto y() const noexcept -> int;

  /**
   * @brief Returns a numerical ID of the window.
   *
   * @return a numerical ID of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto id() const noexcept -> u32;

  /**
   * @brief Returns the display index associated with the window.
   *
   * @return the display index associated with the window; `nothing` if the
   * display index cannot be obtained.
   *
   * @since 3.1.0
   */
  CENTURION_QUERY
  auto display_index() const noexcept -> std::optional<int>;

  /**
   * @brief Returns the current position of the window.
   *
   * @note Windows are centered by default.
   *
   * @return the current position of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto position() const noexcept -> point_i;

  /**
   * @brief Returns the minimum size of the window.
   *
   * @return the minimum size of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto min_size() const noexcept -> area_i;

  /**
   * @brief Returns the maximum size of the window.
   *
   * @return the maximum size of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto max_size() const noexcept -> area_i;

  /**
   * @brief Returns the current width of the window.
   *
   * @return the current width of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto width() const noexcept -> int;

  /**
   * @brief Returns the current height of the window.
   *
   * @return the current height of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto height() const noexcept -> int;

  /**
   * @brief Indicates whether or not the window is usable with an
   * OpenGL-context.
   *
   * @return `true` if the window is compatible with an OpenGL-context; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto opengl() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is usable as a Vulkan surface.
   *
   * @return `true` if the window is is usable as a Vulkan surface; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto vulkan() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window has input focus.
   *
   * @note The window might have to be visible for this to be true.
   *
   * @return `true` if the window has input focus; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto has_input_focus() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window has mouse focus.
   *
   * @return `true` if the window has mouse focus; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto has_mouse_focus() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window wasn't created by SDL.
   *
   * @return `true` if the window wasn't created by SDL; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto is_foreign() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is capturing the mouse.
   *
   * @return `true` if the window is capturing the mouse; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto capturing_mouse() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is set to be always on top of
   * other windows.
   *
   * @return `true` if the window is always on top of other windows; false
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto always_on_top() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is minimized.
   *
   * @return `true` if the window is minimized; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto minimized() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is maximized.
   *
   * @return `true` if the window is maximized; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto maximized() const noexcept -> bool;

  /**
   * @brief Indicates whether or not a flag is set.
   *
   * @details Some of the use cases of this method can be replaced by more
   * explicit methods, e.g. `fullscreen()` instead of
   * `check_flag(SDL_WINDOW_FULLSCREEN)`.
   *
   * @param flag the flag that will be tested.
   *
   * @return `true` if the flag is set; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto check_flag(SDL_WindowFlags flag) const noexcept -> bool;

  /**
   * @brief Returns a mask that represents the flags associated with the window.
   *
   * @details You can check the returned mask using the `SDL_WindowFlags` enum.
   *
   * @return a mask that represents the flags associated with the window.
   *
   * @see `SDL_WindowFlags`
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto flags() const noexcept -> u32;

  /**
   * @brief Returns any renderer that is associated with this window.
   *
   * @note If no renderer is associated with the window, then a null pointer is
   * returned.
   *
   * @warning Don't take ownership of the returned pointer.
   * 
   * @todo Make this method return a view for a renderer instead.
   *
   * @return a pointer to the renderer that is associated with this window;
   * `nullptr` if no such renderer exists.
   *
   * @since 3.1.0
   */
  CENTURION_QUERY
  auto renderer() const noexcept -> const SDL_Renderer*;

  /**
   * @brief Returns the pixel format of the window.
   *
   * @return the pixel format used by the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto pixel_format() const noexcept -> PixelFormat;

  /**
   * @brief Returns the title of the window.
   *
   * @return the title of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto title() const noexcept -> czstring;

  /**
   * @brief Returns a textual representation of the window.
   *
   * @return a textual representation of the window.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto to_string() const -> std::string;

  /**
   * @brief Returns a pointer to the associated SDL window.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Window* { return m_window; }

  /**
   * @brief Converts to `SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Window*() noexcept { return m_window; }

  /**
   * @brief Converts to `const SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Window*() const noexcept
  {
    return m_window;
  }

 private:
  SDL_Window* m_window = nullptr;

  /**
   * @brief Destroys the resources associated with the window.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * @brief Moves the contents of the supplied window instance into this
   * instance.
   *
   * @param other the instance that will be moved.
   *
   * @since 4.0.0
   */
  void move(Window&& other) noexcept;
};

static_assert(std::is_final_v<Window>);
static_assert(std::is_nothrow_move_assignable_v<Window>);
static_assert(std::is_nothrow_move_constructible_v<Window>);
static_assert(!std::is_copy_assignable_v<Window>);
static_assert(!std::is_copy_constructible_v<Window>);
static_assert(std::is_convertible_v<Window, SDL_Window*>);
static_assert(std::is_default_constructible_v<Window>);
static_assert(std::is_nothrow_destructible_v<Window>);

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "window.cpp"
#endif

#endif  // CENTURION_WINDOW_HEADER