#include "window.hpp"

#include <type_traits>

#include "detail/to_string.hpp"
#include "detail/utils.hpp"
#include "exception.hpp"

namespace cen {

static_assert(std::is_final_v<window>);

static_assert(std::is_default_constructible_v<window>);
static_assert(std::is_nothrow_destructible_v<window>);

static_assert(std::is_nothrow_move_assignable_v<window>);
static_assert(std::is_nothrow_move_constructible_v<window>);

static_assert(!std::is_copy_assignable_v<window>);
static_assert(!std::is_copy_constructible_v<window>);

window::window(owner<SDL_Window*> window) : m_window{window}
{
  if (!m_window) {
    throw exception{"Cannot create window from null pointer!"};
  }
}

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

}  // namespace cen
