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

// using u64 = numeric_type<Uint64, struct u64_t>;
//
// using u32 =
//    numeric_type<Uint32, struct u32_t,
//    nt::ImplicitlyConvertibleTo<u64>::templ>;
//
// using u16 = numeric_type<Uint16,
//                         struct u16_t,
//                         nt::ImplicitlyConvertibleTo<u64>::templ,
//                         nt::ImplicitlyConvertibleTo<u32>::templ>;
//
// using u8 = numeric_type<Uint8,
//                        struct u8_t,
//                        nt::ImplicitlyConvertibleTo<u64>::templ,
//                        nt::ImplicitlyConvertibleTo<u32>::templ,
//                        nt::ImplicitlyConvertibleTo<u16>::templ>;
//
// using i64 = numeric_type<Sint64, struct i64_t>;
//
// using i32 =
//    numeric_type<Sint32, struct i32_t,
//    nt::ImplicitlyConvertibleTo<i64>::templ>;
//
// using i16 = numeric_type<Sint16,
//                         struct i16_t,
//                         nt::ImplicitlyConvertibleTo<i64>::templ,
//                         nt::ImplicitlyConvertibleTo<i32>::templ>;
//
// using i8 = numeric_type<Sint8,
//                        struct i8_t,
//                        nt::ImplicitlyConvertibleTo<i64>::templ,
//                        nt::ImplicitlyConvertibleTo<i32>::templ,
//                        nt::ImplicitlyConvertibleTo<i16>::templ>;

// using namespace std::chrono_literals;

// using x_i = x<int>;
// using x_f = x<float>;
//
// using y_i = y<int>;
// using y_f = y<float>;
//
// using width_i = width<int>;
// using width_f = width<float>;
//
// using height_i = height<int>;
// using height_f = height<float>;

// namespace literals {

// using int_t = unsigned long long int;
//
//[[nodiscard]] inline constexpr auto operator"" _xi(int_t i) noexcept -> x_i
//{
//  return static_cast<x_i>(i);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _yi(int_t i) noexcept -> y_i
//{
//  return static_cast<y_i>(i);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _wi(int_t i) noexcept ->
// width_i
//{
//  return static_cast<width_i>(i);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _hi(int_t i) noexcept ->
// height_i
//{
//  return static_cast<height_i>(i);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _xf(long double f) noexcept
//    -> x_f
//{
//  return static_cast<x_f>(f);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _yf(long double f) noexcept
//    -> y_f
//{
//  return static_cast<y_f>(f);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _wf(long double f) noexcept
//    -> width_f
//{
//  return static_cast<width_f>(f);
//}
//
//[[nodiscard]] inline constexpr auto operator"" _hf(long double f) noexcept
//    -> height_f
//{
//  return static_cast<height_f>(f);
//}

//}  // namespace literals
}  // namespace centurion

#endif  // CENTURION_TYPES_HEADER