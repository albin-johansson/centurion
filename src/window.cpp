#include "window.hpp"

#include "error.hpp"

namespace centurion {

window::window(nn_czstring title, area_i size)  // TODO ban nullptr titles?
{
  if ((size.width < 1) || (size.height < 1)) {
    throw centurion_exception{"Invalid width or height!"};
  }

  m_window.reset(SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  size.width,
                                  size.height,
                                  SDL_WINDOW_HIDDEN));
  if (!m_window) {
    throw detail::core_error("Failed to create window!");
  }
}

window::window(nn_owner<SDL_Window*> window) : m_window{window}
{}

window::window() : window{"Centurion window"}
{}

auto window::unique() -> uptr
{
  return std::make_unique<window>();
}

auto window::unique(nn_owner<SDL_Window*> sdlWindow) -> uptr
{
  return std::make_unique<window>(sdlWindow);
}

auto window::unique(nn_czstring title, area_i size) -> uptr
{
  return std::make_unique<window>(title, size);
}

auto window::shared() -> sptr
{
  return std::make_shared<window>();
}

auto window::shared(nn_owner<SDL_Window*> sdlWindow) -> sptr
{
  return std::make_shared<window>(sdlWindow);
}

auto window::shared(nn_czstring title, area_i size) -> sptr
{
  return std::make_shared<window>(title, size);
}

}  // namespace centurion
