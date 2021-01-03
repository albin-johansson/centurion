#include "detail/max.hpp"

#include <gtest/gtest.h>

TEST(Max, Correctness)
{
  EXPECT_EQ(0, cen::detail::max(0, -1));
  EXPECT_EQ(1, cen::detail::max(0, 1));

  EXPECT_EQ(1, cen::detail::max(1, -1));
  EXPECT_EQ(1, cen::detail::max(-1, 1));

  EXPECT_EQ(2, cen::detail::max(1, 2));
  EXPECT_EQ(2, cen::detail::max(2, 1));

  EXPECT_EQ(-1, cen::detail::max(-1, -2));
  EXPECT_EQ(-1, cen::detail::max(-2, -1));
}
