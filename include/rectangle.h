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

#ifndef CENTURION_RECTANGLE_HEADER
#define CENTURION_RECTANGLE_HEADER

#include <SDL.h>

#include <string>
#include <type_traits>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "point.h"

namespace centurion {
namespace math {

template <typename T>
class Rect;

template <typename U>
constexpr bool operator==(const Rect<U>& lhs, const Rect<U>& rhs) noexcept;

template <typename U>
constexpr bool operator!=(const Rect<U>& lhs, const Rect<U>& rhs) noexcept;

/**
 * The Rect class represents a rectangle that supports integral and
 * floating-point components.
 *
 * <p>
 * <code>Rect&lt;int&gt;</code> and <code>Rect&lt;float&gt;</code> can safely
 * be casted to be pointers of their corresponding SDL types,
 * <code>SDL_Rect</code> and <code>SDL_FRect</code> respectively.
 *
 * @tparam T the type of the components of the rectangle. Set to float by
 * default.
 * @since 4.0.0
 */
template <typename T = float>
class Rect final {
 private:
  T x = 0;
  T y = 0;
  T width = 0;
  T height = 0;

 public:
  /**
   * Creates a rectangle with the components (0, 0, 0, 0).
   *
   * @since 4.0.0
   */
  constexpr Rect() noexcept = default;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @since 4.0.0
   */
  constexpr Rect(T x, T y, T width, T height) noexcept
      : x{x}, y{y}, width{width}, height{height}
  {}

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param rx the new x-coordinate of the rectangle.
   * @since 4.0.0
   */
  constexpr void set_x(T rx) noexcept { x = rx; }

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param ry the new y-coordinate of the rectangle.
   * @since 4.0.0
   */
  constexpr void set_y(T ry) noexcept { y = ry; }

  /**
   * Sets the width of the rectangle.
   *
   * @param rwidth the new width of the rectangle.
   * @since 4.0.0
   */
  constexpr void set_width(T rwidth) noexcept { width = rwidth; }

  /**
   * Sets the height of the rectangle.
   *
   * @param rheight the new height of the rectangle.
   * @since 4.0.0
   */
  constexpr void set_height(T rheight) noexcept { height = rheight; }

  /**
   * Sets all of the components of the rectangle.
   *
   * @param rx the new x-coordinate of the rectangle.
   * @param ry the new y-coordinate of the rectangle.
   * @param rwidth the new width of the rectangle.
   * @param rheight the new height of the rectangle.
   * @since 4.0.0
   */
  constexpr void set(T rx, T ry, T rwidth, T rheight) noexcept
  {
    x = rx;
    y = ry;
    width = rwidth;
    height = rheight;
  }

  /**
   * Copies all of the components of the supplied rectangle to the invoked
   * rectangle. The rectangles will be equal after this operation.
   *
   * @param other the rectangle that will be copied.
   * @since 4.0.0
   */
  constexpr void set(const Rect<T>& other) noexcept
  {
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
  }

  /**
   * Indicates whether or not this rectangle intersects the supplied rectangle.
   *
   * @param other the other rectangle to check.
   * @return true if the rectangles intersect; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr bool intersects(const Rect<T>& other) const noexcept
  {
    return !(x >= other.get_max_x() || get_max_x() <= other.x ||
             y >= other.get_max_y() || get_max_y() <= other.y);
  }

  /**
   * Indicates whether or not the supplied point is contained within the
   * rectangle.
   *
   * @param px the x-coordinate of the point.
   * @param py the y-coordinate of the point.
   * @return true if the supplied point is inside the rectangle; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr bool contains(T px, T py) const noexcept
  {
    return !(px < x || py < y || px > get_max_x() || py > get_max_y());
  }

  /**
   * Indicates whether or not the supplied point is contained within the
   * rectangle.
   *
   * @param point the point that will be checked.
   * @return true if the supplied point is inside the rectangle; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr bool contains(Point<T> point) const noexcept
  {
    return contains(point.get_x(), point.get_y());
  }

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_x() const noexcept { return x; }

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_y() const noexcept { return y; }

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_width() const noexcept { return width; }

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_height() const noexcept { return height; }

  /**
   * Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_max_x() const noexcept { return x + width; }

  /**
   * Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_max_y() const noexcept { return y + height; }

  /**
   * Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_center_x() const noexcept { return x + (width / 2); }

  /**
   * Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr T get_center_y() const noexcept { return y + (height / 2); }

  /**
   * Returns the center point of the rectangle.
   *
   * @return the center point of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr Point<T> get_center() const noexcept
  {
    return {get_center_x(), get_center_y()};
  }

  /**
   * Indicates whether or not the rectangle has an area. A rectangle has an
   * area if the width and height are both greater than zero.
   *
   * @return true if the rectangle has an area; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  constexpr bool has_area() const noexcept { return width > 0 && height > 0; }

  /**
   * Calculates and returns a rectangle that represents the union of two
   * rectangles. This method is only available if the rectangle is based on
   * <code>int</code>.
   *
   *
   * @return a rectangle that represents the union of the rectangles.
   * @since 4.0.0
   */
  template <typename U = T, typename = type_if_same<U, int>>
  CENTURION_NODISCARD Rect<T> get_union(const Rect<T>& other) const noexcept
  {
    SDL_Rect result{0, 0, 0, 0};

    const auto* a = static_cast<const SDL_Rect*>(*this);
    const auto* b = static_cast<const SDL_Rect*>(other);

    SDL_UnionRect(a, b, &result);
    return {result.x, result.y, result.w, result.h};
  }

  /**
   * Returns a textual representation of the rectangle.
   *
   * @return a textual representation of the rectangle.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  std::string to_string() const
  {
    const auto sx = std::to_string(x);
    const auto sy = std::to_string(y);
    const auto sw = std::to_string(width);
    const auto sh = std::to_string(height);
    return "[Rect | X: " + sx + ", Y: " + sy + ", Width: " + sw +
           ", Height: " + sh + "]";
  }

  /**
   * Converts the rectangle to a pointer to an SDL_Rect. This conversion is
   * only available if the rectangle is based on <code>int</code>.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   * @return an SDL_Rect pointer that is produced by reinterpreting the
   * invoked rectangle.
   * @since 4.0.0
   */
  template <typename U = T, typename = type_if_same<U, int>>
  CENTURION_NODISCARD explicit operator SDL_Rect*() noexcept
  {
    return reinterpret_cast<SDL_Rect*>(this);
  }

  /**
   * Converts the rectangle to a pointer to an SDL_Rect. This conversion is
   * only available if the rectangle is based on <code>int</code>.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   * @return an SDL_Rect pointer that is produced by reinterpreting the
   * invoked rectangle.
   * @since 4.0.0
   */
  template <typename U = T, typename = type_if_same<U, int>>
  CENTURION_NODISCARD explicit operator const SDL_Rect*() const noexcept
  {
    return reinterpret_cast<const SDL_Rect*>(this);
  }

  /**
   * Converts the rectangle to a pointer to an SDL_FRect. This conversion is
   * only available if the rectangle is based on <code>float</code>.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   * @return an SDL_FRect pointer that is produced by reinterpreting the
   * invoked rectangle.
   * @since 4.0.0
   */
  template <typename U = T, typename = type_if_same<U, float>>
  CENTURION_NODISCARD explicit operator SDL_FRect*() noexcept
  {
    return reinterpret_cast<SDL_FRect*>(this);
  }

  /**
   * Converts the rectangle to a pointer to an SDL_FRect. This conversion is
   * only available if the rectangle is based on <code>float</code>.
   *
   * @tparam U the type parameter, defaults to the type of the rectangle
   * components.
   * @return an SDL_FRect pointer that is produced by reinterpreting the
   * invoked rectangle.
   * @since 4.0.0
   */
  template <typename U = T, typename = type_if_same<U, float>>
  CENTURION_NODISCARD explicit operator const SDL_FRect*() const noexcept
  {
    return reinterpret_cast<const SDL_FRect*>(this);
  }

  /**
   * Indicates whether or not two rectangles are equal.
   *
   * @param lhs the left-hand side rectangle.
   * @param rhs the right-hand side rectangle.
   * @return true if the rectangles are equal; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend bool operator==<T>(const Rect<T>& lhs, const Rect<T>& rhs) noexcept;

  /**
   * Indicates whether or not two rectangles aren't equal.
   *
   * @param lhs the left-hand side rectangle.
   * @param rhs the right-hand side rectangle.
   * @return true if the rectangles aren't equal; false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  friend bool operator!=<T>(const Rect<T>& lhs, const Rect<T>& rhs) noexcept;

  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                "Rect type must be either integral or floating-point!");

  static_assert(std::is_trivial<T>::value, "Rect type must be trivial!");
};

template <typename T>
inline constexpr bool operator==(const Rect<T>& lhs,
                                 const Rect<T>& rhs) noexcept
{
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width &&
         lhs.height == rhs.height;
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

}  // namespace math
}  // namespace centurion

#endif  // CENTURION_RECTANGLE_HEADER