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

#include <array>  // array

#include "centurion/common/literals.hpp"
#include "centurion/events/controller_events.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(ControllerSensorEvent, Defaults)
{
  const cen::controller_sensor_event event;
  ASSERT_EQ(0, event.which());
  ASSERT_EQ(cen::sensor_type::unknown, event.sensor());
}

TEST(ControllerSensorEvent, SetWhich)
{
  cen::controller_sensor_event event;

  const SDL_JoystickID id = 38;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(ControllerSensorEvent, SetSensor)
{
  cen::controller_sensor_event event;

  event.set_sensor(cen::sensor_type::accelerometer);
  ASSERT_EQ(cen::sensor_type::accelerometer, event.sensor());
}

TEST(ControllerSensorEvent, SetData)
{
  cen::controller_sensor_event event;

  const std::array values = {0.3f, 0.5f, 0.8f};

  event.set_data(values);
  ASSERT_EQ(0.3f, event.data().at(0));
  ASSERT_EQ(0.5f, event.data().at(1));
  ASSERT_EQ(0.8f, event.data().at(2));
}

TEST(ControllerSensorEvent, AsSdlEvent)
{
  using namespace cen::literals::time_literals;

  cen::controller_sensor_event event;
  event.set_timestamp(4'895_ms);
  event.set_sensor(cen::sensor_type::gyroscope);
  event.set_which(21);

  const auto sdl = cen::as_sdl_event(event);
  ASSERT_EQ(4'895u, sdl.csensor.timestamp);
  ASSERT_EQ(SDL_CONTROLLERSENSORUPDATE, static_cast<SDL_EventType>(sdl.csensor.type));
  ASSERT_EQ(SDL_SENSOR_GYRO, static_cast<SDL_SensorType>(sdl.csensor.sensor));
  ASSERT_EQ(21, sdl.csensor.which);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
