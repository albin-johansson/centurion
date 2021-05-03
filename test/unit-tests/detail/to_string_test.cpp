#include "detail/to_string.hpp"

#include <gtest/gtest.h>

#include <cstdint>  // int32_t, int64_t, uint32_t, uint64_t
#include <limits>   // numeric_limits
#include <string>   // to_string

TEST(ToString, ToStringFloat)
{
  constexpr auto min = std::numeric_limits<float>::min();
  constexpr auto max = std::numeric_limits<float>::max();
  ASSERT_TRUE(cen::detail::to_string(min).has_value());
  ASSERT_TRUE(cen::detail::to_string(max).has_value());
}

TEST(ToString, ToStringDouble)
{
  constexpr auto min = std::numeric_limits<double>::min();
  constexpr auto max = std::numeric_limits<double>::max();
  ASSERT_TRUE(cen::detail::to_string<32>(min).has_value());
  ASSERT_TRUE(cen::detail::to_string<32>(max).has_value());
}

TEST(ToString, ToStringInt32)
{
  constexpr auto min = std::numeric_limits<int32_t>::min();
  constexpr auto max = std::numeric_limits<int32_t>::max();
  ASSERT_EQ(cen::detail::to_string(min), std::to_string(min));
  ASSERT_EQ(cen::detail::to_string(max), std::to_string(max));
}

TEST(ToString, ToStringUnsigned32)
{
  constexpr auto min = std::numeric_limits<uint32_t>::min();
  constexpr auto max = std::numeric_limits<uint32_t>::max();
  ASSERT_EQ(cen::detail::to_string(min), std::to_string(min));
  ASSERT_EQ(cen::detail::to_string(max), std::to_string(max));
}

TEST(ToString, ToStringInt64)
{
  constexpr auto min = std::numeric_limits<int64_t>::min();
  constexpr auto max = std::numeric_limits<int64_t>::max();
  ASSERT_EQ(cen::detail::to_string<32>(min), std::to_string(min));
  ASSERT_EQ(cen::detail::to_string<32>(max), std::to_string(max));
}

TEST(ToString, ToStringUnsigned64)
{
  constexpr auto min = std::numeric_limits<uint64_t>::min();
  constexpr auto max = std::numeric_limits<uint64_t>::max();
  ASSERT_EQ(cen::detail::to_string<32>(min), std::to_string(min));
  ASSERT_EQ(cen::detail::to_string<32>(max), std::to_string(max));
}