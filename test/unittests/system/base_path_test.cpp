#include "base_path.hpp"

#include <gtest/gtest.h>

TEST(GetBasePath, NoExceptions)
{
  EXPECT_NO_THROW(cen::get_base_path());  // NOLINT
}
