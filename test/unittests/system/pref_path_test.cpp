#include "pref_path.hpp"

#include <gtest/gtest.h>

#include <iostream>

#include "log.hpp"

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
