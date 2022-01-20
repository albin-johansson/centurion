#include "sensor.hpp"

#include <gtest/gtest.h>

TEST(Sensor, StandardGravity)
{
  ASSERT_EQ(SDL_STANDARD_GRAVITY, cen::standard_gravity());
}

TEST(Sensor, PointerConstructor)
{
  ASSERT_THROW(cen::sensor{nullptr}, cen::exception);
  ASSERT_NO_THROW(cen::sensor_handle{nullptr});
}

TEST(Sensor, IndexConstructor)
{
  ASSERT_THROW(cen::sensor{0}, cen::sdl_error);
}
