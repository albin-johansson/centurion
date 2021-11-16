#include "system/ram.hpp"

#include <gtest/gtest.h>

TEST(RAM, MemoryMB)
{
  ASSERT_EQ(SDL_GetSystemRAM(), cen::memory_mb());
}

TEST(RAM, MemoryGB)
{
  ASSERT_EQ(SDL_GetSystemRAM() / 1'000, cen::memory_gb());
}
