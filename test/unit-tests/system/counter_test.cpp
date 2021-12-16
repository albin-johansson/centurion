#include <gtest/gtest.h>

#include "system.hpp"

TEST(Counter, GetFrequency)
{
  ASSERT_EQ(SDL_GetPerformanceFrequency(), cen::GetFrequency());
}

TEST(Counter, Now)
{
  ASSERT_NO_THROW(cen::Now());
}

TEST(Counter, NowInSeconds)
{
  ASSERT_NO_THROW(cen::NowInSeconds());
}

TEST(Counter, GetTicks)
{
  using namespace cen::literals::time_literals;
  ASSERT_GT(cen::GetTicks(), 0_ms);
}
