#include "renderer_handle.hpp"

#include "centurion_utils.hpp"
#include "renderer.hpp"

namespace centurion {

renderer_handle::renderer_handle(SDL_Renderer* renderer) noexcept
    : m_renderer{renderer}
{}

renderer_handle::renderer_handle(renderer& renderer) noexcept
    : m_renderer{renderer.get()}
{}

auto to_string(const renderer_handle& handle) -> std::string
{
  return "[renderer_handle | ptr: " + detail::address_of(handle.get()) + "]";
}

auto operator<<(std::ostream& stream, const renderer_handle& handle)
    -> std::ostream&
{
  stream << to_string(handle);
  return stream;
}

}  // namespace centurion
