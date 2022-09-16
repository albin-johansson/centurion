/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_DETAIL_STDLIB_HPP_
#define CENTURION_DETAIL_STDLIB_HPP_

#include <cassert>       // assert
#include <charconv>      // from_chars
#include <cmath>         // lerp
#include <cstring>       // strcmp, strlen
#include <optional>      // optional, nullopt
#include <sstream>       // stringstream
#include <string>        // string
#include <string_view>   // string_view
#include <system_error>  // errc
#include <type_traits>   // is_integral_v

#include "../common.hpp"
#include "../features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen::detail {

/// Clamps a value in the range [min, max]
template <typename T>
[[nodiscard]] constexpr auto clamp(const T& value,
                                   const T& min,
                                   const T& max) noexcept(noexcept(value < min)) -> T
{
  assert(min <= max);
  if (value < min) {
    return min;
  }
  else if (max < value) {
    return max;
  }
  else {
    return value;
  }
}

template <typename T>
[[nodiscard]] constexpr auto(min)(const T& a, const T& b) noexcept(noexcept(a < b)) -> T
{
  return (a < b) ? a : b;
}

template <typename T>
[[nodiscard]] constexpr auto(max)(const T& a, const T& b) noexcept(noexcept(a < b)) -> T
{
  /* Purposefully use less-than operator, since it's more commonly overloaded */
  return (a < b) ? b : a;
}

[[nodiscard]] constexpr auto lerp(const float a, const float b, const float bias) noexcept
    -> float
{
#if CENTURION_HAS_FEATURE_LERP
  return std::lerp(a, b, bias);
#else
  return (a * (1.0f - bias)) + (b * bias);
#endif  // CENTURION_HAS_FEATURE_LERP
}

template <typename T = int>
[[nodiscard]] auto stoi(const std::string_view str, const int base = 10) noexcept(on_msvc)
    -> maybe<T>
{
  /* We don't check if the compiler provides <charconv> here because all major compilers we
     support provide the integral overloads of from_chars */

  T value{};
  const auto* begin = str.data();
  const auto* end = begin + str.size();
  const auto [ptr, err] = std::from_chars(begin, end, value, base);
  if (ptr == end && err == std::errc{}) {
    return value;
  }
  else {
    return nothing;
  }
}

[[nodiscard]] inline auto cmp(const char* a, const char* b) noexcept -> bool
{
  if (a && b) {
    return std::strcmp(a, b) == 0;
  }
  else {
    return false;
  }
}

/// Returns a string that represents the address of the supplied pointer
[[nodiscard]] inline auto address_of(const void* ptr) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return ptr ? std::format("{}", ptr) : std::string{};
#else
  if (ptr) {
    std::stringstream stream;

    if constexpr (on_msvc) {
      stream << "0x";  // Only MSVC seems to omit this, add it for consistency
    }

    stream << ptr;
    return stream.str();
  }
  else {
    return std::string{};
  }
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

}  // namespace cen::detail

#endif  // CENTURION_DETAIL_STDLIB_HPP_
