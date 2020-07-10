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
Window::Window(owner<SDL_Window*> window) : window_base{window}
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

}  // namespace centurion

#endif  // CENTURION_WINDOW_SOURCE