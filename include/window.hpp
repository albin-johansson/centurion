/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_WINDOW_HEADER
#define CENTURION_WINDOW_HEADER

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // conditional_t, true_type, false_type, enable_if_t

#include "area.hpp"
#include "centurion_cfg.hpp"
#include "czstring.hpp"
#include "detail/address_of.hpp"
#include "detail/clamp.hpp"
#include "detail/convert_bool.hpp"
#include "detail/max.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/to_string.hpp"
#include "exception.hpp"
#include "not_null.hpp"
#include "pixel_format.hpp"
#include "rect.hpp"
#include "surface.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

/**
 * \class basic_window
 *
 * \brief Represents an operating system window.
 *
 * \tparam T `std::true_type` for owning windows; `std::false_type` for
 * non-owning windows.
 *
 * \since 5.0.0
 *
 * \see `window`
 * \see `window_handle`
 *
 * \headerfile window.hpp
 */
template <typename T>
class basic_window final
{
  using owner_t = basic_window<std::true_type>;

 public:
  /**
   * \brief Creates a window from a pointer to an SDL window.
   *
   * \note If you're creating a `window` instance, then ownership of the pointer
   * is claimed. Furthermore, if you're creating a `window_handle`, ownership is
   * *not* claimed.
   *
   * \param window a pointer to the associated SDL window. Ownership of this
   * pointer is claimed if the window is owning.
   *
   * \since 5.0.0
   */
  explicit basic_window(SDL_Window* window) noexcept(!detail::is_owning<T>())
      : m_window{window}
  {
    if constexpr (detail::is_owning<T>()) {
      if (!m_window) {
        throw exception{"Cannot create window from null pointer!"};
      }
    }
  }

  /**
   * \brief Creates an owning window with the specified title and size.
   *
   * \details The window will be hidden by default.
   *
   * \param title the title of the window, can't be null.
   * \param size the size of the window, components must be greater than zero.
   *
   * \throws exception if the supplied width or height aren't
   * greater than zero.
   * \throws sdl_error if the window cannot be created.
   *
   * \since 3.0.0
   */
  template <typename U = T, detail::is_owner<U> = true>
  explicit basic_window(not_null<czstring> title,
                        const iarea& size = default_size())
  {
    assert(title);

    if ((size.width < 1) || (size.height < 1)) {
      throw exception{"Invalid width or height!"};
    }

    m_window.reset(SDL_CreateWindow(title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    size.width,
                                    size.height,
                                    SDL_WINDOW_HIDDEN));
    if (!m_window) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a window.
   *
   * \details The window will use the size obtained from `default_size()` as its
   * initial size.
   *
   * \throws sdl_error if the window cannot be created.
   *
   * \since 3.0.0
   */
  template <typename U = T, detail::is_owner<U> = true>
  basic_window() : basic_window{"Centurion window"}
  {}

  /**
   * \brief Creates a window handle based on an owning window.
   *
   * \param window the owning window to base the handle on.
   *
   * \since 5.0.0
   */
  template <typename U = T, detail::is_handle<U> = true>
  explicit basic_window(const owner_t& window) noexcept : m_window{window.get()}
  {}

  /**
   * \brief Makes the window visible.
   *
   * \since 3.0.0
   */
  void show() noexcept
  {
    SDL_ShowWindow(get());
  }

  /**
   * \brief Makes the window invisible.
   *
   * \since 3.0.0
   */
  void hide() noexcept
  {
    SDL_HideWindow(get());
  }

  /**
   * \brief Centers the window position relative to the screen.
   *
   * \note Windows are centered by default.
   *
   * \since 3.0.0
   */
  void center() noexcept
  {
    set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED});
  }

  /**
   * \brief Raises this window above other windows and requests focus.
   *
   * \since 3.0.0
   */
  void raise() noexcept
  {
    SDL_RaiseWindow(get());
  }

  /**
   * \brief Maximizes the window.
   *
   * \since 3.1.0
   */
  void maximize() noexcept
  {
    SDL_MaximizeWindow(get());
  }

  /**
   * \brief Minimizes the window.
   *
   * \since 3.1.0
   */
  void minimize() noexcept
  {
    SDL_MinimizeWindow(get());
  }

  /**
   * \brief Updates the window surface.
   *
   * \return `true` if the window surface was successfully updated; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  auto update_surface() noexcept -> bool
  {
    return SDL_UpdateWindowSurface(get()) == 0;
  }

  /**
   * \brief Sets whether or not the window is in fullscreen mode.
   *
   * \param fullscreen `true` if the window should enable fullscreen mode;
   * `false` for windowed mode.
   *
   * \since 3.0.0
   */
  void set_fullscreen(const bool fullscreen) noexcept
  {
    constexpr auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
    SDL_SetWindowFullscreen(get(), fullscreen ? flag : 0);
  }

  /**
   * \brief Sets whether or not the window is in fullscreen desktop mode.
   *
   * \details This mode is useful when you want to "fake" fullscreen mode.
   *
   * \param fullscreen `true` if the window should enable fullscreen desktop
   * mode; `false` for windowed mode.
   *
   * \since 4.0.0
   */
  void set_fullscreen_desktop(const bool fullscreen) noexcept
  {
    const auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetWindowFullscreen(get(), fullscreen ? flag : 0);
  }

  /**
   * \brief Sets whether or not the window is decorated.
   *
   * \details This is enabled by default.
   *
   * \param decorated `true` if the window should be decorated; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  void set_decorated(const bool decorated) noexcept
  {
    SDL_SetWindowBordered(get(), detail::convert_bool(decorated));
  }

  /**
   * \brief Sets whether or not the window should be resizable.
   *
   * \param resizable `true` if the window should be resizable; `false`
   * otherwise.
   *
   * \since 3.0.0
   */
  void set_resizable(const bool resizable) noexcept
  {
    SDL_SetWindowResizable(get(), detail::convert_bool(resizable));
  }

  /**
   * \brief Sets the width of the window.
   *
   * \details The supplied width is capped to always be at least 1.
   *
   * \param width the new width of the window, must be greater than zero.
   *
   * \since 3.0.0
   */
  void set_width(const int width) noexcept
  {
    SDL_SetWindowSize(get(), detail::max(width, 1), height());
  }

  /**
   * \brief Sets the height of the window.
   *
   * \details The supplied height is capped to always be at least 1.
   *
   * \param height the new height of the window, must be greater than zero.
   *
   * \since 3.0.0
   */
  void set_height(const int height) noexcept
  {
    SDL_SetWindowSize(get(), width(), detail::max(height, 1));
  }

  /**
   * \brief Sets the size of the window.
   *
   * \details The supplied dimensions are capped to be at least 1.
   *
   * \param size the new size of the window, components must be greater than
   * zero.
   *
   * \since 5.0.0
   */
  void set_size(const iarea& size) noexcept
  {
    const auto width = detail::max(size.width, 1);
    const auto height = detail::max(size.height, 1);
    SDL_SetWindowSize(get(), width, height);
  }

  /**
   * \brief Sets the icon that will be used by the window.
   *
   * \param icon the surface that will serve as the icon of the window.
   *
   * \since 3.0.0
   */
  void set_icon(const surface& icon) noexcept
  {
    SDL_SetWindowIcon(get(), icon.get());
  }

  /**
   * \brief Sets the title of the window.
   *
   * \param title the title of the window, can't be null.
   *
   * \since 3.0.0
   */
  void set_title(not_null<czstring> title) noexcept
  {
    assert(title);
    SDL_SetWindowTitle(get(), title);
  }

  /**
   * \brief Sets the opacity of the window.
   *
   * \details The supplied opacity will be clamped to a value in the legal
   * range.
   *
   * \param opacity the opacity, in the range [0, 1].
   *
   * \since 3.0.0
   */
  void set_opacity(const float opacity) noexcept
  {
    SDL_SetWindowOpacity(get(), opacity);
  }

  /**
   * \brief Sets the minimum size of the window.
   *
   * \details This method has no effect if any of the components aren't greater
   * than zero.
   *
   * \param size the minimum size of the window, components must be greater
   * than zero.
   *
   * \since 3.0.0
   */
  void set_min_size(const iarea& size) noexcept
  {
    SDL_SetWindowMinimumSize(get(), size.width, size.height);
  }

  /**
   * \brief Sets the maximum size of the window.
   *
   * \details This method has no effect if any of the components aren't greater
   * than zero.
   *
   * \param size the maximum size of the window, components must be greater
   * than zero.
   *
   * \since 3.0.0
   */
  void set_max_size(const iarea& size) noexcept
  {
    SDL_SetWindowMaximumSize(get(), size.width, size.height);
  }

  /**
   * \brief Sets the position of the window.
   *
   * \note It's possible to use `SDL_WINDOWPOS_CENTERED` or
   * `SDL_WINDOWPOS_UNDEFINED` as any of the components of the point.
   *
   * \param position the new position of the window.
   *
   * \since 5.0.0
   */
  void set_position(const ipoint& position) noexcept
  {
    SDL_SetWindowPosition(get(), position.x(), position.y());
  }

  /**
   * \brief Sets whether or not the mouse should be confined within the window.
   *
   * \brief This property is disabled by default.
   *
   * \param grabMouse `true` if the mouse should be confined within the window;
   * `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_grab_mouse(const bool grabMouse) noexcept
  {
    SDL_SetWindowGrab(get(), detail::convert_bool(grabMouse));
  }

  /**
   * \brief Sets the overall brightness of the window.
   *
   * \note A brightness value outside the legal range will be clamped to the
   * closest valid value.
   *
   * \param brightness the brightness value, in the range [0, 1].
   *
   * \return `true` if the brightness was successfully set; `false` otherwise.
   *
   * \since 3.0.0
   */
  auto set_brightness(const float brightness) noexcept -> bool
  {
    const auto res =
        SDL_SetWindowBrightness(get(), detail::clamp(brightness, 0.0f, 1.0f));
    return res == 0;
  }

  /**
   * \brief Sets whether or not the mouse should be captured.
   *
   * \note A window might have to be visible in order for the mouse to be
   * captured.
   *
   * \param capturingMouse `true` if the mouse should be captured; `false`
   * otherwise.
   *
   * \see `SDL_CaptureMouse`
   *
   * \since 5.0.0
   */
  static void set_capturing_mouse(const bool capturingMouse) noexcept
  {
    SDL_CaptureMouse(detail::convert_bool(capturingMouse));
  }

  /**
   * \brief Indicates whether or not the window is currently grabbing the mouse
   * input.
   *
   * \return `true` if the window is grabbing the mouse; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto grabbing_mouse() const noexcept -> bool
  {
    return SDL_GetWindowGrab(get());
  }

  /**
   * \brief Indicates whether or not the window has input focus.
   *
   * \note The window might have to be visible for this to be true.
   *
   * \return `true` if the window has input focus; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto has_input_focus() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_INPUT_FOCUS);
  }

  /**
   * \brief Indicates whether or not the window has mouse focus.
   *
   * \return `true` if the window has mouse focus; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto has_mouse_focus() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_FOCUS);
  }

  /**
   * \brief Indicates whether or not the window is decorated.
   *
   * \details Windows are decorated by default.
   *
   * \return `true` if the window is decorated; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_decorated() const noexcept -> bool
  {
    return !(flags() & SDL_WINDOW_BORDERLESS);
  }

  /**
   * \brief Indicates whether or not the window is resizable.
   *
   * \details By default, this property is set to false.
   *
   * \return `true` if the window is resizable; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_resizable() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_RESIZABLE);
  }

  /**
   * \brief Indicates whether or not the window is in fullscreen mode.
   *
   * \return `true` if the window is in fullscreen mode; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_fullscreen() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN);
  }

  /**
   * \brief Indicates whether or not the window is in fullscreen desktop mode.
   *
   * \return `true` if the window is in fullscreen desktop mode;
   * `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_fullscreen_desktop() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN_DESKTOP);
  }

  /**
   * \brief Indicates whether or not the window is visible.
   *
   * \return `true` if the window is visible; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_visible() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_SHOWN);
  }

  /**
   * \brief Indicates whether or not the window is usable with an
   * OpenGL-context.
   *
   * \return `true` if the window is compatible with an OpenGL-context; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_opengl() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_OPENGL);
  }

  /**
   * \brief Indicates whether or not the window is usable as a Vulkan surface.
   *
   * \return `true` if the window is is usable as a Vulkan surface; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_vulkan() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_VULKAN);
  }

  /**
   * \brief Indicates whether or not the window wasn't created by SDL.
   *
   * \return `true` if the window wasn't created by SDL; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_foreign() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_FOREIGN);
  }

  /**
   * \brief Indicates whether or not the window is capturing the mouse.
   *
   * \return `true` if the window is capturing the mouse; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_capturing_mouse() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_CAPTURE);
  }

  /**
   * \brief Indicates whether or not the window is minimized.
   *
   * \return `true` if the window is minimized; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_minimized() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_MINIMIZED);
  }

  /**
   * \brief Indicates whether or not the window is maximized.
   *
   * \return `true` if the window is maximized; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_maximized() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_MAXIMIZED);
  }

  /**
   * \brief Indicates whether or not the window is set to be always on top of
   * other windows.
   *
   * \return `true` if the window is always on top of other windows; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto always_on_top() const noexcept -> bool
  {
    return static_cast<bool>(flags() & SDL_WINDOW_ALWAYS_ON_TOP);
  }

  /**
   * \brief Returns the current brightness value of the window.
   *
   * \details The default value of this property is 1.
   *
   * \return the current brightness of the window, in the range [0, 1].
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto brightness() const noexcept -> float
  {
    return SDL_GetWindowBrightness(get());
  }

  /**
   * \brief Returns the opacity of the window.
   *
   * \return the opacity of the window, in the range [0, 1].
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto opacity() const noexcept -> float
  {
    float opacity{1};
    SDL_GetWindowOpacity(get(), &opacity);
    return opacity;
  }

  /**
   * \brief Returns the x-coordinate of the window position.
   *
   * \return the x-coordinate of the window position.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    int x{};
    SDL_GetWindowPosition(get(), &x, nullptr);
    return x;
  }

  /**
   * \brief Returns the y-coordinate of the window position.
   *
   * \return the y-coordinate of the window position.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    int y{};
    SDL_GetWindowPosition(get(), nullptr, &y);
    return y;
  }

  /**
   * \brief Returns a numerical ID of the window.
   *
   * \return a numerical ID of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto id() const noexcept -> u32
  {
    return SDL_GetWindowID(get());
  }

  /**
   * \brief Returns the display index associated with the window.
   *
   * \return the display index associated with the window; `std::nullopt` if the
   * display index cannot be obtained.
   *
   * \since 3.1.0
   */
  [[nodiscard]] auto display_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_GetWindowDisplayIndex(get());
    if (index != -1) {
      return index;
    } else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the current position of the window.
   *
   * \note Windows are centered by default.
   *
   * \return the current position of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto position() const noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetWindowPosition(get(), &x, &y);
    return {x, y};
  }

  /**
   * \brief Returns the minimum size of the window.
   *
   * \return the minimum size of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto min_size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_GetWindowMinimumSize(get(), &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the maximum size of the window.
   *
   * \return the maximum size of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto max_size() const noexcept -> iarea
  {
    int width{};
    int height{};
    SDL_GetWindowMaximumSize(get(), &width, &height);
    return {width, height};
  }

  /**
   * \brief Returns the current width of the window.
   *
   * \return the current width of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    int width{};
    SDL_GetWindowSize(get(), &width, nullptr);
    return width;
  }

  /**
   * \brief Returns the current height of the window.
   *
   * \return the current height of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    int height{};
    SDL_GetWindowSize(get(), nullptr, &height);
    return height;
  }

  /**
   * \brief Returns the current size of the window.
   *
   * \note Calling this function is slightly faster than calling both `width`
   * and `height` to obtain the window size.
   *
   * \return the size of the window.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowSize(get(), &size.width, &size.height);
    return size;
  }

  /**
   * \brief Indicates whether or not a flag is set.
   *
   * \details Some of the use cases of this method can be replaced by more
   * explicit methods, e.g. `is_fullscreen()` instead of
   * `check_flag(SDL_WINDOW_FULLSCREEN)`.
   *
   * \param flag the flag that will be tested.
   *
   * \return `true` if the flag is set; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto check_flag(const SDL_WindowFlags flag) const noexcept
      -> bool
  {
    return static_cast<bool>(flags() & flag);
  }

  /**
   * \brief Returns a mask that represents the flags associated with the window.
   *
   * \details You can check the returned mask using the `SDL_WindowFlags` enum.
   *
   * \return a mask that represents the flags associated with the window.
   *
   * \see `SDL_WindowFlags`
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto flags() const noexcept -> u32
  {
    return SDL_GetWindowFlags(get());
  }

  /**
   * \brief Returns the pixel format of the window.
   *
   * \return the pixel format used by the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto get_pixel_format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(SDL_GetWindowPixelFormat(get()));
  }

  /**
   * \brief Returns a handle to the window framebuffer surface.
   *
   * \warning It is not possible use the framebuffer surface with the 3D or 2D
   * rendering APIs.
   *
   * \return a handle to the window surface, might not contain a valid surface
   * pointer.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_surface() noexcept -> surface_handle
  {
    return surface_handle{SDL_GetWindowSurface(get())};
  }

  /**
   * \brief Returns the title of the window.
   *
   * \return the title of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto title() const -> std::string
  {
    return SDL_GetWindowTitle(get());
  }

  /**
   * \brief Converts to `SDL_Window*`.
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Window*() noexcept
  {
    return m_window.get();
  }

  /**
   * \brief Converts to `const SDL_Window*`.
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Window*() const noexcept
  {
    return m_window.get();
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \note This function is only available for window handles.
   *
   * \warning It's undefined behaviour to invoke other member functions that
   * use the internal pointer if this function returns `false`.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename U = T, detail::is_handle<U> = true>
  explicit operator bool() const noexcept
  {
    return m_window != nullptr;
  }

  /**
   * \brief Returns a pointer to the associated SDL window.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Window*
  {
    if constexpr (detail::is_owning<T>()) {
      return m_window.get();
    } else {
      return m_window;
    }
  }

  /**
   * \brief Returns the default size of a window.
   *
   * \note This function is only available for owning windows.
   *
   * \return the default size of a window.
   *
   * \since 5.0.0
   */
  template <typename U = T, detail::is_owner<U> = true>
  [[nodiscard]] constexpr static auto default_size() -> iarea
  {
    return {800, 600};
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Window* window) noexcept
    {
      SDL_DestroyWindow(window);
    }
  };

  using rep_t = std::conditional_t<T::value,
                                   std::unique_ptr<SDL_Window, deleter>,
                                   SDL_Window*>;

  rep_t m_window;
};

/**
 * \typedef window
 *
 * \brief Represents an owning window.
 *
 * \since 5.0.0
 */
using window = basic_window<std::true_type>;

/**
 * \typedef window_handle
 *
 * \brief Represents a non-owning window.
 *
 * \since 5.0.0
 */
using window_handle = basic_window<std::false_type>;

/**
 * \brief Returns a textual representation of a window.
 *
 * \param window the window that will be converted.
 *
 * \return a textual representation of the window.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_window<T>& window) -> std::string
{
  using detail::to_string;
  return "[window | ptr: " + detail::address_of(window.get()) +
         ", width: " + to_string(window.width()).value() +
         ", height: " + to_string(window.height()).value() + "]";
}

/**
 * \brief Prints a textual representation of a window.
 *
 * \param stream the stream that will be used.
 * \param window the window that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_window<T>& window)
    -> std::ostream&
{
  stream << to_string(window);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_WINDOW_HEADER
