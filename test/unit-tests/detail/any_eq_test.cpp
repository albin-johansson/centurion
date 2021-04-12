#include "detail/any_eq.hpp"

#include <gtest/gtest.h>

static_assert(!cen::detail::any_eq(1));

static_assert(cen::detail::any_eq(1, 1));
static_assert(cen::detail::any_eq(1, 1, 1));

static_assert(!cen::detail::any_eq(1, 2));
static_assert(!cen::detail::any_eq(1, 2, 3));

static_assert(cen::detail::any_eq(1, 2, 3, 1));

TEST(AnyEq, Correctness)
{
  EXPECT_FALSE(cen::detail::any_eq(1));

  EXPECT_TRUE(cen::detail::any_eq(1, 1));
  EXPECT_TRUE(cen::detail::any_eq(1, 1, 1));

  EXPECT_FALSE(cen::detail::any_eq(1, 2));
  EXPECT_FALSE(cen::detail::any_eq(1, 2, 3));

  EXPECT_TRUE(cen::detail::any_eq(1, 2, 3, 1));
}
