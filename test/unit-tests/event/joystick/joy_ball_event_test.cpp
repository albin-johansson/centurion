#include <gtest/gtest.h>

#include "centurion/joystick_events.hpp"

TEST(JoyBallEvent, Defaults)
{
  const cen::joy_ball_event event;
  ASSERT_EQ(cen::event_type::joy_ball_motion, event.type());
}

TEST(JoyBallEvent, SetWhich)
{
  cen::joy_ball_event event;

  const SDL_JoystickID id = 5;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyBallEvent, SetBall)
{
  cen::joy_ball_event event;

  const cen::uint8 ball = 6;
  event.set_ball(ball);

  ASSERT_EQ(ball, event.ball());
}

TEST(JoyBallEvent, SetDX)
{
  cen::joy_ball_event event;

  const cen::int16 dx = 173;
  event.set_dx(dx);

  ASSERT_EQ(dx, event.dx());
}

TEST(JoyBallEvent, SetDY)
{
  cen::joy_ball_event event;

  const cen::int16 dy = -57;
  event.set_dy(dy);

  ASSERT_EQ(dy, event.dy());
}

TEST(JoyBallEvent, AsSDLEvent)
{
  const cen::joy_ball_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.jball.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.jball.timestamp, event.timestamp().count());
}
