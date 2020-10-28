#include "color.hpp"

#include "detail/to_string.hpp"

namespace cen {

auto to_string(const color& color) -> std::string
{
  using detail::to_string;
  return "[color | r: " + to_string(color.red()).value() +
         ", g: " + to_string(color.green()).value() +
         ", b: " + to_string(color.blue()).value() +
         ", a: " + to_string(color.alpha()).value() + "]";
}

auto operator<<(std::ostream& stream, const color& color) -> std::ostream&
{
  stream << to_string(color);
  return stream;
}

}  // namespace cen
