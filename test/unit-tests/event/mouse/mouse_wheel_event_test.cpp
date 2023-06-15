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

#include "centurion/events/mouse_events.hpp"

TEST(MouseWheelEvent, Defaults)
{
  const cen::mouse_wheel_event event;
  ASSERT_EQ(cen::event_type::mouse_wheel, event.type());
}

TEST(MouseWheelEvent, SetWindowID)
{
  cen::mouse_wheel_event event;

  const cen::uint32 id = 32;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseWheelEvent, SetWhich)
{
  cen::mouse_wheel_event event;

  const cen::uint32 which = 65;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseWheelEvent, SetX)
{
  cen::mouse_wheel_event event;

  const cen::int32 x = -545;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseWheelEvent, SetY)
{
  cen::mouse_wheel_event event;

  const cen::int32 y = 725;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST(MouseWheelEvent, SetPreciseX)
{
  cen::mouse_wheel_event event;

  const float x = 4.5f;
  event.set_precise_x(x);

  ASSERT_EQ(x, event.precise_x());
}

TEST(MouseWheelEvent, SetPreciseY)
{
  cen::mouse_wheel_event event;

  const float y = -89.3f;
  event.set_precise_y(y);

  ASSERT_EQ(y, event.precise_y());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

TEST(MouseWheelEvent, SetDirection)
{
  cen::mouse_wheel_event event;

  event.set_direction(cen::mouse_wheel_direction::flipped);
  ASSERT_EQ(cen::mouse_wheel_direction::flipped, event.direction());
}

TEST(MouseWheelEvent, AsSDLEvent)
{
  const cen::mouse_wheel_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.wheel.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.wheel.timestamp, event.timestamp().count());
}
