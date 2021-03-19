#include "filesystem/preferred_path.hpp"

#include <gtest/gtest.h>

TEST(GetPrefPath, NoExceptions)
{
  using namespace std::string_literals;
  EXPECT_NO_THROW(cen::preferred_path("centurion"s, "tests"s));
}
