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

TEST(Compiler, OnMSVC)
{
#ifdef _MSC_VER
  EXPECT_TRUE(cen::on_msvc());
  EXPECT_FALSE(cen::on_clang());
  EXPECT_FALSE(cen::on_gcc());
  EXPECT_FALSE(cen::on_emscripten());
  EXPECT_FALSE(cen::on_intel_cpp());
#else
  EXPECT_FALSE(cen::on_msvc());
#endif
}

TEST(Compiler, OnClang)
{
#ifdef __clang__
  EXPECT_TRUE(cen::on_clang());
  EXPECT_FALSE(cen::on_msvc());
  EXPECT_FALSE(cen::on_gcc());
  EXPECT_FALSE(cen::on_emscripten());
  EXPECT_FALSE(cen::on_intel_cpp());
#else
  EXPECT_FALSE(cen::on_clang());
#endif
}

TEST(Compiler, OnGCC)
{
#ifdef __GNUC__
  EXPECT_TRUE(cen::on_gcc());
  EXPECT_FALSE(cen::on_clang());
  EXPECT_FALSE(cen::on_msvc());
  EXPECT_FALSE(cen::on_emscripten());
  EXPECT_FALSE(cen::on_intel_cpp());
#else
  EXPECT_FALSE(cen::on_gcc());
#endif
}
