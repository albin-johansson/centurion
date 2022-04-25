#include <gtest/gtest.h>

#include "centurion/detail/stdlib.hpp"

TEST(Min, Correctness)
{
  ASSERT_EQ(-1, cen::detail::min(0, -1));
  ASSERT_EQ(0, cen::detail::min(0, 1));

  ASSERT_EQ(-1, cen::detail::min(1, -1));
  ASSERT_EQ(-1, cen::detail::min(-1, 1));

  ASSERT_EQ(1, cen::detail::min(1, 2));
  ASSERT_EQ(1, cen::detail::min(2, 1));

  ASSERT_EQ(-2, cen::detail::min(-1, -2));
  ASSERT_EQ(-2, cen::detail::min(-2, -1));
}
