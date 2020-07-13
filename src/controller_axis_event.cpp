#ifndef CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
#define CENTURION_CONTROLLER_AXIS_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
controller_axis_event::controller_axis_event() noexcept : common_event{}
{}

CENTURION_DEF
controller_axis_event::controller_axis_event(
    const SDL_ControllerAxisEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void controller_axis_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void controller_axis_event::set_axis(game_controller_axis axis) noexcept
{
  m_event.axis = static_cast<u8>(axis);
}

CENTURION_DEF
void controller_axis_event::set_value(i16 value) noexcept
{
  m_event.value = value;
}

CENTURION_DEF
auto controller_axis_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto controller_axis_event::axis() const noexcept -> game_controller_axis
{
  return static_cast<game_controller_axis>(m_event.axis);
}

CENTURION_DEF
auto controller_axis_event::value() const noexcept -> i16
{
  return m_event.value;
}

}  // namespace centurion

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
