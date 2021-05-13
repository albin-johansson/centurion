#include "detail/czstring_eq.hpp"

#include <gtest/gtest.h>

using cen::detail::czstring_eq;

TEST(CZStringEq, Correctness)
{
  ASSERT_NO_THROW(czstring_eq(nullptr, ""));
  ASSERT_NO_THROW(czstring_eq("", nullptr));
  ASSERT_NO_THROW(czstring_eq(nullptr, nullptr));

  ASSERT_FALSE(czstring_eq(nullptr, nullptr));
  ASSERT_FALSE(czstring_eq(nullptr, ""));
  ASSERT_FALSE(czstring_eq("", nullptr));

  ASSERT_TRUE(czstring_eq("", ""));

  ASSERT_FALSE(czstring_eq("abc", "ABC"));
  ASSERT_FALSE(czstring_eq("ABC", "abc"));

  ASSERT_FALSE(czstring_eq("abc", "abcd"));
  ASSERT_FALSE(czstring_eq("abcd", "abc"));

  ASSERT_TRUE(czstring_eq("foo", "foo"));
}
