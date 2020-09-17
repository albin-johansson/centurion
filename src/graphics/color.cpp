#include "color.hpp"

#include "detail/to_string.hpp"

namespace centurion {

auto to_string(const color& color) -> std::string
{
  const auto r = detail::to_string(color.red()).value();
  const auto g = detail::to_string(color.green()).value();
  const auto b = detail::to_string(color.blue()).value();
  const auto a = detail::to_string(color.alpha()).value();
  return "[color | r: " + r + ", g: " + g + ", b: " + b + ", a: " + a + "]";
}

auto operator<<(std::ostream& stream, const color& color) -> std::ostream&
{
  stream << to_string(color);
  return stream;
}

}  // namespace centurion
