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
 * @file types.hpp
 *
 * @brief Provides various type aliases.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_TYPES_HEADER
#define CENTURION_TYPES_HEADER

#include <SDL_stdinc.h>

#include <array>        // array
#include <chrono>       // duration
#include <cstddef>      // byte
#include <optional>     // optional
#include <type_traits>  // enable_if, is_pointer

#include "centurion_api.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {
namespace detail {

/**
 * @brief Used to enable a template if a type is a floating-point type, such as
 * float and double.
 *
 * @since 4.0.0
 */
template <typename T>
using if_floating_t = std::enable_if_t<std::is_floating_point_v<T>>;

/**
 * @brief Used to enable a template if two types are the same.
 *
 * @since 4.0.0
 */
template <typename T, typename U>
using if_same_t = typename std::enable_if_t<std::is_same_v<T, U>>;

}  // namespace detail

/// @addtogroup misc
/// @{

/**
 * @typedef owner
 *
 * @brief Tag used to denote ownership of raw pointers directly in code.
 *
 * @details If a function takes an `owner<T*>` as a parameter, then the
 * function will claim ownership of that pointer. Subsequently, if a function
 * returns an `owner<T*>`, then ownership is transferred to the caller.
 */
template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using owner = T;

/**
 * @typedef not_null
 *
 * @brief Tag used to indicate that a pointer cannot be null.
 *
 * @note This alias is equivalent to `T`, it is a no-op.
 *
 * @since 5.0.0
 */
template <typename T>
using not_null = T;

/**
 * @typedef czstring
 *
 * @brief Alias for a const C-style null-terminated string.
 */
using czstring = const char*;

/**
 * @typedef zstring
 *
 * @brief Alias for a C-style null-terminated string.
 */
using zstring = char*;

/**
 * @typedef nn_czstring
 *
 * @brief Alias for a C-style null-terminated string that cannot be null.
 *
 * @since 5.0.0
 */
using nn_czstring = not_null<czstring>;

using font_id = std::size_t;

/**
 * @typedef buffer
 *
 * @brief Alias for an array of `std::byte` instances, meant to be used with
 * `pmr` containers.
 *
 * @since 5.0.0
 */
template <std::size_t size>
using buffer = std::array<std::byte, size>;

/**
 * @typedef u64
 *
 * @brief Alias for a 64-bit unsigned integer.
 */
using u64 = Uint64;

/**
 * @typedef u32
 *
 * @brief Alias for a 32-bit unsigned integer.
 */
using u32 = Uint32;

/**
 * @typedef u16
 *
 * @brief Alias for a 16-bit unsigned integer.
 */
using u16 = Uint16;

/**
 * @typedef u8
 *
 * @brief Alias for an 8-bit unsigned integer.
 */
using u8 = Uint8;

/**
 * @typedef i64
 *
 * @brief Alias for a 64-bit signed integer.
 */
using i64 = Sint64;

/**
 * @typedef i32
 *
 * @brief Alias for a 32-bit signed integer.
 */
using i32 = Sint32;

/**
 * @typedef i16
 *
 * @brief Alias for a 16-bit signed integer.
 */
using i16 = Sint16;

/**
 * @typedef i8
 *
 * @brief Alias for an 8-bit signed integer.
 */
using i8 = Sint8;

/**
 * @typedef unicode
 *
 * @brief The representation of Unicode glyphs.
 *
 * @since 5.0.0
 */
using unicode = u16;

/**
 * @typedef seconds
 *
 * @brief Templated alias for durations in seconds.
 */
template <typename T>
using seconds = std::chrono::duration<T>;

/**
 * @typedef milliseconds
 *
 * @brief Templated alias for durations in milliseconds.
 */
template <typename T>
using milliseconds = std::chrono::duration<T, std::milli>;

/**
 * @typedef microseconds
 *
 * @brief Templated alias for durations in microseconds.
 */
template <typename T>
using microseconds = std::chrono::duration<T, std::micro>;

/**
 * @typedef nanoseconds
 *
 * @brief Templated alias for durations in nanoseconds.
 */
template <typename T>
using nanoseconds = std::chrono::duration<T, std::nano>;

/**
 * @typedef minutes
 *
 * @brief Templated alias for durations in minutes.
 */
template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

/**
 * @namespace literals
 *
 * @brief Contains suffix operators.
 *
 * @since 5.0.0
 */
namespace literals {

constexpr auto operator"" _ns(unsigned long long int value) noexcept
    -> nanoseconds<u32>
{
  return nanoseconds<u32>{value};
}

constexpr auto operator"" _us(unsigned long long int value) noexcept
    -> microseconds<u32>
{
  return microseconds<u32>{value};
}

constexpr auto operator"" _ms(unsigned long long int value) noexcept
    -> milliseconds<u32>
{
  return milliseconds<u32>{value};
}

constexpr auto operator"" _s(unsigned long long int value) noexcept
    -> seconds<u32>
{
  return seconds<u32>{value};
}

}  // namespace literals

/// @}

}  // namespace cen

#endif  // CENTURION_TYPES_HEADER