#include <gtest/gtest.h>

#include "system.hpp"

TEST(RAM, MB)
{
  ASSERT_EQ(SDL_GetSystemRAM(), cen::ram_mb());
}

TEST(RAM, GB)
{
  ASSERT_EQ(SDL_GetSystemRAM() / 1'000, cen::ram_gb());
}
