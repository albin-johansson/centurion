#ifndef CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
#define CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
ControllerButtonEvent::ControllerButtonEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF ControllerButtonEvent::ControllerButtonEvent(
    const SDL_ControllerButtonEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void ControllerButtonEvent::set_button(GameControllerButton button) noexcept
{
  m_event.button = static_cast<u8>(button);
}

CENTURION_DEF
void ControllerButtonEvent::set_state(button_state state) noexcept
{
  m_event.state = static_cast<u8>(state);
}

CENTURION_DEF
void ControllerButtonEvent::set_which(SDL_JoystickID id) noexcept
{
  m_event.which = id;
}

CENTURION_DEF
auto ControllerButtonEvent::button() const noexcept -> GameControllerButton
{
  return static_cast<GameControllerButton>(m_event.button);
}

CENTURION_DEF
auto ControllerButtonEvent::state() const noexcept -> button_state
{
  return static_cast<button_state>(m_event.state);
}

CENTURION_DEF
auto ControllerButtonEvent::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

}  // namespace centurion

#endif  // CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
