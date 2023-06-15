/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include "centurion/events/misc_events.hpp"

TEST(DollarGestureEvent, Defaults)
{
  cen::dollar_gesture_event event;
  ASSERT_EQ(cen::event_type::dollar_gesture, event.type());
}

TEST(DollarGestureEvent, SetTouchId)
{
  cen::dollar_gesture_event event;

  constexpr auto id = 4;
  event.set_touch_id(id);

  ASSERT_EQ(id, event.touch_id());
}

TEST(DollarGestureEvent, SetGestureId)
{
  cen::dollar_gesture_event event;

  constexpr auto id = 81;
  event.set_gesture_id(id);

  ASSERT_EQ(id, event.gesture_id());
}

TEST(DollarGestureEvent, SetFingers)
{
  cen::dollar_gesture_event event;

  constexpr Uint32 fingers = 2;
  event.set_fingers(fingers);

  ASSERT_EQ(fingers, event.finger_count());
}

TEST(DollarGestureEvent, SetError)
{
  cen::dollar_gesture_event event;

  constexpr auto error = 5.1f;
  event.set_error(error);

  ASSERT_EQ(error, event.error());
}

TEST(DollarGestureEvent, SetX)
{
  cen::dollar_gesture_event event;

  constexpr auto x = 24.8f;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(DollarGestureEvent, SetY)
{
  cen::dollar_gesture_event event;

  constexpr auto y = -12.9f;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(DollarGestureEvent, TouchId)
{
  SDL_DollarGestureEvent sdl;
  sdl.touchId = 9;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.touchId, event.touch_id());
}

TEST(DollarGestureEvent, GestureId)
{
  SDL_DollarGestureEvent sdl;
  sdl.gestureId = 1;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.gestureId, event.gesture_id());
}

TEST(DollarGestureEvent, FingerCount)
{
  SDL_DollarGestureEvent sdl;
  sdl.numFingers = 3;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.numFingers, event.finger_count());
}

TEST(DollarGestureEvent, Error)
{
  SDL_DollarGestureEvent sdl;
  sdl.error = 7.4f;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.error, event.error());
}

TEST(DollarGestureEvent, X)
{
  SDL_DollarGestureEvent sdl;
  sdl.x = 56.8f;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.x, event.x());
}

TEST(DollarGestureEvent, Y)
{
  SDL_DollarGestureEvent sdl;
  sdl.y = 92.3f;

  const cen::dollar_gesture_event event {sdl};
  ASSERT_EQ(sdl.y, event.y());
}

TEST(DollarGestureEvent, AsSDLEvent)
{
  const cen::dollar_gesture_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.dgesture.type, static_cast<Uint32>(event.type()));
  ASSERT_EQ(sdl.dgesture.timestamp, event.timestamp().count());
}
