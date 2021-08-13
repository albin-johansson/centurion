#include "input/sensor_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(SensorType, Values)
{
  ASSERT_EQ(SDL_SENSOR_INVALID, cen::sensor_type::invalid);
  ASSERT_EQ(SDL_SENSOR_UNKNOWN, cen::sensor_type::unknown);
  ASSERT_EQ(SDL_SENSOR_ACCEL, cen::sensor_type::accelerometer);
  ASSERT_EQ(SDL_SENSOR_GYRO, cen::sensor_type::gyroscope);

  ASSERT_EQ(cen::sensor_type::invalid, SDL_SENSOR_INVALID);
  ASSERT_EQ(cen::sensor_type::unknown, SDL_SENSOR_UNKNOWN);
  ASSERT_EQ(cen::sensor_type::accelerometer, SDL_SENSOR_ACCEL);
  ASSERT_EQ(cen::sensor_type::gyroscope, SDL_SENSOR_GYRO);

  ASSERT_NE(SDL_SENSOR_INVALID, cen::sensor_type::accelerometer);
  ASSERT_NE(cen::sensor_type::gyroscope, SDL_SENSOR_ACCEL);
}

TEST(SensorType, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::sensor_type>(4)), cen::cen_error);

  ASSERT_EQ("invalid", cen::to_string(cen::sensor_type::invalid));
  ASSERT_EQ("unknown", cen::to_string(cen::sensor_type::unknown));
  ASSERT_EQ("accelerometer", cen::to_string(cen::sensor_type::accelerometer));
  ASSERT_EQ("gyroscope", cen::to_string(cen::sensor_type::gyroscope));

  std::clog << "Sensor type example: " << cen::sensor_type::accelerometer << '\n';
}
