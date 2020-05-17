#ifndef CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
#define CENTURION_CONTROLLER_AXIS_EVENT_SOURCE

#include "controller_axis_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent(
    const SDL_ControllerAxisEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent(
    SDL_ControllerAxisEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void ControllerAxisEvent::set_which(JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void ControllerAxisEvent::set_axis(GameControllerAxis axis) noexcept
{
  m_event.axis = static_cast<Uint8>(axis);
}

CENTURION_DEF
void ControllerAxisEvent::set_value(Sint16 value) noexcept
{
  m_event.value = value;
}

CENTURION_DEF
JoystickID ControllerAxisEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
GameControllerAxis ControllerAxisEvent::axis() const noexcept
{
  return static_cast<GameControllerAxis>(m_event.axis);
}

CENTURION_DEF
Sint16 ControllerAxisEvent::value() const noexcept
{
  return m_event.value;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
