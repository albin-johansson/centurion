#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyBallEvent, Defaults)
{
  cen::joy_ball_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::joystick_ball_motion, event.type());
}

TEST(JoyBallEvent, SetWhich)
{
  cen::joy_ball_event event;

  constexpr auto which = 3;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(JoyBallEvent, SetBall)
{
  cen::joy_ball_event event;

  constexpr auto ball = 7;
  event.set_ball(ball);

  ASSERT_EQ(ball, event.ball());
}

TEST(JoyBallEvent, SetDx)
{
  cen::joy_ball_event event;

  constexpr auto dx = 173;
  event.set_dx(dx);

  ASSERT_EQ(dx, event.dx());
}

TEST(JoyBallEvent, SetDy)
{
  cen::joy_ball_event event;

  constexpr auto dy = -57;
  event.set_dy(dy);

  ASSERT_EQ(dy, event.dy());
}

TEST(JoyBallEvent, Which)
{
  SDL_JoyBallEvent sdl;
  sdl.which = 5;

  const cen::joy_ball_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(JoyBallEvent, Ball)
{
  SDL_JoyBallEvent sdl;
  sdl.ball = 17;

  const cen::joy_ball_event event{sdl};
  ASSERT_EQ(sdl.ball, event.ball());
}

TEST(JoyBallEvent, Dx)
{
  SDL_JoyBallEvent sdl;
  sdl.xrel = 723;

  const cen::joy_ball_event event{sdl};
  ASSERT_EQ(sdl.xrel, event.dx());
}

TEST(JoyBallEvent, Dy)
{
  SDL_JoyBallEvent sdl;
  sdl.yrel = 5933;

  const cen::joy_ball_event event{sdl};
  ASSERT_EQ(sdl.yrel, event.dy());
}

TEST(JoyBallEvent, AsSDLEvent)
{
  const cen::joy_ball_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jball.type, static_cast<cen::u32>(event.type()));
  ASSERT_EQ(sdl.jball.timestamp, event.time());
}
