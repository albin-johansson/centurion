#include "window.h"
#include <cstdint>
#include <stdexcept>
#include "window_listener.h"
#include "bool_converter.h"

namespace centurion {

Window::Window(const std::string& title, int width, int height) {
  if ((width < 1) || (height < 1)) {
    throw std::invalid_argument("Invalid width or height!");
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  window = SDL_CreateWindow(title.c_str(), pos, pos, width, height,
                            SDL_WINDOW_HIDDEN);

  // TODO...
//    SDL_SetWindowDisplayMode(window, ...)
}

Window::Window(int width, int height) : Window("Centurion window", width, height) {}

Window::Window() : Window(800, 600) {}

Window::Window(Window&& other) noexcept
    : window{other.window},
      windowListeners{std::move(other.windowListeners)} {
  other.window = nullptr;
}

Window::~Window() {
  if (window) {
    SDL_DestroyWindow(window);
  }
}

Window& Window::operator=(Window&& other) noexcept {
  window = other.window;
  windowListeners = std::move(other.windowListeners);

  other.window = nullptr;

  return *this;
}

void Window::notify_window_listeners() noexcept {
  const auto& self = *this;
  for (auto listener : windowListeners) {
    if (listener) {
      listener->window_updated(self);
    }
  }
}

void Window::show() noexcept {
  SDL_ShowWindow(window);
  notify_window_listeners();
}

void Window::hide() noexcept {
  SDL_HideWindow(window);
  notify_window_listeners();
}

void Window::center() noexcept {
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::raise() noexcept {
  SDL_RaiseWindow(window);
}

void Window::add_window_listener(IWindowListener* listener) noexcept {
  if (listener) {
    windowListeners.push_back(listener);
  }
}

void Window::set_fullscreen(bool fullscreen) noexcept {
  const auto flags = (fullscreen) ? (SDL_GetWindowFlags(window) | SDL_WINDOW_FULLSCREEN)
                                  : (SDL_GetWindowFlags(window) & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);

  if (!fullscreen) {
    set_gamma(1);
  }

  notify_window_listeners();
}

void Window::set_decorated(bool decorated) noexcept {
  SDL_SetWindowBordered(window, BoolConverter::convert(decorated));
  notify_window_listeners();
}

void Window::set_resizable(bool isResizable) noexcept {
  SDL_SetWindowResizable(window, BoolConverter::convert(isResizable));
  notify_window_listeners();
}

void Window::set_width(int width) {
  if (width < 1) {
    throw std::invalid_argument("Invalid width!");
  } else {
    SDL_SetWindowSize(window, width, get_height());
    notify_window_listeners();
  }
}

void Window::set_height(int height) {
  if (height < 1) {
    throw std::invalid_argument("Invalid height!");
  } else {
    SDL_SetWindowSize(window, get_width(), height);
    notify_window_listeners();
  }
}

void Window::set_icon(gsl::not_null<SDL_Surface*> icon) noexcept {
  SDL_SetWindowIcon(window, icon);
  notify_window_listeners();
}

void Window::set_title(const std::string& title) noexcept {
  SDL_SetWindowTitle(window, title.c_str());
}

void Window::set_gamma(float gamma) noexcept {
  if (is_fullscreen()) {
    SDL_SetWindowBrightness(window, gamma);
  }
}

void Window::set_opacity(float opacity) noexcept {
  SDL_SetWindowOpacity(window, opacity);
}

void Window::set_min_size(int width, int height) noexcept {
  SDL_SetWindowMinimumSize(window, width, height);
}

void Window::set_max_size(int width, int height) noexcept {
  SDL_SetWindowMaximumSize(window, width, height);
}

void Window::set_position(int x, int y) noexcept {
  SDL_SetWindowPosition(window, x, y);
}

void Window::set_grab_mouse(bool grabMouse) noexcept {
  SDL_SetWindowGrab(window, BoolConverter::convert(grabMouse));
}

bool Window::is_resizable() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
}

bool Window::is_fullscreen() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
}

bool Window::is_visible() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
}

int Window::get_width() const noexcept {
  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);

  return width;
}

int Window::get_height() const noexcept {
  int height = 0;
  SDL_GetWindowSize(window, nullptr, &height);

  return height;
}

std::string Window::get_title() const noexcept {
  return SDL_GetWindowTitle(window);
}

Window::operator SDL_Window*() const noexcept {
  return window;
}

}