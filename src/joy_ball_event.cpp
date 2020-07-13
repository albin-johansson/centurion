#ifndef CENTURION_name_SOURCE
#define CENTURION_name_SOURCE

#include "event.hpp"

namespace centurion {

CENTURION_DEF
joy_ball_event::joy_ball_event() noexcept : common_event{}
{}

CENTURION_DEF
joy_ball_event::joy_ball_event(const SDL_JoyBallEvent& event) noexcept
    : common_event{event}
{}

CENTURION_DEF
void joy_ball_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

CENTURION_DEF
void joy_ball_event::set_ball(u8 ball) noexcept
{
  m_event.ball = ball;
}

CENTURION_DEF
void joy_ball_event::set_dx(i16 dx) noexcept
{
  m_event.xrel = dx;
}

CENTURION_DEF
void joy_ball_event::set_dy(i16 dy) noexcept
{
  m_event.yrel = dy;
}

CENTURION_DEF
auto joy_ball_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

CENTURION_DEF
auto joy_ball_event::ball() const noexcept -> u8
{
  return m_event.ball;
}

CENTURION_DEF
auto joy_ball_event::dx() const noexcept -> i16
{
  return m_event.xrel;
}

CENTURION_DEF
auto joy_ball_event::dy() const noexcept -> i16
{
  return m_event.yrel;
}

}  // namespace centurion

#endif  // CENTURION_name_SOURCE