#include <gtest/gtest.h>

#include "centurion/detail/stdlib.hpp"

TEST(Max, Correctness)
{
  ASSERT_EQ(0, cen::detail::max(0, -1));
  ASSERT_EQ(1, cen::detail::max(0, 1));

  ASSERT_EQ(1, cen::detail::max(1, -1));
  ASSERT_EQ(1, cen::detail::max(-1, 1));

  ASSERT_EQ(2, cen::detail::max(1, 2));
  ASSERT_EQ(2, cen::detail::max(2, 1));

  ASSERT_EQ(-1, cen::detail::max(-1, -2));
  ASSERT_EQ(-1, cen::detail::max(-2, -1));
}
