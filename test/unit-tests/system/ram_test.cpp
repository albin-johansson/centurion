#include <gtest/gtest.h>

#include "system/memory.hpp"

TEST(RAM, MemoryMB)
{
  ASSERT_EQ(SDL_GetSystemRAM(), cen::memory_mb());
}

TEST(RAM, MemoryGB)
{
  ASSERT_EQ(SDL_GetSystemRAM() / 1'000, cen::memory_gb());
}
