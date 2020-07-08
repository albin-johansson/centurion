/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file centurion_utils.hpp
 * @brief Provides utilities used in the implementation of the library.
 *
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_CENTURION_UTILS_HEADER
#define CENTURION_CENTURION_UTILS_HEADER

#include <SDL.h>

#include <cstring>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

/**
 * @namespace centurion::detail
 * @brief The main namespace used for implementation details of the library.
 *
 * @warning Do not use anything that resides in this namespace, the contents
 * may change at any time without warning.
 */
namespace centurion::detail {

/**
 * @brief Returns the corresponding `SDL_bool` value for the supplied boolean
 * value.
 *
 * @param b the boolean value that will be converted.
 *
 * @return `SDL_TRUE` for `true`; `SDL_FALSE` for `false`.
 *
 * @since 3.0.0
 */
[[nodiscard]] constexpr auto convert_bool(bool b) noexcept -> SDL_bool
{
  return b ? SDL_TRUE : SDL_FALSE;
}

/**
 * @brief Returns a string that represents the memory address of the supplied
 * pointer.
 *
 * @details The empty string is returned if the supplied pointer is null.
 *
 * @tparam T the type of the pointer.
 * @param ptr the pointer that will be converted.
 *
 * @return a string that represents the memory address of the supplied
 * pointer.
 *
 * @since 3.0.0
 */
template <typename T>
[[nodiscard]] auto address_of(T* ptr) -> std::string
{
  if (ptr) {
    std::ostringstream address;
    address << static_cast<void const*>(ptr);
    return address.str();
  } else {
    return "";
  }
}

/**
 * @brief Returns the closest legal value that is inside the specified inclusive
 * range based on the supplied value.
 *
 * @tparam T the type of the range.
 *
 * @param range the inclusive range, the format is (min, max).
 * @param value the value that will be checked.
 *
 * @return the closest legal value that is inside the specified inclusive
 * range.
 *
 * @since 4.0.0
 */
template <typename T>
[[nodiscard]] auto clamp_inclusive(std::pair<T, T> range, T value) noexcept -> T
{
  const auto min = range.first;
  const auto max = range.second;

  if (value < min) {
    return min;
  } else if (value > max) {
    return max;
  } else {
    return value;
  }
}

/**
 * @brief Indicates whether or not two C-style strings are equal.
 *
 * @param lhs the left-hand side string, can safely be null.
 * @param rhs the right-hand side string, can safely be null.
 *
 * @return `true` if the strings are equal; `false` otherwise.
 *
 * @since 4.1.0
 */
[[nodiscard]] inline auto equal(czstring lhs, czstring rhs) noexcept -> bool
{
  if (lhs && rhs) {
    return std::strcmp(lhs, rhs) == 0;
  } else {
    return false;
  }
}

}  // namespace centurion::detail

#endif  // CENTURION_CENTURION_UTILS_HEADER