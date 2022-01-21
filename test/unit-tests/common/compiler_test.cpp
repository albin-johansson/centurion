#include <gtest/gtest.h>

#include "centurion/common.hpp"

TEST(Compiler, IsDebugBuild)
{
#ifdef NDEBUG
  ASSERT_FALSE(cen::is_debug_build);
#else
  ASSERT_TRUE(cen::is_debug_build);
#endif  // NDEBUG
}

TEST(Compiler, IsReleaseBuild)
{
#ifdef NDEBUG
  ASSERT_TRUE(cen::is_release_build);
#else
  ASSERT_FALSE(cen::is_release_build);
#endif  // NDEBUG
}
