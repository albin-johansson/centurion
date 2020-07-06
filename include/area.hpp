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
 * @brief Provides a simple area struct.
 *
 * @file area.hpp
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_AREA_HEADER
#define CENTURION_AREA_HEADER

#include <type_traits>

#include "centurion_api.hpp"

namespace centurion {

template <typename T>
struct Area;

/**
 * @struct Area
 * @brief Simply represents an area with a width and height.
 *
 * @tparam T the type of the components of the area, defaults to float. Must
 * be either an integral or floating-point type. Can't be `bool`.
 *
 * @since 4.0.0
 *
 * @var area::width
 * The width of the area. Defaults to 0.
 * @var area::height
 * The height of the area. Defaults to 0.
 *
 * @headerfile area.hpp
 */
template <typename T = float>
struct Area {
  T width = 0;
  T height = 0;

  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
  static_assert(!std::is_same_v<T, bool>);
};

/**
 * @typedef area_i
 * @brief An alias for `int` areas.
 *
 * @since 4.1.0
 */
using area_i = Area<int>;

/**
 * @typedef area_f
 * @brief An alias for `float` areas.
 *
 * @since 4.1.0
 */
using area_f = Area<float>;

/**
 * @typedef area_d
 * @brief An alias for `double` areas.
 *
 * @since 4.1.0
 */
using area_d = Area<double>;

/**
 * @brief Indicates whether or not two areas are considered to be equal.
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 *
 * @return `true` if the areas are equal; `false` otherwise.
 *
 * @since 4.1.0
 */
template <typename T>
[[nodiscard]] inline constexpr auto operator==(const Area<T>& lhs,
                                               const Area<T>& rhs) noexcept
    -> bool
{
  return (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

/**
 * @brief Indicates whether or not two areas aren't considered to be equal.
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 *
 * @return `true` if the areas aren't equal; `false` otherwise.
 *
 * @since 4.1.0
 */
template <typename T>
[[nodiscard]] inline constexpr auto operator!=(const Area<T>& lhs,
                                               const Area<T>& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_AREA_HEADER