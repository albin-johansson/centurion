#include <gtest/gtest.h>

#include "filesystem.hpp"

TEST(PreferredPath, NoExceptions)
{
  using namespace std::string_literals;
  ASSERT_NO_THROW(cen::GetPreferredPath("centurion"s, "tests"s));
}
