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

TEST(Counter, Ticks32)
{
  ASSERT_GT(cen::ticks32(), cen::u32ms::zero());
}

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST(Counter, Ticks64)
{
  ASSERT_GT(cen::ticks64(), cen::u64ms::zero());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)
