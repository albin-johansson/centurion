/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_MATH_HPP_
#define CENTURION_MATH_HPP_

#include <SDL.h>

#include <cmath>        // sqrt, pow, round
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "common.hpp"
#include "detail/sdl_version_at_least.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
struct basic_vector3;

using ivec3 = basic_vector3<int>;
using fvec3 = basic_vector3<float>;

template <typename T>
struct basic_vector3 final
{
  static_assert(is_number<T>);

  using value_type = T;

  value_type x{};
  value_type y{};
  value_type z{};

  template <typename U>
  [[nodiscard]] explicit operator basic_vector3<U>() const noexcept
  {
    using target_value_type = typename basic_vector3<U>::value_type;
    return basic_vector3<U>{static_cast<target_value_type>(x),
                            static_cast<target_value_type>(y),
                            static_cast<target_value_type>(z)};
  }
};

template <typename Archive, typename T>
void serialize(Archive& archive, basic_vector3<T>& vector)
{
  archive(vector.x, vector.y, vector.z);
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_vector3<T>& a,
                                        const basic_vector3<T>& b) noexcept -> bool
{
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_vector3<T>& a,
                                        const basic_vector3<T>& b) noexcept -> bool
{
  return !(a == b);
}

template <typename T>
[[nodiscard]] auto to_string(const basic_vector3<T>& vector) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("(x: {}, y: {}, z: {})", vector.x, vector.y, vector.z);
#else
  return "(x: " + std::to_string(vector.x) + ", y: " + std::to_string(vector.y) +
         ", z: " + std::to_string(vector.z) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_vector3<T>& vector) -> std::ostream&
{
  return stream << to_string(vector);
}

template <typename T>
struct basic_area;

using iarea = basic_area<int>;
using farea = basic_area<float>;

/**
 * Represents an area with a width and height.
 *
 * \see iarea
 * \see farea
 */
template <typename T>
struct basic_area final
{
  static_assert(is_number<T>);

  using value_type = T;

  value_type width{};
  value_type height{};

  template <typename TT = T, std::enable_if_t<std::is_integral_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_f() const noexcept -> farea
  {
    return {static_cast<farea::value_type>(width), static_cast<farea::value_type>(height)};
  }

  template <typename TT = T, std::enable_if_t<std::is_floating_point_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_i() const noexcept -> iarea
  {
    return {static_cast<iarea::value_type>(width), static_cast<iarea::value_type>(height)};
  }
};

template <typename Archive, typename T>
void serialize(Archive& archive, basic_area<T>& area)
{
  archive(area.width, area.height);
}

template <typename T>
[[nodiscard]] constexpr auto area_of(const basic_area<T> area) noexcept -> T
{
  return area.width * area.height;
}

template <>
[[nodiscard]] constexpr auto cast(const iarea& from) noexcept -> farea
{
  return {static_cast<float>(from.width), static_cast<float>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const farea& from) noexcept -> iarea
{
  return {static_cast<int>(from.width), static_cast<int>(from.height)};
}

template <typename T>
[[nodiscard]] auto to_string(const basic_area<T>& area) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("area(width: {}, height: {})", area.width, area.height);
#else
  return "area(width: " + std::to_string(area.width) +
         ", height: " + std::to_string(area.height) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_area<T>& area) -> std::ostream&
{
  return stream << to_string(area);
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_area<T>& a,
                                        const basic_area<T>& b) noexcept -> bool
{
  return a.width == b.width && a.height == b.height;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_area<T>& a,
                                        const basic_area<T>& b) noexcept -> bool
{
  return !(a == b);
}

template <typename T, enable_for_convertible_t<T, int, float> = 0>
class point_traits final
{
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, SDL_Point, SDL_FPoint>;
};

template <typename T>
class basic_point;

using ipoint = basic_point<int>;
using fpoint = basic_point<float>;

/**
 * Represents a two-dimensional point.
 *
 * This class is a wrapper for either `SDL_Point` or `SDL_FPoint`.
 *
 * \tparam T the component type.
 *
 * \see ipoint
 * \see fpoint
 */
template <typename T>
class basic_point final
{
 public:
  inline constexpr static bool integral = point_traits<T>::integral;
  inline constexpr static bool floating = point_traits<T>::floating;

  using value_type = typename point_traits<T>::value_type;
  using point_type = typename point_traits<T>::point_type;

  constexpr basic_point() noexcept = default;

  constexpr basic_point(const value_type x, const value_type y) noexcept : mPoint{x, y} {}

  constexpr explicit basic_point(const point_type point) noexcept : mPoint{point} {}

  constexpr void set_x(const value_type x) noexcept { mPoint.x = x; }
  constexpr void set_y(const value_type y) noexcept { mPoint.y = y; }

  [[nodiscard]] constexpr auto x() const noexcept -> value_type { return mPoint.x; }
  [[nodiscard]] constexpr auto y() const noexcept -> value_type { return mPoint.y; }

  [[nodiscard]] constexpr auto get() noexcept -> point_type& { return mPoint; }
  [[nodiscard]] constexpr auto get() const noexcept -> const point_type& { return mPoint; }

  template <typename TT = T, std::enable_if_t<std::is_integral_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_f() const noexcept -> fpoint
  {
    return {static_cast<fpoint::value_type>(mPoint.x),
            static_cast<fpoint::value_type>(mPoint.y)};
  }

  template <typename TT = T, std::enable_if_t<std::is_floating_point_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_i() const noexcept -> ipoint
  {
    return {static_cast<ipoint::value_type>(mPoint.x),
            static_cast<ipoint::value_type>(mPoint.y)};
  }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mPoint.x, mPoint.y);
  }

  [[nodiscard]] auto data() noexcept -> point_type* { return &mPoint; }

  [[nodiscard]] auto data() const noexcept -> const point_type* { return &mPoint; }

 private:
  point_type mPoint{};
};

template <typename T>
[[nodiscard]] auto distance(const basic_point<T>& from, const basic_point<T>& to) noexcept ->
    typename basic_point<T>::value_type
{
  const auto distance =
      std::sqrt(std::pow(from.x() - to.x(), T{2}) + std::pow(from.y() - to.y(), T{2}));
  if constexpr (basic_point<T>::integral) {
    return static_cast<int>(std::round(distance));
  }
  else {
    return distance;
  }
}

template <>
[[nodiscard]] constexpr auto cast(const fpoint& from) noexcept -> ipoint
{
  const auto x = static_cast<int>(from.x());
  const auto y = static_cast<int>(from.y());
  return ipoint{x, y};
}

template <>
[[nodiscard]] constexpr auto cast(const ipoint& from) noexcept -> fpoint
{
  const auto x = static_cast<float>(from.x());
  const auto y = static_cast<float>(from.y());
  return fpoint{x, y};
}

template <>
[[nodiscard]] constexpr auto cast(const SDL_FPoint& from) noexcept -> SDL_Point
{
  const auto x = static_cast<int>(from.x);
  const auto y = static_cast<int>(from.y);
  return SDL_Point{x, y};
}

template <>
[[nodiscard]] constexpr auto cast(const SDL_Point& from) noexcept -> SDL_FPoint
{
  const auto x = static_cast<float>(from.x);
  const auto y = static_cast<float>(from.y);
  return SDL_FPoint{x, y};
}

template <typename T>
[[nodiscard]] auto to_string(const basic_point<T>& point) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("(x: {}, y: {})", point.x(), point.y());
#else
  return "(x: " + std::to_string(point.x()) + ", y: " + std::to_string(point.y()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_point<T>& point) -> std::ostream&
{
  return stream << to_string(point);
}

template <typename T>
[[nodiscard]] constexpr auto operator+(const basic_point<T>& a,
                                       const basic_point<T>& b) noexcept -> basic_point<T>
{
  return {a.x() + b.x(), a.y() + b.y()};
}

template <typename T>
[[nodiscard]] constexpr auto operator-(const basic_point<T>& a,
                                       const basic_point<T>& b) noexcept -> basic_point<T>
{
  return {a.x() - b.x(), a.y() - b.y()};
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_point<T> a,
                                        const basic_point<T> b) noexcept -> bool
{
  return a.x() == b.x() && a.y() == b.y();
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_point<T> a,
                                        const basic_point<T> b) noexcept -> bool
{
  return !(a == b);
}

template <typename T, enable_for_convertible_t<T, int, float> = 0>
class rect_traits final
{
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, ipoint, fpoint>;
  using area_type = std::conditional_t<integral, iarea, farea>;
  using rect_type = std::conditional_t<integral, SDL_Rect, SDL_FRect>;
};

template <typename T>
class basic_rect;

using irect = basic_rect<int>;
using frect = basic_rect<float>;

/**
 * A simple rectangle implementation, based on either `SDL_Rect` or `SDL_FRect`.
 *
 * \tparam T underlying value type, i.e. `int` or `float`.
 *
 * \see irect
 * \see frect
 */
template <typename T>
class basic_rect final
{
 public:
  inline constexpr static bool integral = rect_traits<T>::integral;
  inline constexpr static bool floating = rect_traits<T>::floating;

  using value_type = typename rect_traits<T>::value_type;
  using point_type = typename rect_traits<T>::point_type;
  using area_type = typename rect_traits<T>::area_type;
  using rect_type = typename rect_traits<T>::rect_type;

  constexpr basic_rect() noexcept = default;

  constexpr basic_rect(const value_type x,
                       const value_type y,
                       const value_type width,
                       const value_type height) noexcept
      : mRect{x, y, width, height}
  {}

  constexpr basic_rect(const point_type& position, const area_type& size) noexcept
      : mRect{position.x(), position.y(), size.width, size.height}
  {}

  constexpr explicit basic_rect(const rect_type& rect) noexcept : mRect{rect} {}

  constexpr void set_x(const value_type x) noexcept { mRect.x = x; }
  constexpr void set_y(const value_type y) noexcept { mRect.y = y; }

  constexpr void set_position(const value_type x, const value_type y) noexcept
  {
    mRect.x = x;
    mRect.y = y;
  }

  constexpr void set_position(const point_type& pos) noexcept
  {
    set_position(pos.x(), pos.y());
  }

  constexpr void set_width(const value_type width) noexcept { mRect.w = width; }
  constexpr void set_height(const value_type height) noexcept { mRect.h = height; }

  constexpr void set_size(const value_type width, const value_type height) noexcept
  {
    mRect.w = width;
    mRect.h = height;
  }

  constexpr void set_size(const area_type& size) noexcept
  {
    set_size(size.width, size.height);
  }

  constexpr void set_max_x(const value_type mx) noexcept { mRect.x = mx - mRect.w; }
  constexpr void set_max_y(const value_type my) noexcept { mRect.y = my - mRect.h; }

  constexpr void offset_x(const value_type dx) noexcept { mRect.x += dx; }
  constexpr void offset_y(const value_type dy) noexcept { mRect.y += dy; }

  constexpr void offset_width(const value_type dw) noexcept { mRect.w += dw; }
  constexpr void offset_height(const value_type dh) noexcept { mRect.h += dh; }

  [[nodiscard]] constexpr auto x() const noexcept -> value_type { return mRect.x; }
  [[nodiscard]] constexpr auto y() const noexcept -> value_type { return mRect.y; }

  [[nodiscard]] constexpr auto position() const noexcept -> point_type
  {
    return {mRect.x, mRect.y};
  }

  [[nodiscard]] constexpr auto width() const noexcept -> value_type { return mRect.w; }
  [[nodiscard]] constexpr auto height() const noexcept -> value_type { return mRect.h; }

  [[nodiscard]] constexpr auto size() const noexcept -> area_type
  {
    return {mRect.w, mRect.h};
  }

  [[nodiscard]] constexpr auto max_x() const noexcept -> value_type { return x() + width(); }
  [[nodiscard]] constexpr auto max_y() const noexcept -> value_type { return y() + height(); }

  [[nodiscard]] constexpr auto has_area() const noexcept -> bool
  {
    return (width() > 0) && (height() > 0);
  }

  [[nodiscard]] constexpr auto area() const noexcept -> value_type
  {
    return width() * height();
  }

  [[nodiscard]] constexpr auto center_x() const noexcept -> value_type
  {
    return x() + (width() / value_type{2});
  }

  [[nodiscard]] constexpr auto center_y() const noexcept -> value_type
  {
    return y() + (height() / value_type{2});
  }

  [[nodiscard]] constexpr auto center() const noexcept -> point_type
  {
    return {center_x(), center_y()};
  }

  [[nodiscard]] constexpr auto contains(const value_type px,
                                        const value_type py) const noexcept -> bool
  {
    return !(px < x() || py < y() || px > max_x() || py > max_y());
  }

  [[nodiscard]] constexpr auto contains(const point_type& point) const noexcept -> bool
  {
    return contains(point.x(), point.y());
  }

  template <typename TT = T, std::enable_if_t<std::is_integral_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_f() const noexcept -> frect
  {
    return {static_cast<frect::value_type>(mRect.x),
            static_cast<frect::value_type>(mRect.y),
            static_cast<frect::value_type>(mRect.w),
            static_cast<frect::value_type>(mRect.h)};
  }

  template <typename TT = T, std::enable_if_t<std::is_floating_point_v<TT>, int> = 0>
  [[nodiscard]] constexpr auto as_i() const noexcept -> irect
  {
    return {static_cast<irect::value_type>(mRect.x),
            static_cast<irect::value_type>(mRect.y),
            static_cast<irect::value_type>(mRect.w),
            static_cast<irect::value_type>(mRect.h)};
  }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mRect.x, mRect.y, mRect.w, mRect.h);
  }

  [[nodiscard]] auto data() noexcept -> rect_type* { return &mRect; }
  [[nodiscard]] auto data() const noexcept -> const rect_type* { return &mRect; }

  [[nodiscard]] constexpr auto get() noexcept -> rect_type& { return mRect; }
  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type& { return mRect; }

 private:
  rect_type mRect{0, 0, 0, 0};
};

/**
 * Indicates whether two rectangles intersect.
 *
 * This function does not consider rectangles with overlapping borders as intersecting. If you
 * want such behaviour, see the overlaps() function.
 *
 * \param a the first rectangle.
 * \param b the second rectangle.
 *
 * \return `true` if the rectangles intersect; `false` otherwise.
 */
template <typename T>
[[nodiscard]] constexpr auto intersects(const basic_rect<T>& a,
                                        const basic_rect<T>& b) noexcept -> bool
{
  return !(a.x() >= b.max_x() || a.y() >= b.max_y() || a.max_x() <= b.x() ||
           a.max_y() <= b.y());
}

/**
 * Indicates whether or not two rectangles are overlapping.
 *
 * This function differs from intersects() in that this function includes overlapping borders.
 *
 * \param a the first rectangle.
 * \param b the second rectangle.
 *
 * \return `true` if the rectangles overlap; `false` otherwise.
 */
template <typename T>
[[nodiscard]] constexpr auto overlaps(const basic_rect<T>& a, const basic_rect<T>& b) noexcept
    -> bool
{
  return !(a.x() > b.max_x() || a.y() > b.max_y() || a.max_x() < b.x() || a.max_y() < b.y());
}

template <typename T>
[[nodiscard]] constexpr auto get_union(const basic_rect<T>& a, const basic_rect<T>& b) noexcept
    -> basic_rect<T>
{
  if constexpr (detail::sdl_version_at_least(2, 0, 22)) {
    if constexpr (basic_rect<T>::floating) {
      cen::frect res;
      SDL_UnionFRect(a.data(), b.data(), res.data());
      return res;
    }
    else {
      cen::irect res;
      SDL_UnionRect(a.data(), b.data(), res.data());
      return res;
    }
  }
  else {
    const auto aHasArea = a.has_area();
    const auto bHasArea = b.has_area();

    if (!aHasArea && !bHasArea) {
      return {};
    }
    else if (!aHasArea) {
      return b;
    }
    else if (!bHasArea) {
      return a;
    }

    const auto x = detail::min(a.x(), b.x());
    const auto y = detail::min(a.y(), b.y());
    const auto maxX = detail::max(a.max_x(), b.max_x());
    const auto maxY = detail::max(a.max_y(), b.max_y());

    return {{x, y}, {maxX - x, maxY - y}};
  }
}

template <>
[[nodiscard]] constexpr auto cast(const irect& from) noexcept -> frect
{
  const frect::point_type pos{static_cast<float>(from.x()), static_cast<float>(from.y())};
  const frect::area_type size{static_cast<float>(from.width()),
                              static_cast<float>(from.height())};
  return frect{pos, size};
}

template <>
[[nodiscard]] constexpr auto cast(const frect& from) noexcept -> irect
{
  const irect::point_type pos{static_cast<int>(from.x()), static_cast<int>(from.y())};
  const irect::area_type size{static_cast<int>(from.width()), static_cast<int>(from.height())};
  return irect{pos, size};
}

template <typename T>
[[nodiscard]] auto to_string(const basic_rect<T>& rect) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("(x: {}, y: {}, width: {}, height: {})",
                     rect.x(),
                     rect.y(),
                     rect.width(),
                     rect.height());
#else
  return "(x: " + std::to_string(rect.x()) + ", y: " + std::to_string(rect.y()) +
         ", width: " + std::to_string(rect.width()) +
         ", height: " + std::to_string(rect.height()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_rect<T>& rect) -> std::ostream&
{
  return stream << to_string(rect);
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_rect<T>& a,
                                        const basic_rect<T>& b) noexcept -> bool
{
  return a.x() == b.x() && a.y() == b.y() && a.width() == b.width() &&
         a.height() == b.height();
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_rect<T>& a,
                                        const basic_rect<T>& b) noexcept -> bool
{
  return !(a == b);
}

}  // namespace cen

#endif  // CENTURION_MATH_HPP_
