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
  ASSERT_NO_THROW(cen::NowInSeconds<double>());
}

TEST(Counter, GetTicks)
{
  using namespace cen::literals::legacy;
  ASSERT_GT(cen::GetTicks(), 0_ms);
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST(Counter, GetTicks64)
{
  using namespace cen::literals;
  ASSERT_GT(cen::GetTicks64(), 0_ms);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
