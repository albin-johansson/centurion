#include "detail/to_string.hpp"

#include <array>
#include <catch.hpp>
#include <charconv>
#include <cstdint>  // int32_t, int64_t, uint32_t, uint64_t
#include <limits>   // numeric_limits
#include <string>

TEST_CASE("to_string", "[to_string]")
{
  SECTION("float")
  {
    constexpr auto min = std::numeric_limits<float>::min();
    constexpr auto max = std::numeric_limits<float>::max();
    CHECK(cen::detail::to_string(min).has_value());
    CHECK(cen::detail::to_string(max).has_value());
  }

  SECTION("double")
  {
    constexpr auto min = std::numeric_limits<double>::min();
    constexpr auto max = std::numeric_limits<double>::max();
    CHECK(cen::detail::to_string<32>(min).has_value());
    CHECK(cen::detail::to_string<32>(max).has_value());
  }

  SECTION("32-bit int")
  {
    constexpr auto min = std::numeric_limits<int32_t>::min();
    constexpr auto max = std::numeric_limits<int32_t>::max();
    CHECK(cen::detail::to_string(min) == std::to_string(min));
    CHECK(cen::detail::to_string(max) == std::to_string(max));
  }

  SECTION("32-bit unsigned int")
  {
    constexpr auto min = std::numeric_limits<uint32_t>::min();
    constexpr auto max = std::numeric_limits<uint32_t>::max();
    CHECK(cen::detail::to_string(min) == std::to_string(min));
    CHECK(cen::detail::to_string(max) == std::to_string(max));
  }

  SECTION("64-bit int")
  {
    constexpr auto min = std::numeric_limits<int64_t>::min();
    constexpr auto max = std::numeric_limits<int64_t>::max();
    CHECK(cen::detail::to_string<32>(min) == std::to_string(min));
    CHECK(cen::detail::to_string<32>(max) == std::to_string(max));
  }

  SECTION("64-bit unsigned int")
  {
    constexpr auto min = std::numeric_limits<uint64_t>::min();
    constexpr auto max = std::numeric_limits<uint64_t>::max();
    CHECK(cen::detail::to_string<32>(min) == std::to_string(min));
    CHECK(cen::detail::to_string<32>(max) == std::to_string(max));
  }
}