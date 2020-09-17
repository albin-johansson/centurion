#include "window.hpp"

#include "detail/to_string.hpp"
#include "detail/utils.hpp"
#include "exception.hpp"

namespace centurion {

window::window(nn_owner<SDL_Window*> window) noexcept : m_window{window}
{}

window::window(nn_czstring title, const iarea& size)
{
  if ((size.width < 1) || (size.height < 1)) {
    throw exception{"Invalid width or height!"};
  }

  m_window.reset(SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  size.width,
                                  size.height,
                                  SDL_WINDOW_HIDDEN));
  if (!m_window) {
    throw sdl_error{"Failed to create window"};
  }
}

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

auto window::unique(nn_czstring title, const iarea& size) -> uptr
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

auto window::shared(nn_czstring title, const iarea& size) -> sptr
{
  return std::make_shared<window>(title, size);
}

auto to_string(const window& window) -> std::string
{
  const auto ptr = detail::address_of(window.get());
  const auto w = detail::to_string(window.width()).value();
  const auto h = detail::to_string(window.height()).value();
  return "[window | ptr: " + ptr + ", width: " + w + ", height: " + h + "]";
}

auto operator<<(std::ostream& stream, const window& window) -> std::ostream&
{
  stream << to_string(window);
  return stream;
}

}  // namespace centurion
