#include "key_code.hpp"

namespace centurion {

auto to_string(const key_code& keyCode) -> std::string
{
  const auto key = keyCode.name();
  return "[key_code | key: " + key + "]";
}

auto operator<<(std::ostream& stream, const key_code& keyCode) -> std::ostream&
{
  stream << to_string(keyCode);
  return stream;
}

}  // namespace centurion
