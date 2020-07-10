#ifndef CENTURION_WINDOW_SOURCE
#define CENTURION_WINDOW_SOURCE

#include "window.hpp"

#include "error.hpp"
#include "surface.hpp"

namespace centurion {

CENTURION_DEF
Window::Window() : Window{"Centurion window"}
{}

CENTURION_DEF
Window::Window(owner<SDL_Window*> window) : m_window{window}
{
  if (!window) {
    throw centurion_exception{"Cannot create Window from null SDL_Window!"};
  }
}

CENTURION_DEF
Window::Window(czstring title, area_i size)
{
  if ((size.width < 1) || (size.height < 1)) {
    throw centurion_exception{"Invalid width or height!"};
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  m_window = SDL_CreateWindow(
      title ? title : "", pos, pos, size.width, size.height, SDL_WINDOW_HIDDEN);
  if (!m_window) {
    throw detail::Error::from_core("Failed to create Window!");
  }
}

CENTURION_DEF
Window::Window(Window&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Window::~Window() noexcept
{
  destroy();
}

CENTURION_DEF
auto Window::operator=(Window&& other) noexcept -> Window&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void Window::destroy() noexcept
{
  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
}

CENTURION_DEF
void Window::move(Window&& other) noexcept
{
  destroy();

  m_window = other.m_window;

  other.m_window = nullptr;
}

CENTURION_DEF
auto Window::unique() -> std::unique_ptr<Window>
{
  return std::make_unique<Window>();
}

CENTURION_DEF
auto Window::unique(owner<SDL_Window*> window) -> std::unique_ptr<Window>
{
  return std::make_unique<Window>(window);
}

CENTURION_DEF
auto Window::unique(czstring title, area_i size) -> std::unique_ptr<Window>
{
  return std::make_unique<Window>(title, size);
}

CENTURION_DEF
auto Window::shared() -> std::shared_ptr<Window>
{
  return std::make_shared<Window>();
}

CENTURION_DEF
auto Window::shared(owner<SDL_Window*> window) -> std::shared_ptr<Window>
{
  return std::make_shared<Window>(window);
}

CENTURION_DEF
auto Window::shared(czstring title, area_i size) -> std::shared_ptr<Window>
{
  return std::make_shared<Window>(title, size);
}

CENTURION_DEF
void Window::show() noexcept
{
  SDL_ShowWindow(m_window);
}

CENTURION_DEF
void Window::hide() noexcept
{
  SDL_HideWindow(m_window);
}

CENTURION_DEF
void Window::center() noexcept
{
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

CENTURION_DEF
void Window::raise() noexcept
{
  SDL_RaiseWindow(m_window);
}

CENTURION_DEF
void Window::maximize() noexcept
{
  SDL_MaximizeWindow(m_window);
}

CENTURION_DEF
void Window::minimize() noexcept
{
  SDL_MinimizeWindow(m_window);
}

CENTURION_DEF
void Window::set_fullscreen(bool fullscreen) noexcept
{
  const auto fullscreenFlag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(m_window, fullscreen ? fullscreenFlag : 0);

  if (!fullscreen) {
    set_brightness(1);
  }
}

CENTURION_DEF
void Window::set_fullscreen_desktop(bool fullscreen) noexcept
{
  const auto fullscreenFlag =
      static_cast<unsigned>(SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetWindowFullscreen(m_window, fullscreen ? fullscreenFlag : 0);
}

CENTURION_DEF
void Window::set_decorated(bool decorated) noexcept
{
  SDL_SetWindowBordered(m_window, detail::convert_bool(decorated));
}

CENTURION_DEF
void Window::set_resizable(bool resizable) noexcept
{
  SDL_SetWindowResizable(m_window, detail::convert_bool(resizable));
}

CENTURION_DEF
void Window::set_width(int width) noexcept
{
  if (width > 0) {
    SDL_SetWindowSize(m_window, width, height());
  }
}

CENTURION_DEF
void Window::set_height(int height) noexcept
{
  if (height > 0) {
    SDL_SetWindowSize(m_window, width(), height);
  }
}

CENTURION_DEF
void Window::set_icon(const Surface& icon) noexcept
{
  SDL_SetWindowIcon(m_window, icon.get());
}

CENTURION_DEF
void Window::set_title(czstring title) noexcept
{
  if (title) {
    SDL_SetWindowTitle(m_window, title);
  }
}

CENTURION_DEF
void Window::set_opacity(float opacity) noexcept
{
  SDL_SetWindowOpacity(m_window, opacity);
}

CENTURION_DEF
void Window::set_min_size(area_i size) noexcept
{
  SDL_SetWindowMinimumSize(m_window, size.width, size.height);
}

CENTURION_DEF
void Window::set_max_size(area_i size) noexcept
{
  SDL_SetWindowMaximumSize(m_window, size.width, size.height);
}

CENTURION_DEF
void Window::set_position(int x, int y) noexcept
{
  SDL_SetWindowPosition(m_window, x, y);
}

CENTURION_DEF
void Window::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(m_window, detail::convert_bool(grabMouse));
}

CENTURION_DEF
void Window::set_brightness(float brightness) noexcept
{
  if (fullscreen()) {
    SDL_SetWindowBrightness(m_window,
                            detail::clamp_inclusive({0, 1}, brightness));
  }
}

CENTURION_DEF
void Window::set_capturing_mouse(bool capturingMouse) noexcept
{
  SDL_CaptureMouse(detail::convert_bool(capturingMouse));
}

CENTURION_DEF
auto Window::decorated() const noexcept -> bool
{
  return !(flags() & SDL_WINDOW_BORDERLESS);
}

CENTURION_DEF
auto Window::grabbing_mouse() const noexcept -> bool
{
  return SDL_GetWindowGrab(m_window);
}

CENTURION_DEF
auto Window::opacity() const noexcept -> float
{
  float opacity = 1;
  SDL_GetWindowOpacity(m_window, &opacity);
  return opacity;
}

CENTURION_DEF
auto Window::brightness() const noexcept -> float
{
  return SDL_GetWindowBrightness(m_window);
}

CENTURION_DEF
auto Window::id() const noexcept -> u32
{
  return SDL_GetWindowID(m_window);
}

CENTURION_DEF
auto Window::display_index() const noexcept -> std::optional<int>
{
  const auto index = SDL_GetWindowDisplayIndex(m_window);
  if (index != -1) {
    return index;
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Window::x() const noexcept -> int
{
  int x = 0;
  SDL_GetWindowPosition(m_window, &x, nullptr);
  return x;
}

CENTURION_DEF
auto Window::y() const noexcept -> int
{
  int y = 0;
  SDL_GetWindowPosition(m_window, nullptr, &y);
  return y;
}

CENTURION_DEF
auto Window::position() const noexcept -> point_i
{
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(m_window, &x, &y);
  return {x, y};
}

CENTURION_DEF
auto Window::min_size() const noexcept -> area_i
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
auto Window::max_size() const noexcept -> area_i
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
auto Window::width() const noexcept -> int
{
  int width = 0;
  SDL_GetWindowSize(m_window, &width, nullptr);
  return width;
}

CENTURION_DEF
auto Window::height() const noexcept -> int
{
  int height = 0;
  SDL_GetWindowSize(m_window, nullptr, &height);
  return height;
}

CENTURION_DEF
auto Window::resizable() const noexcept -> bool
{
  return flags() & SDL_WINDOW_RESIZABLE;
}

CENTURION_DEF
auto Window::fullscreen() const noexcept -> bool
{
  return flags() & SDL_WINDOW_FULLSCREEN;
}

CENTURION_DEF
auto Window::fullscreen_desktop() const noexcept -> bool
{
  return flags() & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

CENTURION_DEF
auto Window::visible() const noexcept -> bool
{
  return flags() & SDL_WINDOW_SHOWN;
}

CENTURION_DEF
auto Window::opengl() const noexcept -> bool
{
  return flags() & SDL_WINDOW_OPENGL;
}

CENTURION_DEF
auto Window::vulkan() const noexcept -> bool
{
  return flags() & SDL_WINDOW_VULKAN;
}

CENTURION_DEF
auto Window::has_input_focus() const noexcept -> bool
{
  return flags() & SDL_WINDOW_INPUT_FOCUS;
}

CENTURION_DEF
auto Window::has_mouse_focus() const noexcept -> bool
{
  return flags() & SDL_WINDOW_MOUSE_FOCUS;
}

CENTURION_DEF
auto Window::is_foreign() const noexcept -> bool
{
  return flags() & SDL_WINDOW_FOREIGN;
}

CENTURION_DEF
auto Window::capturing_mouse() const noexcept -> bool
{
  return flags() & SDL_WINDOW_MOUSE_CAPTURE;
}

CENTURION_DEF
auto Window::always_on_top() const noexcept -> bool
{
  return flags() & SDL_WINDOW_ALWAYS_ON_TOP;
}

CENTURION_DEF
auto Window::minimized() const noexcept -> bool
{
  return flags() & SDL_WINDOW_MINIMIZED;
}

CENTURION_DEF
auto Window::maximized() const noexcept -> bool
{
  return flags() & SDL_WINDOW_MAXIMIZED;
}

CENTURION_DEF
auto Window::check_flag(SDL_WindowFlags flag) const noexcept -> bool
{
  return flags() & flag;
}

CENTURION_DEF
auto Window::flags() const noexcept -> u32
{
  return SDL_GetWindowFlags(m_window);
}

CENTURION_DEF
auto Window::renderer() noexcept -> std::optional<renderer_view>
{
  auto* renderer = SDL_GetRenderer(m_window);
  if (renderer) {
    return renderer_view{renderer};
  } else {
    return nothing;
  }
}

CENTURION_DEF
auto Window::pixel_format() const noexcept -> PixelFormat
{
  return static_cast<PixelFormat>(SDL_GetWindowPixelFormat(m_window));
}

CENTURION_DEF
auto Window::title() const noexcept -> czstring
{
  return SDL_GetWindowTitle(m_window);
}

CENTURION_DEF
auto Window::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Window@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_SOURCE