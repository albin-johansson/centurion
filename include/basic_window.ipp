#ifndef CENTURION_BASIC_WINDOW_IMPLEMENTATION
#define CENTURION_BASIC_WINDOW_IMPLEMENTATION

#include "centurion_api.hpp"
#include "window_base.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

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
  set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED});
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
void window_base<Derived>::set_size(const iarea& size) noexcept
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
void window_base<Derived>::set_min_size(const iarea& size) noexcept
{
  SDL_SetWindowMinimumSize(ptr(), size.width, size.height);
}

template <class Derived>
void window_base<Derived>::set_max_size(const iarea& size) noexcept
{
  SDL_SetWindowMaximumSize(ptr(), size.width, size.height);
}

template <class Derived>
void window_base<Derived>::set_position(const ipoint& position) noexcept
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
auto window_base<Derived>::position() const noexcept -> ipoint
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
auto window_base<Derived>::min_size() const noexcept -> iarea
{
  int width{};
  int height{};
  SDL_GetWindowMinimumSize(ptr(), &width, &height);
  return {width, height};
}

template <class Derived>
auto window_base<Derived>::max_size() const noexcept -> iarea
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
auto window_base<Derived>::size() const noexcept -> iarea
{
  iarea size{};
  SDL_GetWindowSize(ptr(), &size.width, &size.height);
  return size;
}

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

}  // namespace centurion

#endif  // CENTURION_BASIC_WINDOW_IMPLEMENTATION
