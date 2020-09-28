#include "color.hpp"

namespace cen {

auto to_string(const color& color) -> std::string
{
  return "[color | r: " + std::to_string(color.red()) +
         ", g: " + std::to_string(color.green()) +
         ", b: " + std::to_string(color.blue()) +
         ", a: " + std::to_string(color.alpha()) + "]";
}

auto operator<<(std::ostream& stream, const color& color) -> std::ostream&
{
  stream << to_string(color);
  return stream;
}

}  // namespace cen
