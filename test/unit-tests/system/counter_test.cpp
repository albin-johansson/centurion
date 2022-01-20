#include <gtest/gtest.h>

#include "centurion/system.hpp"

TEST(Counter, Frequency)
{
  ASSERT_EQ(SDL_GetPerformanceFrequency(), cen::frequency());
}

TEST(Counter, Now)
{
  ASSERT_NO_THROW(cen::now());
}

TEST(Counter, NowInSeconds)
{
  ASSERT_NO_THROW(cen::now_in_seconds());
}

TEST(Counter, Ticks)
{
  using namespace cen::literals::time_literals;
  ASSERT_GT(cen::ticks(), 0_ms);
}
