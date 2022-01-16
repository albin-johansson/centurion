#include <gtest/gtest.h>

#include "filesystem.hpp"

TEST(PreferredPath, NoExceptions)
{
  using namespace std::string_literals;
  ASSERT_NO_THROW(cen::preferred_path("centurion"s, "tests"s));
}
