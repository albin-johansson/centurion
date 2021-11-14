#include <gtest/gtest.h>

#include "detail/stdlib.hpp"

TEST(StringCmp, StringCmp)
{
  ASSERT_NO_THROW(cen::detail::cmp(nullptr, ""));
  ASSERT_NO_THROW(cen::detail::cmp("", nullptr));
  ASSERT_NO_THROW(cen::detail::cmp(nullptr, nullptr));

  ASSERT_FALSE(cen::detail::cmp(nullptr, nullptr));
  ASSERT_FALSE(cen::detail::cmp(nullptr, ""));
  ASSERT_FALSE(cen::detail::cmp("", nullptr));

  ASSERT_TRUE(cen::detail::cmp("", ""));

  ASSERT_FALSE(cen::detail::cmp("abc", "ABC"));
  ASSERT_FALSE(cen::detail::cmp("ABC", "abc"));

  ASSERT_FALSE(cen::detail::cmp("abc", "abcd"));
  ASSERT_FALSE(cen::detail::cmp("abcd", "abc"));

  ASSERT_TRUE(cen::detail::cmp("foo", "foo"));
}
