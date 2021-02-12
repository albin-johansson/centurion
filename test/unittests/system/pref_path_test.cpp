#include "pref_path.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <type_traits>

#include "log.hpp"

static_assert(std::is_nothrow_move_constructible_v<cen::pref_path>);
static_assert(std::is_nothrow_move_assignable_v<cen::pref_path>);

static_assert(!std::is_copy_constructible_v<cen::pref_path>);
static_assert(!std::is_copy_assignable_v<cen::pref_path>);

TEST(GetPrefPath, NoExceptions)
{
  EXPECT_NO_THROW(cen::get_pref_path("centurion", "tests"));  // NOLINT
}

TEST(PrefPath, Constructor)
{
  EXPECT_NO_THROW(cen::pref_path("centurion", "tests"));
}

TEST(PrefPath, BoolConversion)
{
  const cen::pref_path pref_path{"centurion", "tests"};
  EXPECT_TRUE(pref_path);
}

TEST(PrefPath, Get)
{
  const cen::pref_path pref_path{"centurion", "tests"};
  EXPECT_TRUE(pref_path.get());
}

TEST(PrefPath, ToString)
{
  const cen::pref_path path{"centurion", "tests"};
  cen::log::put(cen::to_string(path));
}

TEST(PrefPath, StreamOperator)
{
  const cen::pref_path path{"centurion", "tests"};
  std::cout << "COUT: " << path << '\n';
}
