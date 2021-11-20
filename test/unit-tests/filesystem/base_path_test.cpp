#include <gtest/gtest.h>

#include "filesystem/paths.hpp"

TEST(BasePath, NoExceptions)
{
  ASSERT_NO_THROW(cen::base_path());  // NOLINT
}
