/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_COMMON_TRAITS_HPP_
#define CENTURION_COMMON_TRAITS_HPP_

#include <type_traits>  // enable_if_t, is_pointer_v, is_convertible_v, is_enum_v, is_same_v, is_integral_v, is_floating_point_v

#include "../features.hpp"

#if CENTURION_HAS_FEATURE_CONCEPTS

#include <concepts>  // default_initializable, invocable

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

namespace cen {

template <typename T>
using enable_for_pointer_t = std::enable_if_t<std::is_pointer_v<T>, int>;

/// Enables a template if T is convertible to any of the specified types.
template <typename T, typename... Args>
using enable_for_convertible_t =
    std::enable_if_t<(std::is_convertible_v<T, Args> || ...), int>;

template <typename T>
using enable_for_enum_t = std::enable_if_t<std::is_enum_v<T>, int>;

template <typename T>
inline constexpr bool is_number =
    !std::is_same_v<T, bool> && (std::is_integral_v<T> || std::is_floating_point_v<T>);

#if CENTURION_HAS_FEATURE_CONCEPTS

template <typename T, typename... Args>
concept is_stateless_callable = std::default_initializable<T> && std::invocable<T, Args...>;

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

}  // namespace cen

#endif  // CENTURION_COMMON_TRAITS_HPP_
