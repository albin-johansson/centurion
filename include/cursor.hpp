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
 * @file cursor.hpp
 *
 * @brief Provides the cursor API.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_CURSOR_HEADER
#define CENTURION_CURSOR_HEADER

#include <SDL.h>

#include <memory>  // unique_ptr

#include "centurion_api.hpp"
#include "detail/utils.hpp"
#include "point.hpp"
#include "surface.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/**
 * @enum system_cursor
 *
 * @ingroup graphics
 *
 * @brief Represents the various available system cursors.
 *
 * @details Mirrors the values of the `SDL_SystemCursor` enum.
 *
 * @since 4.0.0
 *
 * @see `SDL_SystemCursor`
 *
 * @headerfile cursor.hpp
 */
enum class system_cursor {
  arrow = SDL_SYSTEM_CURSOR_ARROW,
  ibeam = SDL_SYSTEM_CURSOR_IBEAM,
  wait = SDL_SYSTEM_CURSOR_WAIT,
  crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,
  wait_arrow = SDL_SYSTEM_CURSOR_WAITARROW,
  arrow_nw_se = SDL_SYSTEM_CURSOR_SIZENWSE,
  arrow_ne_sw = SDL_SYSTEM_CURSOR_SIZENESW,
  arrow_w_e = SDL_SYSTEM_CURSOR_SIZEWE,
  arrow_n_s = SDL_SYSTEM_CURSOR_SIZENS,
  arrow_all = SDL_SYSTEM_CURSOR_SIZEALL,
  no = SDL_SYSTEM_CURSOR_NO,
  hand = SDL_SYSTEM_CURSOR_HAND
};

/**
 * @brief Indicates whether or not two system cursor values are the same.
 *
 * @ingroup graphics
 *
 * @param lhs the left-hand side system cursor value.
 * @param rhs the right-hand side system cursor value.
 *
 * @return `true` if the system cursor values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(system_cursor lhs,
                                               SDL_SystemCursor rhs) noexcept
    -> bool
{
  return static_cast<SDL_SystemCursor>(lhs) == rhs;
}

/**
 * @copydoc operator==(system_cursor, SDL_SystemCursor)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator==(SDL_SystemCursor lhs,
                                               system_cursor rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not two system cursor values aren't the same.
 *
 * @ingroup graphics
 *
 * @param lhs the left-hand side system cursor value.
 * @param rhs the right-hand side system cursor value.
 *
 * @return `true` if the system cursor values aren't the same; `false`
 * otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(system_cursor lhs,
                                               SDL_SystemCursor rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(system_cursor, SDL_SystemCursor)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator!=(SDL_SystemCursor lhs,
                                               system_cursor rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @class cursor
 *
 * @ingroup graphics
 *
 * @brief Represents a mouse cursor.
 *
 * @details Cursors can be created from various preset shapes or from images
 * (surfaces).
 *
 * @since 4.0.0
 *
 * @headerfile cursor.hpp
 */
class cursor final
{
 public:
  /**
   * @brief Creates a cursor based on the supplied `SDL_Cursor`.
   *
   * @details The ownership of the supplied pointer will be claimed by the
   * created cursor instance.
   *
   * @param sdlCursor a pointer to an `SDL_Cursor` that will be adopted,
   * can't be null.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit cursor(owner<SDL_Cursor*> sdlCursor);

  /**
   * @brief Creates a cursor based on the specified cursor type.
   *
   * @param id the cursor type that will be used.
   *
   * @throws sdl_error if the cursor cannot be created.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit cursor(system_cursor id);

  /**
   * @brief Creates a cursor based on the supplied surface.
   *
   * @details The supplied hotspot must be within the area of the supplied
   * surface.
   *
   * @param surface the surface that will represent the cursor.
   * @param hotspot the point used to determine where the mouse
   * actually is.
   *
   * @throws sdl_error if the cursor cannot be created.
   *
   * @since 4.0.0
   */
  CENTURION_API
  explicit cursor(const surface& surface, const ipoint& hotspot);

  /**
   * @brief Forces a cursor redraw.
   *
   * @since 4.0.0
   */
  CENTURION_API
  static void force_redraw() noexcept;

  /**
   * @brief Resets the cursor to the system default.
   *
   * @since 4.0.0
   */
  CENTURION_API
  static void reset() noexcept;

  /**
   * @brief Sets whether or not the cursor is visible.
   *
   * @param visible `true` if the cursor should be made visible; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  static void set_visible(bool visible) noexcept;

  /**
   * @brief Indicates whether or not the cursor is visible.
   *
   * @return `true` if the cursor is visible; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  static auto visible() noexcept -> bool;

  /**
   * @brief Makes the cursor the used cursor.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void enable() noexcept;

  /**
   * @brief Indicates whether or not the cursor is currently being used.
   *
   * @note This method only checks if the currently used SDL cursor is the
   * same instance referenced in the invoked Centurion cursor. In other
   * words, if two cursors of the same type has been created, and one of them
   * is enabled, then this method could still return `false` even if the
   * cursors have the same type.
   *
   * @return `true` if the cursor is being used; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto is_enabled() const noexcept -> bool;

  /**
   * @brief Returns a pointer to the associated `SDL_Cursor`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However, it's' useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `SDL_Cursor`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Cursor*
  {
    return m_cursor.get();
  }

 private:
  class deleter final
  {
   public:
    void operator()(SDL_Cursor* cursor) noexcept { SDL_FreeCursor(cursor); }
  };

  std::unique_ptr<SDL_Cursor, deleter> m_cursor;
};

}  // namespace cen

#endif  // CENTURION_CURSOR_HEADER