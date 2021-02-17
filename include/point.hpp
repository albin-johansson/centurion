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

#ifndef CENTURION_POINT_HEADER
#define CENTURION_POINT_HEADER

#include <SDL.h>

#include <cmath>        // sqrt, abs, round
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // enable_if_t, conditional_t, is_convertible_v, ...

#include "cast.hpp"
#include "centurion_cfg.hpp"
#include "detail/to_string.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup geometry
/// \{

/**
 * \brief Provides traits used by the `basic_point` class.
 *
 * \tparam T the representation type. Must be convertible to `int` or `float`.
 *
 * \since 5.0.0
 *
 * \see `basic_point`
 * \see `ipoint`
 * \see `fpoint`
 *
 * \headerfile point.hpp
 */
template <typename T,
          typename = std::enable_if_t<std::is_convertible_v<T, int> ||
                                      std::is_convertible_v<T, float>>>
class point_traits final
{
 public:
  /**
   * \var isIntegral
   *
   * \brief Indicates whether or not the point is based on an integral type.
   *
   * \since 5.0.0
   */
  inline constexpr static bool isIntegral = std::is_integral_v<T>;

  /**
   * \var isFloating
   *
   * \brief Indicates whether or not the point is based on a floating-point
   * type.
   *
   * \since 5.0.0
   */
  inline constexpr static bool isFloating = std::is_floating_point_v<T>;

  /**
   * \typedef value_type
   *
   * \brief The actual representation type, i.e. `int` or `float`.
   *
   * \since 5.0.0
   */
  using value_type = std::conditional_t<isIntegral, int, float>;

  /**
   * \typedef point_type
   *
   * \brief The SDL point type, i.e. `SDL_Point` or `SDL_FPoint`.
   *
   * \since 5.0.0
   */
  using point_type = std::conditional_t<isIntegral, SDL_Point, SDL_FPoint>;
};

/**
 * \class basic_point
 *
 * \brief Represents a two-dimensional point.
 *
 * \details This class is designed as a wrapper for `SDL_Point` and
 * `SDL_FPoint`. The representation is specified by the type parameter.
 *
 * \note This point class will only use `int` or `float` as the actual
 * internal representation.
 *
 * \tparam T the representation type. Must be convertible to `int` or `float`.
 *
 * \since 5.0.0
 *
 * \see `ipoint`
 * \see `fpoint`
 *
 * \headerfile point.hpp
 */
template <typename T>
class basic_point final
{
 public:
  /**
   * \copydoc point_traits::isIntegral
   */
  inline constexpr static bool isIntegral = point_traits<T>::isIntegral;

  /**
   * \copydoc point_traits::isFloating
   */
  inline constexpr static bool isFloating = point_traits<T>::isFloating;

  /**
   * \copydoc point_traits::value_type
   */
  using value_type = typename point_traits<T>::value_type;

  /**
   * \copydoc point_traits::point_type
   */
  using point_type = typename point_traits<T>::point_type;

  /**
   * \brief Creates a zero-initialized point.
   *
   * \since 5.0.0
   */
  constexpr basic_point() noexcept = default;

  /**
   * \brief Creates a point with the specified coordinates.
   *
   * \param x the x-coordinate that will be used.
   * \param y the y-coordinate that will be used.
   *
   * \since 5.0.0
   */
  constexpr basic_point(const value_type x, const value_type y) noexcept
  {
    m_point.x = x;
    m_point.y = y;
  };

  /**
   * \brief Sets the x-coordinate of the point.
   *
   * \param x the new x-coordinate.
   *
   * \since 5.0.0
   */
  constexpr void set_x(const value_type x) noexcept
  {
    m_point.x = x;
  }

  /**
   * \brief Sets the y-coordinate of the point.
   *
   * \param y the new y-coordinate.
   *
   * \since 5.0.0
   */
  constexpr void set_y(const value_type y) noexcept
  {
    m_point.y = y;
  }

  /**
   * \brief Returns the x-coordinate of the point.
   *
   * \return the x-coordinate.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type
  {
    return m_point.x;
  }

  /**
   * \brief Returns the y-coordinate of the point.
   *
   * \return the y-coordinate.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type
  {
    return m_point.y;
  }

  /**
   * \brief Returns the internal point representation.
   *
   * \return a reference to the internal representation.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() noexcept -> point_type&
  {
    return m_point;
  }

  /**
   * \copydoc get
   */
  [[nodiscard]] constexpr auto get() const noexcept -> const point_type&
  {
    return m_point;
  }

  /**
   * \brief Returns a pointer to the internal point representation.
   *
   * \note Don't cache the returned pointer.
   *
   * \return a pointer to the point representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto data() noexcept -> point_type*
  {
    return &m_point;
  }

  /**
   * \copydoc data()
   */
  [[nodiscard]] auto data() const noexcept -> const point_type*
  {
    return &m_point;
  }

  /**
   * \brief Converts to the internal representation.
   *
   * \return a copy of the internal point.
   *
   * \see `cen::cast`
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr explicit operator point_type() const noexcept
  {
    return m_point;
  }

  /**
   * \brief Returns a pointer to the internal point.
   *
   * \note You shouldn't store the returned pointer. However, this conversion
   * is safe since `reinterpret_cast` isn't used.
   *
   * \return a pointer to the internal point instance.
   *
   * \since 5.0.0
   */
  [[nodiscard]] explicit operator point_type*() noexcept
  {
    return &m_point;
  }

  /**
   * \brief Returns a pointer to the internal point.
   *
   * \note You shouldn't store the returned pointer. However, this conversion
   * is safe since `reinterpret_cast` isn't used.
   *
   * \return a pointer to the internal point instance.
   *
   * \since 5.0.0
   */
  [[nodiscard]] explicit operator const point_type*() const noexcept
  {
    return &m_point;
  }

  /**
   * \brief Serializes the point.
   *
   * \details This function expects that the archive provides an overloaded
   * `operator()`, used for serializing data. This API is based on the Cereal
   * serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the point.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_point.x, m_point.y);
  }

 private:
  point_type m_point{0, 0};
};

/**
 * \typedef ipoint
 *
 * \ingroup geometry
 *
 * \brief Alias for an `int`-based point.
 *
 * \details This type corresponds to `SDL_Point`.
 *
 * \since 5.0.0
 */
using ipoint = basic_point<int>;

/**
 * \typedef fpoint
 *
 * \ingroup geometry
 *
 * \brief Alias for a `float`-based point.
 *
 * \details This type corresponds to `SDL_FPoint`.
 *
 * \since 5.0.0
 */
using fpoint = basic_point<float>;

/**
 * \brief Converts an `fpoint` instance to the corresponding `ipoint`.
 *
 * \details This function casts the coordinates of the supplied point to
 * `int`, and uses the obtained values to create an `ipoint` instance.
 *
 * \param from the point that will be converted.
 *
 * \return an `ipoint` instance that corresponds to the supplied `fpoint`.
 *
 * \since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const fpoint& from) noexcept -> ipoint
{
  const auto x = static_cast<int>(from.x());
  const auto y = static_cast<int>(from.y());
  return ipoint{x, y};
}

/**
 * \brief Converts an `ipoint` instance to the corresponding `fpoint`.
 *
 * \details This function casts the coordinates of the supplied point to
 * `float`, and uses the obtained values to create an `fpoint` instance.
 *
 * \param from the point that will be converted.
 *
 * \return an `fpoint` instance that corresponds to the supplied `ipoint`.
 *
 * \since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const ipoint& from) noexcept -> fpoint
{
  const auto x = static_cast<float>(from.x());
  const auto y = static_cast<float>(from.y());
  return fpoint{x, y};
}

/**
 * \brief Converts an `SDL_FPoint` instance to the corresponding `SDL_Point`.
 *
 * \details This function casts the coordinates of the supplied point to
 * `int`, and uses the obtained values to create an `SDL_Point` instance.
 *
 * \param from the point that will be converted.
 *
 * \return an `SDL_Point` instance that corresponds to the supplied
 * `SDL_FPoint`.
 *
 * \since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const SDL_FPoint& from) noexcept -> SDL_Point
{
  const auto x = static_cast<int>(from.x);
  const auto y = static_cast<int>(from.y);
  return SDL_Point{x, y};
}

/**
 * \brief Converts an `SDL_Point` instance to the corresponding `SDL_FPoint`.
 *
 * \details This function casts the coordinates of the supplied point to
 * `float`, and uses the obtained values to create an `SDL_FPoint` instance.
 *
 * \param from the point that will be converted.
 *
 * \return an `SDL_FPoint` instance that corresponds to the supplied
 * `SDL_Point`.
 *
 * \since 5.0.0
 */
template <>
[[nodiscard]] constexpr auto cast(const SDL_Point& from) noexcept -> SDL_FPoint
{
  const auto x = static_cast<float>(from.x);
  const auto y = static_cast<float>(from.y);
  return SDL_FPoint{x, y};
}

/**
 * \brief Returns the distance between two points.
 *
 * \tparam T the representation type used by the points.
 *
 * \param from the first point.
 * \param to the second point.
 *
 * \return the distance between the two points.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] inline auto distance(const basic_point<T>& from,
                                   const basic_point<T>& to) noexcept ->
    typename point_traits<T>::value_type
{
  if constexpr (basic_point<T>::isIntegral) {
    const auto xDiff = std::abs(from.x() - to.x());
    const auto yDiff = std::abs(from.y() - to.y());
    const auto dist = std::sqrt(xDiff + yDiff);
    return static_cast<int>(std::round(dist));
  } else {
    return std::sqrt(std::abs(from.x() - to.x()) + std::abs(from.y() - to.y()));
  }
}

[[nodiscard]] constexpr auto operator+(const fpoint& lhs,
                                       const fpoint& rhs) noexcept -> fpoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] constexpr auto operator-(const fpoint& lhs,
                                       const fpoint& rhs) noexcept -> fpoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] constexpr auto operator+(const ipoint& lhs,
                                       const ipoint& rhs) noexcept -> ipoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] constexpr auto operator-(const ipoint& lhs,
                                       const ipoint& rhs) noexcept -> ipoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] constexpr auto operator==(const ipoint& lhs,
                                        const ipoint& rhs) noexcept -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] constexpr auto operator==(const fpoint& lhs,
                                        const fpoint& rhs) noexcept -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] constexpr auto operator!=(const ipoint& lhs,
                                        const ipoint& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] constexpr auto operator!=(const fpoint& lhs,
                                        const fpoint& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] inline auto to_string(const ipoint& point) -> std::string
{
  return "[ipoint | X: " + detail::to_string(point.x()).value() +
         ", Y: " + detail::to_string(point.y()).value() + "]";
}

[[nodiscard]] inline auto to_string(const fpoint& point) -> std::string
{
  return "[fpoint | X: " + detail::to_string(point.x()).value() +
         ", Y: " + detail::to_string(point.y()).value() + "]";
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

/// \}

}  // namespace cen

#endif  // CENTURION_POINT_HEADER