// Copyright (C) 2019-2024 Albin Johansson (MIT License)

#include "centurion/detail/enum.hpp"

#include <cstdint>

#include <gtest/gtest.h>

namespace cen::test {
inline namespace enum_test {

enum class u16 : std::uint16_t
{
  value = 123
};

enum class i64 : std::int64_t
{
  value = 123
};

}  // namespace enum_test

// cen::detail::to_underlying
TEST(Enum, ToUnderlying)
{
  const auto u16_value = detail::to_underlying(u16::value);
  const auto i64_value = detail::to_underlying(i64::value);

  static_assert(std::same_as<decltype(u16_value), const std::uint16_t>);
  static_assert(std::same_as<decltype(i64_value), const std::int64_t>);

  EXPECT_EQ(u16_value, std::uint16_t {123});
  EXPECT_EQ(i64_value, std::int64_t {123});
}

}  // namespace cen::test
