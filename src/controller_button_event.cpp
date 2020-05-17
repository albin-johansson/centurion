#ifndef CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
#define CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE

#include "controller_button_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
ControllerButtonEvent::ControllerButtonEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF ControllerButtonEvent::ControllerButtonEvent(
    const SDL_ControllerButtonEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
ControllerButtonEvent::ControllerButtonEvent(
    SDL_ControllerButtonEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void ControllerButtonEvent::set_button(GameControllerButton button) noexcept
{
  m_event.button = static_cast<Uint8>(button);
}

CENTURION_DEF
void ControllerButtonEvent::set_state(ButtonState state) noexcept
{
  m_event.state = static_cast<Uint8>(state);
}

CENTURION_DEF
void ControllerButtonEvent::set_which(JoystickID id) noexcept
{
  m_event.which = id;
}

CENTURION_DEF
GameControllerButton ControllerButtonEvent::button() const noexcept
{
  return static_cast<GameControllerButton>(m_event.button);
}

CENTURION_DEF
ButtonState ControllerButtonEvent::state() const noexcept
{
  return static_cast<ButtonState>(m_event.state);
}

CENTURION_DEF
JoystickID ControllerButtonEvent::which() const noexcept
{
  return m_event.which;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_CONTROLLER_BUTTON_EVENT_SOURCE
