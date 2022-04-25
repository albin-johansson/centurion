#include <gtest/gtest.h>

#include "centurion/detail/stdlib.hpp"

TEST(FromString, IntegerBase10)
{
  ASSERT_FALSE(cen::detail::stoi("foo"));

  ASSERT_EQ(42, cen::detail::stoi("42"));
  ASSERT_EQ(123, cen::detail::stoi("123"));
  ASSERT_EQ(-834, cen::detail::stoi("-834"));
}

TEST(FromString, IntegerBase16)
{
  ASSERT_FALSE(cen::detail::stoi("foo", 16));

  ASSERT_EQ(0xB7, cen::detail::stoi("B7", 16));
  ASSERT_EQ(0x123, cen::detail::stoi("123", 16));
  ASSERT_EQ(0xE9A, cen::detail::stoi("E9A", 16));
}
