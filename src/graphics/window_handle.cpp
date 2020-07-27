#include "window_handle.hpp"

#include "centurion_utils.hpp"

namespace centurion {

window_handle::window_handle(SDL_Window* window) noexcept : m_window{window}
{}

window_handle::window_handle(const window& window) noexcept
    : m_window{window.get()}
{}

window_handle::operator bool() const noexcept
{
  return static_cast<bool>(m_window);
}

auto to_string(const window_handle& handle) -> std::string
{
  const auto ptr = detail::address_of(handle.get());
  return "[window_handle | ptr: " + ptr + "]";
}

auto operator<<(std::ostream& stream, const window_handle& handle)
    -> std::ostream&
{
  stream << to_string(handle);
  return stream;
}

}  // namespace centurion
