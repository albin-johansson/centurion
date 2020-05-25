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

#ifndef CENTURION_AREA_HEADER
#define CENTURION_AREA_HEADER

#include <type_traits>

#include "centurion_api.h"

namespace centurion {

template <typename T>
struct TArea;

/**
 * A simple struct that represents a width and a height.
 *
 * @tparam T the type of the components of the Area, defaults to float.
 * @since 4.0.0
 */
template <typename T = float>
struct TArea {
  constexpr TArea() noexcept = default;
  constexpr TArea(T width, T height) noexcept : width{width}, height{height} {}
  T width = 0;
  T height = 0;

  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Area type must be either integral or floating-point!");
  static_assert(!std::is_same<T, bool>::value, "Area type cannot be bool!");
  static_assert(std::is_trivial<T>::value, "Area type must be trivial!");
};

/**
 * A type alias for TArea&lt;int&gt;, for backwards compatibility reasons.
 * Use of this type alias is discouraged.
 *
 * @since 4.1.0
 */
using Area = TArea<int>;

/**
 * A type alias for TArea&lt;int&gt;. Prefer usage of this alias over
 * <code>Area</code>, since it might be removed in a future release of
 * Centurion.
 *
 * @since 4.1.0
 */
using IArea = TArea<int>;

/**
 * A type alias for TArea&lt;float&gt;.
 *
 * @since 4.1.0
 */
using FArea = TArea<float>;

/**
 * A type alias for TArea&lt;double&gt;.
 *
 * @since 4.1.0
 */
using DArea = TArea<double>;

/**
 * Indicates whether or not two areas are considered to be equal.
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 * @return true if the areas are equal; false otherwise.
 * @since 4.1.0
 */
template <typename T>
CENTURION_NODISCARD inline constexpr bool operator==(
    const TArea<T>& lhs,
    const TArea<T>& rhs) noexcept
{
  return (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

/**
 * Indicates whether or not two areas aren't considered to be equal.
 *
 * @param lhs the left-hand side area.
 * @param rhs the right-hand side area.
 * @return true if the areas aren't equal; false otherwise.
 * @since 4.1.0
 */
template <typename T>
CENTURION_NODISCARD inline constexpr bool operator!=(
    const TArea<T>& lhs,
    const TArea<T>& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_AREA_HEADER