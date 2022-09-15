/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#ifndef CENTURION_WINDOW_HPP_
#define CENTURION_WINDOW_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <memory>    // unique_ptr
#include <optional>  // optional, nullopt
#include <ostream>   // ostream
#include <string>    // string, to_string
#include <utility>   // pair, make_pair, move

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "render.hpp"
#include "surface.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
class basic_window;

using window = basic_window<detail::owner_tag>;
using window_handle = basic_window<detail::handle_tag>;

/**
 * Represents an operating-system window.
 *
 * \see window
 * \see window_handle
 *
 * \see get_grabbed_window()
 * \see get_mouse_focus_window()
 * \see get_keyboard_focus_window()
 * \see get_window()
 * \see get_renderer()
 */
template <typename T>
class basic_window final
{
 public:
  enum window_flags : uint32
  {
    fullscreen = SDL_WINDOW_FULLSCREEN,
    fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,

    shown = SDL_WINDOW_SHOWN,
    hidden = SDL_WINDOW_HIDDEN,
    minimized = SDL_WINDOW_MINIMIZED,
    maximized = SDL_WINDOW_MAXIMIZED,

    borderless = SDL_WINDOW_BORDERLESS,
    resizable = SDL_WINDOW_RESIZABLE,
    skip_taskbar = SDL_WINDOW_SKIP_TASKBAR,

    input_grabbed = SDL_WINDOW_INPUT_GRABBED,
    input_focus = SDL_WINDOW_INPUT_FOCUS,
    mouse_focus = SDL_WINDOW_MOUSE_FOCUS,
    mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,

    allow_high_dpi = SDL_WINDOW_ALLOW_HIGHDPI,
    always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,

    foreign = SDL_WINDOW_FOREIGN,
    utility = SDL_WINDOW_UTILITY,
    tooltip = SDL_WINDOW_TOOLTIP,
    popup_menu = SDL_WINDOW_POPUP_MENU,

    opengl = SDL_WINDOW_OPENGL,
    vulkan = SDL_WINDOW_VULKAN,

#if SDL_VERSION_ATLEAST(2, 0, 14)
    metal = SDL_WINDOW_METAL
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  };

  /**
   * Creates a window from an existing SDL window.
   *
   * Ownership of the supplied pointer is claimed if the window has owning semantics.
   *
   * \param window a pointer to the associated SDL window.
   */
  explicit basic_window(maybe_owner<SDL_Window*> window) noexcept(detail::is_handle<T>)
      : mWindow{window}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mWindow) {
        throw exception{"Cannot create window from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_window(const char* title,
                        const iarea size = default_size(),
                        const uint32 flags = default_flags())
  {
    assert(title);

    if (size.width < 1) {
      throw exception{"Bad window width!"};
    }
    else if (size.height < 1) {
      throw exception{"Bad window height!"};
    }

    mWindow.reset(SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   size.width,
                                   size.height,
                                   flags));
    if (!mWindow) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_window(const std::string& title,
                        const iarea size = default_size(),
                        const uint32 flags = default_flags())
      : basic_window{title.c_str(), size, flags}
  {}

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_window() : basic_window{"Centurion"}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_window(const window& owner) noexcept : mWindow{owner.get()}
  {}

  [[nodiscard]] auto make_renderer(const uint32 flags = renderer::default_flags()) -> renderer
  {
    if (auto* ptr = SDL_CreateRenderer(get(), -1, flags)) {
      return renderer{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  [[nodiscard]] auto get_renderer() noexcept -> renderer_handle
  {
    return renderer_handle{SDL_GetRenderer(mWindow)};
  }

  void show() noexcept { SDL_ShowWindow(mWindow); }

  void hide() noexcept { SDL_HideWindow(mWindow); }

  void raise() noexcept { SDL_RaiseWindow(mWindow); }

  void maximize() noexcept { SDL_MaximizeWindow(mWindow); }

  void minimize() noexcept { SDL_MinimizeWindow(mWindow); }

  void restore() noexcept { SDL_RestoreWindow(mWindow); }

  auto update_surface() noexcept -> result { return SDL_UpdateWindowSurface(mWindow) == 0; }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  auto flash(const flash_op op = flash_op::briefly) noexcept -> result
  {
    return SDL_FlashWindow(mWindow, static_cast<SDL_FlashOperation>(op)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  auto set_fullscreen(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? fullscreen : 0) == 0;
  }

  auto set_fullscreen_desktop(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? fullscreen_desktop : 0) == 0;
  }

  void set_decorated(const bool decorated) noexcept
  {
    SDL_SetWindowBordered(mWindow, decorated ? SDL_TRUE : SDL_FALSE);
  }

  void set_resizable(const bool resizable) noexcept
  {
    SDL_SetWindowResizable(mWindow, resizable ? SDL_TRUE : SDL_FALSE);
  }

  void set_icon(const surface& icon) noexcept { SDL_SetWindowIcon(mWindow, icon.get()); }

  void set_title(const char* title) noexcept
  {
    assert(title);
    SDL_SetWindowTitle(mWindow, title);
  }

  void set_title(const std::string& title) noexcept { set_title(title.c_str()); }

  auto set_opacity(const float opacity) noexcept -> result
  {
    return SDL_SetWindowOpacity(mWindow, opacity) == 0;
  }

  auto set_brightness(const float brightness) noexcept -> result
  {
    return SDL_SetWindowBrightness(mWindow, detail::clamp(brightness, 0.0f, 1.0f)) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  void set_grab_keyboard(const bool grab) noexcept
  {
    SDL_SetWindowKeyboardGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  void set_always_on_top(const bool enabled) noexcept
  {
    SDL_SetWindowAlwaysOnTop(mWindow, enabled ? SDL_TRUE : SDL_FALSE);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  void center() noexcept { set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}); }

  void set_position(const ipoint position) noexcept
  {
    SDL_SetWindowPosition(mWindow, position.x(), position.y());
  }

  void set_x(const int x) noexcept { set_position({x, y()}); }
  void set_y(const int y) noexcept { set_position({x(), y}); }

  [[nodiscard]] auto position() const noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetWindowPosition(mWindow, &x, &y);
    return {x, y};
  }

  [[nodiscard]] auto x() const noexcept -> int { return position().x(); }
  [[nodiscard]] auto y() const noexcept -> int { return position().y(); }

  void set_size(const iarea size) noexcept
  {
    SDL_SetWindowSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  void set_width(const int width) noexcept
  {
    SDL_SetWindowSize(mWindow, detail::max(width, 1), height());
  }

  void set_height(const int height) noexcept
  {
    SDL_SetWindowSize(mWindow, width(), detail::max(height, 1));
  }

  void set_min_size(const iarea size) noexcept
  {
    SDL_SetWindowMinimumSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  void set_max_size(const iarea size) noexcept
  {
    SDL_SetWindowMaximumSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  [[nodiscard]] auto size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowSize(mWindow, &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto width() const noexcept -> int { return size().width; }
  [[nodiscard]] auto height() const noexcept -> int { return size().height; }

  [[nodiscard]] auto min_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMinimumSize(mWindow, &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto max_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMaximumSize(mWindow, &size.width, &size.height);
    return size;
  }

  static auto set_capturing_mouse(const bool capture) noexcept -> result
  {
    return SDL_CaptureMouse(capture ? SDL_TRUE : SDL_FALSE) == 0;
  }

  void set_grab_mouse(const bool grab) noexcept
  {
    SDL_SetWindowGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  [[nodiscard]] auto is_grabbing_mouse() const noexcept -> bool
  {
    return SDL_GetWindowGrab(mWindow);
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  auto reset_mouse_rect() noexcept -> result
  {
    return SDL_SetWindowMouseRect(mWindow, nullptr) == 0;
  }

  auto set_mouse_rect(const irect& rect) noexcept -> result
  {
    return SDL_SetWindowMouseRect(mWindow, rect.data()) == 0;
  }

  [[nodiscard]] auto mouse_rect() const noexcept -> maybe<irect>
  {
    if (const auto* rect = SDL_GetWindowMouseRect(mWindow)) {
      return irect{*rect};
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto title() const -> std::string { return SDL_GetWindowTitle(mWindow); }

  [[nodiscard]] auto brightness() const noexcept -> float
  {
    return SDL_GetWindowBrightness(mWindow);
  }

  [[nodiscard]] auto opacity() const noexcept -> float
  {
    float opacity{1};
    SDL_GetWindowOpacity(mWindow, &opacity);
    return opacity;
  }

  [[nodiscard]] auto id() const noexcept -> uint32 { return SDL_GetWindowID(mWindow); }

  [[nodiscard]] auto display_index() const noexcept -> maybe<int>
  {
    const auto index = SDL_GetWindowDisplayIndex(mWindow);
    if (index != -1) {
      return index;
    }
    else {
      return nothing;
    }
  }

  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(SDL_GetWindowPixelFormat(mWindow));
  }

  [[nodiscard]] auto is_screen_keyboard_shown() const noexcept -> bool
  {
    return SDL_IsScreenKeyboardShown(get()) == SDL_TRUE;
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  struct icc_profile_data final
  {
    using data_type = std::unique_ptr<void, detail::sdl_deleter>;

    data_type data;  ///< Pointer to the raw ICC profile data.
    usize size{};    ///< The size of the raw data, in bytes.
  };

  [[nodiscard]] auto icc_profile() const noexcept -> maybe<icc_profile_data>
  {
    usize size{};
    if (auto* icc = SDL_GetWindowICCProfile(get(), &size)) {
      return icc_profile_data{icc, size};
    }
    else {
      return nothing;
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto flags() const noexcept -> uint32 { return SDL_GetWindowFlags(mWindow); }

  [[nodiscard]] auto check_flag(const uint32 flag) const noexcept -> bool
  {
    return flags() & flag;
  }

  [[nodiscard]] auto has_grabbed_input() const noexcept -> bool
  {
    return check_flag(input_grabbed);
  }

  [[nodiscard]] auto has_input_focus() const noexcept -> bool
  {
    return check_flag(input_focus);
  }

  [[nodiscard]] auto has_mouse_focus() const noexcept -> bool
  {
    return check_flag(mouse_focus);
  }

  [[nodiscard]] auto is_borderless() const noexcept -> bool { return check_flag(borderless); }

  [[nodiscard]] auto is_decorated() const noexcept -> bool { return !is_borderless(); }

  [[nodiscard]] auto is_resizable() const noexcept -> bool { return check_flag(resizable); }

  [[nodiscard]] auto is_high_dpi() const noexcept -> bool
  {
    return check_flag(allow_high_dpi);
  }

  [[nodiscard]] auto is_fullscreen() const noexcept -> bool { return check_flag(fullscreen); }

  [[nodiscard]] auto is_fullscreen_desktop() const noexcept -> bool
  {
    return check_flag(fullscreen_desktop);
  }

  [[nodiscard]] auto is_visible() const noexcept -> bool { return check_flag(shown); }

  [[nodiscard]] auto is_hidden() const noexcept -> bool { return check_flag(hidden); }

  [[nodiscard]] auto is_opengl() const noexcept -> bool { return check_flag(opengl); }

  [[nodiscard]] auto is_vulkan() const noexcept -> bool { return check_flag(vulkan); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto is_metal() const noexcept -> bool { return check_flag(metal); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto is_foreign() const noexcept -> bool { return check_flag(foreign); }

  [[nodiscard]] auto is_capturing_mouse() const noexcept -> bool
  {
    return check_flag(mouse_capture);
  }

  [[nodiscard]] auto is_minimized() const noexcept -> bool { return check_flag(minimized); }

  [[nodiscard]] auto is_maximized() const noexcept -> bool { return check_flag(maximized); }

  [[nodiscard]] auto is_always_on_top() const noexcept -> bool
  {
    return check_flag(always_on_top);
  }

  [[nodiscard]] auto is_utility() const noexcept -> bool { return check_flag(utility); }

  [[nodiscard]] auto is_tooltip() const noexcept -> bool { return check_flag(tooltip); }

  [[nodiscard]] auto is_popup_menu() const noexcept -> bool { return check_flag(popup_menu); }

  [[nodiscard]] auto is_excluded_from_taskbar() const noexcept -> bool
  {
    return check_flag(skip_taskbar);
  }

  [[nodiscard]] auto get_surface() noexcept -> surface_handle
  {
    return surface_handle{SDL_GetWindowSurface(mWindow)};
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Window* { return mWindow.get(); }

  /// Indicates whether a handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mWindow != nullptr;
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_size() noexcept -> iarea
  {
    return {800, 600};
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_flags() noexcept -> uint32
  {
    return hidden;
  }

 private:
  detail::pointer<T, SDL_Window> mWindow;
};

template <typename T>
[[nodiscard]] auto to_string(const basic_window<T>& window) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("window(data: {}, width: {}, height: {})",
                     detail::address_of(window.get()),
                     window.width(),
                     window.height());
#else
  return "window(data: " + detail::address_of(window.get()) +
         ", width: " + std::to_string(window.width()) +
         ", height: " + std::to_string(window.height()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_window<T>& window) -> std::ostream&
{
  return stream << to_string(window);
}

[[nodiscard]] inline auto get_grabbed_window() noexcept -> window_handle
{
  return window_handle{SDL_GetGrabbedWindow()};
}

[[nodiscard]] inline auto get_mouse_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetMouseFocus()};
}

[[nodiscard]] inline auto get_keyboard_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetKeyboardFocus()};
}

[[nodiscard]] inline auto get_window(const uint32 id) noexcept -> window_handle
{
  return window_handle{SDL_GetWindowFromID(id)};
}

#if SDL_VERSION_ATLEAST(2, 0, 22)

[[nodiscard]] inline auto get_window(const renderer_handle renderer) noexcept -> window_handle
{
  return window_handle{SDL_RenderGetWindow(renderer.get())};
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)

}  // namespace cen

#endif  // CENTURION_WINDOW_HPP_
