#include "system/counter.hpp"

#include <gtest/gtest.h>

TEST(Counter, Frequency)
{
  ASSERT_EQ(SDL_GetPerformanceFrequency(), cen::counter::frequency());
}

TEST(Counter, Now)
{
  ASSERT_NO_THROW(cen::counter::now());
}

TEST(Counter, NowInSeconds)
{
  ASSERT_NO_THROW(cen::counter::now_in_seconds<double>());
}

TEST(Counter, Ticks)
{
  using namespace cen::literals::legacy;
  ASSERT_GT(cen::counter::ticks(), 0_ms);
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST(Counter, Ticks64)
{
  using namespace cen::literals;
  ASSERT_GT(cen::counter::ticks64(), 0_ms);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
