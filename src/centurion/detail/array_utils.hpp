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

#ifndef CENTURION_DETAIL_ARRAY_UTILS_HPP_
#define CENTURION_DETAIL_ARRAY_UTILS_HPP_

#include <array>    // array, to_array
#include <cstddef>  // size_t

#include "../common.hpp"
#include "../features.hpp"

namespace cen::detail {

template <typename T, usize Size>
constexpr void assign(const std::array<T, Size>& array, bounded_array_ref<T, Size> out)
{
  usize index = 0;
  for (auto&& value : array) {
    out[index] = value;
    ++index;
  }
}

template <typename T, usize Size>
[[nodiscard]] constexpr auto to_array(bounded_array_ref<const T, Size> data)
    -> std::array<T, Size>
{
#if CENTURION_HAS_FEATURE_TO_ARRAY
  return std::to_array(data);
#else
  std::array<T, Size> array;  // NOLINT

  for (usize i = 0; i < Size; ++i) {
    array[i] = data[i];
  }

  return array;
#endif  // CENTURION_HAS_FEATURE_TO_ARRAY
}

}  // namespace cen::detail

#endif  // CENTURION_DETAIL_ARRAY_UTILS_HPP_
