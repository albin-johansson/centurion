#include "system/counter.hpp"

#include <gtest/gtest.h>

TEST(Counter, HighResFreq)
{
  ASSERT_EQ(SDL_GetPerformanceFrequency(), cen::counter::high_res_freq());
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
  ASSERT_NO_THROW(cen::counter::ticks());
}
