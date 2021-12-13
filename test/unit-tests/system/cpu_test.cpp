#include <gtest/gtest.h>

#include "system/system.hpp"

TEST(CPU, IsLittleEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_LIL_ENDIAN, cen::IsLittleEndian());
}

TEST(CPU, IsBigEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_BIG_ENDIAN, cen::IsBigEndian());
}
