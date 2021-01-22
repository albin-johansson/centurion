#include "sensor.hpp"

#include <gtest/gtest.h>

TEST(Sensor, PointerConstructor)
{
  EXPECT_THROW(cen::sensor{nullptr}, cen::exception);
  EXPECT_NO_THROW(cen::sensor_handle{nullptr});
}

TEST(Sensor, IndexConstructor)
{
  EXPECT_THROW(cen::sensor{0}, cen::sdl_error);
}

TEST(Sensor, StandardGravity)
{
  EXPECT_EQ(SDL_STANDARD_GRAVITY, cen::standard_gravity());
}

TEST(Sensor, SensorTypeEnum)
{
  EXPECT_EQ(SDL_SENSOR_INVALID, cen::sensor_type::invalid);
  EXPECT_EQ(SDL_SENSOR_UNKNOWN, cen::sensor_type::unknown);
  EXPECT_EQ(SDL_SENSOR_ACCEL, cen::sensor_type::accelerometer);
  EXPECT_EQ(SDL_SENSOR_GYRO, cen::sensor_type::gyroscope);

  EXPECT_EQ(cen::sensor_type::invalid, SDL_SENSOR_INVALID);
  EXPECT_EQ(cen::sensor_type::unknown, SDL_SENSOR_UNKNOWN);
  EXPECT_EQ(cen::sensor_type::accelerometer, SDL_SENSOR_ACCEL);
  EXPECT_EQ(cen::sensor_type::gyroscope, SDL_SENSOR_GYRO);

  EXPECT_NE(SDL_SENSOR_INVALID, cen::sensor_type::accelerometer);
  EXPECT_NE(cen::sensor_type::gyroscope, SDL_SENSOR_ACCEL);
}
