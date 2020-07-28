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

#ifndef CENTURION_GRAPHICS_HEADER
#define CENTURION_GRAPHICS_HEADER

#include <SDL_render.h>
#include <SDL_video.h>

#include <memory>
#include <optional>
#include <string>
#include <type_traits>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "centurion_types.hpp"
#include "pixel_format.hpp"
#include "point.hpp"
#include "surface.hpp"

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
 * @tparam Derived the type of the derived renderer.
 *
 * @since 5.0.0
 *
 * @see `window`
 * @see `window_handle`
 *
 * @headerfile graphics.hpp
 */
template <class Derived>
class basic_window {
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
   * @return the display index associated with the window; `nothing` if the
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

 protected:
  basic_window() noexcept = default;

 private:
  [[nodiscard]] auto ptr() noexcept -> SDL_Window*
  {
    return static_cast<Derived*>(this)->get();
  }

  [[nodiscard]] auto ptr() const noexcept -> SDL_Window*
  {
    return static_cast<const Derived*>(this)->get();
  }
};

}  // namespace centurion

#include "basic_window.ipp"

#endif  // CENTURION_GRAPHICS_HEADER
