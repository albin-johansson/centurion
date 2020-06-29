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

#ifndef CENTURION_POINT_HEADER
#define CENTURION_POINT_HEADER

#include <SDL.h>

#include <cmath>
#include <string>
#include <type_traits>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {

template <typename T>
class Point;

template <typename U>
constexpr bool operator==(const Point<U>& lhs, const Point<U>& rhs) noexcept;

template <typename U>
constexpr bool operator!=(const Point<U>& lhs, const Point<U>& rhs) noexcept;

template <typename U>
constexpr Point<U> operator-(const Point<U>& lhs, const Point<U>& rhs) noexcept;

template <typename U>
constexpr Point<U> operator+(const Point<U>& lhs, const Point<U>& rhs) noexcept;

/**
 * The Point class represents an integer or floating-point based 2D point.
 * There are two pre-defined type aliases pre-defined for this class: IPoint and
 * FPoint.
 *
 * @tparam T the type of the components of the point. Must be either integral
 * or real. Defaults to float.
 * @since 4.0.0
 */
template <typename T = float>
class Point final {
 public:
  /**
   * Creates a point with coordinates (0, 0).
   *
   * @since 4.0.0
   */
  constexpr Point() noexcept = default;

  /**
   * Creates a point with the specified coordinates.
   *
   * @param px the x-coordinate of the point.
   * @param py the y-coordinate of the point.
   * @since 4.0.0
   */
  constexpr Point(T px, T py) noexcept : m_x{px}, m_y{py} {}

  /**
   * Sets the x-coordinate of the point.
   *
   * @param px the new x-coordinate of the point.
   * @since 4.0.0
   */
  constexpr void set_x(T px) noexcept { m_x = px; }

  /**
   * Sets the y-coordinate of the point.
   *
   * @param py the new y-coordinate of the point.
   * @since 4.0.0
   */
  constexpr void set_y(T py) noexcept { m_y = py; }

  /**
   * Sets the values of the x- and y-coordinates of the point.
   *
   * @param px the new x-coordinate of the point.
   * @param py the new y-coordinate of the point.
   * @since 4.0.0
   */
  constexpr void set(T px, T py) noexcept
  {
    m_x = px;
    m_y = py;
  }

  /**
   * Copies the components of the supplied point into this point.
   *
   * @param other the point that will be copied.
   * @since 4.0.0
   */
  constexpr void set(const Point<T>& other) noexcept
  {
    m_x = other.m_x;
    m_y = other.m_y;
  }

  /**
   * Calculates and returns the distance from this point to the supplied
   * point. It doesn't matter in which order the method call is performed
   * (i.e. <code>a.distance_to(b) == b.distance_to(a)</code>)
   *
   * @param other the point to calculate the distance to.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  T distance_to(const Point<T>& other) const noexcept
  {
    return std::sqrt(std::abs(m_x - other.m_x) + std::abs(m_y - other.m_y));
  }

  /**
   * Returns a textual representation of the point.
   *
   * @return a textual representation of the point.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  std::string to_string() const
  {
    return "[Point | X: " + std::to_string(m_x) +
           ", Y: " + std::to_string(m_y) + "]";
  }

  /**
   * Returns the x-coordinate of the point.
   *
   * @return the x-coordinate of the point.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T x() const noexcept { return m_x; }

  /**
   * Returns the y-coordinate of the point.
   *
   * @return the y-coordinate of the point.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T y() const noexcept { return m_y; }

  /**
   * Indicates whether or not the point is considered to be equal to the
   * supplied point. This method is only enabled if the points are
   * floating-point based.
   *
   * @param other the other point to compare this point with.
   * @param epsilon the exclusive limit on the maximum allowed absolute
   * difference between the coordinates of the points.
   * @since 4.0.0
   */
  template <typename U = T, typename X = detail::type_if_floating<U>>
  CENTURION_NODISCARD bool equals(const Point<T>& other,
                                  T epsilon = 0.0001) const noexcept
  {
    return std::abs(m_x - other.m_x) < epsilon &&
           std::abs(m_y - other.m_y) < epsilon;
  }

  /**
   * Returns an SDL_Point instance based on the point.
   *
   * @return an SDL_Point instance based on the point.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr SDL_Point to_sdl_point() const noexcept
  {
    return {static_cast<int>(m_x), static_cast<int>(m_y)};
  }

  /**
   * Returns an SDL_FPoint instance based on the point.
   *
   * @return an SDL_FPoint instance based on the point.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr SDL_FPoint to_sdl_fpoint() const noexcept
  {
    return {static_cast<float>(m_x), static_cast<float>(m_y)};
  }

  /**
   * Creates and returns a point in which the coordinates are the sums
   * obtained by adding the x- and y-coordinates of the supplied points.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   * @return a point in which the coordinates are the sums obtained by adding
   * the x- and y-coordinates of the supplied points.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend constexpr Point<T> operator+
      <T>(const Point<T>& lhs, const Point<T>& rhs) noexcept;

  /**
   * Converts the point to a pointer to an SDL_Point instance. This
   * conversion is only available if the point is based on <code>int</code>.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   * @return an SDL_Point pointer that is produced by reinterpreting the
   * invoked point.
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD explicit operator SDL_Point*() noexcept
  {
    return reinterpret_cast<SDL_Point*>(this);
  }

  /**
   * Converts the point to a pointer to an SDL_Point instance. This
   * conversion is only available if the point is based on <code>int</code>.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   * @return an SDL_Point pointer that is produced by reinterpreting the
   * invoked point.
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD explicit operator const SDL_Point*() const noexcept
  {
    return reinterpret_cast<const SDL_Point*>(this);
  }

  /**
   * Converts the point to a pointer to an SDL_FPoint instance. This
   * conversion is only available if the point is based on <code>float</code>.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   * @return an SDL_FPoint pointer that is produced by reinterpreting the
   * invoked point.
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::type_if_same<U, float>>
  CENTURION_NODISCARD explicit operator SDL_FPoint*() noexcept
  {
    return reinterpret_cast<SDL_FPoint*>(this);
  }

  /**
   * Converts the point to a pointer to an SDL_FPoint instance. This
   * conversion is only available if the point is based on <code>float</code>.
   *
   * @tparam U the type parameter, defaults to the type of the point
   * components.
   * @return an SDL_FPoint pointer that is produced by reinterpreting the
   * invoked point.
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::type_if_same<U, float>>
  CENTURION_NODISCARD explicit operator const SDL_FPoint*() const noexcept
  {
    return reinterpret_cast<const SDL_FPoint*>(this);
  }

  /**
   * Creates and returns a point in which the coordinates are the differences
   * obtained by subtracting the x- and y-coordinates of the supplied points.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   * @return a point in which the coordinates are the differences obtained by
   * subtracting the x- and y-coordinates of the supplied points.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend constexpr Point<T> operator-
      <T>(const Point<T>& lhs, const Point<T>& rhs) noexcept;

  /**
   * Indicates whether or not two points are considered to be equal.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   * @return true if the points are equal; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend constexpr bool operator==
      <T>(const Point<T>& lhs, const Point<T>& rhs) noexcept;

  /**
   * Indicates whether or not two points aren't considered to be equal.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   * @return true if the points aren't equal; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend constexpr bool operator!=
      <T>(const Point<T>& lhs, const Point<T>& rhs) noexcept;

 private:
  T m_x = 0;
  T m_y = 0;

  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Point type must be either integral or floating-point!");
  static_assert(std::is_trivial<T>::value, "Point type must be trivial!");
};

template <typename T>
inline constexpr Point<T> operator+(const Point<T>& lhs,
                                    const Point<T>& rhs) noexcept
{
  return Point<T>{lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y};
}

template <typename T>
inline constexpr Point<T> operator-(const Point<T>& lhs,
                                    const Point<T>& rhs) noexcept
{
  return Point<T>{lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y};
}

template <typename T>
inline constexpr bool operator==(const Point<T>& lhs,
                                 const Point<T>& rhs) noexcept
{
  return lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y;
}

template <typename T>
inline constexpr bool operator!=(const Point<T>& lhs,
                                 const Point<T>& rhs) noexcept
{
  return !(lhs == rhs);
}

static_assert(std::is_nothrow_default_constructible<Point<float>>::value,
              "Point isn't nothrow default constructible!");

static_assert(std::is_nothrow_copy_constructible<Point<float>>::value,
              "Point isn't nothrow copy constructible!");

static_assert(std::is_nothrow_move_constructible<Point<float>>::value,
              "Point isn't nothrow move constructible!");

static_assert(std::is_nothrow_copy_assignable<Point<float>>::value,
              "Point isn't nothrow copy assignable!");

static_assert(std::is_nothrow_move_assignable<Point<float>>::value,
              "Point isn't nothrow move assignable!");

static_assert(sizeof(Point<int>) == sizeof(SDL_Point),
              "Point<int> has invalid size!");

static_assert(sizeof(Point<float>) == sizeof(SDL_FPoint),
              "Point<float> has invalid size!");

/**
 * An alias for Point&lt;int&gt;.
 *
 * @since 4.0.0
 */
using IPoint = Point<int>;

/**
 * An alias for Point&lt;float&gt;.
 *
 * @since 4.0.0
 */
using FPoint = Point<float>;

}  // namespace centurion

#endif  // CENTURION_POINT_HEADER