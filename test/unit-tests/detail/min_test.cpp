#include "detail/min.hpp"

#include <gtest/gtest.h>

TEST(Min, Correctness)
{
  EXPECT_EQ(-1, cen::detail::min(0, -1));
  EXPECT_EQ(0, cen::detail::min(0, 1));

  EXPECT_EQ(-1, cen::detail::min(1, -1));
  EXPECT_EQ(-1, cen::detail::min(-1, 1));

  EXPECT_EQ(1, cen::detail::min(1, 2));
  EXPECT_EQ(1, cen::detail::min(2, 1));

  EXPECT_EQ(-2, cen::detail::min(-1, -2));
  EXPECT_EQ(-2, cen::detail::min(-2, -1));
}
