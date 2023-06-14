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

#include "centurion/events/misc_events.hpp"

TEST(SensorEvent, Defaults)
{
  const cen::sensor_event event;
  ASSERT_EQ(cen::event_type::sensor_update, event.type());
  ASSERT_EQ(0, event.which());
}

TEST(SensorEvent, SetWhich)
{
  cen::sensor_event event;

  const auto id = 42;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(SensorEvent, SetData)
{
  cen::sensor_event event;

  const std::array values = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
  event.set_data(values);

  ASSERT_EQ(1.0f, event.data().at(0));
  ASSERT_EQ(2.0f, event.data().at(1));
  ASSERT_EQ(3.0f, event.data().at(2));
  ASSERT_EQ(4.0f, event.data().at(3));
  ASSERT_EQ(5.0f, event.data().at(4));
  ASSERT_EQ(6.0f, event.data().at(5));
}

TEST(SensorEvent, AsSDLEvent)
{
  const cen::sensor_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.sensor.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.sensor.which, event.which());
  ASSERT_EQ(sdl.sensor.timestamp, event.timestamp().count());
}
