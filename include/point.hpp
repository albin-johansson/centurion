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
 * @file point.hpp
 *
 * @brief Provides simple 2D point representations.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_POINT_HEADER
#define CENTURION_POINT_HEADER

#include <SDL.h>

#include <cmath>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "centurion_utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class ipoint_traits final {
 public:
  using point_type = SDL_Point;
  using value_type = int;
};

class fpoint_traits final {
 public:
  using point_type = SDL_FPoint;
  using value_type = float;
};

}  // namespace detail

/// @endcond

/**
 * @class basic_point
 *
 * @ingroup geometry
 *
 * @brief Represents a two-dimensional point.
 *
 * @details This class is designed as a wrapper for `SDL_Point` and
 * `SDL_FPoint`. The representation is specified by the traits type parameter.
 *
 * @note The type parameter is not the type of the coordinates.
 *
 * @tparam Traits the type of the "traits" class, which should provide the
 * member types `point_type` and `value_type`.
 *
 * @since 5.0.0
 *
 * @see `ipoint`
 * @see `fpoint`
 *
 * @headerfile point.hpp
 */
template <typename Traits>
class basic_point final {
 public:
  /**
   * @typedef point_type
   *
   * @brief The SDL point type, i.e. `SDL_Point` or `SDL_FPoint`.
   *
   * @since 5.0.0
   */
  using point_type = typename Traits::point_type;

  /**
   * @typedef value_type
   *
   * @brief The type of the point coordinates, i.e. `int` or `float`.
   *
   * @since 5.0.0
   */
  using value_type = typename Traits::value_type;

  /**
   * @brief Creates a zero-initialized point.
   *
   * @since 5.0.0
   */
  constexpr basic_point() noexcept = default;

  /**
   * @brief Creates a point with the specified coordinates.
   *
   * @param x the x-coordinate that will be used.
   * @param y the y-coordinate that will be used.
   *
   * @since 5.0.0
   */
  constexpr basic_point(value_type x, value_type y) noexcept
  {
    m_point.x = x;
    m_point.y = y;
  };

  /**
   * @brief Sets the x-coordinate of the point.
   *
   * @param x the new x-coordinate.
   *
   * @since 5.0.0
   */
  constexpr void set_x(value_type x) noexcept { m_point.x = x; }

  /**
   * @brief Sets the y-coordinate of the point.
   *
   * @param y the new y-coordinate.
   *
   * @since 5.0.0
   */
  constexpr void set_y(value_type y) noexcept { m_point.y = y; }

  /**
   * @brief Returns the x-coordinate of the point.
   *
   * @return the x-coordinate.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type
  {
    return m_point.x;
  }

  /**
   * @brief Returns the y-coordinate of the point.
   *
   * @return the y-coordinate.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type
  {
    return m_point.y;
  }

  /**
   * @brief Returns the internal point representation.
   *
   * @return a reference to the internal representation.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto get() noexcept -> point_type& { return m_point; }

  /**
   * @copydoc get
   */
  [[nodiscard]] constexpr auto get() const noexcept -> const point_type&
  {
    return m_point;
  }

  /**
   * @brief Converts to the internal representation.
   *
   * @return a copy of the internal point.
   *
   * @see `centurion::cast`
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator point_type() const noexcept
  {
    return m_point;
  }

  /**
   * @brief Returns a pointer to the internal point.
   *
   * @note You shouldn't store the returned pointer. However, this conversion
   * is safe since `reinterpret_cast` isn't used.
   *
   * @return a pointer to the internal point instance.
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator point_type*() noexcept { return &m_point; }

  /**
   * @brief Returns a pointer to the internal point.
   *
   * @note You shouldn't store the returned pointer. However, this conversion
   * is safe since `reinterpret_cast` isn't used.
   *
   * @return a pointer to the internal point instance.
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator const point_type*() const noexcept
  {
    return &m_point;
  }

 private:
  point_type m_point{0, 0};
};

/**
 * @typedef ipoint
 *
 * @ingroup geometry
 *
 * @brief Alias for an `int`-based point.
 *
 * @details This type corresponds to `SDL_Point`.
 *
 * @since 5.0.0
 */
using ipoint = basic_point<detail::ipoint_traits>;

/**
 * @typedef fpoint
 *
 * @ingroup geometry
 *
 * @brief Alias for a `float`-based point.
 *
 * @details This type corresponds to `SDL_FPoint`.
 *
 * @since 5.0.0
 */
using fpoint = basic_point<detail::fpoint_traits>;

static_assert(std::is_nothrow_default_constructible_v<ipoint>);
static_assert(std::is_nothrow_destructible_v<ipoint>);
static_assert(std::is_nothrow_copy_constructible_v<ipoint>);
static_assert(std::is_nothrow_copy_assignable_v<ipoint>);
static_assert(std::is_nothrow_move_constructible_v<ipoint>);
static_assert(std::is_nothrow_move_assignable_v<ipoint>);

static_assert(std::is_nothrow_default_constructible_v<fpoint>);
static_assert(std::is_nothrow_destructible_v<fpoint>);
static_assert(std::is_nothrow_copy_constructible_v<fpoint>);
static_assert(std::is_nothrow_copy_assignable_v<fpoint>);
static_assert(std::is_nothrow_move_constructible_v<fpoint>);
static_assert(std::is_nothrow_move_assignable_v<fpoint>);

/**
 * @brief Creates a point with the specified coordinates.
 *
 * @ingroup geometry
 *
 * @details This function could be useful in generic code if you want to create
 * points and you only know the type of the coordinates. This function can
 * only be used with `int` or `float` as the requested coordinate type.
 *
 * @tparam T the type of the coordinates of the point, i.e. `int` or `float`.
 * @tparam Args the type of the arguments that will be forwarded.
 *
 * @param args the arguments that will be forwarded to the point constructor.
 *
 * @return a point based on the specified type.
 *
 * @since 5.0.0
 */
template <typename T,
          typename... Args,
          typename = std::enable_if_t<std::is_same_v<T, int> ||
                                      std::is_same_v<T, float>>>
[[nodiscard]] constexpr auto make_point(Args&&... args) noexcept
{
  if constexpr (std::is_same_v<T, int>) {
    return ipoint{std::forward<Args>(args)...};
  } else {
    return fpoint{std::forward<Args>(args)...};
  }
}

/**
 * @brief Converts an `fpoint` instance to the corresponding `ipoint`.
 *
 * @ingroup geometry
 *
 * @details This function casts the coordinates of the supplied point to
 * `int`, and uses the obtained values to create an `ipoint` instance.
 *
 * @param from the point that will be converted.
 *
 * @return an `ipoint` instance that corresponds to the supplied `fpoint`.
 *
 * @since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const fpoint& from) noexcept -> ipoint
{
  const auto x = static_cast<int>(from.x());
  const auto y = static_cast<int>(from.y());
  return ipoint{x, y};
}

/**
 * @brief Converts an `ipoint` instance to the corresponding `fpoint`.
 *
 * @details This function casts the coordinates of the supplied point to
 * `float`, and uses the obtained values to create an `fpoint` instance.
 *
 * @ingroup geometry
 *
 * @param from the point that will be converted.
 *
 * @return an `fpoint` instance that corresponds to the supplied `ipoint`.
 *
 * @since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const ipoint& from) noexcept -> fpoint
{
  const auto x = static_cast<float>(from.x());
  const auto y = static_cast<float>(from.y());
  return fpoint{x, y};
}

/**
 * @brief Converts an `SDL_FPoint` instance to the corresponding `SDL_Point`.
 *
 * @details This function casts the coordinates of the supplied point to
 * `int`, and uses the obtained values to create an `SDL_Point` instance.
 *
 * @ingroup geometry
 *
 * @param from the point that will be converted.
 *
 * @return an `SDL_Point` instance that corresponds to the supplied
 * `SDL_FPoint`.
 *
 * @since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const SDL_FPoint& from) noexcept -> SDL_Point
{
  const auto x = static_cast<int>(from.x);
  const auto y = static_cast<int>(from.y);
  return SDL_Point{x, y};
}

/**
 * @brief Converts an `SDL_Point` instance to the corresponding `SDL_FPoint`.
 *
 * @details This function casts the coordinates of the supplied point to
 * `float`, and uses the obtained values to create an `SDL_FPoint` instance.
 *
 * @ingroup geometry
 *
 * @param from the point that will be converted.
 *
 * @return an `SDL_FPoint` instance that corresponds to the supplied
 * `SDL_Point`.
 *
 * @since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const SDL_Point& from) noexcept -> SDL_FPoint
{
  const auto x = static_cast<float>(from.x);
  const auto y = static_cast<float>(from.y);
  return SDL_FPoint{x, y};
}

/**
 * @brief Returns the distance between two points.
 *
 * @ingroup geometry
 *
 * @tparam Traits the traits used by the points.
 *
 * @param from the first point.
 * @param to the second point.
 *
 * @return the distance between the two points.
 *
 * @since 5.0.0
 */
template <typename Traits>
[[nodiscard]] inline auto distance(const basic_point<Traits>& from,
                                   const basic_point<Traits>& to) noexcept ->
    typename Traits::value_type
{
  if constexpr (std::is_same_v<typename Traits::value_type, int>) {
    const auto xDiff = std::abs(from.x() - to.x());
    const auto yDiff = std::abs(from.y() - to.y());
    const auto dist = std::sqrt(xDiff + yDiff);
    return static_cast<int>(std::round(dist));
  } else {
    return std::sqrt(std::abs(from.x() - to.x()) + std::abs(from.y() - to.y()));
  }
}

[[nodiscard]] inline constexpr auto operator+(const fpoint& lhs,
                                              const fpoint& rhs) noexcept
    -> fpoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] inline constexpr auto operator-(const fpoint& lhs,
                                              const fpoint& rhs) noexcept
    -> fpoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] inline constexpr auto operator+(const ipoint& lhs,
                                              const ipoint& rhs) noexcept
    -> ipoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] inline constexpr auto operator-(const ipoint& lhs,
                                              const ipoint& rhs) noexcept
    -> ipoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] inline constexpr auto operator==(const ipoint& lhs,
                                               const ipoint& rhs) noexcept
    -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] inline constexpr auto operator==(const fpoint& lhs,
                                               const fpoint& rhs) noexcept
    -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] inline constexpr auto operator!=(const ipoint& lhs,
                                               const ipoint& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] inline constexpr auto operator!=(const fpoint& lhs,
                                               const fpoint& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] inline auto to_string(const ipoint& point) -> std::string
{
  using namespace std::string_literals;

  const auto xStr = std::to_string(point.x());
  const auto yStr = std::to_string(point.y());

  return "[i_point | X: "s + xStr + ", Y: "s + yStr + "]"s;
}

[[nodiscard]] inline auto to_string(const fpoint& point) -> std::string
{
  using namespace std::string_literals;

  const auto xStr = std::to_string(point.x());
  const auto yStr = std::to_string(point.y());

  return "[f_point | X: "s + xStr + ", Y: "s + yStr + "]"s;
}

inline auto operator<<(std::ostream& stream, const ipoint& point)
    -> std::ostream&
{
  stream << to_string(point);
  return stream;
}

inline auto operator<<(std::ostream& stream, const fpoint& point)
    -> std::ostream&
{
  stream << to_string(point);
  return stream;
}

}  // namespace centurion

#endif  // CENTURION_POINT_HEADER