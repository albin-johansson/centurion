#include <gtest/gtest.h>

#include <array>  // array

#include "events/controller_events.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(ControllerSensorEvent, Defaults)
{
  const cen::ControllerSensorEvent event;
  ASSERT_EQ(0, event.GetWhich());
  ASSERT_EQ(cen::sensor_type::unknown, event.GetSensor());
}

TEST(ControllerSensorEvent, SetWhich)
{
  cen::ControllerSensorEvent event;

  event.SetWhich(38);
  ASSERT_EQ(38, event.GetWhich());
}

TEST(ControllerSensorEvent, SetSensor)
{
  cen::ControllerSensorEvent event;

  event.SetSensor(cen::sensor_type::accelerometer);
  ASSERT_EQ(cen::sensor_type::accelerometer, event.GetSensor());
}

TEST(ControllerSensorEvent, SetData)
{
  cen::ControllerSensorEvent event;

  const std::array<float, 3> values = {0.3f, 0.5f, 0.8f};

  event.SetData(values);
  ASSERT_EQ(0.3f, event.GetData().at(0));
  ASSERT_EQ(0.5f, event.GetData().at(1));
  ASSERT_EQ(0.8f, event.GetData().at(2));
}

TEST(ControllerSensorEvent, AsSdlEvent)
{
  cen::ControllerSensorEvent event;
  event.SetTimestamp(4'895u);
  event.SetSensor(cen::sensor_type::gyroscope);
  event.SetWhich(21);

  const auto sdl = cen::AsSDLEvent(event);
  ASSERT_EQ(4'895u, sdl.csensor.timestamp);
  ASSERT_EQ(SDL_CONTROLLERSENSORUPDATE, static_cast<SDL_EventType>(sdl.csensor.type));
  ASSERT_EQ(SDL_SENSOR_GYRO, static_cast<SDL_SensorType>(sdl.csensor.sensor));
  ASSERT_EQ(21, sdl.csensor.which);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
