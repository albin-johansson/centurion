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
 * @file centurion_types.hpp
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

#include <chrono>
#include <gsl/gsl>
#include <named_type.hpp>
#include <optional>
#include <type_traits>

#include "centurion_api.hpp"

namespace centurion {
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

template <typename T, typename = std::enable_if_t<std::is_pointer_v<T>>>
using owner = T;
using czstring = const char*;
using zstring = char*;

// namespace nt = fluent;

inline constexpr std::nullopt_t nothing = std::nullopt;

// template <typename T>
// using if_numeric_t = typename std::enable_if_t<std::is_integral_v<T> ||
//                                               std::is_floating_point_v<T>>;

// namespace skills {
//
// template <typename T>
// struct Dividable : nt::crtp<T, Dividable> {
//  constexpr auto operator/(const T& other) const -> T
//  {
//    return T(this->underlying().get() / other.get());
//  }
//};
//
//}  // namespace skills

// template <typename T, typename = if_numeric_t<T>>
// using x = nt::NamedType<T,
//                        struct x_t,
//                        nt::Addable,
//                        nt::Subtractable,
//                        nt::Comparable,
//                        nt::FunctionCallable>;
//
// template <typename T, typename = if_numeric_t<T>>
// using y = nt::NamedType<T,
//                        struct y_t,
//                        nt::Addable,
//                        nt::Subtractable,
//                        nt::Comparable,
//                        nt::FunctionCallable>;
//
// template <typename T, typename = if_numeric_t<T>>
// using width = nt::NamedType<T,
//                            struct width_t,
//                            nt::Addable,
//                            nt::Subtractable,
//                            nt::Comparable,
//                            nt::FunctionCallable>;
//
// template <typename T, typename = if_numeric_t<T>>
// using height = nt::NamedType<T,
//                             struct height_t,
//                             nt::Addable,
//                             nt::Subtractable,
//                             nt::Comparable,
//                             nt::FunctionCallable>;

// template <typename T, typename Tag, template <typename> class... Skills>
// using numeric_type = nt::NamedType<T,
//                                   Tag,
//                                   nt::Addable,
//                                   nt::Subtractable,
//                                   nt::Multiplicable,
//                                   skills::Dividable,
//                                   nt::Comparable,
//                                   Skills...>;

using u64 = Uint64;
using u32 = Uint32;
using u16 = Uint16;
using u8 = Uint8;

using i64 = Sint64;
using i32 = Sint32;
using i16 = Sint16;
using i8 = Sint8;

template <typename T>
using seconds = std::chrono::duration<T>;

template <typename T>
using milliseconds = std::chrono::duration<T, std::milli>;

template <typename T>
using microseconds = std::chrono::duration<T, std::micro>;

template <typename T>
using nanoseconds = std::chrono::duration<T, std::nano>;

template <typename T>
using minutes = std::chrono::duration<T, std::ratio<60>>;

}  // namespace centurion

#endif  // CENTURION_TYPES_HEADER