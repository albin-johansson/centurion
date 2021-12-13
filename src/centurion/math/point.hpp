#ifndef CENTURION_MATH_POINT_HPP_
#define CENTURION_MATH_POINT_HPP_

#include <SDL.h>

#include <cmath>        // sqrt, abs, round
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "../core/common.hpp"
#include "../core/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup math
/// \{

template <typename T, enable_if_convertible_t<T, int, float> = 0>
class PointTraits final {
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, SDL_Point, SDL_FPoint>;
};

template <typename T>
class BasicPoint;

using Point = BasicPoint<int>;
using FPoint = BasicPoint<float>;

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

/* Returns the distance between two points. */
template <typename T>
[[nodiscard]] auto GetDistance(const BasicPoint<T> from, const BasicPoint<T> to) noexcept ->
    typename BasicPoint<T>::value_type
{
  if constexpr (BasicPoint<T>::integral) {
    const auto xDiff = std::abs(from.GetX() - to.GetX());
    const auto yDiff = std::abs(from.GetY() - to.GetY());
    const auto dist = std::sqrt(xDiff + yDiff);
    return static_cast<int>(std::round(dist));
  }
  else {
    return std::sqrt(std::abs(from.GetX() - to.GetX()) + std::abs(from.GetY() - to.GetY()));
  }
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
auto operator<<(std::ostream& stream, const BasicPoint<T>& point) -> std::ostream&
{
  return stream << to_string(point);
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

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_MATH_POINT_HPP_