#ifndef CENTURION_JOY_AXIS_EVENT_SOURCE
#define CENTURION_JOY_AXIS_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
joy_axis_event::joy_axis_event() noexcept : common_event{}
{}

CENTURION_DEF
joy_axis_event::joy_axis_event(const SDL_JoyAxisEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void joy_axis_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void joy_axis_event::set_axis(u8 axis) noexcept
{
  m_event.axis = axis;
}

CENTURION_DEF
void joy_axis_event::set_value(i16 value) noexcept
{
  m_event.value = value;
}

CENTURION_DEF
auto joy_axis_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto joy_axis_event::axis() const noexcept -> u8
{
  return m_event.axis;
}

CENTURION_DEF
auto joy_axis_event::value() const noexcept -> i16
{
  return m_event.value;
}

}  // namespace centurion

#endif  // CENTURION_JOY_AXIS_EVENT_SOURCE