#include "input/sensor.hpp"

#include <gtest/gtest.h>

TEST(Sensor, PointerConstructor)
{
  ASSERT_THROW(cen::sensor{nullptr}, cen::Error);
  ASSERT_NO_THROW(cen::sensor_handle{nullptr});
}

TEST(Sensor, IndexConstructor)
{
  ASSERT_THROW(cen::sensor{0}, cen::SDLError);
}

TEST(Sensor, StandardGravity)
{
  ASSERT_EQ(SDL_STANDARD_GRAVITY, cen::standard_gravity());
}
