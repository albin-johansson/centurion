#include <gtest/gtest.h>

#include "detail/stdlib.hpp"

TEST(Clamp, Correctness)
{
  ASSERT_EQ(1, cen::detail::clamp(1, 0, 1));
  ASSERT_EQ(1, cen::detail::clamp(1, 1, 1));
  ASSERT_EQ(1, cen::detail::clamp(1, 0, 2));
  ASSERT_EQ(1, cen::detail::clamp(1, -1, 2));

  ASSERT_EQ(2, cen::detail::clamp(3, 0, 2));
  ASSERT_EQ(0, cen::detail::clamp(-1, 0, 2));

  ASSERT_EQ(-2, cen::detail::clamp(-2, -3, -1));
  ASSERT_EQ(-3, cen::detail::clamp(-4, -3, -1));
  ASSERT_EQ(-1, cen::detail::clamp(0, -3, -1));
}
