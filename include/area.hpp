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
 * @file area.hpp
 *
 * @brief Provides a simple area struct.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_AREA_HEADER
#define CENTURION_AREA_HEADER

#include <ostream>
#include <type_traits>

#include "centurion_api.hpp"
#include "detail/utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @struct basic_area
 *
 * @ingroup geometry
 *
 * @brief Simply represents an area with a width and height.
 *
 * @tparam T the type of the components of the area. Must
 * be either an integral or floating-point type. Can't be `bool`.
 *
 * @since 4.0.0
 *
 * @see `iarea`
 * @see `farea`
 * @see `darea`
 *
 * @var basic_area::width
 * The width of the area. Defaults to 0.
 * @var basic_area::height
 * The height of the area. Defaults to 0.
 *
 * @headerfile area.hpp
 */
template <typename T>
struct basic_area
{
  T width{0};
  T height{0};

  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
  static_assert(!std::is_same_v<T, bool>);
};

/**
 * @typedef iarea
 *
 * @ingroup geometry
 *
 * @brief An alias for `int` areas.
 *
 * @since 4.1.0
 */
using iarea = basic_area<int>;

/**
 * @typedef farea
 *
 * @ingroup geometry
 *
 * @brief An alias for `float` areas.
 *
 * @since 4.1.0
 */
using farea = basic_area<float>;

/**
 * @typedef darea
 *
 * @ingroup geometry
 *
 * @brief An alias for `double` areas.
 *
 * @since 4.1.0
 */
using darea = basic_area<double>;

/**
 * @brief Indicates whether or not two areas are considered to be equal.
 *
 * @ingroup geometry
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 *
 * @return `true` if the areas are equal; `false` otherwise.
 *
 * @since 4.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_area<T>& lhs,
                                        const basic_area<T>& rhs) noexcept
    -> bool
{
  return (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

/**
 * @brief Indicates whether or not two areas aren't considered to be equal.
 *
 * @ingroup geometry
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 *
 * @return `true` if the areas aren't equal; `false` otherwise.
 *
 * @since 4.1.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_area<T>& lhs,
                                        const basic_area<T>& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Returns a textual representation of an area.
 *
 * @ingroup geometry
 *
 * @tparam T the type of the area components.
 *
 * @param area the area that will be converted.
 *
 * @return a string that represents the area.
 *
 * @since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_area<T>& area) -> std::string
{
  const auto width = std::to_string(area.width);
  const auto height = std::to_string(area.height);
  return "[area | width: " + width + ", height: " + height + "]";
}

/**
 * @brief Prints a textual representation of an area using a stream.
 *
 * @ingroup geometry
 *
 * @tparam T the type of the area components.
 *
 * @param stream the stream that will be used.
 * @param area the are that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_area<T>& area)
    -> std::ostream&
{
  stream << to_string(area);
  return stream;
}

}  // namespace cen

#endif  // CENTURION_AREA_HEADER