#ifndef CENTURION_JOY_BUTTON_EVENT_SOURCE
#define CENTURION_JOY_BUTTON_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
JoyButtonEvent::JoyButtonEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyButtonEvent::JoyButtonEvent(const SDL_JoyButtonEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void JoyButtonEvent::set_which(SDL_JoystickID which) noexcept
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
auto JoyButtonEvent::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto JoyButtonEvent::button() const noexcept -> Uint8
{
  return m_event.button;
}

CENTURION_DEF
auto JoyButtonEvent::state() const noexcept -> ButtonState
{
  return static_cast<ButtonState>(m_event.state);
}

}  // namespace centurion::event

#endif  // CENTURION_JOY_BUTTON_EVENT_SOURCE