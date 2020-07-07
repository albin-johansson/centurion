#ifndef CENTURION_JOY_AXIS_EVENT_SOURCE
#define CENTURION_JOY_AXIS_EVENT_SOURCE

#include "event.hpp"

namespace centurion ::event {

CENTURION_DEF
JoyAxisEvent::JoyAxisEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyAxisEvent::JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void JoyAxisEvent::set_which(JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void JoyAxisEvent::set_axis(Uint8 axis) noexcept
{
  m_event.axis = axis;
}

CENTURION_DEF
void JoyAxisEvent::set_value(Sint16 value) noexcept
{
  m_event.value = value;
}

CENTURION_DEF
auto JoyAxisEvent::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto JoyAxisEvent::axis() const noexcept -> Uint8
{
  return m_event.axis;
}

CENTURION_DEF
auto JoyAxisEvent::value() const noexcept -> Sint16
{
  return m_event.value;
}

}  // namespace centurion::event

#endif  // CENTURION_JOY_AXIS_EVENT_SOURCE