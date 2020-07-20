#include "window.hpp"

#include "error.hpp"

namespace centurion {

window::window() : window{"Centurion window"}
{}

window::window(owner<SDL_Window*> window) : window_base{window}
{
  if (!window) {
    throw centurion_exception{"Cannot create Window from null SDL_Window!"};
  }
}

window::window(czstring title, area_i size)
{
  if ((size.width < 1) || (size.height < 1)) {
    throw centurion_exception{"Invalid width or height!"};
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  m_window = SDL_CreateWindow(
      title ? title : "", pos, pos, size.width, size.height, SDL_WINDOW_HIDDEN);
  if (!m_window) {
    throw detail::core_error("Failed to create Window!");
  }
}

window::window(window&& other) noexcept
{
  move(std::move(other));
}

window::~window() noexcept
{
  destroy();
}

auto window::operator=(window&& other) noexcept -> window&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

void window::destroy() noexcept
{
  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
}

void window::move(window&& other) noexcept
{
  destroy();

  m_window = other.m_window;

  other.m_window = nullptr;
}

auto window::unique() -> std::unique_ptr<window>
{
  return std::make_unique<window>();
}

auto window::unique(owner<SDL_Window*> sdlWindow) -> std::unique_ptr<window>
{
  return std::make_unique<window>(sdlWindow);
}

auto window::unique(czstring title, area_i size) -> std::unique_ptr<window>
{
  return std::make_unique<window>(title, size);
}

auto window::shared() -> std::shared_ptr<window>
{
  return std::make_shared<window>();
}

auto window::shared(owner<SDL_Window*> sdlWindow) -> std::shared_ptr<window>
{
  return std::make_shared<window>(sdlWindow);
}

auto window::shared(czstring title, area_i size) -> std::shared_ptr<window>
{
  return std::make_shared<window>(title, size);
}

}  // namespace centurion
