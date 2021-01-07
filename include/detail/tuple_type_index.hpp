/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#ifndef CENTURION_DETAIL_TUPLE_TYPE_INDEX_HEADER
#define CENTURION_DETAIL_TUPLE_TYPE_INDEX_HEADER

#include <cstddef>      // size_t
#include <tuple>        // tuple
#include <type_traits>  // is_same_v
#include <utility>      // index_sequence, index_sequence_for

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

/// \cond FALSE
namespace cen::detail {

template <typename Target, typename Tuple>
class tuple_type_index;

template <typename Target, typename... T>
class tuple_type_index<Target, std::tuple<T...>>
{
  template <std::size_t... index>
  static constexpr int find(std::index_sequence<index...>)
  {
    return -1 + ((std::is_same_v<Target, T> ? index + 1 : 0) + ...);
  }

 public:
  inline static constexpr auto value = find(std::index_sequence_for<T...>{});
};

template <typename Target, typename... T>
inline constexpr int tuple_type_index_v = tuple_type_index<Target, T...>::value;

}  // namespace cen::detail
/// \endcond

#endif  // CENTURION_DETAIL_TUPLE_TYPE_INDEX_HEADER
