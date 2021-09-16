#include "events/controller_sensor_event.hpp"

#include <gtest/gtest.h>

#include <array>  // array

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

  event.set_which(38);
  ASSERT_EQ(38, event.which());
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

  const std::array<float, 3> values = {0.3f, 0.5f, 0.8f};

  event.set_data(values);
  ASSERT_EQ(0.3f, event.data().at(0));
  ASSERT_EQ(0.5f, event.data().at(1));
  ASSERT_EQ(0.8f, event.data().at(2));
}

TEST(ControllerSensorEvent, AsSdlEvent)
{
  cen::controller_sensor_event event;
  event.set_time(4'895);
  event.set_sensor(cen::sensor_type::gyroscope);
  event.set_which(21);

  const auto sdl = cen::as_sdl_event(event);
  ASSERT_EQ(4'895, sdl.csensor.timestamp);
  ASSERT_EQ(SDL_CONTROLLERSENSORUPDATE, sdl.csensor.type);
  ASSERT_EQ(SDL_SENSOR_GYRO, sdl.csensor.sensor);
  ASSERT_EQ(21, sdl.csensor.which);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
