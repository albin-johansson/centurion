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
 * @brief Provides a generic rectangle implementation.
 *
 * @file rect.h
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_RECTANGLE_HEADER
#define CENTURION_RECTANGLE_HEADER

#include <SDL.h>

#include "area.hpp"
#include "centurion_api.hpp"
#include "centurion_utils.hpp"
#include "point.hpp"

namespace centurion {

template <typename T>
class Rect;

template <typename U>
constexpr bool operator==(const Rect<U>& lhs, const Rect<U>& rhs) noexcept;

template <typename U>
constexpr bool operator!=(const Rect<U>& lhs, const Rect<U>& rhs) noexcept;

/**
 * @class Rect
 * @brief A rectangle that supports integral and floating-point components.
 *
 * @details `Rect<int>` and `Rect<float>` can safely be explicitly casted to
 * pointers to `SDL_Rect` and `SDL_FRect` respectively.
 *
 * @par Examples
 * The following are some examples of interaction with the SDL rectangle
 * structs.
 * @code{.cpp}
 *   FRect frect{};
 *   auto* a = static_cast<SDL_FRect*>(frect);
 *   const auto* b = static_cast<const SDL_FRect*>(frect);
 *   SDL_FRect c = frect;
 *
 *   IRect rect{};
 *   auto* d = static_cast<SDL_Rect*>(rect);
 *   const auto* e = static_cast<const SDL_Rect*>(rect);
 *   SDL_Rect f = rect;
 * @endcode
 *
 * @tparam T the type of the components of the rectangle. Set to float by
 * default.
 *
 * @headerfile rect.h
 * @since 4.0.0
 */
template <typename T = float>
class Rect final {
 public:
  /**
   * @brief Creates a rectangle with the components (0, 0, 0, 0).
   *
   * @since 4.0.0
   */
  constexpr Rect() noexcept = default;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   *
   * @deprecated this constructor is deprecated in favor of <code>Rect
   * (Point, TArea)</code> since 4.1.0.
   *
   * @since 4.0.0
   */
  CENTURION_DEPRECATED
  constexpr Rect(T x, T y, T width, T height) noexcept
      : Rect{{x, y}, {width, height}}
  {}

  /**
   * @param position the position of the rectangle.
   * @param size the size of the rectangle.
   *
   * @since 4.1.0
   */
  constexpr Rect(Point<T> position, TArea<T> size) noexcept
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
  constexpr void move_to(Point<T> pos) noexcept { m_position.set(pos); }

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
  constexpr void resize(TArea<T> size) noexcept
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
  CENTURION_DEPRECATED
  constexpr void set(T x, T y, T width, T height) noexcept
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
  constexpr void set(Point<T> position, TArea<T> size) noexcept
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
  constexpr void set(const Rect<T>& other) noexcept
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
  CENTURION_NODISCARD
  constexpr bool intersects(const Rect<T>& other) const noexcept
  {
    return !(x() >= other.max_x() || max_x() <= other.x() ||
             y() >= other.max_y() || max_y() <= other.y());
  }

  /**
   * @brief Indicates whether or not the rectangle contains the point.
   *
   * @param px the x-coordinate of the point.
   * @param py the y-coordinate of the point.
   *
   * @return `true` if the rectangle contains the point; `false` otherwise.
   *
   * @deprecated this method is deprecated in favor of <code>contains(Point)
   * </code> since 4.1.0.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_DEPRECATED
  constexpr bool contains(T px, T py) const noexcept
  {
    return contains({px, py});
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
  CENTURION_NODISCARD
  constexpr bool contains(Point<T> point) const noexcept
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
  CENTURION_NODISCARD
  constexpr T x() const noexcept { return m_position.x(); }

  /**
   * @brief Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T y() const noexcept { return m_position.y(); }

  /**
   * @brief Returns the position of the rectangle.
   *
   * @return the position of the rectangle.
   *
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  constexpr Point<T> position() const noexcept { return m_position; }

  /**
   * @brief Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T width() const noexcept { return m_size.width; }

  /**
   * @brief Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T height() const noexcept { return m_size.height; }

  /**
   * @brief Returns the size of the rectangle.
   *
   * @return the size of the rectangle.
   *
   * @since 4.1.0
   */
  CENTURION_NODISCARD
  constexpr TArea<T> size() const noexcept { return m_size; }

  /**
   * @brief Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T max_x() const noexcept { return x() + m_size.width; }

  /**
   * @brief Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T max_y() const noexcept { return y() + m_size.height; }

  /**
   * @brief Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T center_x() const noexcept { return x() + (m_size.width / 2); }

  /**
   * @brief Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T center_y() const noexcept { return y() + (m_size.height / 2); }

  /**
   * @brief Returns the center point of the rectangle.
   *
   * @return the center point of the rectangle.
   *
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr Point<T> center() const noexcept
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
  CENTURION_NODISCARD
  constexpr T area() const noexcept { return m_size.width * m_size.height; }

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
  CENTURION_NODISCARD
  constexpr bool has_area() const noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD Rect<T> get_union(const Rect<T>& other) const noexcept
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
  CENTURION_NODISCARD
  std::string to_string() const
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
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD constexpr explicit operator SDL_Rect*() noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD constexpr explicit operator const SDL_Rect*()
      const noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, float>>
  CENTURION_NODISCARD constexpr explicit operator SDL_FRect*() noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, float>>
  CENTURION_NODISCARD constexpr explicit operator const SDL_FRect*()
      const noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, int>>
  CENTURION_NODISCARD constexpr operator SDL_Rect() const noexcept
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
  template <typename U = T, typename = detail::type_if_same<U, float>>
  CENTURION_NODISCARD constexpr operator SDL_FRect() const noexcept
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
  CENTURION_NODISCARD
  friend constexpr bool operator==
      <T>(const Rect<T>& lhs, const Rect<T>& rhs) noexcept;

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
  CENTURION_NODISCARD
  friend constexpr bool operator!=
      <T>(const Rect<T>& lhs, const Rect<T>& rhs) noexcept;

 private:
  Point<T> m_position = {0, 0};
  TArea<T> m_size = {0, 0};

  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Rect type must be either integral or floating-point!");
  static_assert(std::is_trivial<T>::value, "Rect type must be trivial!");
};

template <typename T>
inline constexpr bool operator==(const Rect<T>& lhs,
                                 const Rect<T>& rhs) noexcept
{
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() &&
         lhs.width() == rhs.width() && lhs.height() == rhs.height();
}

template <typename T>
inline constexpr bool operator!=(const Rect<T>& lhs,
                                 const Rect<T>& rhs) noexcept
{
  return !(lhs == rhs);
}

static_assert(std::is_nothrow_default_constructible<Rect<float>>::value,
              "Rect isn't nothrow default constructible!");

static_assert(std::is_nothrow_copy_constructible<Rect<float>>::value,
              "Rect isn't nothrow copy constructible!");

static_assert(std::is_nothrow_move_constructible<Rect<float>>::value,
              "Rect isn't nothrow move constructible!");

static_assert(std::is_nothrow_copy_assignable<Rect<float>>::value,
              "Rect isn't nothrow copy assignable!");

static_assert(std::is_nothrow_move_assignable<Rect<float>>::value,
              "Rect isn't nothrow move assignable!");

static_assert(sizeof(Rect<int>) == sizeof(SDL_Rect),
              "Rect<int> has invalid size!");

static_assert(sizeof(Rect<float>) == sizeof(SDL_FRect),
              "Rect<float> has invalid size!");

using IRect = Rect<int>;
using FRect = Rect<float>;

}  // namespace centurion

#endif  // CENTURION_RECTANGLE_HEADER