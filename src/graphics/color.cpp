#include "color.hpp"

namespace centurion {

auto to_string(const color& color) -> std::string
{
  const auto r = std::to_string(color.red());
  const auto g = std::to_string(color.green());
  const auto b = std::to_string(color.blue());
  const auto a = std::to_string(color.alpha());
  return "[Color | R: " + r + ", G: " + g + ", B: " + b + ", A: " + a + "]";
}

auto operator<<(std::ostream& stream, const color& color) -> std::ostream&
{
  stream << to_string(color);
  return stream;
}

}  // namespace centurion
