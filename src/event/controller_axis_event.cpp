#include "event.hpp"

namespace centurion {

controller_axis_event::controller_axis_event() noexcept : common_event{}
{}

controller_axis_event::controller_axis_event(
    const SDL_ControllerAxisEvent& event) noexcept
    : common_event{event}
{}

void controller_axis_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

void controller_axis_event::set_axis(gamepad_axis axis) noexcept
{
  m_event.axis = static_cast<u8>(axis);
}

void controller_axis_event::set_value(i16 value) noexcept
{
  m_event.value = value;
}

auto controller_axis_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

auto controller_axis_event::axis() const noexcept -> gamepad_axis
{
  return static_cast<gamepad_axis>(m_event.axis);
}

auto controller_axis_event::value() const noexcept -> i16
{
  return m_event.value;
}

}  // namespace centurion
