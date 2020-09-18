#include "scan_code.hpp"

namespace cen {

auto to_string(const scan_code& scanCode) -> std::string
{
  const auto key = scanCode.name();
  return "[scan_code | key: " + key + "]";
}

auto operator<<(std::ostream& stream, const scan_code& scanCode)
    -> std::ostream&
{
  stream << to_string(scanCode);
  return stream;
}

}  // namespace cen
