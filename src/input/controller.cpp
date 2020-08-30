#include "controller.hpp"

#include "detail/utils.hpp"

namespace centurion {

auto to_string(const controller& controller) -> std::string
{
  using namespace std::string_literals;
  const auto ptr = detail::address_of(controller.get());
  const auto name = controller.name() ? controller.name() : "N/A";
  return "[controller | ptr: "s + ptr + ", name: "s + name + "]"s;
}

auto to_string(controller_handle handle) -> std::string
{
  using namespace std::string_literals;
  const auto ptr = detail::address_of(handle.get());
  const auto name = handle.name() ? handle.name() : "N/A";
  return "[controller_handle | ptr: "s + ptr + ", name: "s + name + "]"s;
}

auto operator<<(std::ostream& stream, const controller& controller)
    -> std::ostream&
{
  stream << to_string(controller);
  return stream;
}

auto operator<<(std::ostream& stream, controller_handle handle) -> std::ostream&
{
  stream << to_string(handle);
  return stream;
}

}  // namespace centurion
