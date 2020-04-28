#ifndef CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
#define CENTURION_CONTROLLER_AXIS_EVENT_SOURCE

#include "controller_axis_event.h"

namespace centurion {
namespace event {

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent() noexcept : BaseEvent{}
{}

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent(
    const SDL_ControllerAxisEvent& event) noexcept
    : BaseEvent{event}
{}

CENTURION_DEF
ControllerAxisEvent::ControllerAxisEvent(
    SDL_ControllerAxisEvent&& event) noexcept
    : BaseEvent{event}
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
void ControllerAxisEvent::set_value(int16_t value) noexcept
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
int16_t ControllerAxisEvent::value() const noexcept
{
  return m_event.value;
}

CENTURION_DEF
bool operator==(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept
{
  return static_cast<SDL_GameControllerAxis>(axis) == sdlAxis;
}

CENTURION_DEF
bool operator==(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept
{
  return sdlAxis == static_cast<SDL_GameControllerAxis>(axis);
}

CENTURION_DEF
bool operator!=(GameControllerAxis axis,
                SDL_GameControllerAxis sdlAxis) noexcept
{
  return !(axis == sdlAxis);
}

CENTURION_DEF
bool operator!=(SDL_GameControllerAxis sdlAxis,
                GameControllerAxis axis) noexcept
{
  return !(sdlAxis == axis);
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_SOURCE
