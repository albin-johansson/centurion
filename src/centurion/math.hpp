#ifndef CENTURION_MATH_HPP_
#define CENTURION_MATH_HPP_

#include <SDL.h>

#include <cmath>        // sqrt, pow, round
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "common.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup common
 * \defgroup math Math
 *
 * \brief Provides common math utilities such as points, areas, and rectangles.
 */

/// \addtogroup math
/// \{

template <typename T>
struct basic_vector3;

using ivec3 = basic_vector3<int>;
using fvec3 = basic_vector3<float>;

template <typename T>
struct basic_vector3 final {
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

/// \name Vector3 functions
/// \{

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
  return std::format("vector3(x: {}, y: {}, z: {})", vector.x, vector.y, vector.z);
#else
  return "vector3(x: " + std::to_string(vector.x) + ", y: " + std::to_string(vector.y) +
         ", z: " + std::to_string(vector.z) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_vector3<T>& vector) -> std::ostream&
{
  return stream << to_string(vector);
}

/// \} End of vector3 functions

template <typename T>
struct basic_area;

using iarea = basic_area<int>;    ///< An `int`-based area.
using farea = basic_area<float>;  ///< A `float`-based area.

/**
 * \brief Simply represents an area with a width and height.
 *
 * \serializable
 *
 * \see `iarea`
 * \see `farea`
 * \see `area_of()`
 */
template <typename T>
struct basic_area final {
  static_assert(is_number<T>);

  using value_type = T;

  value_type width{};
  value_type height{};
};

/// \name Area functions
/// \{

template <typename Archive, typename T>
void serialize(Archive& archive, basic_area<T>& area)
{
  archive(area.width, area.height);
}

/**
 * \brief Returns the size (width x height) of an area.
 *
 * \param area the area that will be used.
 *
 * \return the size of the area.
 */
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

/// \} End of area functions

/**
 * \brief Provides traits used by the `basic_point` class.
 *
 * \tparam T the representation type. Must be convertible to `int` or `float`.
 *
 * \see `basic_point`
 */
template <typename T, enable_for_convertible_t<T, int, float> = 0>
class point_traits final {
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, SDL_Point, SDL_FPoint>;
};

template <typename T>
class basic_point;

using ipoint = basic_point<int>;    ///< An `int`-based 2D point.
using fpoint = basic_point<float>;  ///< A `float`-based 2D point.

/**
 * \brief Represents a two-dimensional point.
 *
 * \details This class is a wrapper for either `SDL_Point` or `SDL_FPoint`.
 *
 * \serializable
 *
 * \tparam T the representation type.
 *
 * \see `ipoint`
 * \see `fpoint`
 *
 * \see `distance(const basic_point&, const basic_point&)`
 */
template <typename T>
class basic_point final {
 public:
  inline constexpr static bool integral = point_traits<T>::integral;
  inline constexpr static bool floating = point_traits<T>::floating;

  using value_type = typename point_traits<T>::value_type;
  using point_type = typename point_traits<T>::point_type;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a zero-initialized point.
   */
  constexpr basic_point() noexcept = default;

  /**
   * \brief Creates a point with the specified coordinates.
   *
   * \param x the x-coordinate that will be used.
   * \param y the y-coordinate that will be used.
   */
  constexpr basic_point(const value_type x, const value_type y) noexcept : mPoint{x, y} {}

  /**
   * \brief Copies an SDL point.
   *
   * \param point the point that will be copied.
   */
  constexpr explicit basic_point(const point_type point) noexcept : mPoint{point} {}

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets the x-coordinate of the point.
   *
   * \param x the new x-coordinate.
   */
  constexpr void set_x(const value_type x) noexcept { mPoint.x = x; }

  /**
   * \brief Sets the y-coordinate of the point.
   *
   * \param y the new y-coordinate.
   */
  constexpr void set_y(const value_type y) noexcept { mPoint.y = y; }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the x-coordinate of the point.
   *
   * \return the x-coordinate.
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type { return mPoint.x; }

  /**
   * \brief Returns the y-coordinate of the point.
   *
   * \return the y-coordinate.
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type { return mPoint.y; }

  [[nodiscard]] constexpr auto get() noexcept -> point_type& { return mPoint; }

  [[nodiscard]] constexpr auto get() const noexcept -> const point_type& { return mPoint; }

  /// \} End of getters

  /// \name Misc functions
  /// \{

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mPoint.x, mPoint.y);
  }

  [[nodiscard]] auto data() noexcept -> point_type* { return &mPoint; }

  [[nodiscard]] auto data() const noexcept -> const point_type* { return &mPoint; }

  /// \} End of misc functions

 private:
  point_type mPoint{};
};

/// \name Point functions
/// \{

/**
 * \brief Returns the distance between two points.
 *
 * \param from the start point.
 * \param to the end point.
 *
 * \return the euclidean distance between the points.
 */
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
  return std::format("point(x: {}, y: {})", point.x(), point.y());
#else
  return "point(x: " + std::to_string(point.x()) + ", y: " + std::to_string(point.y()) + ")";
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

/// \} End of point functions

/**
 * \brief Provides traits used by the `basic_rect` class.
 *
 * \note Whilst it is possible to supply a type that isn't `int` or `float`, rectangles will
 * always use one of them as the representation type.
 *
 * \tparam T the representation type, must be convertible to `int` or `float`.
 *
 * \see `basic_rect`
 */
template <typename T, enable_for_convertible_t<T, int, float> = 0>
class rect_traits final {
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

using irect = basic_rect<int>;    ///< A rectangle based on `SDL_Point`.
using frect = basic_rect<float>;  ///< A rectangle based on `SDL_FPoint`.

/**
 * \brief A simple rectangle implementation, based on either `SDL_Rect` or `SDL_FRect`.
 *
 * \serializable
 *
 * \tparam T underlying value type, i.e. `int` or `float`.
 *
 * \see `irect`
 * \see `frect`
 *
 * \see `intersects(const basic_rect&, const basic_rect&)`
 * \see `overlaps(const basic_rect&, const basic_rect&)`
 * \see `get_union(const basic_rect&, const basic_rect&)`
 */
template <typename T>
class basic_rect final {
 public:
  inline constexpr static bool integral = rect_traits<T>::integral;
  inline constexpr static bool floating = rect_traits<T>::floating;

  using value_type = typename rect_traits<T>::value_type;
  using point_type = typename rect_traits<T>::point_type;
  using area_type = typename rect_traits<T>::area_type;
  using rect_type = typename rect_traits<T>::rect_type;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a zero-initialized rectangle.
   */
  constexpr basic_rect() noexcept = default;

  /**
   * \brief Creates a rectangle with the supplied position and size.
   *
   * \param x the x-coordinate of the rectangle.
   * \param y the y-coordinate of the rectangle.
   * \param width the width of the rectangle.
   * \param height the height of the rectangle.
   */
  constexpr basic_rect(const value_type x,
                       const value_type y,
                       const value_type width,
                       const value_type height) noexcept
      : mRect{x, y, width, height}
  {}

  /**
   * \brief Creates a rectangle with the supplied position and size.
   *
   * \param position the position of the rectangle.
   * \param size the size of the rectangle.
   */
  constexpr basic_rect(const point_type& position, const area_type& size) noexcept
      : mRect{position.x(), position.y(), size.width, size.height}
  {}

  /**
   * \brief Copies an SDL rectangle.
   *
   * \param rect the rectangle that will be copied.
   */
  constexpr explicit basic_rect(const rect_type& rect) noexcept : mRect{rect} {}

  /// \} End of construction

  /// \name Plain setters
  /// \{

  /**
   * \brief Sets the x-coordinate of the rectangle.
   *
   * \param x the new x-coordinate.
   */
  constexpr void set_x(const value_type x) noexcept { mRect.x = x; }

  /**
   * \brief Sets the y-coordinate of the rectangle.
   *
   * \param y the new y-coordinate.
   */
  constexpr void set_y(const value_type y) noexcept { mRect.y = y; }

  /**
   * \brief Sets the position of the rectangle.
   *
   * \details The size of the rectangle is preserved by this function.
   *
   * \param x the new x-coordinate.
   * \param y the new y-coordinate.
   */
  constexpr void set_position(const value_type x, const value_type y) noexcept
  {
    mRect.x = x;
    mRect.y = y;
  }

  /**
   * \brief Sets the position of the rectangle.
   *
   * \details The size of the rectangle is preserved by this function.
   *
   * \param pos the new position.
   */
  constexpr void set_position(const point_type& pos) noexcept
  {
    set_position(pos.x(), pos.y());
  }

  /**
   * \brief Sets the width of the rectangle.
   *
   * \param width the new width.
   */
  constexpr void set_width(const value_type width) noexcept { mRect.w = width; }

  /**
   * \brief Sets the height of the rectangle.
   *
   * \param height the new height.
   */
  constexpr void set_height(const value_type height) noexcept { mRect.h = height; }

  /**
   * \brief Sets the size of the rectangle.
   *
   * \param width the new width.
   * \param height the new height.
   */
  constexpr void set_size(const value_type width, const value_type height) noexcept
  {
    mRect.w = width;
    mRect.h = height;
  }

  /**
   * \brief Sets the size of the rectangle.
   *
   * \param size the new size.
   */
  constexpr void set_size(const area_type& size) noexcept
  {
    set_size(size.width, size.height);
  }

  /// \} End of plain setters

  /// \name Mutators
  /// \{

  /**
   * \brief Sets the maximum x-coordinate of the rectangle.
   *
   * \note This function preserves the width of the rectangle.
   *
   * \param mx the maximum x-coordinate.
   */
  constexpr void set_max_x(const value_type mx) noexcept { mRect.x = mx - mRect.w; }

  /**
   * \brief Sets the maximum y-coordinate of the rectangle.
   *
   * \note This function preserves the height of the rectangle.
   *
   * \param my the maximum y-coordinate.
   */
  constexpr void set_max_y(const value_type my) noexcept { mRect.y = my - mRect.h; }

  /**
   * \brief Offsets the x-coordinate of the rectangle by the specified amount.
   *
   * \param dx the offset to the x-coordinate.
   */
  constexpr void offset_x(const value_type dx) noexcept { mRect.x += dx; }

  /**
   * \brief Offsets the y-coordinate of the rectangle by the specified amount.
   *
   * \param dy the offset to the y-coordinate.
   */
  constexpr void offset_y(const value_type dy) noexcept { mRect.y += dy; }

  /**
   * \brief Offsets the width of the rectangle by the specified amount.
   *
   * \param dw the offset to the width.
   */
  constexpr void offset_width(const value_type dw) noexcept { mRect.w += dw; }

  /**
   * \brief Offsets the height of the rectangle by the specified amount.
   *
   * \param dh the offset to the height.
   */
  constexpr void offset_height(const value_type dh) noexcept { mRect.h += dh; }

  /// \} End of mutators

  /// \name Plain getters
  /// \{

  /**
   * \brief Returns the x-coordinate of the rectangle.
   *
   * \return the rectangle x-coordinate.
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type { return mRect.x; }

  /**
   * \brief Returns the y-coordinate of the rectangle.
   *
   * \return the rectangle y-coordinate.
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type { return mRect.y; }

  /**
   * \brief Returns the position of the rectangle.
   *
   * \return the rectangle position.
   */
  [[nodiscard]] constexpr auto position() const noexcept -> point_type
  {
    return {mRect.x, mRect.y};
  }

  /**
   * \brief Returns the width of the rectangle.
   *
   * \return the rectangle width.
   */
  [[nodiscard]] constexpr auto width() const noexcept -> value_type { return mRect.w; }

  /**
   * \brief Returns the height of the rectangle.
   *
   * \return the rectangle height.
   */
  [[nodiscard]] constexpr auto height() const noexcept -> value_type { return mRect.h; }

  /**
   * \brief Returns the size of the rectangle.
   *
   * \return the rectangle size.
   */
  [[nodiscard]] constexpr auto size() const noexcept -> area_type
  {
    return {mRect.w, mRect.h};
  }

  /// \} End of plain getters

  /// \name Queries
  /// \{

  /**
   * \brief Returns the maximum x-coordinate of the rectangle.
   *
   * \return the maximum x-coordinate.
   */
  [[nodiscard]] constexpr auto max_x() const noexcept -> value_type { return x() + width(); }

  /**
   * \brief Returns the maximum y-coordinate of the rectangle.
   *
   * \return the maximum y-coordinate.
   */
  [[nodiscard]] constexpr auto max_y() const noexcept -> value_type { return y() + height(); }

  /**
   * \brief Indicates whether the rectangle has an area.
   *
   * \details The rectangle has an area if both the width and height are greater than zero.
   *
   * \return `true` if the rectangle has an area; `false` otherwise.
   */
  [[nodiscard]] constexpr auto has_area() const noexcept -> bool
  {
    return (width() > 0) && (height() > 0);
  }

  /**
   * \brief Computes the area of the rectangle.
   *
   * \note The returned area may be zero or even negative.
   *
   * \return the computed area.
   */
  [[nodiscard]] constexpr auto area() const noexcept -> value_type
  {
    return width() * height();
  }

  /**
   * \brief Returns the x-coordinate of the center point of the rectangle.
   *
   * \return the center point x-coordinate.
   */
  [[nodiscard]] constexpr auto center_x() const noexcept -> value_type
  {
    return x() + (width() / value_type{2});
  }

  /**
   * \brief Returns the y-coordinate of the center point of the rectangle.
   *
   * \return the center point y-coordinate.
   */
  [[nodiscard]] constexpr auto center_y() const noexcept -> value_type
  {
    return y() + (height() / value_type{2});
  }

  /**
   * \brief Returns the center point of the rectangle.
   *
   * \return the rectangle center point.
   */
  [[nodiscard]] constexpr auto center() const noexcept -> point_type
  {
    return {center_x(), center_y()};
  }

  /**
   * \brief Indicates whether the rectangle contains a point.
   *
   * \param px the x-coordinate of the point that will be checked.
   * \param py the y-coordinate of the point that will be checked.
   *
   * \return `true` if the rectangle contains the point; `false` otherwise.
   */
  [[nodiscard]] constexpr auto contains(const value_type px,
                                        const value_type py) const noexcept -> bool
  {
    return !(px < x() || py < y() || px > max_x() || py > max_y());
  }

  /**
   * \brief Indicates whether the rectangle contains a point.
   *
   * \param point the point that will be checked.
   *
   * \return `true` if the rectangle contains the point; `false` otherwise.
   */
  [[nodiscard]] constexpr auto contains(const point_type& point) const noexcept -> bool
  {
    return contains(point.x(), point.y());
  }

  /// \} End of queries

  /// \name Misc functions
  /// \{

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(mRect.x, mRect.y, mRect.w, mRect.h);
  }

  [[nodiscard]] auto data() noexcept -> rect_type* { return &mRect; }

  [[nodiscard]] auto data() const noexcept -> const rect_type* { return &mRect; }

  [[nodiscard]] constexpr auto get() noexcept -> rect_type& { return mRect; }

  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type& { return mRect; }

  /// \} End of misc functions

 private:
  rect_type mRect{0, 0, 0, 0};
};

/// \name Rectangle functions
/// \{

/**
 * \brief Indicates whether two rectangles intersect.
 *
 * \details This function does not consider rectangles with overlapping borders as
 * intersecting. If you want such behaviour, see the `overlaps()` function.
 *
 * \param a the first rectangle.
 * \param b the second rectangle.
 *
 * \return `true` if the rectangles intersect; `false` otherwise.
 *
 * \see `overlaps(const basic_rect&, const basic_rect&)`
 */
template <typename T>
[[nodiscard]] constexpr auto intersects(const basic_rect<T>& a,
                                        const basic_rect<T>& b) noexcept -> bool
{
  return !(a.x() >= b.max_x() || a.y() >= b.max_y() || a.max_x() <= b.x() ||
           a.max_y() <= b.y());
}

/**
 * \brief Indicates whether or not two rectangles are overlapping.
 *
 * \details This function differs from `intersects()` in that this function includes
 * overlapping borders.
 *
 * \param a the first rectangle.
 * \param b the second rectangle.
 *
 * \return `true` if the rectangles overlap; `false` otherwise.
 *
 * \see `intersects(const basic_rect&, const basic_rect&)`
 */
template <typename T>
[[nodiscard]] constexpr auto overlaps(const basic_rect<T>& a, const basic_rect<T>& b) noexcept
    -> bool
{
  return !(a.x() > b.max_x() || a.y() > b.max_y() || a.max_x() < b.x() || a.max_y() < b.y());
}

/**
 * \brief Returns the union of two rectangles.
 *
 * \param a the first rectangle.
 * \param b the second rectangle.
 *
 * \return the union of the rectangles.
 */
template <typename T>
[[nodiscard]] constexpr auto get_union(const basic_rect<T>& a, const basic_rect<T>& b) noexcept
    -> basic_rect<T>
{
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
  return std::format("irect(x: {}, y: {}, width: {}, height: {})",
                     rect.x(),
                     rect.y(),
                     rect.width(),
                     rect.height());
#else
  return "irect(x: " + std::to_string(rect.x()) + ", y: " + std::to_string(rect.y()) +
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

/// \} End of rectangle functions

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_MATH_HPP_
