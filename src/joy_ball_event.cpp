#ifndef CENTURION_name_SOURCE
#define CENTURION_name_SOURCE

#include "joy_ball_event.h"

#include <utility>

namespace centurion {
namespace event {

CENTURION_DEF
JoyBallEvent::JoyBallEvent() noexcept : CommonEvent{}
{}

CENTURION_DEF
JoyBallEvent::JoyBallEvent(const SDL_JoyBallEvent& event) noexcept
    : CommonEvent{event}
{}

CENTURION_DEF
JoyBallEvent::JoyBallEvent(SDL_JoyBallEvent&& event) noexcept
    : CommonEvent{std::move(event)}
{}

CENTURION_DEF
void JoyBallEvent::set_which(JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void JoyBallEvent::set_ball(Uint8 ball) noexcept
{
  m_event.ball = ball;
}

CENTURION_DEF
void JoyBallEvent::set_dx(Sint16 dx) noexcept
{
  m_event.xrel = dx;
}

CENTURION_DEF
void JoyBallEvent::set_dy(Sint16 dy) noexcept
{
  m_event.yrel = dy;
}

CENTURION_DEF
JoystickID JoyBallEvent::which() const noexcept
{
  return m_event.which;
}

CENTURION_DEF
Uint8 JoyBallEvent::ball() const noexcept
{
  return m_event.ball;
}

CENTURION_DEF
Sint16 JoyBallEvent::dx() const noexcept
{
  return m_event.xrel;
}

CENTURION_DEF
Sint16 JoyBallEvent::dy() const noexcept
{
  return m_event.yrel;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_name_SOURCE