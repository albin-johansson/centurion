#include "input/sensor.hpp"

#include <gtest/gtest.h>

TEST(Sensor, PointerConstructor)
{
  ASSERT_THROW(cen::sensor{nullptr}, cen::cen_error);
  ASSERT_NO_THROW(cen::sensor_handle{nullptr});
}

TEST(Sensor, IndexConstructor)
{
  ASSERT_THROW(cen::sensor{0}, cen::sdl_error);
}

TEST(Sensor, StandardGravity)
{
  ASSERT_EQ(SDL_STANDARD_GRAVITY, cen::standard_gravity());
}

TEST(Sensor, SensorTypeEnum)
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
