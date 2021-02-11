#include "detail/czstring_eq.hpp"

#include <gtest/gtest.h>

using cen::detail::czstring_eq;

TEST(CZStringEq, Correctness)
{
  ASSERT_NO_THROW(czstring_eq(nullptr, ""));
  ASSERT_NO_THROW(czstring_eq("", nullptr));
  ASSERT_NO_THROW(czstring_eq(nullptr, nullptr));

  EXPECT_FALSE(czstring_eq(nullptr, nullptr));
  EXPECT_FALSE(czstring_eq(nullptr, ""));
  EXPECT_FALSE(czstring_eq("", nullptr));

  EXPECT_TRUE(czstring_eq("", ""));

  EXPECT_FALSE(czstring_eq("abc", "ABC"));
  EXPECT_FALSE(czstring_eq("ABC", "abc"));

  EXPECT_FALSE(czstring_eq("abc", "abcd"));
  EXPECT_FALSE(czstring_eq("abcd", "abc"));

  EXPECT_TRUE(czstring_eq("foo", "foo"));
}
