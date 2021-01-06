#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyBallEvent, Defaults)
{
  cen::joy_ball_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::joystick_ball_motion, event.type());
}

TEST(JoyBallEvent, SetWhich)
{
  cen::joy_ball_event event;

  constexpr auto which = 3;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(JoyBallEvent, SetBall)
{
  cen::joy_ball_event event;

  constexpr auto ball = 7;
  event.set_ball(ball);

  EXPECT_EQ(ball, event.ball());
}

TEST(JoyBallEvent, SetDx)
{
  cen::joy_ball_event event;

  constexpr auto dx = 173;
  event.set_dx(dx);

  EXPECT_EQ(dx, event.dx());
}

TEST(JoyBallEvent, SetDy)
{
  cen::joy_ball_event event;

  constexpr auto dy = -57;
  event.set_dy(dy);

  EXPECT_EQ(dy, event.dy());
}

TEST(JoyBallEvent, Which)
{
  SDL_JoyBallEvent sdl;
  sdl.which = 5;

  const cen::joy_ball_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(JoyBallEvent, Ball)
{
  SDL_JoyBallEvent sdl;
  sdl.ball = 17;

  const cen::joy_ball_event event{sdl};
  EXPECT_EQ(sdl.ball, event.ball());
}

TEST(JoyBallEvent, Dx)
{
  SDL_JoyBallEvent sdl;
  sdl.xrel = 723;

  const cen::joy_ball_event event{sdl};
  EXPECT_EQ(sdl.xrel, event.dx());
}

TEST(JoyBallEvent, Dy)
{
  SDL_JoyBallEvent sdl;
  sdl.yrel = 5933;

  const cen::joy_ball_event event{sdl};
  EXPECT_EQ(sdl.yrel, event.dy());
}
