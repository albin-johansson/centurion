#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/sensor.hpp"

TEST(SensorType, Values)
{
  ASSERT_EQ(SDL_SENSOR_INVALID, to_underlying(cen::sensor_type::invalid));
  ASSERT_EQ(SDL_SENSOR_UNKNOWN, to_underlying(cen::sensor_type::unknown));
  ASSERT_EQ(SDL_SENSOR_ACCEL, to_underlying(cen::sensor_type::accelerometer));
  ASSERT_EQ(SDL_SENSOR_GYRO, to_underlying(cen::sensor_type::gyroscope));
}

TEST(SensorType, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::sensor_type>(4)), cen::exception);

  ASSERT_EQ("invalid", to_string(cen::sensor_type::invalid));
  ASSERT_EQ("unknown", to_string(cen::sensor_type::unknown));
  ASSERT_EQ("accelerometer", to_string(cen::sensor_type::accelerometer));
  ASSERT_EQ("gyroscope", to_string(cen::sensor_type::gyroscope));

  std::cout << "sensor_type::accelerometer == " << cen::sensor_type::accelerometer << '\n';
}
