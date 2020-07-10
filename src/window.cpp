#ifndef CENTURION_WINDOW_SOURCE
#define CENTURION_WINDOW_SOURCE

#include "window.hpp"

#include "error.hpp"

namespace centurion {

CENTURION_DEF
window::window() : window{"Centurion window"}
{}

CENTURION_DEF
window::window(owner<SDL_Window*> window) : window_base{window}
{
  if (!window) {
    throw centurion_exception{"Cannot create Window from null SDL_Window!"};
  }
}

CENTURION_DEF
window::window(czstring title, area_i size)
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
window::window(window&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
window::~window() noexcept
{
  destroy();
}

CENTURION_DEF
auto window::operator=(window&& other) noexcept -> window&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void window::destroy() noexcept
{
  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
}

CENTURION_DEF
void window::move(window&& other) noexcept
{
  destroy();

  m_window = other.m_window;

  other.m_window = nullptr;
}

CENTURION_DEF
auto window::unique() -> std::unique_ptr<window>
{
  return std::make_unique<window>();
}

CENTURION_DEF
auto window::unique(owner<SDL_Window*> sdlWindow) -> std::unique_ptr<window>
{
  return std::make_unique<window>(sdlWindow);
}

CENTURION_DEF
auto window::unique(czstring title, area_i size) -> std::unique_ptr<window>
{
  return std::make_unique<window>(title, size);
}

CENTURION_DEF
auto window::shared() -> std::shared_ptr<window>
{
  return std::make_shared<window>();
}

CENTURION_DEF
auto window::shared(owner<SDL_Window*> sdlWindow) -> std::shared_ptr<window>
{
  return std::make_shared<window>(sdlWindow);
}

CENTURION_DEF
auto window::shared(czstring title, area_i size) -> std::shared_ptr<window>
{
  return std::make_shared<window>(title, size);
}

}  // namespace centurion

#endif  // CENTURION_WINDOW_SOURCE