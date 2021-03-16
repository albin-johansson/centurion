#include "compiler.hpp"

#include <gtest/gtest.h>

TEST(Compiler, IsDebugBuild)
{
#ifdef NDEBUG
  EXPECT_FALSE(cen::is_debug_build());
#else
  EXPECT_TRUE(cen::is_debug_build());
#endif
}

TEST(Compiler, IsReleaseBuild)
{
#ifdef NDEBUG
  EXPECT_TRUE(cen::is_release_build());
#else
  EXPECT_FALSE(cen::is_release_build());
#endif
}
