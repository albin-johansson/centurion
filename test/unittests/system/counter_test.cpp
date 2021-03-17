#include "system/counter.hpp"

#include <gtest/gtest.h>

TEST(Counter, HighResFreq)
{
  EXPECT_EQ(SDL_GetPerformanceFrequency(), cen::counter::high_res_freq());
}

TEST(Counter, Now)
{
  EXPECT_NO_THROW(cen::counter::now());
}

TEST(Counter, NowSec)
{
  EXPECT_NO_THROW(cen::counter::now_sec<double>());
}

TEST(Counter, Ticks)
{
  EXPECT_NO_THROW(cen::counter::ticks());
}
