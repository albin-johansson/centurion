#ifndef CENTURION_MATH_RECT_HPP_
#define CENTURION_MATH_RECT_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <type_traits>  // conditional_t, is_integral_v, is_floating_point_v, ...

#include "../core/common.hpp"
#include "../core/features.hpp"
#include "../detail/stdlib.hpp"
#include "area.hpp"
#include "point.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup math
/// \{

template <typename T, enable_if_convertible_t<T, int, float> = 0>
class RectTraits final {
 public:
  inline constexpr static bool integral = std::is_integral_v<T>;
  inline constexpr static bool floating = std::is_floating_point_v<T>;

  using value_type = std::conditional_t<integral, int, float>;
  using point_type = std::conditional_t<integral, ipoint, fpoint>;
  using area_type = std::conditional_t<integral, iarea, farea>;
  using rect_type = std::conditional_t<integral, SDL_Rect, SDL_FRect>;
};

template <typename T>
class BasicRect;

using Rect = BasicRect<int>;
using FRect = BasicRect<float>;

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
      : m_rect{x, y, width, height}
  {}

  constexpr BasicRect(const point_type& position, const area_type& size) noexcept
      : m_rect{position.x(), position.y(), size.width, size.height}
  {}

  constexpr explicit BasicRect(const rect_type& rect) noexcept : m_rect{rect} {}

  constexpr void SetX(const value_type x) noexcept { m_rect.x = x; }
  constexpr void SetY(const value_type y) noexcept { m_rect.y = y; }

  constexpr void SetMaxX(const value_type maxX) noexcept { m_rect.x = maxX - m_rect.w; }
  constexpr void SetMaxY(const value_type maxY) noexcept { m_rect.y = maxY - m_rect.h; }

  constexpr void OffsetX(const value_type offset) noexcept { m_rect.x += offset; }
  constexpr void OffsetY(const value_type offset) noexcept { m_rect.y += offset; }
  constexpr void OffsetWidth(const value_type offset) noexcept { m_rect.w += offset; }
  constexpr void OffsetHeight(const value_type offset) noexcept { m_rect.h += offset; }

  constexpr void SetPosition(const value_type x, const value_type y) noexcept
  {
    m_rect.x = x;
    m_rect.y = y;
  }

  constexpr void SetPosition(const point_type& pos) noexcept { SetPosition(pos.x(), pos.y()); }

  constexpr void SetWidth(const value_type width) noexcept { m_rect.w = width; }
  constexpr void SetHeight(const value_type height) noexcept { m_rect.h = height; }

  constexpr void SetSize(const value_type width, const value_type height) noexcept
  {
    m_rect.w = width;
    m_rect.h = height;
  }

  constexpr void SetSize(const area_type& size) noexcept { SetSize(size.width, size.height); }

  [[nodiscard]] constexpr auto GetX() const noexcept -> value_type { return m_rect.x; }
  [[nodiscard]] constexpr auto GetY() const noexcept -> value_type { return m_rect.y; }

  [[nodiscard]] constexpr auto GetPosition() const noexcept -> point_type
  {
    return point_type{m_rect.x, m_rect.y};
  }

  [[nodiscard]] constexpr auto GetWidth() const noexcept -> value_type { return m_rect.w; }
  [[nodiscard]] constexpr auto GetHeight() const noexcept -> value_type { return m_rect.h; }

  [[nodiscard]] constexpr auto GetSize() const noexcept -> area_type
  {
    return area_type{m_rect.w, m_rect.h};
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
    const auto px = point.x();
    const auto py = point.y();
    return !(px < GetX() || py < GetY() || px > GetMaxX() || py > GetMaxY());
  }

  [[nodiscard]] constexpr auto HasArea() const noexcept -> bool
  {
    return (GetWidth() > 0) && (GetHeight() > 0);
  }

  [[nodiscard]] auto data() noexcept -> rect_type* { return &m_rect; }
  [[nodiscard]] auto data() const noexcept -> const rect_type* { return &m_rect; }

  [[nodiscard]] constexpr auto get() noexcept -> rect_type& { return m_rect; }
  [[nodiscard]] constexpr auto get() const noexcept -> const rect_type& { return m_rect; }

  template <typename Archive>
  void serialize(Archive& archive)
  {
    archive(m_rect.x, m_rect.y, m_rect.w, m_rect.h);
  }

 private:
  rect_type m_rect{0, 0, 0, 0};
};

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
auto operator<<(std::ostream& stream, const BasicRect<T>& rect) -> std::ostream&
{
  return stream << to_string(rect);
}

/// \} End of group math

}  // namespace cen

#endif  // CENTURION_MATH_RECT_HPP_