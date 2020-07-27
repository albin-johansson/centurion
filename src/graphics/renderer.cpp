#include "renderer.hpp"

#include "centurion_utils.hpp"

namespace centurion {

auto to_string(const renderer& renderer) -> std::string
{
  return "[renderer | ptr: " + detail::address_of(renderer.get()) + "]";
}

auto operator<<(std::ostream& stream, const renderer& renderer) -> std::ostream&
{
  stream << to_string(renderer);
  return stream;
}

}  // namespace centurion
