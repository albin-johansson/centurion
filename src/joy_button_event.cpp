#ifndef CENTURION_JOY_BUTTON_EVENT_SOURCE
#define CENTURION_JOY_BUTTON_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
joy_button_event::joy_button_event() noexcept : common_event{}
{}

CENTURION_DEF
joy_button_event::joy_button_event(const SDL_JoyButtonEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void joy_button_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void joy_button_event::set_button(u8 button) noexcept
{
  m_event.button = button;
}

CENTURION_DEF
void joy_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
auto joy_button_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto joy_button_event::button() const noexcept -> u8
{
  return m_event.button;
}

CENTURION_DEF
auto joy_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

}  // namespace centurion

#endif  // CENTURION_JOY_BUTTON_EVENT_SOURCE