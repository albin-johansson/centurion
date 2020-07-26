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

#include <ostream>
#include <string>
#include <type_traits>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "point.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class irect_traits final {
 public:
  using rect_type = SDL_Rect;
  using point_type = ipoint;
  using area_type = iarea;
  using value_type = int;
};

class frect_traits final {
 public:
  using rect_type = SDL_FRect;
  using point_type = fpoint;
  using area_type = farea;
  using value_type = float;
};

}  // namespace detail

/// @endcond

/**
 * @class basic_rect
 *
 * @ingroup geometry
 *
 * @brief A rectangle that supports integral and floating-point components.
 *
 * @par Examples
 * The following are some examples of interaction with the SDL rectangle
 * structs.
 * @code{.cpp}
 *   ctn::frect f{};
 *   auto* a = static_cast<SDL_FRect*>(f);
 *   const auto* b = static_cast<const SDL_FRect*>(f);
 *   SDL_FRect& c = f.get();
 *
 *   ctn::irect r{};
 *   auto* d = static_cast<SDL_Rect*>(r);
 *   const auto* e = static_cast<const SDL_Rect*>(r);
 *   SDL_Rect& f = r.get();
 * @endcode
 *
 * @tparam Traits the traits used by the rectangle. Must provide
 * `rect_type`, `area_type`, `point_type` and `value_type`.
 *
 * @since 4.0.0
 *
 * @see `irect`
 * @see `frect`
 *
 * @headerfile rect.hpp
 */
template <typename Traits>
class basic_rect final {
 public:
  using rect_type = typename Traits::rect_type;
  using point_type = typename Traits::point_type;
  using area_type = typename Traits::area_type;
  using value_type = typename Traits::value_type;

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
   * @brief Sets the position and size of the rectangle.
   *
   * @param position the new position of the rectangle.
   * @param size the new size of the rectangle.
   *
   * @since 4.1.0
   */
  constexpr void set(const point_type& position, const area_type& size) noexcept
  {
    move_to(position);
    set_size(size);
  }

  /**
   * @brief Indicates whether or not the two rectangles intersect.
   *
   * @details This function does *not* consider rectangles with overlapping
   * borders as intersecting. If you want such behaviour, see the
   * `collides_with` function.
   *
   * @param other the other rectangle to check.
   *
   * @return `true` if the rectangles intersect; `false` otherwise.
   *
   * @see `collides_with`
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto intersects(
      const basic_rect<Traits>& other) const noexcept -> bool
  {
    return !(x() >= other.max_x() || max_x() <= other.x() ||
             y() >= other.max_y() || max_y() <= other.y());
  }

  /**
   * @brief Indicates whether or not two rectangles are colliding.
   *
   * @details This function considers rectangles with overlapping borders as
   * colliding.
   *
   * @param other the other rectangle to check.
   *
   * @return `true` if the rectangles collide; `false` otherwise.
   *
   * @see `intersects`
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto collides_with(
      const basic_rect<Traits>& other) const noexcept -> bool
  {
    return !(x() > other.max_x() || max_x() < other.x() ||
             y() > other.max_y() || max_y() < other.y());
  }

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
   * @brief Returns the area of the rectangle.
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

  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type&
  {
    return m_rect;
  }

  [[nodiscard]] explicit operator rect_type*() noexcept { return &m_rect; }

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
using irect = basic_rect<detail::irect_traits>;

/**
 * @typedef frect
 *
 * @ingroup geometry
 *
 * @brief Alias for a `float`-based rectangle.
 *
 * @since 5.0.0
 */
using frect = basic_rect<detail::frect_traits>;

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
 * @param lhs the left-hand side rectangle.
 * @param rhs the right-hand side rectangle.
 *
 * @return `true` if the rectangles are equal; `false` otherwise.
 *
 * @since 4.0.0
 */
template <typename Traits>
[[nodiscard]] inline constexpr auto operator==(
    const basic_rect<Traits>& lhs,
    const basic_rect<Traits>& rhs) noexcept -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) &&
         (lhs.width() == rhs.width()) && (lhs.height() == rhs.height());
}

/**
 * @brief Indicates whether or not two rectangles aren't equal.
 *
 * @ingroup geometry
 *
 * @param lhs the left-hand side rectangle.
 * @param rhs the right-hand side rectangle.
 *
 * @return `true` if the rectangles aren't equal; `false` otherwise.
 *
 * @since 4.0.0
 */
template <typename Traits>
[[nodiscard]] inline constexpr auto operator!=(
    const basic_rect<Traits>& lhs,
    const basic_rect<Traits>& rhs) noexcept -> bool
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
 * @brief Returns the union of two rectangles.
 *
 * @ingroup geometry
 *
 * @details Returns a rectangle that represents the union of two rectangles.
 *
 * @param fst the first rectangle.
 * @param snd the second rectangle.
 *
 * @return a rectangle that represents the union of the rectangles.
 *
 * @since 5.0.0
 */
[[nodiscard]] inline auto get_union(const irect& fst, const irect& snd) noexcept
    -> irect
{
  SDL_Rect result{0, 0, 0, 0};
  SDL_UnionRect(&fst.get(), &snd.get(), &result);
  return {{result.x, result.y}, {result.w, result.h}};
}

/**
 * @brief Returns a textual representation of a rectangle.
 *
 * @ingroup geometry
 *
 * @tparam Traits the traits used by the rectangle.
 *
 * @param rect the rectangle that will be converted to a string.
 *
 * @return a textual representation of the rectangle.
 *
 * @since 5.0.0
 */
template <typename Traits>
[[nodiscard]] auto to_string(const basic_rect<Traits>& rect) -> std::string
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
 * @tparam Traits the traits used by the rectangle.
 *
 * @param stream the stream that will be used.
 * @param rect the rectangle that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
template <typename Traits>
inline auto operator<<(std::ostream& stream, const basic_rect<Traits>& rect)
    -> std::ostream&
{
  return stream << to_string(rect);
  return stream;
}

}  // namespace centurion

#endif  // CENTURION_RECTANGLE_HEADER