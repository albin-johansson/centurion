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

TEST(MultiGestureEvent, Defaults)
{
  const cen::multi_gesture_event event;
  ASSERT_EQ(cen::event_type::multi_gesture, event.type());
}

TEST(MultiGestureEvent, SetTouchId)
{
  cen::multi_gesture_event event;

  event.set_touch_id(3);
  ASSERT_EQ(3, event.touch_id());
}

TEST(MultiGestureEvent, SetDeltaTheta)
{
  cen::multi_gesture_event event;

  event.set_delta_theta(65);
  ASSERT_EQ(65, event.delta_theta());
}

TEST(MultiGestureEvent, SetDeltaDistance)
{
  cen::multi_gesture_event event;

  event.set_delta_distance(-79);
  ASSERT_EQ(-79, event.delta_distance());
}

TEST(MultiGestureEvent, SetCenterX)
{
  cen::multi_gesture_event event;

  event.set_center_x(154);
  ASSERT_EQ(154, event.center_x());
}

TEST(MultiGestureEvent, SetCenterY)
{
  cen::multi_gesture_event event;

  event.set_center_y(867);
  ASSERT_EQ(867, event.center_y());
}

TEST(MultiGestureEvent, SetFingers)
{
  cen::multi_gesture_event event;

  event.set_finger_count(3);
  ASSERT_EQ(3, event.finger_count());
}

TEST(MultiGestureEvent, TouchId)
{
  SDL_MultiGestureEvent sdl;
  sdl.touchId = 54;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.touchId, event.touch_id());
}

TEST(MultiGestureEvent, DeltaTheta)
{
  SDL_MultiGestureEvent sdl;
  sdl.dTheta = 98;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.dTheta, event.delta_theta());
}

TEST(MultiGestureEvent, DeltaDistance)
{
  SDL_MultiGestureEvent sdl;
  sdl.dDist = -87;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.dDist, event.delta_distance());
}

TEST(MultiGestureEvent, CenterX)
{
  SDL_MultiGestureEvent sdl;
  sdl.x = 564;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.x, event.center_x());
}

TEST(MultiGestureEvent, CenterY)
{
  SDL_MultiGestureEvent sdl;
  sdl.y = 913;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.y, event.center_y());
}

TEST(MultiGestureEvent, FingerCount)
{
  SDL_MultiGestureEvent sdl;
  sdl.numFingers = 2;

  const cen::multi_gesture_event event {sdl};
  ASSERT_EQ(sdl.numFingers, event.finger_count());
}

TEST(MultiGestureEvent, AsSDLEvent)
{
  const cen::multi_gesture_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.mgesture.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.mgesture.timestamp, event.timestamp().count());
}
