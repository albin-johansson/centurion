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
  ASSERT_FALSE(cen::detail::any_eq(1));

  ASSERT_TRUE(cen::detail::any_eq(1, 1));
  ASSERT_TRUE(cen::detail::any_eq(1, 1, 1));

  ASSERT_FALSE(cen::detail::any_eq(1, 2));
  ASSERT_FALSE(cen::detail::any_eq(1, 2, 3));

  ASSERT_TRUE(cen::detail::any_eq(1, 2, 3, 1));
}
