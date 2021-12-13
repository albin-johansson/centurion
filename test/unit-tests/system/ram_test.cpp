#include <gtest/gtest.h>

#include "system.hpp"

TEST(RAM, GetMemoryMB)
{
  ASSERT_EQ(SDL_GetSystemRAM(), cen::GetMemoryMB());
}

TEST(RAM, GetMemoryGB)
{
  ASSERT_EQ(SDL_GetSystemRAM() / 1'000, cen::GetMemoryGB());
}
