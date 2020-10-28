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
 * \defgroup misc Miscellaneous
 *
 * \brief Provides miscellaneous components used throughout the library.
 */

#ifndef CENTURION_CENTURION_UTILS_HEADER
#define CENTURION_CENTURION_UTILS_HEADER

#include <SDL.h>

#include <array>        // array
#include <cstring>      // strcmp
#include <sstream>      // ostringstream
#include <string>       // string
#include <type_traits>  // is_enum_v, enable_if_t, true_type, false_type
#include <utility>      // pair

#include "centurion_api.hpp"
#include "exception.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \brief Casts a value to a value of another type.
 *
 * \ingroup misc
 *
 * \details This is the default implementation, which simply attempts to use
 * `static_cast`. The idea is that this function will be specialized for
 * various Centurion and SDL types. This is useful because it isn't always
 * possible to implement conversion operators as members.
 *
 * \tparam To the type of the value that will be converted.
 * \tparam From the type that the value will be casted to.
 *
 * \param from the value that will be converted.
 *
 * \return the result of casting the supplied value to the specified type.
 *
 * \since 5.0.0
 */
template <typename To, typename From>
[[nodiscard]] constexpr auto cast(const From& from) noexcept -> To
{
  return static_cast<To>(from);
}

/// \cond FALSE

/**
 * \namespace cen::detail
 *
 * \brief The main namespace used for implementation details of the library.
 *
 * \warning Do not use anything that resides in this namespace, the contents
 * may change at any time without warning.
 */
namespace detail {

/**
 * \brief Returns the corresponding `SDL_bool` value for the supplied boolean
 * value.
 *
 * \param b the boolean value that will be converted.
 *
 * \return `SDL_TRUE` for `true`; `SDL_FALSE` for `false`.
 *
 * \since 3.0.0
 */
[[nodiscard]] constexpr auto convert_bool(bool b) noexcept -> SDL_bool
{
  return b ? SDL_TRUE : SDL_FALSE;
}

/**
 * \brief Returns a string that represents the memory address of the supplied
 * pointer.
 *
 * \details The empty string is returned if the supplied pointer is null.
 *
 * \tparam T the type of the pointer.
 * \param ptr the pointer that will be converted.
 *
 * \return a string that represents the memory address of the supplied
 * pointer.
 *
 * \since 3.0.0
 */
template <typename T>
[[nodiscard]] auto address_of(T* ptr) -> std::string
{
  if (ptr) {
    std::ostringstream address;
    address << static_cast<const void*>(ptr);
    return address.str();
  } else {
    return "";
  }
}

/**
 * \brief Indicates whether or not two C-style strings are equal.
 *
 * \param lhs the left-hand side string, can safely be null.
 * \param rhs the right-hand side string, can safely be null.
 *
 * \return `true` if the strings are equal; `false` otherwise.
 *
 * \since 4.1.0
 */
[[nodiscard]] inline auto equal(czstring lhs, czstring rhs) noexcept -> bool
{
  if (lhs && rhs) {
    return std::strcmp(lhs, rhs) == 0;
  } else {
    return false;
  }
}

template <typename T>
[[nodiscard]] constexpr auto at_least(T value,
                                      T least) noexcept(noexcept(value < least))
    -> T
{
  return (value < least) ? least : value;
}

template <typename T>
using is_owner = std::enable_if_t<std::is_same_v<T, std::true_type>, bool>;

template <typename T>
using is_handle = std::enable_if_t<std::is_same_v<T, std::false_type>, bool>;

template <typename T>
[[nodiscard]] constexpr auto is_owning() noexcept -> bool
{
  return std::is_same_v<T, std::true_type>;
}

}  // namespace detail

/// \endcond

}  // namespace cen

#endif  // CENTURION_CENTURION_UTILS_HEADER