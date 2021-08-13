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
