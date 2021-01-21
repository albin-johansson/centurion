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

#ifndef CENTURION_VECTOR3_HEADER
#define CENTURION_VECTOR3_HEADER

#include <ostream>  // ostream
#include <string>   // string

#include "centurion_cfg.hpp"
#include "detail/to_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * \struct vector3
 *
 * \brief A simple representation of a 3-dimensional vector.
 *
 * \tparam T the representation type, e.g. `float` or `double`.
 *
 * \since 5.2.0
 *
 * \headerfile vector3.hpp
 */
template <typename T>
struct vector3 final
{
  using value_type = T;  ///< The type of the vector components.

  value_type x{};  ///< The x-coordinate of the vector.
  value_type y{};  ///< The y-coordinate of the vector.
  value_type z{};  ///< The z-coordinate of the vector.

  /**
   * \brief Casts the vector to a vector with another representation type.
   *
   * \tparam U the target vector type.
   *
   * \return the result vector.
   *
   * \since 5.2.0
   */
  template <typename U>
  [[nodiscard]] explicit operator vector3<U>() const noexcept
  {
    using target_value_type = typename vector3<U>::value_type;
    return vector3<U>{static_cast<target_value_type>(x),
                      static_cast<target_value_type>(y),
                      static_cast<target_value_type>(z)};
  }
};

/**
 * \brief Returns a string that represents a vector.
 *
 * \tparam T the representation type used by the vector.
 *
 * \param vector the vector that will be converted to a string.
 *
 * \return a string that represents the supplied vector.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] auto to_string(const vector3<T>& vector) -> std::string
{
  return "[vector3 | x: " + detail::to_string(vector.x).value() +
         ", y: " + detail::to_string(vector.y).value() +
         ", z: " + detail::to_string(vector.z).value() + "]";
}

/**
 * \brief Prints a textual representation of a vector.
 *
 * \tparam T the representation type used by the vector.
 *
 * \param stream the stream that will be used.
 * \param vector the vector that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.2.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const vector3<T>& vector) -> std::ostream&
{
  stream << to_string(vector);
  return stream;
}

/**
 * \brief Indicates whether or not two 3D vectors are equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the vectors are equal; `false` otherwise.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const vector3<T>& lhs,
                                        const vector3<T>& rhs) noexcept -> bool
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

/**
 * \brief Indicates whether or not two 3D vectors aren't equal.
 *
 * \tparam T the representation type used by the vectors.
 *
 * \param lhs the left-hand side vector.
 * \param rhs the right-hand side vector.
 *
 * \return `true` if the vectors aren't equal; `false` otherwise.
 *
 * \since 5.2.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const vector3<T>& lhs,
                                        const vector3<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

}  // namespace cen

#endif  // CENTURION_VECTOR3_HEADER
