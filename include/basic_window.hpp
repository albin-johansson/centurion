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

#ifndef CENTURION_BASIC_WINDOW_HEADER
#define CENTURION_BASIC_WINDOW_HEADER

#include <SDL_render.h>
#include <SDL_video.h>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "pixel_format.hpp"
#include "rect.hpp"
#include "surface.hpp"
#include "types.hpp"
#include "video.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/**
 * @class basic_window
 *
 * @ingroup graphics
 *
 * @brief Provides the base implementation for windows.
 *
 * @tparam Derived the type of the derived window.
 *
 * @since 5.0.0
 *
 * @see `window`
 * @see `window_handle`
 *
 * @headerfile basic_window.hpp
 */
template <class Derived>
class basic_window
{
 public:
  /**
   * @brief Makes the window visible.
   *
   * @since 3.0.0
   */
  void show() noexcept;

  /**
   * @brief Makes the window invisible.
   *
   * @since 3.0.0
   */
  void hide() noexcept;

  /**
   * @brief Centers the window position relative to the screen.
   *
   * @note Windows are centered by default.
   *
   * @since 3.0.0
   */
  void center() noexcept;

  /**
   * @brief Raises this window above other windows and requests focus.
   *
   * @since 3.0.0
   */
  void raise() noexcept;

  /**
   * @brief Maximizes the window.
   *
   * @since 3.1.0
   */
  void maximize() noexcept;

  /**
   * @brief Minimizes the window.
   *
   * @since 3.1.0
   */
  void minimize() noexcept;

  /**
   * @brief Sets whether or not the window is in fullscreen mode.
   *
   * @param fullscreen `true` if the window should enable fullscreen mode;
   * `false` for windowed mode.
   *
   * @since 3.0.0
   */
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
  void set_decorated(bool decorated) noexcept;

  /**
   * @brief Sets whether or not the window should be resizable.
   *
   * @param resizable `true` if the window should be resizable; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
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
  void set_height(int height) noexcept;

  /**
   * @brief Sets the size of the window.
   *
   * @details This method has no effect if any of the area components aren't
   * greater than zero.
   *
   * @param size the new size of the window, components must be greater than
   * zero.
   *
   * @since 5.0.0
   */
  void set_size(const iarea& size) noexcept;

  /**
   * @brief Sets the icon that will be used by the window.
   *
   * @param icon the surface that will serve as the icon of the window.
   *
   * @since 3.0.0
   */
  void set_icon(const surface& icon) noexcept;

  /**
   * @brief Sets the title of the window.
   *
   * @param title the title of the window, can't be null.
   *
   * @since 3.0.0
   */
  void set_title(nn_czstring title) noexcept;

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
  void set_min_size(const iarea& size) noexcept;

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
  void set_max_size(const iarea& size) noexcept;

  /**
   * @brief Sets the position of the window.
   *
   * @note It's possible to use `SDL_WINDOWPOS_CENTERED` or
   * `SDL_WINDOWPOS_UNDEFINED` as any of the components of the point.
   *
   * @param position the new position of the window.
   *
   * @since 5.0.0
   */
  void set_position(const ipoint& position) noexcept;

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
  void set_brightness(float brightness) noexcept;

  /**
   * @brief Sets whether or not the mouse should be captured.
   *
   * @note A window might have to be visible in order for the mouse to be
   * captured.
   *
   * @param capturingMouse `true` if the mouse should be captured; `false`
   * otherwise.
   *
   * @see `SDL_CaptureMouse`
   *
   * @since 5.0.0
   */
  static void set_capturing_mouse(bool capturingMouse) noexcept;

  /**
   * @brief Indicates whether or not the window is decorated.
   *
   * @details Windows are decorated by default.
   *
   * @return `true` if the window is decorated; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_decorated() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is currently grabbing the mouse
   * input.
   *
   * @return `true` if the window is grabbing the mouse; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto grabbing_mouse() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is resizable.
   *
   * @details By default, this property is set to false.
   *
   * @return `true` if the window is resizable; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_resizable() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is in fullscreen mode.
   *
   * @return `true` if the window is in fullscreen mode; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_fullscreen() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is in fullscreen desktop mode.
   *
   * @return `true` if the window is in fullscreen desktop mode;
   * `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_fullscreen_desktop() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is visible.
   *
   * @return `true` if the window is visible; `false` otherwise.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto is_visible() const noexcept -> bool;

  /**
   * @brief Returns the current brightness value of the window.
   *
   * @details The default value of this property is 1.
   *
   * @return the current brightness of the window, in the range [0, 1].
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto brightness() const noexcept -> float;

  /**
   * @brief Returns the opacity of the window.
   *
   * @return the opacity of the window, in the range [0, 1].
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto opacity() const noexcept -> float;

  /**
   * @brief Returns the x-coordinate of the window position.
   *
   * @return the x-coordinate of the window position.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto x() const noexcept -> int;

  /**
   * @brief Returns the y-coordinate of the window position.
   *
   * @return the y-coordinate of the window position.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto y() const noexcept -> int;

  /**
   * @brief Returns a numerical ID of the window.
   *
   * @return a numerical ID of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto id() const noexcept -> u32;

  /**
   * @brief Returns the display index associated with the window.
   *
   * @return the display index associated with the window; `std::nullopt` if the
   * display index cannot be obtained.
   *
   * @since 3.1.0
   */
  [[nodiscard]] auto display_index() const noexcept -> std::optional<int>;

  /**
   * @brief Returns the current position of the window.
   *
   * @note Windows are centered by default.
   *
   * @return the current position of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto position() const noexcept -> ipoint;

  /**
   * @brief Returns the minimum size of the window.
   *
   * @return the minimum size of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto min_size() const noexcept -> iarea;

  /**
   * @brief Returns the maximum size of the window.
   *
   * @return the maximum size of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto max_size() const noexcept -> iarea;

  /**
   * @brief Returns the current width of the window.
   *
   * @return the current width of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int;

  /**
   * @brief Returns the current height of the window.
   *
   * @return the current height of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int;

  /**
   * @brief Returns the current size of the window.
   *
   * @note Calling this function is slightly faster than calling both `width`
   * and `height` to obtain the window size.
   *
   * @return the size of the window.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea;

  /**
   * @brief Indicates whether or not the window is usable with an
   * OpenGL-context.
   *
   * @return `true` if the window is compatible with an OpenGL-context; false
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_opengl() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is usable as a Vulkan surface.
   *
   * @return `true` if the window is is usable as a Vulkan surface; false
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_vulkan() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window has input focus.
   *
   * @note The window might have to be visible for this to be true.
   *
   * @return `true` if the window has input focus; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto has_input_focus() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window has mouse focus.
   *
   * @return `true` if the window has mouse focus; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto has_mouse_focus() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window wasn't created by SDL.
   *
   * @return `true` if the window wasn't created by SDL; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_foreign() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is capturing the mouse.
   *
   * @return `true` if the window is capturing the mouse; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_capturing_mouse() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is set to be always on top of
   * other windows.
   *
   * @return `true` if the window is always on top of other windows; false
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto always_on_top() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is minimized.
   *
   * @return `true` if the window is minimized; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_minimized() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the window is maximized.
   *
   * @return `true` if the window is maximized; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto is_maximized() const noexcept -> bool;

  /**
   * @brief Indicates whether or not a flag is set.
   *
   * @details Some of the use cases of this method can be replaced by more
   * explicit methods, e.g. `is_fullscreen()` instead of
   * `check_flag(SDL_WINDOW_FULLSCREEN)`.
   *
   * @param flag the flag that will be tested.
   *
   * @return `true` if the flag is set; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto check_flag(SDL_WindowFlags flag) const noexcept -> bool;

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
  [[nodiscard]] auto flags() const noexcept -> u32;

  /**
   * @brief Returns the pixel format of the window.
   *
   * @return the pixel format used by the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto get_pixel_format() const noexcept -> pixel_format;

  /**
   * @brief Returns the title of the window.
   *
   * @return the title of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto title() const -> std::string;

  [[nodiscard]] auto ptr() const noexcept -> SDL_Window*;

 protected:
  basic_window() noexcept = default;

 private:
  template <typename Traits>
  friend auto get_renderer(const basic_window<Traits>& window) noexcept
      -> renderer_handle;
};

template <class Derived>
auto basic_window<Derived>::ptr() const noexcept -> SDL_Window*
{
  return static_cast<const Derived*>(this)->get();
}

template <class Derived>
void basic_window<Derived>::show() noexcept
{
  SDL_ShowWindow(ptr());
}

template <class Derived>
void basic_window<Derived>::hide() noexcept
{
  SDL_HideWindow(ptr());
}

template <class Derived>
void basic_window<Derived>::raise() noexcept
{
  SDL_RaiseWindow(ptr());
}

template <class Derived>
void basic_window<Derived>::center() noexcept
{
  set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED});
}

template <class Derived>
void basic_window<Derived>::maximize() noexcept
{
  SDL_MaximizeWindow(ptr());
}

template <class Derived>
void basic_window<Derived>::minimize() noexcept
{
  SDL_MinimizeWindow(ptr());
}

template <class Derived>
void basic_window<Derived>::set_fullscreen(bool fullscreen) noexcept
{
  const auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(ptr(), fullscreen ? flag : 0);

  if (!fullscreen) {
    set_brightness(1);
  }
}

template <class Derived>
void basic_window<Derived>::set_fullscreen_desktop(bool fullscreen) noexcept
{
  const auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetWindowFullscreen(ptr(), fullscreen ? flag : 0);
}

template <class Derived>
void basic_window<Derived>::set_decorated(bool decorated) noexcept
{
  SDL_SetWindowBordered(ptr(), detail::convert_bool(decorated));
}

template <class Derived>
void basic_window<Derived>::set_resizable(bool resizable) noexcept
{
  SDL_SetWindowResizable(ptr(), detail::convert_bool(resizable));
}

template <class Derived>
void basic_window<Derived>::set_width(int width) noexcept
{
  if (width > 0) {
    SDL_SetWindowSize(ptr(), width, height());
  }
}

template <class Derived>
void basic_window<Derived>::set_height(int height) noexcept
{
  if (height > 0) {
    SDL_SetWindowSize(ptr(), width(), height);
  }
}

template <class Derived>
void basic_window<Derived>::set_size(const iarea& size) noexcept
{
  if ((size.width > 0) && (size.height > 0)) {
    SDL_SetWindowSize(ptr(), size.width, size.height);
  }
}

template <class Derived>
void basic_window<Derived>::set_icon(const surface& icon) noexcept
{
  SDL_SetWindowIcon(ptr(), icon.get());
}

template <class Derived>
void basic_window<Derived>::set_title(nn_czstring title) noexcept
{
  SDL_SetWindowTitle(ptr(), title);
}

template <class Derived>
void basic_window<Derived>::set_opacity(float opacity) noexcept
{
  SDL_SetWindowOpacity(ptr(), opacity);
}

template <class Derived>
void basic_window<Derived>::set_min_size(const iarea& size) noexcept
{
  SDL_SetWindowMinimumSize(ptr(), size.width, size.height);
}

template <class Derived>
void basic_window<Derived>::set_max_size(const iarea& size) noexcept
{
  SDL_SetWindowMaximumSize(ptr(), size.width, size.height);
}

template <class Derived>
void basic_window<Derived>::set_position(const ipoint& position) noexcept
{
  SDL_SetWindowPosition(ptr(), position.x(), position.y());
}

template <class Derived>
void basic_window<Derived>::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(ptr(), detail::convert_bool(grabMouse));
}

template <class Derived>
void basic_window<Derived>::set_brightness(float brightness) noexcept
{
  if (is_fullscreen()) {
    SDL_SetWindowBrightness(ptr(), std::clamp(brightness, 0.0f, 1.0f));
  }
}

template <class Derived>
void basic_window<Derived>::set_capturing_mouse(bool capturingMouse) noexcept
{
  SDL_CaptureMouse(detail::convert_bool(capturingMouse));
}

template <class Derived>
auto basic_window<Derived>::is_decorated() const noexcept -> bool
{
  return !(flags() & SDL_WINDOW_BORDERLESS);
}

template <class Derived>
auto basic_window<Derived>::grabbing_mouse() const noexcept -> bool
{
  return SDL_GetWindowGrab(ptr());
}

template <class Derived>
auto basic_window<Derived>::is_resizable() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_RESIZABLE);
}

template <class Derived>
auto basic_window<Derived>::is_fullscreen() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN);
}

template <class Derived>
auto basic_window<Derived>::is_fullscreen_desktop() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN_DESKTOP);
}

template <class Derived>
auto basic_window<Derived>::is_visible() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_SHOWN);
}

template <class Derived>
auto basic_window<Derived>::is_opengl() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_OPENGL);
}

template <class Derived>
auto basic_window<Derived>::is_vulkan() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_VULKAN);
}

template <class Derived>
auto basic_window<Derived>::has_input_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_INPUT_FOCUS);
}

template <class Derived>
auto basic_window<Derived>::has_mouse_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_FOCUS);
}

template <class Derived>
auto basic_window<Derived>::is_foreign() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FOREIGN);
}

template <class Derived>
auto basic_window<Derived>::is_capturing_mouse() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_CAPTURE);
}

template <class Derived>
auto basic_window<Derived>::always_on_top() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_ALWAYS_ON_TOP);
}

template <class Derived>
auto basic_window<Derived>::is_minimized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MINIMIZED);
}

template <class Derived>
auto basic_window<Derived>::is_maximized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MAXIMIZED);
}

template <class Derived>
auto basic_window<Derived>::check_flag(SDL_WindowFlags flag) const noexcept
    -> bool
{
  return static_cast<bool>(flags() & flag);
}

template <class Derived>
auto basic_window<Derived>::flags() const noexcept -> u32
{
  return SDL_GetWindowFlags(ptr());
}

template <class Derived>
auto basic_window<Derived>::brightness() const noexcept -> float
{
  return SDL_GetWindowBrightness(ptr());
}

template <class Derived>
auto basic_window<Derived>::opacity() const noexcept -> float
{
  float opacity{1};
  SDL_GetWindowOpacity(ptr(), &opacity);
  return opacity;
}

template <class Derived>
auto basic_window<Derived>::x() const noexcept -> int
{
  int x{};
  SDL_GetWindowPosition(ptr(), &x, nullptr);
  return x;
}

template <class Derived>
auto basic_window<Derived>::y() const noexcept -> int
{
  int y{};
  SDL_GetWindowPosition(ptr(), nullptr, &y);
  return y;
}

template <class Derived>
auto basic_window<Derived>::position() const noexcept -> ipoint
{
  int x{};
  int y{};
  SDL_GetWindowPosition(ptr(), &x, &y);
  return {x, y};
}

template <class Derived>
auto basic_window<Derived>::id() const noexcept -> u32
{
  return SDL_GetWindowID(ptr());
}

template <class Derived>
auto basic_window<Derived>::display_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_GetWindowDisplayIndex(ptr());
  if (index != -1) {
    return index;
  } else {
    return std::nullopt;
  }
}

template <class Derived>
auto basic_window<Derived>::min_size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_GetWindowMinimumSize(ptr(), &width, &height);
  return {width, height};
}

template <class Derived>
auto basic_window<Derived>::max_size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_GetWindowMaximumSize(ptr(), &width, &height);
  return {width, height};
}

template <class Derived>
auto basic_window<Derived>::width() const noexcept -> int
{
  int width{};
  SDL_GetWindowSize(ptr(), &width, nullptr);
  return width;
}

template <class Derived>
auto basic_window<Derived>::height() const noexcept -> int
{
  int height{};
  SDL_GetWindowSize(ptr(), nullptr, &height);
  return height;
}

template <class Derived>
auto basic_window<Derived>::size() const noexcept -> iarea
{
  iarea size{};
  SDL_GetWindowSize(ptr(), &size.width, &size.height);
  return size;
}

template <class Derived>
auto basic_window<Derived>::get_pixel_format() const noexcept -> pixel_format
{
  return static_cast<pixel_format>(SDL_GetWindowPixelFormat(ptr()));
}

template <class Derived>
auto basic_window<Derived>::title() const -> std::string
{
  return SDL_GetWindowTitle(ptr());
}

}  // namespace centurion

#endif  // CENTURION_BASIC_WINDOW_HEADER
