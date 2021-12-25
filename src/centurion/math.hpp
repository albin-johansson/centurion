#ifndef CENTURION_MATH_HPP_
#define CENTURION_MATH_HPP_

#include <SDL.h>

#include <cmath>        // sqrt, abs, round
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "common.hpp"
#include "features.hpp"
#include "detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
struct BasicVector3;

template <typename T>
struct BasicArea;

template <typename T>
class BasicPoint;

template <typename T>
class BasicRect;

using Vector3 = BasicVector3<int>;
using FVector3 = BasicVector3<float>;

using Area = BasicArea<int>;
using FArea = BasicArea<float>;

using Point = BasicPoint<int>;
using FPoint = BasicPoint<float>;

using Rect = BasicRect<int>;
using FRect = BasicRect<float>;

template <typename T>
struct BasicVector3 final {
  static_assert(is_number<T>);

  using value_type = T;

  value_type x{};
  value_type y{};
  value_type z{};

  template <typename U>
  [[nodiscard]] explicit operator BasicVector3<U>() const noexcept
  {
    using target_value_type = typename BasicVector3<U>::value_type;
    return BasicVector3<U>{static_cast<target_value_type>(x),
                           static_cast<target_value_type>(y),
                           static_cast<target_value_type>(z)};
  }
};

template <typename T>
struct BasicArea final {
  static_assert(is_number<T>);

  using value_type = T;

  value_type width{};
  value_type height{};
};

template <typename T, RequireConvertible<T, int, float> = 0>
class PointTraits final {
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, SDL_Point, SDL_FPoint>;
};

template <typename T>
class BasicPoint final {
 public:
  inline constexpr static bool integral = PointTraits<T>::integral;
  inline constexpr static bool floating = PointTraits<T>::floating;

  using value_type = typename PointTraits<T>::value_type;
  using point_type = typename PointTraits<T>::point_type;

  constexpr BasicPoint() noexcept = default;

  constexpr BasicPoint(const value_type x, const value_type y) noexcept : mPoint{x, y} {}

  constexpr explicit BasicPoint(const point_type point) noexcept : mPoint{point} {}

  constexpr void SetX(const value_type x) noexcept { mPoint.x = x; }
  constexpr void SetY(const value_type y) noexcept { mPoint.y = y; }

  [[nodiscard]] constexpr auto GetX() const noexcept -> value_type { return mPoint.x; }
  [[nodiscard]] constexpr auto GetY() const noexcept -> value_type { return mPoint.y; }

  [[nodiscard]] constexpr auto get() noexcept -> point_type& { return mPoint; }
  [[nodiscard]] constexpr auto get() const noexcept -> const point_type& { return mPoint; }

  [[nodiscard]] auto data() noexcept -> point_type* { return &mPoint; }
  [[nodiscard]] auto data() const noexcept -> const point_type* { return &mPoint; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mPoint.x, mPoint.y);
  }

 private:
  point_type mPoint{};
};

template <typename T, RequireConvertible<T, int, float> = 0>
class RectTraits final {
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, Point, FPoint>;
  using area_type = std::conditional_t<integral, Area, FArea>;
  using rect_type = std::conditional_t<integral, SDL_Rect, SDL_FRect>;
};

template <typename T>
class BasicRect final {
 public:
  inline constexpr static bool integral = RectTraits<T>::integral;
  inline constexpr static bool floating = RectTraits<T>::floating;

  using value_type = typename RectTraits<T>::value_type;
  using point_type = typename RectTraits<T>::point_type;
  using area_type = typename RectTraits<T>::area_type;
  using rect_type = typename RectTraits<T>::rect_type;

  constexpr BasicRect() noexcept = default;

  constexpr BasicRect(const value_type x,
                      const value_type y,
                      const value_type width,
                      const value_type height) noexcept
      : mRect{x, y, width, height}
  {}

  constexpr BasicRect(const point_type& position, const area_type& size) noexcept
      : mRect{position.GetX(), position.GetY(), size.width, size.height}
  {}

  constexpr explicit BasicRect(const rect_type& rect) noexcept : mRect{rect} {}

  constexpr void SetX(const value_type x) noexcept { mRect.x = x; }
  constexpr void SetY(const value_type y) noexcept { mRect.y = y; }

  constexpr void SetMaxX(const value_type maxX) noexcept { mRect.x = maxX - mRect.w; }
  constexpr void SetMaxY(const value_type maxY) noexcept { mRect.y = maxY - mRect.h; }

  constexpr void OffsetX(const value_type offset) noexcept { mRect.x += offset; }
  constexpr void OffsetY(const value_type offset) noexcept { mRect.y += offset; }
  constexpr void OffsetWidth(const value_type offset) noexcept { mRect.w += offset; }
  constexpr void OffsetHeight(const value_type offset) noexcept { mRect.h += offset; }

  constexpr void SetPosition(const value_type x, const value_type y) noexcept
  {
    mRect.x = x;
    mRect.y = y;
  }

  constexpr void SetPosition(const point_type& pos) noexcept
  {
    SetPosition(pos.GetX(), pos.GetY());
  }

  constexpr void SetWidth(const value_type width) noexcept { mRect.w = width; }
  constexpr void SetHeight(const value_type height) noexcept { mRect.h = height; }

  constexpr void SetSize(const value_type width, const value_type height) noexcept
  {
    mRect.w = width;
    mRect.h = height;
  }

  constexpr void SetSize(const area_type& size) noexcept { SetSize(size.width, size.height); }

  [[nodiscard]] constexpr auto GetX() const noexcept -> value_type { return mRect.x; }
  [[nodiscard]] constexpr auto GetY() const noexcept -> value_type { return mRect.y; }

  [[nodiscard]] constexpr auto GetPosition() const noexcept -> point_type
  {
    return point_type{mRect.x, mRect.y};
  }

  [[nodiscard]] constexpr auto GetWidth() const noexcept -> value_type { return mRect.w; }
  [[nodiscard]] constexpr auto GetHeight() const noexcept -> value_type { return mRect.h; }

  [[nodiscard]] constexpr auto GetSize() const noexcept -> area_type
  {
    return area_type{mRect.w, mRect.h};
  }

  [[nodiscard]] constexpr auto GetMaxX() const noexcept -> value_type
  {
    return GetX() + GetWidth();
  }

  [[nodiscard]] constexpr auto GetMaxY() const noexcept -> value_type
  {
    return GetY() + GetHeight();
  }

  [[nodiscard]] constexpr auto GetCenterX() const noexcept -> value_type
  {
    return GetX() + (GetWidth() / value_type{2});
  }

  [[nodiscard]] constexpr auto GetCenterY() const noexcept -> value_type
  {
    return GetY() + (GetHeight() / value_type{2});
  }

  [[nodiscard]] constexpr auto GetCenter() const noexcept -> point_type
  {
    return {GetCenterX(), GetCenterY()};
  }

  [[nodiscard]] constexpr auto GetArea() const noexcept -> value_type
  {
    return GetWidth() * GetHeight();
  }

  [[nodiscard]] constexpr auto Contains(const point_type& point) const noexcept -> bool
  {
    const auto x = point.GetX();
    const auto y = point.GetY();
    return !(x < GetX() || y < GetY() || x > GetMaxX() || y > GetMaxY());
  }

  [[nodiscard]] constexpr auto HasArea() const noexcept -> bool
  {
    return (GetWidth() > 0) && (GetHeight() > 0);
  }

  [[nodiscard]] auto data() noexcept -> rect_type* { return &mRect; }
  [[nodiscard]] auto data() const noexcept -> const rect_type* { return &mRect; }

  [[nodiscard]] constexpr auto get() noexcept -> rect_type& { return mRect; }
  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type& { return mRect; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mRect.x, mRect.y, mRect.w, mRect.h);
  }

 private:
  rect_type mRect{0, 0, 0, 0};
};

template <typename T>
[[nodiscard]] constexpr auto AreaOf(const BasicArea<T> area) noexcept -> T
{
  return area.width * area.height;
}

/* Returns the distance between two points. */
template <typename T>
[[nodiscard]] auto GetDistance(const BasicPoint<T> from, const BasicPoint<T> to) noexcept ->
    typename BasicPoint<T>::value_type
{
  const auto distance =
      std::sqrt(std::abs(from.GetX() - to.GetX()) + std::abs(from.GetY() - to.GetY()));
  if constexpr (BasicPoint<T>::integral) {
    return static_cast<int>(std::round(distance));
  }
  else {
    return distance;
  }
}

/* Indicates whether two rectangles intersect, does not include overlapping borders. */
template <typename T>
[[nodiscard]] constexpr auto Intersects(const BasicRect<T>& a, const BasicRect<T>& b) noexcept
    -> bool
{
  return !(a.GetX() >= b.GetMaxX() || a.GetY() >= b.GetMaxY() || a.GetMaxX() <= b.GetX() ||
           a.GetMaxY() <= b.GetY());
}

/* Indicates whether two rectangles intersect, includes overlapping borders. */
template <typename T>
[[nodiscard]] constexpr auto Overlaps(const BasicRect<T>& a, const BasicRect<T>& b) noexcept
    -> bool
{
  return !(a.GetX() > b.GetMaxX() || a.GetY() > b.GetMaxY() || a.GetMaxX() < b.GetX() ||
           a.GetMaxY() < b.GetY());
}

/* Returns the union of two rectangles. */
template <typename T>
[[nodiscard]] constexpr auto Union(const BasicRect<T>& a, const BasicRect<T>& b) noexcept
    -> BasicRect<T>
{
  const auto aHasArea = a.HasArea();
  const auto bHasArea = b.HasArea();

  if (!aHasArea && !bHasArea) {
    return {};
  }
  else if (!aHasArea) {
    return b;
  }
  else if (!bHasArea) {
    return a;
  }

  const auto x = detail::min(a.GetX(), b.GetX());
  const auto y = detail::min(a.GetY(), b.GetY());
  const auto maxX = detail::max(a.GetMaxX(), b.GetMaxX());
  const auto maxY = detail::max(a.GetMaxY(), b.GetMaxY());

  return {{x, y}, {maxX - x, maxY - y}};
}

template <typename Archive, typename T>
void serialize(Archive& archive, BasicVector3<T>& vector)
{
  archive(vector.x, vector.y, vector.z);
}

template <typename Archive, typename T>
void serialize(Archive& archive, BasicArea<T>& area)
{
  archive(area.width, area.height);
}

template <>
[[nodiscard]] constexpr auto cast(const Area& from) noexcept -> FArea
{
  return {static_cast<float>(from.width), static_cast<float>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const FArea& from) noexcept -> Area
{
  return {static_cast<int>(from.width), static_cast<int>(from.height)};
}

template <>
[[nodiscard]] constexpr auto cast(const FPoint& from) noexcept -> Point
{
  const auto x = static_cast<int>(from.GetX());
  const auto y = static_cast<int>(from.GetY());
  return Point{x, y};
}

template <>
[[nodiscard]] constexpr auto cast(const Point& from) noexcept -> FPoint
{
  const auto x = static_cast<float>(from.GetX());
  const auto y = static_cast<float>(from.GetY());
  return FPoint{x, y};
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

template <>
[[nodiscard]] constexpr auto cast(const Rect& from) noexcept -> FRect
{
  const FRect::point_type pos{static_cast<float>(from.GetX()),
                              static_cast<float>(from.GetY())};
  const FRect::area_type size{static_cast<float>(from.GetWidth()),
                              static_cast<float>(from.GetHeight())};
  return FRect{pos, size};
}

template <>
[[nodiscard]] constexpr auto cast(const FRect& from) noexcept -> Rect
{
  const Rect::point_type pos{static_cast<int>(from.GetX()), static_cast<int>(from.GetY())};
  const Rect::area_type size{static_cast<int>(from.GetWidth()),
                             static_cast<int>(from.GetHeight())};
  return Rect{pos, size};
}

template <typename T>
[[nodiscard]] auto to_string(const BasicVector3<T>& vector) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Vector3(x: {}, y: {}, z: {})", vector.x, vector.y, vector.z);
#else
  return "Vector3(x: " + std::to_string(vector.x) + ", y: " + std::to_string(vector.y) +
         ", z: " + std::to_string(vector.z) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
[[nodiscard]] auto to_string(const BasicArea<T>& area) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Area(width: {}, height: {})", area.width, area.height);
#else
  return "Area(width: " + std::to_string(area.width) +
         ", height: " + std::to_string(area.height) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

[[nodiscard]] inline auto to_string(const Point point) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Point(x: {}, y: {})", point.GetX(), point.GetY());
#else
  return "Point(x: " + std::to_string(point.GetX()) + ", y: " + std::to_string(point.GetY()) +
         ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

[[nodiscard]] inline auto to_string(const FPoint point) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("FPoint(x: {}, y: {})", point.GetX(), point.GetY());
#else
  return "FPoint(x: " + std::to_string(point.GetX()) + ", y: " + std::to_string(point.GetY()) +
         ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
[[nodiscard]] auto to_string(const BasicRect<T>& rect) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Rect(x: {}, y: {}, width: {}, height: {})",
                     rect.GetX(),
                     rect.GetY(),
                     rect.GetWidth(),
                     rect.GetHeight());
#else
  return "Rect(x: " + std::to_string(rect.GetX()) + ", y: " + std::to_string(rect.GetY()) +
         ", width: " + std::to_string(rect.GetWidth()) +
         ", height: " + std::to_string(rect.GetHeight()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const BasicVector3<T>& a,
                                        const BasicVector3<T>& b) noexcept -> bool
{
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const BasicVector3<T>& a,
                                        const BasicVector3<T>& b) noexcept -> bool
{
  return !(a == b);
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const BasicArea<T>& a, const BasicArea<T>& b) noexcept
    -> bool
{
  return a.width == b.width && a.height == b.height;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const BasicArea<T>& a, const BasicArea<T>& b) noexcept
    -> bool
{
  return !(a == b);
}

template <typename T>
[[nodiscard]] constexpr auto operator+(const BasicPoint<T>& a, const BasicPoint<T>& b) noexcept
    -> BasicPoint<T>
{
  return {a.GetX() + b.GetX(), a.GetY() + b.GetY()};
}

template <typename T>
[[nodiscard]] constexpr auto operator-(const BasicPoint<T>& a, const BasicPoint<T>& b) noexcept
    -> BasicPoint<T>
{
  return {a.GetX() - b.GetX(), a.GetY() - b.GetY()};
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const BasicPoint<T> a, const BasicPoint<T> b) noexcept
    -> bool
{
  return a.GetX() == b.GetX() && a.GetY() == b.GetY();
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const BasicPoint<T> a, const BasicPoint<T> b) noexcept
    -> bool
{
  return !(a == b);
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const BasicRect<T>& a, const BasicRect<T>& b) noexcept
    -> bool
{
  return a.GetX() == b.GetX() && a.GetY() == b.GetY() && a.GetWidth() == b.GetWidth() &&
         a.GetHeight() == b.GetHeight();
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const BasicRect<T>& a, const BasicRect<T>& b) noexcept
    -> bool
{
  return !(a == b);
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicVector3<T>& vector) -> std::ostream&
{
  return stream << to_string(vector);
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicArea<T>& area) -> std::ostream&
{
  return stream << to_string(area);
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicPoint<T>& point) -> std::ostream&
{
  return stream << to_string(point);
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicRect<T>& rect) -> std::ostream&
{
  return stream << to_string(rect);
}

}  // namespace cen

#endif  // CENTURION_MATH_HPP_
