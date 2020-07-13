#ifndef CENTURION_WINDOW_BASE_SOURCE
#define CENTURION_WINDOW_BASE_SOURCE

#include "window.hpp"

namespace centurion {

CENTURION_DEF
void window_base::show() noexcept
{
  SDL_ShowWindow(m_window);
}

CENTURION_DEF
void window_base::hide() noexcept
{
  SDL_HideWindow(m_window);
}

CENTURION_DEF
void window_base::center() noexcept
{
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

CENTURION_DEF
void window_base::raise() noexcept
{
  SDL_RaiseWindow(m_window);
}

CENTURION_DEF
void window_base::maximize() noexcept
{
  SDL_MaximizeWindow(m_window);
}

CENTURION_DEF
void window_base::minimize() noexcept
{
  SDL_MinimizeWindow(m_window);
}

CENTURION_DEF
void window_base::set_fullscreen(bool fullscreen) noexcept
{
  const auto fullscreenFlag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(m_window, fullscreen ? fullscreenFlag : 0);

  if (!fullscreen) {
    set_brightness(1);
  }
}

CENTURION_DEF
void window_base::set_fullscreen_desktop(bool fullscreen) noexcept
{
  const auto fullscreenFlag =
      static_cast<unsigned>(SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetWindowFullscreen(m_window, fullscreen ? fullscreenFlag : 0);
}

CENTURION_DEF
void window_base::set_decorated(bool decorated) noexcept
{
  SDL_SetWindowBordered(m_window, detail::convert_bool(decorated));
}

CENTURION_DEF
void window_base::set_resizable(bool resizable) noexcept
{
  SDL_SetWindowResizable(m_window, detail::convert_bool(resizable));
}

CENTURION_DEF
void window_base::set_width(int width) noexcept
{
  if (width > 0) {
    SDL_SetWindowSize(m_window, width, height());
  }
}

CENTURION_DEF
void window_base::set_height(int height) noexcept
{
  if (height > 0) {
    SDL_SetWindowSize(m_window, width(), height);
  }
}

CENTURION_DEF
void window_base::set_icon(const surface& icon) noexcept
{
  SDL_SetWindowIcon(m_window, icon.get());
}

CENTURION_DEF
void window_base::set_title(czstring title) noexcept
{
  if (title) {
    SDL_SetWindowTitle(m_window, title);
  }
}

CENTURION_DEF
void window_base::set_opacity(float opacity) noexcept
{
  SDL_SetWindowOpacity(m_window, opacity);
}

CENTURION_DEF
void window_base::set_min_size(area_i size) noexcept
{
  SDL_SetWindowMinimumSize(m_window, size.width, size.height);
}

CENTURION_DEF
void window_base::set_max_size(area_i size) noexcept
{
  SDL_SetWindowMaximumSize(m_window, size.width, size.height);
}

CENTURION_DEF
void window_base::set_position(int x, int y) noexcept
{
  SDL_SetWindowPosition(m_window, x, y);
}

CENTURION_DEF
void window_base::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(m_window, detail::convert_bool(grabMouse));
}

CENTURION_DEF
void window_base::set_brightness(float brightness) noexcept
{
  if (fullscreen()) {
    SDL_SetWindowBrightness(m_window,
                            detail::clamp_inclusive({0, 1}, brightness));
  }
}

CENTURION_DEF
void window_base::set_capturing_mouse(bool capturingMouse) noexcept
{
  SDL_CaptureMouse(detail::convert_bool(capturingMouse));
}

CENTURION_DEF
auto window_base::decorated() const noexcept -> bool
{
  return !(flags() & SDL_WINDOW_BORDERLESS);
}

CENTURION_DEF
auto window_base::grabbing_mouse() const noexcept -> bool
{
  return SDL_GetWindowGrab(m_window);
}

CENTURION_DEF
auto window_base::opacity() const noexcept -> float
{
  float opacity = 1;
  SDL_GetWindowOpacity(m_window, &opacity);
  return opacity;
}

CENTURION_DEF
auto window_base::brightness() const noexcept -> float
{
  return SDL_GetWindowBrightness(m_window);
}

CENTURION_DEF
auto window_base::id() const noexcept -> u32
{
  return SDL_GetWindowID(m_window);
}

CENTURION_DEF
auto window_base::display_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_GetWindowDisplayIndex(m_window);
  if (index != -1) {
    return index;
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto window_base::x() const noexcept -> int
{
  int x = 0;
  SDL_GetWindowPosition(m_window, &x, nullptr);
  return x;
}

CENTURION_DEF
auto window_base::y() const noexcept -> int
{
  int y = 0;
  SDL_GetWindowPosition(m_window, nullptr, &y);
  return y;
}

CENTURION_DEF
auto window_base::position() const noexcept -> point_i
{
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(m_window, &x, &y);
  return {x, y};
}

CENTURION_DEF
auto window_base::min_size() const noexcept -> area_i
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
auto window_base::max_size() const noexcept -> area_i
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
auto window_base::width() const noexcept -> int
{
  int width = 0;
  SDL_GetWindowSize(m_window, &width, nullptr);
  return width;
}

CENTURION_DEF
auto window_base::height() const noexcept -> int
{
  int height = 0;
  SDL_GetWindowSize(m_window, nullptr, &height);
  return height;
}

CENTURION_DEF
auto window_base::resizable() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_RESIZABLE);
}

CENTURION_DEF
auto window_base::fullscreen() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN);
}

CENTURION_DEF
auto window_base::fullscreen_desktop() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FULLSCREEN_DESKTOP);
}

CENTURION_DEF
auto window_base::visible() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_SHOWN);
}

CENTURION_DEF
auto window_base::opengl() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_OPENGL);
}

CENTURION_DEF
auto window_base::vulkan() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_VULKAN);
}

CENTURION_DEF
auto window_base::has_input_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_INPUT_FOCUS);
}

CENTURION_DEF
auto window_base::has_mouse_focus() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_FOCUS);
}

CENTURION_DEF
auto window_base::is_foreign() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_FOREIGN);
}

CENTURION_DEF
auto window_base::capturing_mouse() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MOUSE_CAPTURE);
}

CENTURION_DEF
auto window_base::always_on_top() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_ALWAYS_ON_TOP);
}

CENTURION_DEF
auto window_base::minimized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MINIMIZED);
}

CENTURION_DEF
auto window_base::maximized() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_WINDOW_MAXIMIZED);
}

CENTURION_DEF
auto window_base::check_flag(SDL_WindowFlags flag) const noexcept -> bool
{
  return static_cast<bool>(flags() & flag);
}

CENTURION_DEF
auto window_base::flags() const noexcept -> u32
{
  return SDL_GetWindowFlags(m_window);
}

CENTURION_DEF
auto window_base::renderer() noexcept -> std::optional<renderer_view>
{
  auto* renderer = SDL_GetRenderer(m_window);
  if (renderer) {
    return renderer_view{renderer};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto window_base::get_pixel_format() const noexcept -> pixel_format
{
  return static_cast<pixel_format>(SDL_GetWindowPixelFormat(m_window));
}

CENTURION_DEF
auto window_base::title() const noexcept -> czstring
{
  return SDL_GetWindowTitle(m_window);
}

CENTURION_DEF
auto window_base::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Window@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_BASE_SOURCE