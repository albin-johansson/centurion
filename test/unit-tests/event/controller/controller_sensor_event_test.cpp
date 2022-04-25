#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/event.hpp"

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
