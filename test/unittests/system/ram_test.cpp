#include "ram.hpp"

#include <gtest/gtest.h>

TEST(RAM, AmountMB)
{
  EXPECT_EQ(SDL_GetSystemRAM(), cen::ram::amount_mb());
}

TEST(RAM, AmountGB)
{
  EXPECT_EQ(SDL_GetSystemRAM() / 1'000, cen::ram::amount_gb());
}
