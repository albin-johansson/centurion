#include <gtest/gtest.h>

#include "centurion/memory.hpp"

TEST(SIMDBlock, Usage)
{
  cen::simd_block block{100};
  ASSERT_TRUE(block);
  ASSERT_TRUE(block.data());

  const auto& cblock = block;
  ASSERT_TRUE(cblock);
  ASSERT_TRUE(cblock.data());

#if SDL_VERSION_ATLEAST(2, 0, 14)
  block.reallocate(50);
  ASSERT_TRUE(block);
  ASSERT_TRUE(block.data());
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}
