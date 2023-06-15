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

#include "centurion/events/joystick_events.hpp"

TEST(JoyAxisEvent, Defaults)
{
  const cen::joy_axis_event event;
  ASSERT_EQ(cen::event_type::joy_axis_motion, event.type());
}

TEST(JoyAxisEvent, SetWhich)
{
  cen::joy_axis_event event;

  const SDL_JoystickID id = 3;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyAxisEvent, SetAxis)
{
  cen::joy_axis_event event;

  const cen::uint8 axis = 42;
  event.set_axis(axis);

  ASSERT_EQ(axis, event.axis());
}

TEST(JoyAxisEvent, SetValue)
{
  cen::joy_axis_event event;

  const cen::int16 value = 4'234;
  event.set_value(value);

  ASSERT_EQ(value, event.value());
}

TEST(JoyAxisEvent, AsSDLEvent)
{
  const cen::joy_axis_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jaxis.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jaxis.timestamp, event.timestamp().count());
}
