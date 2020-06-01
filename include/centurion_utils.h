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

#ifndef CENTURION_CENTURION_UTILS_HEADER
#define CENTURION_CENTURION_UTILS_HEADER

#include <SDL.h>

#include <lib/gsl-lite.hpp>
#include <lib/optional.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>

#include "centurion_api.h"

namespace centurion {
namespace detail {

/**
 * Creates and returns a unique pointer. This method is used since C++11
 * doesn't provide std::make_unique.
 *
 * @tparam T the type of the object that will be created.
 * @tparam Args the type of the arguments that will be passed to an appropriate
 * constructor.
 * @param args the arguments that will be passed to an appropriate constructor.
 * @return a unique pointer.
 * @since 4.0.0
 */
template <typename T, typename... Args>
CENTURION_NODISCARD std::unique_ptr<T> make_unique(Args&&... args)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<T>(std::forward<Args>(args)...);
#else
  return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
#endif
}

/**
 * Returns the corresponding SDL_bool value for the supplied boolean value.
 *
 * @param b the boolean value that will be converted.
 * @return the corresponding SDL_bool value for the supplied boolean value.
 * @since 3.0.0
 */
CENTURION_NODISCARD
constexpr SDL_bool convert_bool(bool b) noexcept
{
  return b ? SDL_TRUE : SDL_FALSE;
}

/**
 * Returns a string that represents the memory address of the supplied
 * pointer. The empty string is returned if the supplied pointer is null.
 *
 * @tparam T the type of the pointer.
 * @param ptr the pointer that will be converted.
 * @return a string that represents the memory address of the supplied
 * pointer.
 * @since 3.0.0
 */
template <typename T>
CENTURION_NODISCARD std::string address_of(T* ptr)
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
 * Returns the closest legal value that is inside the specified inclusive
 * range based on the supplied value.
 *
 * @tparam T the type of the range.
 * @param range the inclusive range, the format is (min, max).
 * @param value the value that will be checked.
 * @return the closest legal value that is inside the specified inclusive
 * range.
 * @since 4.0.0
 */
template <typename T>
CENTURION_NODISCARD T clamp_inclusive(std::pair<T, T> range, T value) noexcept
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
 * Used to enable a template if a condition is true.
 *
 * @since 4.0.0
 */
template <bool condition>
using type_if = typename std::enable_if<condition>::type;

/**
 * Used to enable a template if a type is a floating-point type, such as
 * float and double.
 *
 * @since 4.0.0
 */
template <typename T>
using type_if_floating = type_if<std::is_floating_point<T>::value>;

/**
 * Used to enable a template if a type is an integral type, such as
 * int and long, etc.
 *
 * @since 4.0.0
 */
template <typename T>
using type_if_integral = type_if<std::is_integral<T>::value>;

/**
 * Used to enable a template if two types are the same.
 *
 * @since 4.0.0
 */
template <typename T, typename U>
using type_if_same = typename std::enable_if<std::is_same<T, U>::value>::type;

}  // namespace detail

/**
 * A type alias for gsl::owner. This is used to denote ownership of raw
 * pointers.
 *
 * @since 4.0.0
 */
template <typename T>
using Owner = gsl::owner<T>;

/**
 * A type alias for tl::optional.
 *
 * @since 4.0.0
 */
template <typename T>
using Optional = tl::optional<T>;

/**
 * A type alias for unique pointers.
 *
 * @since 4.0.0
 */
template <typename T, typename Deleter = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T, Deleter>;

/**
 * A type alias for shared pointers.
 *
 * @since 4.0.0
 */
template <typename T>
using SharedPtr = std::shared_ptr<T>;

/**
 * A type alias for weak pointers.
 *
 * @since 4.0.0
 */
template <typename T>
using WeakPtr = std::weak_ptr<T>;

/**
 * A type alias for a const null-terminated C-style string.
 *
 * @since 4.0.0
 */
using CZString = gsl::czstring;

/**
 * A type alias for a null-terminated C-style string.
 *
 * @since 4.0.0
 */
using ZString = gsl::zstring;

/**
 * A constant that represents an empty Optional.
 *
 * @since 4.0.0
 */
constexpr tl::nullopt_t nothing = tl::nullopt;

}  // namespace centurion

#endif  // CENTURION_CENTURION_UTILS_HEADER