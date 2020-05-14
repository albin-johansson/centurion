#ifndef CENTURION_WINDOW_SOURCE
#define CENTURION_WINDOW_SOURCE

#include "window.h"

#include <string>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "surface.h"
#include "window_listener.h"

namespace centurion {

CENTURION_DEF
Window::Window(const char* title, int width, int height)
{
  if ((width < 1) || (height < 1)) {
    throw CenturionException{"Invalid width or height!"};
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  m_window = SDL_CreateWindow(
      title ? title : "", pos, pos, width, height, SDL_WINDOW_HIDDEN);
}

CENTURION_DEF
Window::Window(int width, int height)
    : Window{"Centurion window", width, height}
{}

CENTURION_DEF
Window::Window(const char* title) : Window{title, 800, 600}
{}

CENTURION_DEF
Window::Window(Owner<SDL_Window*> window) : m_window{window}
{
  if (!window) {
    throw CenturionException{"Cannot create window from null SDL_Window!"};
  }
}

CENTURION_DEF
Window::Window() : Window{800, 600}
{}

CENTURION_DEF
Window::Window(Window&& other) noexcept
{
  move(std::forward<Window>(other));
}

CENTURION_DEF
Window::~Window() noexcept
{
  destroy();
}

CENTURION_DEF
Window& Window::operator=(Window&& other) noexcept
{
  if (this != &other) {
    move(std::forward<Window>(other));
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
  m_windowListeners = std::move(other.m_windowListeners);

  other.m_window = nullptr;
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(const char* title, int width, int height)
{
  return centurion::detail::make_unique<Window>(title, width, height);
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(int width, int height)
{
  return centurion::detail::make_unique<Window>(width, height);
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(const char* title)
{
  return centurion::detail::make_unique<Window>(title);
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(Owner<SDL_Window*> window)
{
  return centurion::detail::make_unique<Window>(window);
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique()
{
  return centurion::detail::make_unique<Window>();
}

CENTURION_DEF
std::shared_ptr<Window> Window::shared(const char* title, int width, int height)
{
  return std::make_shared<Window>(title, width, height);
}

CENTURION_DEF
std::shared_ptr<Window> Window::shared(int width, int height)
{
  return std::make_shared<Window>(width, height);
}

CENTURION_DEF
std::shared_ptr<Window> Window::shared(const char* title)
{
  return std::make_shared<Window>(title);
}

CENTURION_DEF
std::shared_ptr<Window> Window::shared(Owner<SDL_Window*> window)
{
  return std::make_shared<Window>(window);
}

CENTURION_DEF
std::shared_ptr<Window> Window::shared()
{
  return std::make_shared<Window>();
}

CENTURION_DEF
void Window::notify_window_listeners() noexcept
{
  const auto& self = *this;
  for (const auto& listener : m_windowListeners) {
    auto tmp = listener.lock();
    if (tmp) {
      tmp->window_updated(self);
    }
  }
}

CENTURION_DEF
void Window::show() noexcept
{
  SDL_ShowWindow(m_window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::hide() noexcept
{
  SDL_HideWindow(m_window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::center() noexcept
{
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  notify_window_listeners();
}

CENTURION_DEF
void Window::raise() noexcept
{
  SDL_RaiseWindow(m_window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::maximize() noexcept
{
  SDL_MaximizeWindow(m_window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::minimize() noexcept
{
  SDL_MinimizeWindow(m_window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::add_window_listener(
    std::weak_ptr<IWindowListener> listener) noexcept
{
  if (!listener.expired()) {
    m_windowListeners.push_back(listener);
  }
}

CENTURION_DEF
void Window::set_fullscreen(bool fullscreen) noexcept
{
  const auto fullscreenFlag = static_cast<unsigned>(SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(m_window, fullscreen ? fullscreenFlag : 0);

  if (!fullscreen) {
    set_brightness(1);
  }

  notify_window_listeners();
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
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_resizable(bool isResizable) noexcept
{
  SDL_SetWindowResizable(m_window, detail::convert_bool(isResizable));
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_width(int width)
{
  if (width < 1) {
    throw CenturionException{"Invalid window width!"};
  } else {
    SDL_SetWindowSize(m_window, width, height());
    notify_window_listeners();
  }
}

CENTURION_DEF
void Window::set_height(int height)
{
  if (height < 1) {
    throw CenturionException{"Invalid window height!"};
  } else {
    SDL_SetWindowSize(m_window, width(), height);
    notify_window_listeners();
  }
}

CENTURION_DEF
void Window::set_icon(const Surface& icon) noexcept
{
  SDL_SetWindowIcon(m_window, icon.get());
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_title(const std::string& title) noexcept
{
  SDL_SetWindowTitle(m_window, title.c_str());
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_opacity(float opacity) noexcept
{  // TODO doc: the window must be visible?
  SDL_SetWindowOpacity(m_window, opacity);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_min_size(int width, int height) noexcept
{
  SDL_SetWindowMinimumSize(m_window, width, height);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_max_size(int width, int height) noexcept
{
  SDL_SetWindowMaximumSize(m_window, width, height);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_position(int x, int y) noexcept
{
  SDL_SetWindowPosition(m_window, x, y);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(m_window, detail::convert_bool(grabMouse));
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_brightness(float brightness) noexcept
{
  if (fullscreen()) {
    SDL_SetWindowBrightness(m_window,
                            detail::clamp_inclusive({0, 1}, brightness));
    notify_window_listeners();
  }
}

CENTURION_DEF
void Window::set_capturing_mouse(bool capturingMouse) noexcept
{
  SDL_CaptureMouse(detail::convert_bool(capturingMouse));
}

CENTURION_DEF
bool Window::decorated() const noexcept
{
  return !(flags() & SDL_WINDOW_BORDERLESS);
}

CENTURION_DEF
bool Window::grabbing_mouse() const noexcept
{
  return SDL_GetWindowGrab(m_window);
}

CENTURION_DEF
float Window::opacity() const noexcept
{
  float opacity = 1;
  SDL_GetWindowOpacity(m_window, &opacity);
  return opacity;
}

CENTURION_DEF
float Window::brightness() const noexcept
{
  return SDL_GetWindowBrightness(m_window);
}

CENTURION_DEF
Uint32 Window::id() const noexcept
{
  return SDL_GetWindowID(m_window);
}

CENTURION_DEF
Optional<int> Window::display_index() const noexcept
{
  const auto index = SDL_GetWindowDisplayIndex(m_window);
  if (index != -1) {
    return index;
  } else {
    return nothing;
  }
}

CENTURION_DEF
int Window::x() const noexcept
{
  int x = 0;
  SDL_GetWindowPosition(m_window, &x, nullptr);
  return x;
}

CENTURION_DEF
int Window::y() const noexcept
{
  int y = 0;
  SDL_GetWindowPosition(m_window, nullptr, &y);
  return y;
}

CENTURION_DEF
IPoint Window::position() const noexcept
{
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(m_window, &x, &y);
  return {x, y};
}

CENTURION_DEF
Dimension Window::min_size() const noexcept
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
Dimension Window::max_size() const noexcept
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(m_window, &w, &h);
  return {w, h};
}

CENTURION_DEF
int Window::width() const noexcept
{
  int width = 0;
  SDL_GetWindowSize(m_window, &width, nullptr);
  return width;
}

CENTURION_DEF
int Window::height() const noexcept
{
  int height = 0;
  SDL_GetWindowSize(m_window, nullptr, &height);
  return height;
}

CENTURION_DEF
bool Window::resizable() const noexcept
{
  return flags() & SDL_WINDOW_RESIZABLE;
}

CENTURION_DEF
bool Window::fullscreen() const noexcept
{
  return flags() & SDL_WINDOW_FULLSCREEN;
}

CENTURION_DEF
bool Window::fullscreen_desktop() const noexcept
{
  return flags() & SDL_WINDOW_FULLSCREEN_DESKTOP;
}

CENTURION_DEF
bool Window::visible() const noexcept
{
  return flags() & SDL_WINDOW_SHOWN;
}

CENTURION_DEF
bool Window::opengl() const noexcept
{
  return flags() & SDL_WINDOW_OPENGL;
}

CENTURION_DEF
bool Window::vulkan() const noexcept
{
  return flags() & SDL_WINDOW_VULKAN;
}

CENTURION_DEF
bool Window::has_input_focus() const noexcept
{
  return flags() & SDL_WINDOW_INPUT_FOCUS;
}

CENTURION_DEF
bool Window::has_mouse_focus() const noexcept
{
  return flags() & SDL_WINDOW_MOUSE_FOCUS;
}

CENTURION_DEF
bool Window::is_foreign() const noexcept
{
  return flags() & SDL_WINDOW_FOREIGN;
}

CENTURION_DEF
bool Window::capturing_mouse() const noexcept
{
  return flags() & SDL_WINDOW_MOUSE_CAPTURE;
}

CENTURION_DEF
bool Window::always_on_top() const noexcept
{
  return flags() & SDL_WINDOW_ALWAYS_ON_TOP;
}

CENTURION_DEF
bool Window::minimized() const noexcept
{
  return flags() & SDL_WINDOW_MINIMIZED;
}

CENTURION_DEF
bool Window::maximized() const noexcept
{
  return flags() & SDL_WINDOW_MAXIMIZED;
}

CENTURION_DEF
bool Window::check_flag(SDL_WindowFlags flag) const noexcept
{
  return flags() & flag;
}

CENTURION_DEF
Uint32 Window::flags() const noexcept
{
  return SDL_GetWindowFlags(m_window);
}

CENTURION_DEF
SDL_Renderer* Window::renderer() const noexcept
{
  return SDL_GetRenderer(m_window);
}

CENTURION_DEF
PixelFormat Window::pixel_format() const noexcept
{
  return static_cast<PixelFormat>(SDL_GetWindowPixelFormat(m_window));
}

CENTURION_DEF
std::string Window::title() const noexcept
{
  return SDL_GetWindowTitle(m_window);
}

CENTURION_DEF
std::string Window::to_string() const
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Window@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_SOURCE