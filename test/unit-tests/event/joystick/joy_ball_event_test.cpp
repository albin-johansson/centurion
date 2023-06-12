/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include "centurion/events/joystick_events.hpp"

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
