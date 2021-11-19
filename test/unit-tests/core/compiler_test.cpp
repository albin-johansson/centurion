#include "compiler/compiler.hpp"

#include <gtest/gtest.h>

TEST(Compiler, IsDebugBuild)
{
#ifdef NDEBUG
  ASSERT_FALSE(cen::is_debug_build());
#else
  ASSERT_TRUE(cen::is_debug_build());
#endif // NDEBUG
}

TEST(Compiler, IsReleaseBuild)
{
#ifdef NDEBUG
  ASSERT_TRUE(cen::is_release_build());
#else
  ASSERT_FALSE(cen::is_release_build());
#endif // NDEBUG
}

TEST(Compiler, OnMSVC)
{
#ifdef _MSC_VER
  ASSERT_TRUE(cen::on_msvc());
#else
  ASSERT_FALSE(cen::on_msvc());
#endif // _MSC_VER
}

TEST(Compiler, OnClang)
{
#ifdef __clang__
  ASSERT_TRUE(cen::on_clang());
#else
  ASSERT_FALSE(cen::on_clang());
#endif // __clang__
}

TEST(Compiler, OnGCC)
{
#ifdef __GNUC__
  ASSERT_TRUE(cen::on_gcc());
#else
  ASSERT_FALSE(cen::on_gcc());
#endif // __GNUC__
}
