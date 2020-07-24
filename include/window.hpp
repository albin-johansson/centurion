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

#include <memory>
#include <optional>
#include <type_traits>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "centurion_utils.hpp"
#include "pixel_format.hpp"
#include "point.hpp"
#include "surface.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class window_deleter final {
 public:
  void operator()(SDL_Window* window) noexcept { SDL_DestroyWindow(window); }
};

}  // namespace detail

/// @endcond

/**
 * @class window_base
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
 * @see `window_view`
 *
 * @headerfile window.hpp
 */
template <class Derived>
class window_base {
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
  void set_size(const area_i& size) noexcept;

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
  void set_min_size(const area_i& size) noexcept;

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
  void set_max_size(const area_i& size) noexcept;

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
  void set_position(const point_i& position) noexcept;

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
  [[nodiscard]] auto position() const noexcept -> point_i;

  /**
   * @brief Returns the minimum size of the window.
   *
   * @return the minimum size of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto min_size() const noexcept -> area_i;

  /**
   * @brief Returns the maximum size of the window.
   *
   * @return the maximum size of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto max_size() const noexcept -> area_i;

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
  [[nodiscard]] auto size() const noexcept -> area_i;

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

  //  /**
  //   * @brief Returns a view to the renderer that is associated with this
  //   window.
  //   *
  //   * @return a view to the renderer that is associated with this window;
  //   * `nothing` if no such renderer exists.
  //   *
  //   * @since 3.1.0
  //   */
  //  [[nodiscard]] auto get_renderer() noexcept -> renderer_view;

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

  /**
   * @brief Returns a textual representation of the window.
   *
   * @return a textual representation of the window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto to_string() const -> std::string;

 protected:
  window_base() noexcept = default;

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

/**
 * @class window
 *
 * @ingroup graphics
 *
 * @brief Represents an owning window.
 *
 * @details This is the main representation of a window in the library. This
 * class should always be the preferred option over `window_view`. The API of
 * this class and `window_view` is identical, except for the RAII semantics
 * of this class.
 *
 * @par Examples
 * The following example illustrates a typical setup for a responsive window.
 * Of course, the example assumes that the library has been initialized.
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <window.hpp>
 *   #include <graphics.hpp>
 *   #include <event.hpp>
 *   #include <rect.hpp>
 *
 *   void demo()
 *   {
 *     ctn::window window;
 *     ctn::renderer renderer{window};
 *
 *     window.set_title("Window demo");
 *
 *     ctn::Event event;
 *     bool running = true;
 *
 *     window.show();
 *     while (running) {
 *       while (event.poll()) {
 *         if (event.is<ctn::QuitEvent>()) {
 *           running = false;
 *           break;
 *         }
 *       }
 *
 *       renderer.clear_with(ctn::black);
 *
 *       const ctn::rect_i rect{{100, 100}, {150, 80}};
 *
 *       renderer.set_color(ctn::pink);
 *       renderer.fill_rect(rect);
 *
 *       renderer.present();
 *     }
 *     window.hide();
 *   }
 *
 * @endcode
 *
 * @since 3.0.0
 *
 * @see `window_view`
 *
 * @headerfile window.hpp
 */
class window final : public window_base<window> {
 public:
  /**
   * @typedef uptr
   *
   * @brief Simple alias for a unique pointer to a window.
   *
   * @since 5.0.0
   */
  using uptr = std::unique_ptr<window>;

  /**
   * @typedef sptr
   *
   * @brief Simple alias for a shared pointer to a window.
   *
   * @since 5.0.0
   */
  using sptr = std::shared_ptr<window>;

  /**
   * @typedef wptr
   *
   * @brief Simple alias for a weak pointer to a window.
   *
   * @since 5.0.0
   */
  using wptr = std::weak_ptr<window>;

  /**
   * @brief Creates a window instance.
   *
   * @details The window will be hidden by default.
   *
   * @param title the title of the window, can't be null.
   * @param size the size of the window, components must be greater than
   * zero, defaults to `default_size()`.
   *
   * @throws centurion_exception if the supplied width or height isn't
   * greater than zero or if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit window(nn_czstring title, area_i size = default_size());

  /**
   * @brief Creates a window based on the supplied SDL_Window instance.
   *
   * @details The created window will claim ownership of the supplied pointer.
   *
   * @param sdlWindow a pointer to the window that will be claimed, can't be
   * null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit window(nn_owner<SDL_Window*> sdlWindow);

  /**
   * @brief Creates a 800x600 window. The window will be hidden by default.
   *
   * @throws centurion_exception if the window cannot be created.
   *
   * @since 3.0.0
   */
  CENTURION_API
  window();

  /**
   * @copydoc window(nn_czstring, area_i)
   */
  CENTURION_QUERY
  static auto unique(nn_czstring title, area_i size = default_size()) -> uptr;

  /**
   * @copydoc window(nn_owner<SDL_Window*>)
   */
  CENTURION_QUERY
  static auto unique(nn_owner<SDL_Window*> sdlWindow) -> uptr;

  /**
   * @copydoc window()
   */
  CENTURION_QUERY
  static auto unique() -> uptr;

  /**
   * @copydoc window(nn_czstring, area_i)
   */
  CENTURION_QUERY
  static auto shared(nn_czstring title, area_i size = default_size()) -> sptr;

  /**
   * @copydoc window(nn_owner<SDL_Window*>)
   */
  CENTURION_QUERY
  static auto shared(nn_owner<SDL_Window*> sdlWindow) -> sptr;

  /**
   * @copydoc window()
   */
  CENTURION_QUERY
  static auto shared() -> sptr;

  /**
   * @brief Converts to `SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Window*() noexcept
  {
    return m_window.get();
  }

  /**
   * @brief Converts to `const SDL_Window*`.
   *
   * @return a pointer to the associated SDL window.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Window*() const noexcept
  {
    return m_window.get();
  }

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
  [[nodiscard]] auto get() const noexcept -> SDL_Window*
  {
    return m_window.get();
  }

  [[nodiscard]] static constexpr auto default_size() -> area_i
  {
    return {800, 600};
  }

 private:
  std::unique_ptr<SDL_Window, detail::window_deleter> m_window;
};

static_assert(std::is_final_v<window>);
static_assert(std::is_default_constructible_v<window>);
static_assert(std::is_nothrow_destructible_v<window>);
static_assert(std::is_nothrow_move_assignable_v<window>);
static_assert(std::is_nothrow_move_constructible_v<window>);
static_assert(!std::is_copy_assignable_v<window>);
static_assert(!std::is_copy_constructible_v<window>);

/**
 * @class window_view
 *
 * @ingroup graphics
 *
 * @brief Represents a non-owning window.
 *
 * @details This class is meant to be used when you want to utilize the same
 * window API as with the the `window` class, but you don't want the
 * window to claim ownership of the SDL window. In a nutshell, this class
 * is merely a wrapper around an `SDL_Window*`.
 *
 * @note Naturally, since instances of this class don't own the associated
 * SDL window, you'll have to manually manage the lifetime of the
 * SDL window. In general, prefer `window` unless you absolutely
 * cannot claim ownership of the SDL window.
 *
 * @warning It is undefined behaviour to invoke a member function if the
 * internal pointer is null!
 *
 * @par Examples
 * The following example displays how one could utilize this class to take
 * advantage of the Centurion window API, that wouldn't be possible with
 * `window`.
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <window.hpp>
 *
 *   // Assume that we can't change the parameter of this method
 *   void foo(SDL_Window* window)
 *   {
 *     ctn::window_view view{window}; // very cheap to construct
 *
 *     if (!view) { // checks if internal pointer is non-null
 *       return;
 *     }
 *
 *     view.set_title("bar");
 *
 *     if (view.is_fullscreen()) {
 *       // ...
 *     }
 *
 *     const auto x = view.x();
 *     const auto y = view.y();
 *   }
 * @endcode
 *
 * @since 5.0.0
 *
 * @see `window`
 *
 * @headerfile window.hpp
 */
class window_view final : public window_base<window_view> {
 public:
  explicit window_view(SDL_Window* window) noexcept : m_window{window} {}

  explicit window_view(const window& window) noexcept : m_window{window.get()}
  {}

  /**
   * @brief Indicates whether or not the instance holds a non-null pointer.
   *
   * @warning It's undefined behaviour to invoke other member functions that
   * use the internal pointer if this function returns `false`.
   *
   * @return `true` if the instance holds a non-null pointer; `false` otherwise.
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return static_cast<bool>(m_window);
  }

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

 private:
  SDL_Window* m_window{};
};

static_assert(std::is_final_v<window_view>);
static_assert(!std::is_default_constructible_v<window_view>);
static_assert(std::is_nothrow_destructible_v<window_view>);
static_assert(std::is_nothrow_move_assignable_v<window>);
static_assert(std::is_nothrow_move_constructible_v<window>);
static_assert(!std::is_copy_assignable_v<window>);
static_assert(!std::is_copy_constructible_v<window>);

template <class Derived>
void window_base<Derived>::show() noexcept
{
  SDL_ShowWindow(ptr());
}

template <class Derived>
void window_base<Derived>::hide() noexcept
{
  SDL_HideWindow(ptr());
}

template <class Derived>
void window_base<Derived>::raise() noexcept
{
  SDL_RaiseWindow(ptr());
}

template <class Derived>
void window_base<Derived>::center() noexcept
{
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

template <class Derived>
void window_base<Derived>::maximize() noexcept
{
  SDL_MaximizeWindow(ptr());
}

template <class Derived>
void window_base<Derived>::minimize() noexcept
{
  SDL_MinimizeWindow(ptr());
}

template <class Derived>
void window_base<Derived>::set_fullscreen(bool fullscreen) noexcept
{
  const auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(ptr(), fullscreen ? flag : 0);

  if (!fullscreen) {
    set_brightness(1);
  }
}

template <class Derived>
void window_base<Derived>::set_fullscreen_desktop(bool fullscreen) noexcept
{
  const auto flag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetWindowFullscreen(ptr(), fullscreen ? flag : 0);
}

template <class Derived>
void window_base<Derived>::set_decorated(bool decorated) noexcept
{
  SDL_SetWindowBordered(ptr(), detail::convert_bool(decorated));
}

template <class Derived>
void window_base<Derived>::set_resizable(bool resizable) noexcept
{
  SDL_SetWindowResizable(ptr(), detail::convert_bool(resizable));
}

template <class Derived>
void window_base<Derived>::set_width(int width) noexcept
{
  if (width > 0) {
    SDL_SetWindowSize(ptr(), width, height());
  }
}

template <class Derived>
void window_base<Derived>::set_height(int height) noexcept
{
  if (height > 0) {
    SDL_SetWindowSize(ptr(), width(), height);
  }
}

template <class Derived>
void window_base<Derived>::set_size(const area_i& size) noexcept
{
  if ((size.width > 0) && (size.height > 0)) {
    SDL_SetWindowSize(ptr(), size.width, size.height);
  }
}

template <class Derived>
void window_base<Derived>::set_icon(const surface& icon) noexcept
{
  SDL_SetWindowIcon(ptr(), icon.get());
}

template <class Derived>
void window_base<Derived>::set_title(nn_czstring title) noexcept
{
  SDL_SetWindowTitle(ptr(), title);
}

template <class Derived>
void window_base<Derived>::set_opacity(float opacity) noexcept
{
  SDL_SetWindowOpacity(ptr(), opacity);
}

template <class Derived>
void window_base<Derived>::set_min_size(const area_i& size) noexcept
{
  SDL_SetWindowMinimumSize(ptr(), size.width, size.height);
}

template <class Derived>
void window_base<Derived>::set_max_size(const area_i& size) noexcept
{
  SDL_SetWindowMaximumSize(ptr(), size.width, size.height);
}

template <class Derived>
void window_base<Derived>::set_position(const point_i& position) noexcept
{
  SDL_SetWindowPosition(ptr(), position.x(), position.y());
}

template <class Derived>
void window_base<Derived>::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(ptr(), detail::convert_bool(grabMouse));
}

template <class Derived>
void window_base<Derived>::set_brightness(float brightness) noexcept
{
  if (is_fullscreen()) {
    SDL_SetWindowBrightness(ptr(), std::clamp(brightness, 0.0f, 1.0f));
  }
}

template <class Derived>
void window_base<Derived>::set_capturing_mouse(bool capturingMouse) noexcept
{
  SDL_CaptureMouse(detail::convert_bool(capturingMouse));
}

template <class Derived>
auto window_base<Derived>::is_decorated() const noexcept -> bool
{
  return !(flags() & SDL_WINDOW_BORDERLESS);
}

template <class Derived>
auto window_base<Derived>::grabbing_mouse() const noexcept -> bool
{
  return SDL_GetWindowGrab(ptr());
}

template <class Derived>
auto window_base<Derived>::is_resizable() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_RESIZABLE);
}

template <class Derived>
auto window_base<Derived>::is_fullscreen() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN);
}

template <class Derived>
auto window_base<Derived>::is_fullscreen_desktop() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN_DESKTOP);
}

template <class Derived>
auto window_base<Derived>::is_visible() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_SHOWN);
}

template <class Derived>
auto window_base<Derived>::is_opengl() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_OPENGL);
}

template <class Derived>
auto window_base<Derived>::is_vulkan() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_VULKAN);
}

template <class Derived>
auto window_base<Derived>::has_input_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_INPUT_FOCUS);
}

template <class Derived>
auto window_base<Derived>::has_mouse_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_FOCUS);
}

template <class Derived>
auto window_base<Derived>::is_foreign() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FOREIGN);
}

template <class Derived>
auto window_base<Derived>::is_capturing_mouse() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_CAPTURE);
}

template <class Derived>
auto window_base<Derived>::always_on_top() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_ALWAYS_ON_TOP);
}

template <class Derived>
auto window_base<Derived>::is_minimized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MINIMIZED);
}

template <class Derived>
auto window_base<Derived>::is_maximized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MAXIMIZED);
}

template <class Derived>
auto window_base<Derived>::check_flag(SDL_WindowFlags flag) const noexcept
    -> bool
{
  return static_cast<bool>(flags() & flag);
}

template <class Derived>
auto window_base<Derived>::flags() const noexcept -> u32
{
  return SDL_GetWindowFlags(ptr());
}

template <class Derived>
auto window_base<Derived>::brightness() const noexcept -> float
{
  return SDL_GetWindowBrightness(ptr());
}

template <class Derived>
auto window_base<Derived>::opacity() const noexcept -> float
{
  float opacity{1};
  SDL_GetWindowOpacity(ptr(), &opacity);
  return opacity;
}

template <class Derived>
auto window_base<Derived>::x() const noexcept -> int
{
  int x{};
  SDL_GetWindowPosition(ptr(), &x, nullptr);
  return x;
}

template <class Derived>
auto window_base<Derived>::y() const noexcept -> int
{
  int y{};
  SDL_GetWindowPosition(ptr(), nullptr, &y);
  return y;
}

template <class Derived>
auto window_base<Derived>::position() const noexcept -> point_i
{
  int x{};
  int y{};
  SDL_GetWindowPosition(ptr(), &x, &y);
  return {x, y};
}

template <class Derived>
auto window_base<Derived>::id() const noexcept -> u32
{
  return SDL_GetWindowID(ptr());
}

template <class Derived>
auto window_base<Derived>::display_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_GetWindowDisplayIndex(ptr());
  if (index != -1) {
    return index;
  } else {
    return nothing;
  }
}

template <class Derived>
auto window_base<Derived>::min_size() const noexcept -> area_i
{
  int width{};
  int height{};
  SDL_GetWindowMinimumSize(ptr(), &width, &height);
  return {width, height};
}

template <class Derived>
auto window_base<Derived>::max_size() const noexcept -> area_i
{
  int width{};
  int height{};
  SDL_GetWindowMaximumSize(ptr(), &width, &height);
  return {width, height};
}

template <class Derived>
auto window_base<Derived>::width() const noexcept -> int
{
  int width{};
  SDL_GetWindowSize(ptr(), &width, nullptr);
  return width;
}

template <class Derived>
auto window_base<Derived>::height() const noexcept -> int
{
  int height{};
  SDL_GetWindowSize(ptr(), nullptr, &height);
  return height;
}

template <class Derived>
auto window_base<Derived>::size() const noexcept -> area_i
{
  area_i size{};
  SDL_GetWindowSize(ptr(), &size.width, &size.height);
  return size;
}

// template <class Derived>
// auto window_base<Derived>::get_renderer() noexcept -> renderer_view
//{
//  auto* renderer = SDL_GetRenderer(ptr());
//  if (renderer) {
//    return renderer_view{renderer};
//  } else {
//    return nullptr;
//  }
//}

template <class Derived>
auto window_base<Derived>::get_pixel_format() const noexcept -> pixel_format
{
  return static_cast<pixel_format>(SDL_GetWindowPixelFormat(ptr()));
}

template <class Derived>
auto window_base<Derived>::title() const -> std::string
{
  return SDL_GetWindowTitle(ptr());
}

template <class Derived>
auto window_base<Derived>::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Window | Data: " + address + ", Width: " + w + ", Height: " + h +
         "]";
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_HEADER