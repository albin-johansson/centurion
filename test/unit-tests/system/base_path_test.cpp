#include "filesystem/base_path.hpp"

#include <gtest/gtest.h>

TEST(BasePath, NoExceptions)
{
  ASSERT_NO_THROW(cen::base_path());  // NOLINT
}
