#ifndef CENTURION_JOY_AXIS_EVENT_SOURCE
#define CENTURION_JOY_AXIS_EVENT_SOURCE

#include "joy_axis_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
JoyAxisEvent::JoyAxisEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyAxisEvent::JoyAxisEvent(const SDL_JoyAxisEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
JoyAxisEvent::JoyAxisEvent(SDL_JoyAxisEvent&& event) noexcept
    : CommonEvent{std::move(event)}
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
JoystickID JoyAxisEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
Uint8 JoyAxisEvent::axis() const noexcept
{
  return m_event.axis;
}

CENTURION_DEF
Sint16 JoyAxisEvent::value() const noexcept
{
  return m_event.value;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_JOY_AXIS_EVENT_SOURCE