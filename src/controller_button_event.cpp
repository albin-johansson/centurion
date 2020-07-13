#ifndef CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
#define CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
controller_button_event::controller_button_event() noexcept : common_event{}
{}

CENTURION_DEF controller_button_event::controller_button_event(
    const SDL_ControllerButtonEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void controller_button_event::set_button(game_controller_button button) noexcept
{
  m_event.button = static_cast<u8>(button);
}

CENTURION_DEF
void controller_button_event::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
void controller_button_event::set_which(SDL_JoystickID id) noexcept
{
  m_event.which = id;
}

CENTURION_DEF
auto controller_button_event::button() const noexcept -> game_controller_button
{
  return static_cast<game_controller_button>(m_event.button);
}

CENTURION_DEF
auto controller_button_event::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

CENTURION_DEF
auto controller_button_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

}  // namespace centurion

#endif  // CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
