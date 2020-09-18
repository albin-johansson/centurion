#include "event.hpp"

namespace cen {

joy_ball_event::joy_ball_event() noexcept : common_event{}
{}

joy_ball_event::joy_ball_event(const SDL_JoyBallEvent& event) noexcept
    : common_event{event}
{}

void joy_ball_event::set_which(SDL_JoystickID which) noexcept
{
  m_event.which = which;
}

void joy_ball_event::set_ball(u8 ball) noexcept
{
  m_event.ball = ball;
}

void joy_ball_event::set_dx(i16 dx) noexcept
{
  m_event.xrel = dx;
}

void joy_ball_event::set_dy(i16 dy) noexcept
{
  m_event.yrel = dy;
}

auto joy_ball_event::which() const noexcept -> SDL_JoystickID
{
  return m_event.which;
}

auto joy_ball_event::ball() const noexcept -> u8
{
  return m_event.ball;
}

auto joy_ball_event::dx() const noexcept -> i16
{
  return m_event.xrel;
}

auto joy_ball_event::dy() const noexcept -> i16
{
  return m_event.yrel;
}

}  // namespace cen
