#include "events/sensor_event.hpp"

#include <gtest/gtest.h>

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
  ASSERT_EQ(sdl.sensor.timestamp, event.time());
}
