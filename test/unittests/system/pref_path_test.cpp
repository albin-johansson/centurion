#include "filesystem/pref_path.hpp"

#include <gtest/gtest.h>

TEST(GetPrefPath, NoExceptions)
{
  EXPECT_NO_THROW(cen::get_pref_path("centurion", "tests"));  // NOLINT
}
