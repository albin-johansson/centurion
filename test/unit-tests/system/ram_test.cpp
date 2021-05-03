#include "system/ram.hpp"

#include <gtest/gtest.h>

TEST(RAM, AmountMB)
{
  ASSERT_EQ(SDL_GetSystemRAM(), cen::ram::amount_mb());
}

TEST(RAM, AmountGB)
{
  ASSERT_EQ(SDL_GetSystemRAM() / 1'000, cen::ram::amount_gb());
}
