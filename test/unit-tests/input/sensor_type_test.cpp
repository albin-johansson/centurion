#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "input/sensor.hpp"

TEST(SensorType, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::sensor_type::invalid), SDL_SENSOR_INVALID);
  ASSERT_EQ(cen::to_underlying(cen::sensor_type::unknown), SDL_SENSOR_UNKNOWN);
  ASSERT_EQ(cen::to_underlying(cen::sensor_type::accelerometer), SDL_SENSOR_ACCEL);
  ASSERT_EQ(cen::to_underlying(cen::sensor_type::gyroscope), SDL_SENSOR_GYRO);
}

TEST(SensorType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::sensor_type>(4)), cen::Error);

  ASSERT_EQ("invalid", cen::to_string(cen::sensor_type::invalid));
  ASSERT_EQ("unknown", cen::to_string(cen::sensor_type::unknown));
  ASSERT_EQ("accelerometer", cen::to_string(cen::sensor_type::accelerometer));
  ASSERT_EQ("gyroscope", cen::to_string(cen::sensor_type::gyroscope));

  std::clog << "Sensor type example: " << cen::sensor_type::accelerometer << '\n';
}
