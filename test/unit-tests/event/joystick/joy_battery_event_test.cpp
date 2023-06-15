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

#if SDL_VERSION_ATLEAST(2, 24, 0)

TEST(JoyBatteryEvent, Defaults)
{
  const cen::joy_battery_event event;
  ASSERT_EQ(cen::event_type::joy_battery_updated, event.type());
}

TEST(JoyBatteryEvent, SetWhich)
{
  cen::joy_battery_event event;

  const SDL_JoystickID id = 42;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyBatteryEvent, SetPowerLevel)
{
  cen::joy_battery_event event;

  const auto level = cen::joystick_power::medium;
  event.set_power_level(level);

  ASSERT_EQ(level, event.power_level());
}

TEST(JoyBatteryEvent, AsSDLEvent)
{
  const cen::joy_battery_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.jbattery.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.jbattery.timestamp, event.timestamp().count());
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
