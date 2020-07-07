#ifndef CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
#define CENTURION_CONTROLLER_AXIS_EVENT_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent(
    const SDL_ControllerAxisEvent& event) noexcept
    : CommonEvent{event}
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
auto ControllerAxisEvent::which() const noexcept -> JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto ControllerAxisEvent::axis() const noexcept -> GameControllerAxis
{
  return static_cast<GameControllerAxis>(m_event.axis);
}

CENTURION_DEF
auto ControllerAxisEvent::value() const noexcept -> Sint16
{
  return m_event.value;
}

}  // namespace centurion::event

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
