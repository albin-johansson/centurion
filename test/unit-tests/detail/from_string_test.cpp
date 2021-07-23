#include "detail/from_string.hpp"

#include <gtest/gtest.h>

TEST(FromString, IntegerBase10)
{
  ASSERT_FALSE(cen::detail::from_string<int>("foo"));

  ASSERT_EQ(42, cen::detail::from_string<int>("42"));
  ASSERT_EQ(123, cen::detail::from_string<int>("123"));
  ASSERT_EQ(-834, cen::detail::from_string<int>("-834"));
}

TEST(FromString, FloatBase10)
{
  ASSERT_FALSE(cen::detail::from_string<float>("foo"));

  ASSERT_FLOAT_EQ(4.2f, cen::detail::from_string<float>("4.2").value());
  ASSERT_FLOAT_EQ(12.3f, cen::detail::from_string<float>("12.3").value());
  ASSERT_FLOAT_EQ(-834.0f, cen::detail::from_string<float>("-834").value());
}

TEST(FromString, Base16)
{
  ASSERT_FALSE(cen::detail::from_string<int>("foo", 16));

  ASSERT_EQ(0xB7, cen::detail::from_string<int>("B7", 16));
  ASSERT_EQ(0x123, cen::detail::from_string<int>("123", 16));
  ASSERT_EQ(0xE9A, cen::detail::from_string<int>("E9A", 16));
}