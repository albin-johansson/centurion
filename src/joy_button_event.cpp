#ifndef CENTURION_JOY_BUTTON_EVENT_SOURCE
#define CENTURION_JOY_BUTTON_EVENT_SOURCE

#include "joy_button_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
JoyButtonEvent::JoyButtonEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
JoyButtonEvent::JoyButtonEvent(SDL_JoyButtonEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void JoyButtonEvent::set_which(JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void JoyButtonEvent::set_button(Uint8 button) noexcept
{
  m_event.button = button;
}

CENTURION_DEF
void JoyButtonEvent::set_state(ButtonState state) noexcept
{
  m_event.state = static_cast<Uint8>(state);
}

CENTURION_DEF
JoystickID JoyButtonEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
Uint8 JoyButtonEvent::button() const noexcept
{
  return m_event.button;
}

CENTURION_DEF
ButtonState JoyButtonEvent::state() const noexcept
{
  return static_cast<ButtonState>(m_event.state);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_JOY_BUTTON_EVENT_SOURCE