#ifndef CENTURION_name_SOURCE
#define CENTURION_name_SOURCE

#include "event.hpp"

namespace centurion::event {

CENTURION_DEF
JoyBallEvent::JoyBallEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyBallEvent::JoyBallEvent(const SDL_JoyBallEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
void JoyBallEvent::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void JoyBallEvent::set_ball(u8 ball) noexcept
{
  m_event.ball = ball;
}

CENTURION_DEF
void JoyBallEvent::set_dx(i16 dx) noexcept
{
  m_event.xrel = dx;
}

CENTURION_DEF
void JoyBallEvent::set_dy(i16 dy) noexcept
{
  m_event.yrel = dy;
}

CENTURION_DEF
auto JoyBallEvent::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto JoyBallEvent::ball() const noexcept -> u8
{
  return m_event.ball;
}

CENTURION_DEF
auto JoyBallEvent::dx() const noexcept -> i16
{
  return m_event.xrel;
}

CENTURION_DEF
auto JoyBallEvent::dy() const noexcept -> i16
{
  return m_event.yrel;
}

}  // namespace centurion::event

#endif  // CENTURION_name_SOURCE