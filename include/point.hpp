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
 * @file point.hpp
 *
 * @brief Provides simple 2D point representations.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_POINT_HEADER
#define CENTURION_POINT_HEADER

#include <SDL.h>

#include <cmath>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>

#include "centurion_api.hpp"
#include "centurion_types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class ipoint_traits final {
 public:
  using point_type = SDL_Point;
  using value_type = int;
};

class fpoint_traits final {
 public:
  using point_type = SDL_FPoint;
  using value_type = float;
};

}  // namespace detail

/// @endcond

template <typename Traits>
class basic_point {
 public:
  using point_type = typename Traits::point_type;
  using value_type = typename Traits::value_type;

  constexpr basic_point() noexcept = default;

  constexpr basic_point(value_type x, value_type y) noexcept
  {
    m_point.x = x;
    m_point.y = y;
  };

  void set_x(value_type x) noexcept { m_point.x = x; }

  void set_y(value_type y) noexcept { m_point.y = y; }

  [[nodiscard]] constexpr auto x() const noexcept -> value_type
  {
    return m_point.x;
  }

  [[nodiscard]] constexpr auto y() const noexcept -> value_type
  {
    return m_point.y;
  }

  [[nodiscard]] constexpr auto get() noexcept -> point_type& { return m_point; }

  [[nodiscard]] constexpr auto get() const noexcept -> const point_type&
  {
    return m_point;
  }

  [[nodiscard]] explicit operator point_type() const noexcept
  {
    return m_point;
  }

  [[nodiscard]] explicit operator point_type*() noexcept { return &m_point; }

  [[nodiscard]] explicit operator const point_type*() const noexcept
  {
    return &m_point;
  }

 private:
  point_type m_point{0, 0};
};

class ipoint;
class fpoint;

class ipoint final : public basic_point<detail::ipoint_traits> {
 public:
  using point_type = detail::ipoint_traits::point_type;
  using value_type = detail::ipoint_traits::value_type;

  constexpr ipoint() noexcept = default;
  constexpr ipoint(value_type x, value_type y) noexcept : basic_point{x, y} {}

  [[nodiscard]] constexpr explicit operator fpoint() const noexcept;
};

static_assert(std::is_final_v<ipoint>);
static_assert(std::is_nothrow_default_constructible_v<ipoint>);
static_assert(std::is_nothrow_destructible_v<ipoint>);
static_assert(std::is_nothrow_copy_constructible_v<ipoint>);
static_assert(std::is_nothrow_copy_assignable_v<ipoint>);
static_assert(std::is_nothrow_move_constructible_v<ipoint>);
static_assert(std::is_nothrow_move_assignable_v<ipoint>);

class fpoint final : public basic_point<detail::fpoint_traits> {
 public:
  using point_type = detail::fpoint_traits::point_type;
  using value_type = detail::fpoint_traits::value_type;

  constexpr fpoint() noexcept = default;
  constexpr fpoint(value_type x, value_type y) noexcept : basic_point{x, y} {}

  [[nodiscard]] constexpr explicit operator ipoint() const noexcept
  {
    return {static_cast<int>(x()), static_cast<int>(y())};
  }
};

static_assert(std::is_final_v<fpoint>);
static_assert(std::is_nothrow_default_constructible_v<fpoint>);
static_assert(std::is_nothrow_destructible_v<fpoint>);
static_assert(std::is_nothrow_copy_constructible_v<fpoint>);
static_assert(std::is_nothrow_copy_assignable_v<fpoint>);
static_assert(std::is_nothrow_move_constructible_v<fpoint>);
static_assert(std::is_nothrow_move_assignable_v<fpoint>);

inline constexpr ipoint::operator fpoint() const noexcept
{
  return {static_cast<float>(x()), static_cast<float>(y())};
}

// potentially useful in generic code
template <typename T,
          typename... Args,
          typename = std::enable_if_t<std::is_same_v<T, int> ||
                                      std::is_same_v<T, float>>>
[[nodiscard]] constexpr auto make_point(Args&&... args) noexcept
{
  if constexpr (std::is_same_v<T, int>) {
    return ipoint{std::forward<Args>(args)...};
  } else {
    return fpoint{std::forward<Args>(args)...};
  }
}

/// @cond FALSE

namespace detail {

template <typename From, typename To>
[[nodiscard]] constexpr auto valid_point_cast() noexcept -> bool
{
  return (std::is_same_v<From, ipoint> && std::is_same_v<To, fpoint>) ||
         (std::is_same_v<From, fpoint> && std::is_same_v<To, ipoint>);
}

}  // namespace detail

/// @endcond

[[nodiscard]] inline auto distance(const ipoint& from,
                                   const ipoint& to) noexcept -> int
{
  const auto xDiff = std::abs(from.x() - to.x());
  const auto yDiff = std::abs(from.y() - to.y());
  const auto dist = std::sqrt(xDiff + yDiff);
  return static_cast<int>(std::round(dist));
}

[[nodiscard]] inline auto distance(const fpoint& from,
                                   const fpoint& to) noexcept -> float
{
  return std::sqrt(std::abs(from.x() - to.x()) + std::abs(from.y() - to.y()));
}

[[nodiscard]] inline constexpr auto operator+(const fpoint& lhs,
                                              const fpoint& rhs) noexcept
    -> fpoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] inline constexpr auto operator-(const fpoint& lhs,
                                              const fpoint& rhs) noexcept
    -> fpoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] inline constexpr auto operator+(const ipoint& lhs,
                                              const ipoint& rhs) noexcept
    -> ipoint
{
  return {lhs.x() + rhs.x(), lhs.y() + rhs.y()};
}

[[nodiscard]] inline constexpr auto operator-(const ipoint& lhs,
                                              const ipoint& rhs) noexcept
    -> ipoint
{
  return {lhs.x() - rhs.x(), lhs.y() - rhs.y()};
}

[[nodiscard]] inline constexpr auto operator==(const ipoint& lhs,
                                               const ipoint& rhs) noexcept
    -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] inline constexpr auto operator==(const fpoint& lhs,
                                               const fpoint& rhs) noexcept
    -> bool
{
  return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

[[nodiscard]] inline constexpr auto operator!=(const ipoint& lhs,
                                               const ipoint& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] inline constexpr auto operator!=(const fpoint& lhs,
                                               const fpoint& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

[[nodiscard]] inline auto to_string(const ipoint& point) -> std::string
{
  using namespace std::string_literals;

  const auto xStr = std::to_string(point.x());
  const auto yStr = std::to_string(point.y());

  return "[i_point | X: "s + xStr + ", Y: "s + yStr + "]"s;
}

[[nodiscard]] inline auto to_string(const fpoint& point) -> std::string
{
  using namespace std::string_literals;

  const auto xStr = std::to_string(point.x());
  const auto yStr = std::to_string(point.y());

  return "[f_point | X: "s + xStr + ", Y: "s + yStr + "]"s;
}

inline auto operator<<(std::ostream& stream, const ipoint& point)
    -> std::ostream&
{
  stream << to_string(point);
  return stream;
}

inline auto operator<<(std::ostream& stream, const fpoint& point)
    -> std::ostream&
{
  stream << to_string(point);
  return stream;
}

}  // namespace centurion

#endif  // CENTURION_POINT_HEADER