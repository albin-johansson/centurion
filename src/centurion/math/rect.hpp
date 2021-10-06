#ifndef CENTURION_RECTANGLE_HEADER
#define CENTURION_RECTANGLE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/cast.hpp"
#include "../core/sfinae.hpp"
#include "../detail/max.hpp"
#include "../detail/min.hpp"
#include "area.hpp"
#include "point.hpp"

namespace cen {

/// \addtogroup math
/// \{

/**
 * \class rect_traits
 *
 * \brief Provides rectangle traits used by `basic_rect`.
 *
 * \note Whilst it is possible to supply a type that isn't `int` or `float`, rectangles
 * will always use one of them as the representation type.
 *
 * \tparam T the representation type, must be convertible to `int` or `float`.
 *
 * \see `basic_rect`
 * \see `irect`
 * \see `frect`
 *
 * \since 5.0.0
 */
template <typename T, enable_if_convertible_t<T, int, float> = 0>
class rect_traits final
{
 public:
  inline constexpr static bool isIntegral = std::is_integral_v<T>;
  inline constexpr static bool isFloating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<isIntegral, int, float>;
  using point_type = std::conditional_t<isIntegral, ipoint, fpoint>;
  using area_type = std::conditional_t<isIntegral, iarea, farea>;
  using rect_type = std::conditional_t<isIntegral, SDL_Rect, SDL_FRect>;
};

template <typename T>
class basic_rect;

/**
 * \typedef irect
 *
 * \brief Alias for an `int`-based rectangle.
 *
 * \since 5.0.0
 */
using irect = basic_rect<int>;

/**
 * \typedef frect
 *
 * \brief Alias for a `float`-based rectangle.
 *
 * \since 5.0.0
 */
using frect = basic_rect<float>;

/**
 * \class basic_rect
 *
 * \brief A simple rectangle implementation, based on either `SDL_Rect` or `SDL_FRect`.
 *
 * \serializable
 *
 * \tparam T the representation type. Must be convertible to either `int` or `float`.
 *
 * \see `irect`
 * \see `frect`
 * \see `rect()`
 * \see `intersects()`
 * \see `collides()`
 * \see `get_union()`
 *
 * \since 4.0.0
 */
template <typename T>
class basic_rect final
{
 public:
  /**
   * \brief Indicates whether or not the rectangle is based on an integral type.
   *
   * \since 5.0.0
   */
  inline constexpr static bool isIntegral = rect_traits<T>::isIntegral;

  /**
   * \brief Indicates whether or not the rectangle is based on a floating-point
   * type.
   *
   * \since 5.0.0
   */
  inline constexpr static bool isFloating = rect_traits<T>::isFloating;

  /**
   * \typedef value_type
   *
   * \brief The representation type, i.e. `int` or `float`.
   *
   * \since 5.0.0
   */
  using value_type = typename rect_traits<T>::value_type;

  /**
   * \typedef point_type
   *
   * \brief The point type used, i.e. `ipoint` or `fpoint`.
   *
   * \since 5.0.0
   */
  using point_type = typename rect_traits<T>::point_type;

  /**
   * \typedef area_type
   *
   * \brief The area type used, i.e. `iarea` or `farea`.
   *
   * \since 5.0.0
   */
  using area_type = typename rect_traits<T>::area_type;

  /**
   * \typedef rect_type
   *
   * \brief The underlying SDL rectangle type, i.e. `SDL_Rect` or `SDL_FRect`.
   *
   * \since 5.0.0
   */
  using rect_type = typename rect_traits<T>::rect_type;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a rectangle with the components (0, 0, 0, 0).
   *
   * \since 4.0.0
   */
  constexpr basic_rect() noexcept = default;

  /**
   * \brief Creates a rectangle based on an SDL rectangle.
   *
   * \param rect the rectangle that will be copied.
   *
   * \since 5.3.0
   */
  constexpr explicit basic_rect(const rect_type& rect) noexcept : m_rect{rect}
  {}

  /**
   * \brief Creates a rectangle with the supplied position and size.
   *
   * \param position the position of the rectangle.
   * \param size the size of the rectangle.
   *
   * \since 4.1.0
   */
  constexpr basic_rect(const point_type& position, const area_type& size) noexcept
      : m_rect{position.x(), position.y(), size.width, size.height}
  {}

  /**
   * \brief Creates a rectangle with the supplied position and size.
   *
   * \param x the x-coordinate of the rectangle.
   * \param y the y-coordinate of the rectangle.
   * \param width the width of the rectangle.
   * \param height the height of the rectangle.
   *
   * \since 5.3.0
   */
  constexpr basic_rect(const value_type x,
                       const value_type y,
                       const value_type width,
                       const value_type height) noexcept
      : m_rect{x, y, width, height}
  {}

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets the x-coordinate of the rectangle.
   *
   * \param x the new x-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  constexpr void set_x(const value_type x) noexcept
  {
    m_rect.x = x;
  }

  /**
   * \brief Sets the y-coordinate of the rectangle.
   *
   * \param y the new y-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  constexpr void set_y(const value_type y) noexcept
  {
    m_rect.y = y;
  }

  /**
   * \brief Sets the maximum x-coordinate of the rectangle.
   *
   * \note This function preserves the width of the rectangle.
   *
   * \param maxX the new maximum x-coordinate of the rectangle.
   *
   * \since 5.1.0
   */
  constexpr void set_max_x(const value_type maxX) noexcept
  {
    m_rect.x = maxX - m_rect.w;
  }

  /**
   * \brief Sets the maximum y-coordinate of the rectangle.
   *
   * \note This function preserves the height of the rectangle.
   *
   * \param maxY the new maximum y-coordinate of the rectangle.
   *
   * \since 5.1.0
   */
  constexpr void set_max_y(const value_type maxY) noexcept
  {
    m_rect.y = maxY - m_rect.h;
  }

  /**
   * \brief Offsets the x-coordinate of the rectangle by the specified amount.
   *
   * \details This function is effectively equivalent to calling `set_x()` with the sum of
   * `x()` and `offset`.
   *
   * \param offset the offset to the x-coordinate of the rectangle.
   *
   * \since 6.0.0
   */
  constexpr void offset_x(const value_type offset) noexcept
  {
    m_rect.x += offset;
  }

  /**
   * \brief Offsets the y-coordinate of the rectangle by the specified amount.
   *
   * \details This function is effectively equivalent to calling `set_y()` with the sum of
   * `y()` and `offset`.
   *
   * \param offset the offset to the y-coordinate of the rectangle.
   *
   * \since 6.0.0
   */
  constexpr void offset_y(const value_type offset) noexcept
  {
    m_rect.y += offset;
  }

  /**
   * \brief Tweaks the width of the rectangle by the specified amount.
   *
   * \details This function is effectively equivalent to calling `set_width()` with the
   * sum of `width()` and `offset`.
   *
   * \param offset the offset to the width of the rectangle.
   *
   * \since 6.0.0
   */
  constexpr void offset_width(const value_type offset) noexcept
  {
    m_rect.w += offset;
  }

  /**
   * \brief Tweaks the height of the rectangle by the specified amount.
   *
   * \details This function is effectively equivalent to calling `set_height()` with the
   * sum of `height()` and `offset`.
   *
   * \param offset the offset to the height of the rectangle.
   *
   * \since 6.0.0
   */
  constexpr void offset_height(const value_type offset) noexcept
  {
    m_rect.h += offset;
  }

  /**
   * \brief Sets the position of the rectangle.
   *
   * \note Some frameworks have this kind of function change the size of the rectangle.
   * However, this function does *not* change the size of the rectangle.
   *
   * \param pos the new position of the rectangle.
   *
   * \since 5.1.0
   */
  constexpr void set_position(const point_type& pos) noexcept
  {
    m_rect.x = pos.x();
    m_rect.y = pos.y();
  }

  /**
   * \brief Sets the width of the rectangle.
   *
   * \param width the new width of the rectangle.
   *
   * \since 4.0.0
   */
  constexpr void set_width(const value_type width) noexcept
  {
    m_rect.w = width;
  }

  /**
   * \brief Sets the height of the rectangle.
   *
   * \param height the new height of the rectangle.
   *
   * \since 4.0.0
   */
  constexpr void set_height(const value_type height) noexcept
  {
    m_rect.h = height;
  }

  /**
   * \brief Sets the size of the rectangle.
   *
   * \param size the new size of the rectangle.
   *
   * \since 5.1.0
   */
  constexpr void set_size(const area_type& size) noexcept
  {
    m_rect.w = size.width;
    m_rect.h = size.height;
  };

  /// \} End of setters

  /// \name Queries
  /// \{

  /**
   * \brief Returns the x-coordinate of the rectangle.
   *
   * \return the x-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto x() const noexcept -> value_type
  {
    return m_rect.x;
  }

  /**
   * \brief Returns the y-coordinate of the rectangle.
   *
   * \return the y-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto y() const noexcept -> value_type
  {
    return m_rect.y;
  }

  /**
   * \brief Returns the position of the rectangle.
   *
   * \return the position of the rectangle.
   *
   * \since 4.1.0
   */
  [[nodiscard]] constexpr auto position() const noexcept -> point_type
  {
    return point_type{m_rect.x, m_rect.y};
  }

  /**
   * \brief Returns the width of the rectangle.
   *
   * \return the width of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto width() const noexcept -> value_type
  {
    return m_rect.w;
  }

  /**
   * \brief Returns the height of the rectangle.
   *
   * \return the height of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto height() const noexcept -> value_type
  {
    return m_rect.h;
  }

  /**
   * \brief Returns the size of the rectangle.
   *
   * \return the size of the rectangle.
   *
   * \since 4.1.0
   */
  [[nodiscard]] constexpr auto size() const noexcept -> area_type
  {
    return area_type{m_rect.w, m_rect.h};
  }

  /**
   * \brief Returns the maximum x-coordinate of the rectangle.
   *
   * \return the maximum x-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto max_x() const noexcept -> value_type
  {
    return x() + width();
  }

  /**
   * \brief Returns the maximum y-coordinate of the rectangle.
   *
   * \return the maximum y-coordinate of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto max_y() const noexcept -> value_type
  {
    return y() + height();
  }

  /**
   * \brief Returns the x-coordinate of the center point of the rectangle.
   *
   * \return the x-coordinate of the center point of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto center_x() const noexcept -> value_type
  {
    return x() + (width() / static_cast<value_type>(2));
  }

  /**
   * \brief Returns the y-coordinate of the center point of the rectangle.
   *
   * \return the y-coordinate of the center point of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto center_y() const noexcept -> value_type
  {
    return y() + (height() / static_cast<value_type>(2));
  }

  /**
   * \brief Returns the center point of the rectangle.
   *
   * \return the center point of the rectangle.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto center() const noexcept -> point_type
  {
    return {center_x(), center_y()};
  }

  /**
   * \brief Returns the total area of the rectangle.
   *
   * \return the area of the rectangle.
   *
   * \since 4.2.0
   */
  [[nodiscard]] constexpr auto area() const noexcept -> value_type
  {
    return width() * height();
  }

  /**
   * \brief Indicates whether or not the rectangle contains the point.
   *
   * \param point the point that will be checked.
   *
   * \return `true` if the rectangle contains the point; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto contains(const point_type& point) const noexcept -> bool
  {
    const auto px = point.x();
    const auto py = point.y();
    return !(px < x() || py < y() || px > max_x() || py > max_y());
  }

  /**
   * \brief Indicates whether or not the rectangle has an area.
   *
   * \details The rectangle has an area if both the width and height are
   * greater than zero.
   *
   * \return `true` if the rectangle has an area; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] constexpr auto has_area() const noexcept -> bool
  {
    return (width() > 0) && (height() > 0);
  }

  /**
   * \brief Returns a pointer to the internal rectangle representation.
   *
   * \note Don't cache the returned pointer.
   *
   * \return a pointer to the rectangle representation.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto data() noexcept -> rect_type*
  {
    return &m_rect;
  }

  /**
   * \copydoc data()
   */
  [[nodiscard]] auto data() const noexcept -> const rect_type*
  {
    return &m_rect;
  }

  /**
   * \brief Returns the internal rectangle.
   *
   * \return a reference to the internal rectangle.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() noexcept -> rect_type&
  {
    return m_rect;
  }

  /**
   * \brief Returns the internal rectangle.
   *
   * \return a reference to the internal rectangle.
   *
   * \since 5.0.0
   */
  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type&
  {
    return m_rect;
  }

  /// \} End of queries

  /// \name Conversions
  /// \{

  /**
   * \brief Returns a pointer to the internal rectangle.
   *
   * \return a pointer to the internal rectangle.
   *
   * \since 5.0.0
   */
  [[nodiscard]] explicit operator rect_type*() noexcept
  {
    return &m_rect;
  }

  /**
   * \brief Returns a pointer to the internal rectangle.
   *
   * \return a pointer to the internal rectangle.
   *
   * \since 5.0.0
   */
  [[nodiscard]] explicit operator const rect_type*() const noexcept
  {
    return &m_rect;
  }

  /// \} End of conversions

  /**
   * \brief Serializes the rectangle.
   *
   * \details This function expects that the archive provides an overloaded `operator()`,
   * used for serializing data. This API is based on the Cereal serialization library.
   *
   * \tparam Archive the type of the archive.
   *
   * \param archive the archive used to serialize the rectangle.
   *
   * \since 5.3.0
   */
  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_rect.x, m_rect.y, m_rect.w, m_rect.h);
  }

 private:
  rect_type m_rect{0, 0, 0, 0};
};

/// \name Rectangle functions
/// \{

/**
 * \brief Creates a rectangle with automatically deduced precision.
 *
 * \note The only supported precisions for rectangles are `int` and `float`, so this
 * function will cast the supplied values to the corresponding type. For example, if you
 * supply doubles to this function, the returned point will use float as the precision.
 *
 * \tparam T the deduced precision type.
 *
 * \param x the x-coordinate of the rectangle.
 * \param y the y-coordinate of the rectangle.
 * \param width the width of the rectangle.
 * \param height the height of the rectangle.
 *
 * \return a rectangle with the specified position and size.
 *
 * \since 6.0.0
 */
template <typename T, enable_if_number_t<T> = 0>
[[nodiscard]] constexpr auto rect(const T x, const T y, const T width, const T height) noexcept
    -> basic_rect<typename rect_traits<T>::value_type>
{
  using value_type = typename rect_traits<T>::value_type;
  return basic_rect<value_type>{static_cast<value_type>(x),
                                static_cast<value_type>(y),
                                static_cast<value_type>(width),
                                static_cast<value_type>(height)};
}

/**
 * \brief Indicates whether or not the two rectangles intersect.
 *
 * \details This function does *not* consider rectangles with overlapping borders as
 * intersecting. If you want such behaviour, see the `collides` function.
 *
 * \tparam T the representation type used by the rectangles.
 *
 * \param fst the first rectangle.
 * \param snd the second rectangle.
 *
 * \return `true` if the rectangles intersect; `false` otherwise.
 *
 * \see `collides`
 *
 * \since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto intersects(const basic_rect<T>& fst,
                                        const basic_rect<T>& snd) noexcept -> bool
{
  return !(fst.x() >= snd.max_x() || fst.max_x() <= snd.x() || fst.y() >= snd.max_y() ||
           fst.max_y() <= snd.y());
}

/**
 * \brief Indicates whether or not two rectangles are colliding.
 *
 * \details This function considers rectangles with overlapping borders as colliding.
 *
 * \tparam T the representation type used by the rectangles.
 *
 * \param fst the first rectangle.
 * \param snd the second rectangle.
 *
 * \return `true` if the rectangles collide; `false` otherwise.
 *
 * \see `intersects`
 *
 * \since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto collides(const basic_rect<T>& fst,
                                      const basic_rect<T>& snd) noexcept -> bool
{
  return !(fst.x() > snd.max_x() || fst.max_x() < snd.x() || fst.y() > snd.max_y() ||
           fst.max_y() < snd.y());
}

/**
 * \brief Returns the union of two rectangles.
 *
 * \details Returns a rectangle that represents the union of two rectangles.
 *
 * \tparam T the representation type used by the rectangles.
 *
 * \param fst the first rectangle.
 * \param snd the second rectangle.
 *
 * \return a rectangle that represents the union of the rectangles.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto get_union(const basic_rect<T>& fst,
                                       const basic_rect<T>& snd) noexcept -> basic_rect<T>
{
  const auto fstHasArea = fst.has_area();
  const auto sndHasArea = snd.has_area();

  if (!fstHasArea && !sndHasArea) {
    return {};
  }
  else if (!fstHasArea) {
    return snd;
  }
  else if (!sndHasArea) {
    return fst;
  }

  const auto x = detail::min(fst.x(), snd.x());
  const auto y = detail::min(fst.y(), snd.y());
  const auto maxX = detail::max(fst.max_x(), snd.max_x());
  const auto maxY = detail::max(fst.max_y(), snd.max_y());

  return {{x, y}, {maxX - x, maxY - y}};
}

/// \} End of rectangle functions

/// \name Rectangle comparison operators
/// \{

/**
 * \brief Indicates whether or not two rectangles are equal.
 *
 * \tparam T the representation type used by the rectangles.
 *
 * \param lhs the left-hand side rectangle.
 * \param rhs the right-hand side rectangle.
 *
 * \return `true` if the rectangles are equal; `false` otherwise.
 *
 * \since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator==(const basic_rect<T>& lhs,
                                        const basic_rect<T>& rhs) noexcept -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.width() == rhs.width()) &&
         (lhs.height() == rhs.height());
}

/**
 * \brief Indicates whether or not two rectangles aren't equal.
 *
 * \tparam T the representation type used by the rectangles.
 *
 * \param lhs the left-hand side rectangle.
 * \param rhs the right-hand side rectangle.
 *
 * \return `true` if the rectangles aren't equal; `false` otherwise.
 *
 * \since 4.0.0
 */
template <typename T>
[[nodiscard]] constexpr auto operator!=(const basic_rect<T>& lhs,
                                        const basic_rect<T>& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of rectangle comparison operators

/// \name Rectangle cast specializations
/// \{

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

/// \} End of rectangle cast specializations

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a rectangle.
 *
 * \tparam T the representation type used by the rectangle.
 *
 * \param rect the rectangle that will be converted to a string.
 *
 * \return a textual representation of the rectangle.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_rect<T>& rect) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("rect{{x: {}, y: {}, width: {}, height: {}}}",
                     rect.x(),
                     rect.y(),
                     rect.width(),
                     rect.height());
#else
  return "rect{x: " + std::to_string(rect.x()) + ", y: " + std::to_string(rect.y()) +
         ", width: " + std::to_string(rect.width()) +
         ", height: " + std::to_string(rect.height()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a rectangle using a stream.
 *
 * \tparam T the representation type used by the rectangle.
 *
 * \param stream the stream that will be used.
 * \param rect the rectangle that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_rect<T>& rect) -> std::ostream&
{
  return stream << to_string(rect);
}

/// \} End of streaming

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_RECTANGLE_HEADER