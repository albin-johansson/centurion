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

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "point.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

template <typename T>
class basic_rect;

template <typename U>
constexpr auto operator==(const basic_rect<U>& lhs,
                          const basic_rect<U>& rhs) noexcept -> bool;

template <typename U>
constexpr auto operator!=(const basic_rect<U>& lhs,
                          const basic_rect<U>& rhs) noexcept -> bool;

/**
 * @class basic_rect
 *
 * @ingroup geometry
 *
 * @brief A rectangle that supports integral and floating-point components.
 *
 *
 * @par Examples
 * The following are some examples of interaction with the SDL rectangle
 * structs.
 * @code{.cpp}
 *   rect_f frect{};
 *   auto* a = static_cast<SDL_FRect*>(frect);
 *   const auto* b = static_cast<const SDL_FRect*>(frect);
 *   SDL_FRect c = static_cast<SDL_FRect>(frect);
 *
 *   rect_i rect{};
 *   auto* d = static_cast<SDL_Rect*>(rect);
 *   const auto* e = static_cast<const SDL_Rect*>(rect);
 *   SDL_Rect f = static_cast<SDL_Rect>(rect);
 * @endcode
 *
 * @tparam T the type of the components of the rectangle. Set to float by
 * default.
 *
 * @since 4.0.0
 *
 * @see `rect_i`
 * @see `rect_f`
 *
 * @headerfile rect.hpp
 */
template <typename T = float>
class basic_rect final {
 public:
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
  constexpr basic_rect(basic_point<T> position, basic_area<T> size) noexcept
      : m_position{position}, m_size{size}
  {}

  /**
   * @brief Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_x(T x) noexcept { m_position.set_x(x); }

  /**
   * @brief Sets the y-coordinate of the rectangle.
   *
   * @param y the new y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_y(T y) noexcept { m_position.set_y(y); }

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
  constexpr void move_to(basic_point<T> pos) noexcept { m_position.set(pos); }

  /**
   * @brief Sets the width of the rectangle.
   *
   * @param width the new width of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_width(T width) noexcept { m_size.width = width; }

  /**
   * @brief Sets the height of the rectangle.
   *
   * @param height the new height of the rectangle.
   *
   * @since 4.0.0
   */
  constexpr void set_height(T height) noexcept { m_size.height = height; }

  /**
   * @brief Changes the size of the rectangle.
   *
   * @param size the new size of the rectangle.
   *
   * @since 4.2.0
   */
  constexpr void resize(basic_area<T> size) noexcept
  {
    m_size.width = size.width;
    m_size.height = size.height;
  };

  /**
   * @brief Sets all of the components of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   * @param y the new y-coordinate of the rectangle.
   * @param width the new width of the rectangle.
   * @param height the new height of the rectangle.
   *
   * @deprecated this method is deprecated in favor of <code>set(Point,
   * TArea)</code> since 4.1.0.
   *
   * @since 4.0.0
   */
  [[deprecated]] constexpr void set(T x, T y, T width, T height) noexcept
  {
    set({x, y}, {width, height});
  }

  /**
   * @brief Sets the position and size of the rectangle.
   *
   * @param position the new position of the rectangle.
   * @param size the new size of the rectangle.
   *
   * @since 4.1.0
   */
  constexpr void set(basic_point<T> position, basic_area<T> size) noexcept
  {
    m_position = position;
    m_size = size;
  }

  /**
   * @brief Copies all of the components of the supplied rectangle.
   *
   * @details The two rectangles will be equal after this operation.
   *
   * @param other the rectangle that will be copied.
   *
   * @since 4.0.0
   */
  constexpr void set(const basic_rect<T>& other) noexcept
  {
    m_position.set_x(other.x());
    m_position.set_y(other.y());
    m_size.width = other.width();
    m_size.height = other.height();
  }

  /**
   * @brief Indicates whether or not the two rectangles intersect.
   *
   * @param other the other rectangle to check.
   *
   * @return `true` if the rectangles intersect; `false` otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto intersects(
      const basic_rect<T>& other) const noexcept -> bool
  {
    return !(x() >= other.max_x() || max_x() <= other.x() ||
             y() >= other.max_y() || max_y() <= other.y());
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
  [[nodiscard]] constexpr auto contains(basic_point<T> point) const noexcept
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
  [[nodiscard]] constexpr auto x() const noexcept -> T
  {
    return m_position.x();
  }

  /**
   * @brief Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> T
  {
    return m_position.y();
  }

  /**
   * @brief Returns the position of the rectangle.
   *
   * @return the position of the rectangle.
   *
   * @since 4.1.0
   */
  [[nodiscard]] constexpr auto position() const noexcept -> basic_point<T>
  {
    return m_position;
  }

  /**
   * @brief Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto width() const noexcept -> T
  {
    return m_size.width;
  }

  /**
   * @brief Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto height() const noexcept -> T
  {
    return m_size.height;
  }

  /**
   * @brief Returns the size of the rectangle.
   *
   * @return the size of the rectangle.
   *
   * @since 4.1.0
   */
  [[nodiscard]] constexpr auto size() const noexcept -> basic_area<T>
  {
    return m_size;
  }

  /**
   * @brief Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto max_x() const noexcept -> T
  {
    return x() + m_size.width;
  }

  /**
   * @brief Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto max_y() const noexcept -> T
  {
    return y() + m_size.height;
  }

  /**
   * @brief Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center_x() const noexcept -> T
  {
    return x() + (m_size.width / 2);
  }

  /**
   * @brief Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center_y() const noexcept -> T
  {
    return y() + (m_size.height / 2);
  }

  /**
   * @brief Returns the center point of the rectangle.
   *
   * @return the center point of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] constexpr auto center() const noexcept -> basic_point<T>
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
  [[nodiscard]] constexpr auto area() const noexcept -> T
  {
    return m_size.width * m_size.height;
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
    return m_size.width > 0 && m_size.height > 0;
  }

  /**
   * @brief Returns the union of two rectangles.
   *
   * @details Returns a rectangle that represents the union of two rectangles.
   * This method is only available if the rectangle is based on `int`.
   *
   * @return a rectangle that represents the union of the rectangles.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] auto get_union(const basic_rect<T>& other) const noexcept
      -> basic_rect<T>
  {
    SDL_Rect result{0, 0, 0, 0};

    const auto* a = static_cast<const SDL_Rect*>(*this);
    const auto* b = static_cast<const SDL_Rect*>(other);

    SDL_UnionRect(a, b, &result);
    return {{result.x, result.y}, {result.w, result.h}};
  }

  /**
   * @brief Returns a textual representation of the rectangle.
   *
   * @return a textual representation of the rectangle.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto to_string() const -> std::string
  {
    const auto sx = std::to_string(m_position.x());
    const auto sy = std::to_string(m_position.y());
    const auto sw = std::to_string(m_size.width);
    const auto sh = std::to_string(m_size.height);
    return "[Rect | X: " + sx + ", Y: " + sy + ", Width: " + sw +
           ", Height: " + sh + "]";
  }

  /**
   * @brief Converts the rectangle to `SDL_Rect*`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `int`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return an `SDL_Rect*` that is produced by reinterpreting the invoked
   * rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] constexpr explicit operator SDL_Rect*() noexcept
  {
    return reinterpret_cast<SDL_Rect*>(this);
  }

  /**
   * @brief Converts the rectangle to `const SDL_Rect*`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `int`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return a `const SDL_Rect*` that is produced by reinterpreting the invoked
   * rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] constexpr explicit operator const SDL_Rect*() const noexcept
  {
    return reinterpret_cast<const SDL_Rect*>(this);
  }

  /**
   * @brief Converts the rectangle to `SDL_FRect*`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `float`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return an `SDL_FRect*` that is produced by reinterpreting the invoked
   * rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, float>>
  [[nodiscard]] constexpr explicit operator SDL_FRect*() noexcept
  {
    return reinterpret_cast<SDL_FRect*>(this);
  }

  /**
   * @brief Converts the rectangle to `const SDL_FRect*`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `float`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return a `const SDL_FRect*` that is produced by reinterpreting the invoked
   * rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, float>>
  [[nodiscard]] constexpr explicit operator const SDL_FRect*() const noexcept
  {
    return reinterpret_cast<const SDL_FRect*>(this);
  }

  /**
   * @brief Converts the rectangle to an `SDL_Rect`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `int`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return an `SDL_Rect` based on this rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, int>>
  [[nodiscard]] constexpr explicit operator SDL_Rect() const noexcept
  {
    return {m_position.x(), m_position.y(), m_size.width, m_size.height};
  }

  /**
   * @brief Converts the rectangle to an `SDL_FRect`.
   *
   * @details This conversion is only available if the rectangle is based on
   * `float`.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   *
   * @return an `SDL_FRect` based on this rectangle.
   *
   * @since 4.0.0
   */
  template <typename U = T, typename = detail::if_same_t<U, float>>
  [[nodiscard]] constexpr explicit operator SDL_FRect() const noexcept
  {
    return {m_position.x(), m_position.y(), m_size.width, m_size.height};
  }

  /**
   * @brief Indicates whether or not two rectangles are equal.
   *
   * @param lhs the left-hand side rectangle.
   * @param rhs the right-hand side rectangle.
   *
   * @return `true` if the rectangles are equal; `false` otherwise.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator==
      <T>(const basic_rect<T>& lhs, const basic_rect<T>& rhs) noexcept -> bool;

  /**
   * @brief Indicates whether or not two rectangles aren't equal.
   *
   * @param lhs the left-hand side rectangle.
   * @param rhs the right-hand side rectangle.
   *
   * @return `true` if the rectangles aren't equal; `false` otherwise.
   *
   * @since 4.0.0
   */
  friend constexpr auto operator!=
      <T>(const basic_rect<T>& lhs, const basic_rect<T>& rhs) noexcept -> bool;

 private:
  basic_point<T> m_position;
  basic_area<T> m_size;

  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
  static_assert(std::is_trivial_v<T>);
};

template <typename T>
inline constexpr auto operator==(const basic_rect<T>& lhs,
                                 const basic_rect<T>& rhs) noexcept -> bool
{
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() &&
         lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

template <typename T>
inline constexpr auto operator!=(const basic_rect<T>& lhs,
                                 const basic_rect<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

static_assert(std::is_nothrow_default_constructible_v<basic_rect<float>>);
static_assert(std::is_nothrow_copy_constructible_v<basic_rect<float>>);
static_assert(std::is_nothrow_move_constructible_v<basic_rect<float>>);
static_assert(std::is_nothrow_copy_assignable_v<basic_rect<float>>);
static_assert(std::is_nothrow_move_assignable_v<basic_rect<float>>);
static_assert(sizeof(basic_rect<int>) == sizeof(SDL_Rect));
static_assert(sizeof(basic_rect<float>) == sizeof(SDL_FRect));

using rect_i = basic_rect<int>;
using rect_f = basic_rect<float>;

}  // namespace centurion

#endif  // CENTURION_RECTANGLE_HEADER