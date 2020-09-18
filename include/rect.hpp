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
 * @defgroup geometry Geometry
 *
 * @brief Contains basic geometric components, used throughout the library.
 */

/**
 * @file rect.hpp
 *
 * @brief Provides a generic rectangle implementation.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_RECTANGLE_HEADER
#define CENTURION_RECTANGLE_HEADER

#include <SDL.h>

#include <algorithm>
#include <ostream>
#include <string>
#include <type_traits>

#include "area.hpp"
#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "point.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @class rect_traits
 *
 * @ingroup geometry
 *
 * @brief Provides rectangle traits used by `basic_rect`.
 *
 * @note Whilst it is possible to supply a type that isn't `int` or `float`,
 * rectangles will always use one of them as the representation type.
 *
 * @tparam T the representation type, must be convertible to `int` or `float`.
 *
 * @see `basic_rect`
 * @see `irect`
 * @see `frect`
 *
 * @since 5.0.0
 *
 * @headerfile rect.hpp
 */
template <typename T,
          typename = std::enable_if_t<std::is_convertible_v<T, int> ||
                                      std::is_convertible_v<T, float>>>
class rect_traits final
{
 public:
  /**
   * @var isIntegral
   *
   * @brief Indicates whether or not the rectangle is based on an integral type.
   *
   * @since 5.0.0
   */
  inline static constexpr bool isIntegral = std::is_integral_v<T>;

  /**
   * @var isFloating
   *
   * @brief Indicates whether or not the rectangle is based on a floating-point
   * type.
   *
   * @since 5.0.0
   */
  inline static constexpr bool isFloating = std::is_floating_point_v<T>;

  /**
   * @typedef value_type
   *
   * @brief The representation type, i.e. `int` or `float`.
   *
   * @since 5.0.0
   */
  using value_type = std::conditional_t<isIntegral, int, float>;

  /**
   * @typedef point_type
   *
   * @brief The point type used, i.e. `ipoint` or `fpoint`.
   *
   * @since 5.0.0
   */
  using point_type = std::conditional_t<isIntegral, ipoint, fpoint>;

  /**
   * @typedef area_type
   *
   * @brief The area type used, i.e. `iarea` or `farea`.
   *
   * @since 5.0.0
   */
  using area_type = std::conditional_t<isIntegral, iarea, farea>;

  /**
   * @typedef rect_type
   *
   * @brief The underlying SDL rectangle type, i.e. `SDL_Rect` or `SDL_FRect`.
   *
   * @since 5.0.0
   */
  using rect_type = std::conditional_t<isIntegral, SDL_Rect, SDL_FRect>;
};

/**
 * @class basic_rect
 *
 * @ingroup geometry
 *
 * @brief A simple rectangle implementation.
 *
 * @tparam T the representation type. Must be convertible to either `int` or
 * `float`.
 *
 * @see `irect`
 * @see `frect`
 *
 * @since 4.0.0
 *
 * @headerfile rect.hpp
 */
template <typename T>
class basic_rect final
{
 public:
  /**
   * @copydoc rect_traits<T>::isIntegral
   */
  inline static constexpr bool isIntegral = rect_traits<T>::isIntegral;

  /**
   * @copydoc rect_traits<T>::isFloating
   */
  inline static constexpr bool isFloating = rect_traits<T>::isFloating;

  /**
   * @copydoc rect_traits<T>::value_type
   */
  using value_type = typename rect_traits<T>::value_type;

  /**
   * @copydoc rect_traits<T>::point_type
   */
  using point_type = typename rect_traits<T>::point_type;

  /**
   * @copydoc rect_traits<T>::area_type
   */
  using area_type = typename rect_traits<T>::area_type;

  /**
   * @copydoc rect_traits<T>::rect_type
   */
  using rect_type = typename rect_traits<T>::rect_type;

  /**
   * @brief Creates a rectangle with the components (0, 0, 0, 0).
   *
   * @since 4.0.0
   */
  constexpr basic_rect() noexcept = default;

  /**
   * @brief Creates a rectangle with the supplied position and size.
   *
   * @param position the position of the rectangle.
   * @param size the size of the rectangle.
   *
   * @since 4.1.0
   */
  constexpr basic_rect(const point_type& position,
                       const area_type& size) noexcept
      : m_rect{position.x(), position.y(), size.width, size.height}
  {}

  /**
   * @brief Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_x(value_type x) noexcept { m_rect.x = x; }

  /**
   * @brief Sets the y-coordinate of the rectangle.
   *
   * @param y the new y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_y(value_type y) noexcept { m_rect.y = y; }

  /**
   * @brief Moves the rectangle to the specified position.
   *
   * @note Some frameworks have this kind of method change the size of the
   * rectangle. However, this method does *not* change the size of the
   * rectangle.
   *
   * @param pos the new position of the rectangle.
   *
   * @since 4.2.0
   */
  constexpr void move_to(const point_type& pos) noexcept
  {
    m_rect.x = pos.x();
    m_rect.y = pos.y();
  }

  /**
   * @brief Sets the width of the rectangle.
   *
   * @param width the new width of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_width(value_type width) noexcept { m_rect.w = width; }

  /**
   * @brief Sets the height of the rectangle.
   *
   * @param height the new height of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_height(value_type height) noexcept { m_rect.h = height; }

  /**
   * @brief Changes the size of the rectangle.
   *
   * @param size the new size of the rectangle.
   *
   * @since 4.2.0
   */
  constexpr void resize(const area_type& size) noexcept
  {
    m_rect.w = size.width;
    m_rect.h = size.height;
  };

  /**
   * @brief Indicates whether or not the rectangle contains the point.
   *
   * @param point the point that will be checked.
   *
   * @return `true` if the rectangle contains the point; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto contains(const point_type& point) const noexcept
      -> bool
  {
    const auto px = point.x();
    const auto py = point.y();
    return !(px < x() || py < y() || px > max_x() || py > max_y());
  }

  /**
   * @brief Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type
  {
    return m_rect.x;
  }

  /**
   * @brief Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type
  {
    return m_rect.y;
  }

  /**
   * @brief Returns the position of the rectangle.
   *
   * @return the position of the rectangle.
   *
   * @since 4.1.0
   */
  [[nodiscard]] constexpr auto position() const noexcept -> point_type
  {
    return point_type{m_rect.x, m_rect.y};
  }

  /**
   * @brief Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto width() const noexcept -> value_type
  {
    return m_rect.w;
  }

  /**
   * @brief Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto height() const noexcept -> value_type
  {
    return m_rect.h;
  }

  /**
   * @brief Returns the size of the rectangle.
   *
   * @return the size of the rectangle.
   *
   * @since 4.1.0
   */
  [[nodiscard]] constexpr auto size() const noexcept -> area_type
  {
    return area_type{m_rect.w, m_rect.h};
  }

  /**
   * @brief Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto max_x() const noexcept -> value_type
  {
    return x() + width();
  }

  /**
   * @brief Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto max_y() const noexcept -> value_type
  {
    return y() + height();
  }

  /**
   * @brief Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center_x() const noexcept -> value_type
  {
    return x() + (width() / static_cast<value_type>(2));
  }

  /**
   * @brief Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center_y() const noexcept -> value_type
  {
    return y() + (height() / static_cast<value_type>(2));
  }

  /**
   * @brief Returns the center point of the rectangle.
   *
   * @return the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center() const noexcept -> point_type
  {
    return {center_x(), center_y()};
  }

  /**
   * @brief Returns the total area of the rectangle.
   *
   * @return the area of the rectangle.
   *
   * @since 4.2.0
   */
  [[nodiscard]] constexpr auto area() const noexcept -> value_type
  {
    return width() * height();
  }

  /**
   * @brief Indicates whether or not the rectangle has an area.
   *
   * @details The rectangle has an area if both the width and height are
   * greater than zero.
   *
   * @return `true` if the rectangle has an area; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto has_area() const noexcept -> bool
  {
    return (width() > 0) && (height() > 0);
  }

  /**
   * @brief Returns the internal rectangle.
   *
   * @return a reference to the internal rectangle.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto get() noexcept -> rect_type& { return m_rect; }

  /**
   * @brief Returns the internal rectangle.
   *
   * @return a reference to the internal rectangle.
   *
   * @since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type&
  {
    return m_rect;
  }

  /**
   * @brief Returns a pointer to the internal rectangle.
   *
   * @return a pointer to the internal rectangle.
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator rect_type*() noexcept { return &m_rect; }

  /**
   * @brief Returns a pointer to the internal rectangle.
   *
   * @return a pointer to the internal rectangle.
   *
   * @since 5.0.0
   */
  [[nodiscard]] explicit operator const rect_type*() const noexcept
  {
    return &m_rect;
  }

 private:
  rect_type m_rect{0, 0, 0, 0};
};

/**
 * @typedef irect
 *
 * @ingroup geometry
 *
 * @brief Alias for an `int`-based rectangle.
 *
 * @since 5.0.0
 */
using irect = basic_rect<int>;

/**
 * @typedef frect
 *
 * @ingroup geometry
 *
 * @brief Alias for a `float`-based rectangle.
 *
 * @since 5.0.0
 */
using frect = basic_rect<float>;

static_assert(std::is_nothrow_default_constructible_v<frect>);
static_assert(std::is_nothrow_default_constructible_v<irect>);

static_assert(std::is_nothrow_copy_constructible_v<frect>);
static_assert(std::is_nothrow_copy_constructible_v<irect>);

static_assert(std::is_nothrow_copy_assignable_v<frect>);
static_assert(std::is_nothrow_copy_assignable_v<irect>);

static_assert(std::is_nothrow_move_constructible_v<frect>);
static_assert(std::is_nothrow_move_constructible_v<irect>);

static_assert(std::is_nothrow_move_assignable_v<frect>);
static_assert(std::is_nothrow_move_assignable_v<irect>);

static_assert(std::is_nothrow_destructible_v<frect>);
static_assert(std::is_nothrow_destructible_v<irect>);

/**
 * @brief Indicates whether or not two rectangles are equal.
 *
 * @ingroup geometry
 *
 * @tparam T the representation type used by the rectangles.
 *
 * @param lhs the left-hand side rectangle.
 * @param rhs the right-hand side rectangle.
 *
 * @return `true` if the rectangles are equal; `false` otherwise.
 *
 * @since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_rect<T>& lhs,
                                        const basic_rect<T>& rhs) noexcept
    -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) &&
         (lhs.width() == rhs.width()) && (lhs.height() == rhs.height());
}

/**
 * @brief Indicates whether or not two rectangles aren't equal.
 *
 * @ingroup geometry
 *
 * @tparam T the representation type used by the rectangles.
 *
 * @param lhs the left-hand side rectangle.
 * @param rhs the right-hand side rectangle.
 *
 * @return `true` if the rectangles aren't equal; `false` otherwise.
 *
 * @since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_rect<T>& lhs,
                                        const basic_rect<T>& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

template <>
[[nodiscard]] constexpr auto cast(const irect& from) noexcept -> frect
{
  const frect::point_type pos{static_cast<float>(from.x()),
                              static_cast<float>(from.y())};
  const frect::area_type size{static_cast<float>(from.width()),
                              static_cast<float>(from.height())};
  return frect{pos, size};
}

template <>
[[nodiscard]] constexpr auto cast(const frect& from) noexcept -> irect
{
  const irect::point_type pos{static_cast<int>(from.x()),
                              static_cast<int>(from.y())};
  const irect::area_type size{static_cast<int>(from.width()),
                              static_cast<int>(from.height())};
  return irect{pos, size};
}

/**
 * @brief Indicates whether or not the two rectangles intersect.
 *
 * @details This function does *not* consider rectangles with overlapping
 * borders as intersecting. If you want such behaviour, see the
 * `collides` function.
 *
 * @tparam T the representation type used by the rectangles.
 *
 * @param fst the first rectangle.
 * @param snd the second rectangle.
 *
 * @return `true` if the rectangles intersect; `false` otherwise.
 *
 * @see `collides`
 *
 * @since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto intersects(const basic_rect<T>& fst,
                                        const basic_rect<T>& snd) noexcept
    -> bool
{
  return !(fst.x() >= snd.max_x() || fst.max_x() <= snd.x() ||
           fst.y() >= snd.max_y() || fst.max_y() <= snd.y());
}

/**
 * @brief Indicates whether or not two rectangles are colliding.
 *
 * @details This function considers rectangles with overlapping borders as
 * colliding.
 *
 * @tparam T the representation type used by the rectangles.
 *
 * @param fst the first rectangle.
 * @param snd the second rectangle.
 *
 * @return `true` if the rectangles collide; `false` otherwise.
 *
 * @see `intersects`
 *
 * @since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto collides(const basic_rect<T>& fst,
                                      const basic_rect<T>& snd) noexcept -> bool
{
  return !(fst.x() > snd.max_x() || fst.max_x() < snd.x() ||
           fst.y() > snd.max_y() || fst.max_y() < snd.y());
}

/**
 * @brief Returns the union of two rectangles.
 *
 * @ingroup geometry
 *
 * @details Returns a rectangle that represents the union of two rectangles.
 *
 * @tparam T the representation type used by the rectangles.
 *
 * @param fst the first rectangle.
 * @param snd the second rectangle.
 *
 * @return a rectangle that represents the union of the rectangles.
 *
 * @since 5.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto get_union(const basic_rect<T>& fst,
                                       const basic_rect<T>& snd) noexcept
    -> basic_rect<T>
{
  const auto fstHasArea = fst.has_area();
  const auto sndHasArea = snd.has_area();

  if (!fstHasArea && !sndHasArea) {
    return {};
  } else if (!fstHasArea) {
    return snd;
  } else if (!sndHasArea) {
    return fst;
  }

  const auto x = std::min(fst.x(), snd.x());
  const auto y = std::min(fst.y(), snd.y());
  const auto maxX = std::max(fst.max_x(), snd.max_x());
  const auto maxY = std::max(fst.max_y(), snd.max_y());

  return {{x, y}, {maxX - x, maxY - y}};
}

/**
 * @brief Returns a textual representation of a rectangle.
 *
 * @ingroup geometry
 *
 * @tparam T the representation type used by the rectangle.
 *
 * @param rect the rectangle that will be converted to a string.
 *
 * @return a textual representation of the rectangle.
 *
 * @since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_rect<T>& rect) -> std::string
{
  const auto x = std::to_string(rect.x());
  const auto y = std::to_string(rect.y());
  const auto w = std::to_string(rect.width());
  const auto h = std::to_string(rect.height());
  return "[Rect | X: " + x + ", Y: " + y + ", Width: " + w + ", Height: " + h +
         "]";
}

/**
 * @brief Prints a textual representation of a rectangle using a stream.
 *
 * @ingroup geometry
 *
 * @tparam T the representation type used by the rectangle.
 *
 * @param stream the stream that will be used.
 * @param rect the rectangle that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_rect<T>& rect)
    -> std::ostream&
{
  stream << to_string(rect);
  return stream;
}

}  // namespace cen

#endif  // CENTURION_RECTANGLE_HEADER