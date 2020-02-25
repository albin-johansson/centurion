#ifndef CENTURION_WINDOW_SOURCE
#define CENTURION_WINDOW_SOURCE

#include "window.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "surface.h"
#include "window_listener.h"

namespace centurion {
namespace video {

CENTURION_DEF
Window::Window(const char* title, int width, int height)
{
  if ((width < 1) || (height < 1)) {
    throw CenturionException{"Invalid width or height!"};
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  window = SDL_CreateWindow(
      title ? title : "", pos, pos, width, height, SDL_WINDOW_HIDDEN);

  SDL_Surface* icon = IMG_Load("centurion_icon.png");
  if (icon) {
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
  }
}

CENTURION_DEF
Window::Window(int width, int height)
    : Window{"Centurion window", width, height}
{}

CENTURION_DEF
Window::Window(const char* title) : Window{title, 800, 600}
{}

CENTURION_DEF
Window::Window() : Window{800, 600}
{}

CENTURION_DEF
Window::Window(Window&& other) noexcept
{
  SDL_DestroyWindow(window);

  window = other.window;
  other.window = nullptr;

  windowListeners = std::move(other.windowListeners);
}

CENTURION_DEF
Window::~Window()
{
  if (window) {
    SDL_DestroyWindow(window);
  }
}

CENTURION_DEF
Window& Window::operator=(Window&& other) noexcept
{
  SDL_DestroyWindow(window);

  window = other.window;
  other.window = nullptr;

  windowListeners = std::move(other.windowListeners);

  return *this;
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(const char* title, int width, int height)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Window>(title, width, height);
#else
  return centurion::make_unique<Window>(title, width, height);
#endif
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(int width, int height)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Window>(width, height);
#else
  return centurion::make_unique<Window>(width, height);
#endif
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique(const char* title)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Window>(title);
#else
  return centurion::make_unique<Window>(title);
#endif
}

CENTURION_DEF
std::unique_ptr<Window> Window::unique()
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Window>();
#else
  return centurion::make_unique<Window>();
#endif
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
std::shared_ptr<Window> Window::shared()
{
  return std::make_shared<Window>();
}

CENTURION_DEF
void Window::notify_window_listeners() noexcept
{
  const auto& self = *this;
  for (const auto& listener : windowListeners) {
    auto tmp = listener.lock();
    if (tmp) {
      tmp->window_updated(self);
    }
  }
}

CENTURION_DEF
void Window::show() noexcept
{
  SDL_ShowWindow(window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::hide() noexcept
{
  SDL_HideWindow(window);
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
  SDL_RaiseWindow(window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::maximise() noexcept
{
  SDL_MaximizeWindow(window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::minimise() noexcept
{
  SDL_MinimizeWindow(window);
  notify_window_listeners();
}

CENTURION_DEF
void Window::add_window_listener(
    std::weak_ptr<IWindowListener> listener) noexcept
{
  if (!listener.expired()) {
    windowListeners.push_back(listener);
  }
}

CENTURION_DEF
void Window::set_fullscreen(bool fullscreen) noexcept
{
  const auto flags =
      (fullscreen) ? (SDL_GetWindowFlags(window) | SDL_WINDOW_FULLSCREEN)
                   : (SDL_GetWindowFlags(window) & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);

  if (!fullscreen) {
    set_brightness(1);
  }

  notify_window_listeners();
}

CENTURION_DEF
void Window::set_decorated(bool decorated) noexcept
{
  SDL_SetWindowBordered(window, convert_bool(decorated));
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_resizable(bool isResizable) noexcept
{
  SDL_SetWindowResizable(window, convert_bool(isResizable));
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_width(int width)
{
  if (width < 1) {
    throw CenturionException{"Invalid window width!"};
  } else {
    SDL_SetWindowSize(window, width, get_height());
    notify_window_listeners();
  }
}

CENTURION_DEF
void Window::set_height(int height)
{
  if (height < 1) {
    throw CenturionException{"Invalid window height!"};
  } else {
    SDL_SetWindowSize(window, get_width(), height);
    notify_window_listeners();
  }
}

CENTURION_DEF
void Window::set_icon(const Surface& icon) noexcept
{
  SDL_SetWindowIcon(window, icon.get_internal());
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_title(const std::string& title) noexcept
{
  SDL_SetWindowTitle(window, title.c_str());
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_opacity(float opacity) noexcept
{  // TODO doc: the window must be visible?
  SDL_SetWindowOpacity(window, opacity);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_min_size(int width, int height) noexcept
{
  SDL_SetWindowMinimumSize(window, width, height);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_max_size(int width, int height) noexcept
{
  SDL_SetWindowMaximumSize(window, width, height);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_position(int x, int y) noexcept
{
  SDL_SetWindowPosition(window, x, y);
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_grab_mouse(bool grabMouse) noexcept
{
  SDL_SetWindowGrab(window, convert_bool(grabMouse));
  notify_window_listeners();
}

CENTURION_DEF
void Window::set_brightness(float brightness) noexcept
{
  if (is_fullscreen()) {
    if (brightness < 0) {
      brightness = 0;
    } else if (brightness > 1) {
      brightness = 1;
    }
    SDL_SetWindowBrightness(window, brightness);
    notify_window_listeners();
  }
}

CENTURION_DEF
bool Window::is_decorated() const noexcept
{
  int left = 0;
  int right = 0;
  int top = 0;
  int bottom = 0;
  SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
  return left || right || top || bottom;
}

CENTURION_DEF
bool Window::is_grabbing_mouse() const noexcept
{
  return SDL_GetWindowGrab(window);
}

CENTURION_DEF
bool Window::is_resizable() const noexcept
{
  return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
}

CENTURION_DEF
bool Window::is_fullscreen() const noexcept
{
  return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
}

CENTURION_DEF
bool Window::is_visible() const noexcept
{
  return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
}

CENTURION_DEF
float Window::get_opacity() const noexcept
{
  float opacity = 1;
  SDL_GetWindowOpacity(window, &opacity);
  return opacity;
}

CENTURION_DEF
float Window::get_brightness() const noexcept
{
  return SDL_GetWindowBrightness(window);
}

CENTURION_DEF
uint32_t Window::get_id() const noexcept
{
  return SDL_GetWindowID(window);
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF
std::optional<int> Window::get_display_index() const noexcept
{
  const auto index = SDL_GetWindowDisplayIndex(window);
  if (index != -1) {
    return index;
  } else {
    return std::nullopt;
  }
}

#endif

CENTURION_DEF
int Window::get_x() const noexcept
{
  int x = 0;
  SDL_GetWindowPosition(window, &x, nullptr);
  return x;
}

CENTURION_DEF
int Window::get_y() const noexcept
{
  int y = 0;
  SDL_GetWindowPosition(window, nullptr, &y);
  return y;
}

CENTURION_DEF
math::IPoint Window::get_position() const noexcept
{
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(window, &x, &y);
  return {x, y};
}

CENTURION_DEF
std::pair<int, int> Window::get_min_size() const noexcept
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(window, &w, &h);
  return {w, h};
}

CENTURION_DEF
std::pair<int, int> Window::get_max_size() const noexcept
{
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(window, &w, &h);
  return {w, h};
}

CENTURION_DEF
int Window::get_width() const noexcept
{
  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);
  return width;
}

CENTURION_DEF
int Window::get_height() const noexcept
{
  int height = 0;
  SDL_GetWindowSize(window, nullptr, &height);
  return height;
}

CENTURION_DEF
SDL_Renderer* Window::get_renderer() const noexcept
{
  return SDL_GetRenderer(window);
}

CENTURION_DEF
PixelFormat Window::get_pixel_format() const noexcept
{
  return static_cast<PixelFormat>(SDL_GetWindowPixelFormat(window));
}

CENTURION_DEF
std::string Window::get_title() const noexcept
{
  return SDL_GetWindowTitle(window);
}

CENTURION_DEF
std::string Window::to_string() const
{
  const auto address = address_of(this);
  const auto width = std::to_string(get_width());
  const auto height = std::to_string(get_height());
  return "[Window@" + address + " | Width: " + width + ", Height: " + height +
         "]";
}

CENTURION_DEF
Window::operator SDL_Window*() const noexcept
{
  return window;
}

CENTURION_DEF
SDL_Window* Window::get_internal() const noexcept
{
  return window;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_WINDOW_SOURCE