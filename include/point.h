/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once
#include <string>
#include <SDL.h>
#include "centurion_api.h"

namespace centurion {

/**
 * The Point class is a simple representation of a point in the plane, with integer components.
 *
 * @since 3.0.0
 */
class CENTURION_API Point final {
 private:
  int x = 0;
  int y = 0;

 public:
  /**
   * Creates a point with the coordinates (0, 0).
   *
   * @since 3.0.0
   */
  CENTURION_API Point() noexcept;

  /**
   * @param x the x-coordinate of the point.
   * @param y the y-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API Point(int x, int y) noexcept;

  /**
   * Creates a point based on an SDL_Point instance.
   *
   * @param rect the SDL point that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit Point(SDL_Point point) noexcept;

  /**
   * Sets the x-coordinate of the point.
   *
   * @param x the x-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API void set_x(int x) noexcept;

  /**
   * Sets the y-coordinate of the point.
   *
   * @param y the y-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API void set_y(int y) noexcept;

  /**
   * Returns the x-coordinate of the point.
   *
   * @return the x-coordinate of the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_x() const noexcept;

  /**
   * Returns the y-coordinate of the point.
   *
   * @return the y-coordinate of the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_y() const noexcept;

  /**
   * Returns a textual representation of the Point instance.
   *
   * @return a textual representation of the Point instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Converts the point into an SDL_Point.
   *
   * @return an SDL_Point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API /*implicit*/ operator SDL_Point() const noexcept;
};

/**
 * The FPoint class is a simple representation of a point in the plane, with floating-point
 * components.
 *
 * @since 3.0.0
 */
class CENTURION_API FPoint final {
 private:
  float x = 0;
  float y = 0;

 public:
  /**
   * Creates a point with the coordinates (0, 0).
   *
   * @since 3.0.0
   */
  CENTURION_API FPoint() noexcept;

  /**
   * @param x the x-coordinate of the point.
   * @param y the y-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API FPoint(float x, float y) noexcept;

  /**
   * Creates a FPoint based on the supplied SDL_FRect.
   *
   * @param point the SDL rectangle that will be copied.
   * @since 3.0.0
   */
  CENTURION_API explicit FPoint(SDL_FPoint point) noexcept;

  /**
   * Sets the x-coordinate of the point.
   *
   * @param x the new x-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API void set_x(float x) noexcept;

  /**
   * Sets the y-coordinate of the point.
   *
   * @param y the new y-coordinate of the point.
   * @since 3.0.0
   */
  CENTURION_API void set_y(float y) noexcept;

  /**
   * Returns the x-coordinate of the point.
   *
   * @return the x-coordinate of the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_x() const noexcept;

  /**
   * Returns the y-coordinate of the point.
   *
   * @return the y-coordinate of the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_y() const noexcept;

  /**
   * Returns a textual representation of the Point instance.
   *
   * @return a textual representation of the Point instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Converts the point into an SDL_FPoint.
   *
   * @return an SDL_FPoint instance, based on the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API /*implicit*/ operator SDL_FPoint() const noexcept;

  /**
   * Indicates whether or not two points are considered to be equal. The points are considered
   * tobe equal iff the absolute difference of the components of the points are less than the
   * specified epsilon value.
   *
   * @param lhs the left-hand side point.
   * @param rhs the right-hand side point.
   * @param epsilon the epsilon value that will be used. Denotes the exclusive upper bound for
   * the maximum allowed difference of the components of the points. A negative value will be
   * converted to zero.
   * @return true if the points are considered to be equal; false otherwise.
   * @since 3.1.0
   */
  [[nodiscard]]
  CENTURION_API static bool equals(const FPoint& lhs,
                                   const FPoint& rhs,
                                   float epsilon = 0.0001f) noexcept;
};

/**
 * Indicates whether or not two points are the same.
 *
 * @param lhs the left-hand side point.
 * @param rhs the right-hand side point.
 * @return true if the points are the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
CENTURION_API bool operator==(const Point& lhs, const Point& rhs) noexcept;

/**
 * Indicates whether or not two points aren't the same.
 *
 * @param lhs the left-hand side point.
 * @param rhs the right-hand side point.
 * @return true if the points aren't the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
CENTURION_API bool operator!=(const Point& lhs, const Point& rhs) noexcept;

/**
 * Indicates whether or not two points are the same. The absolute difference of the components of
 * the points must be less than 0.0001, in order for the points to be considered equal.
 *
 * @param lhs the left-hand side point.
 * @param rhs the right-hand side point.
 * @return true if the points are the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
CENTURION_API bool operator==(const FPoint& lhs, const FPoint& rhs) noexcept;

/**
 * Indicates whether or not two points aren't the same.
 *
 * @param lhs the left-hand side point.
 * @param rhs the right-hand side point.
 * @return true if the points aren't the same; false otherwise.
 * @since 3.1.0
 */
[[nodiscard]]
CENTURION_API bool operator!=(const FPoint& lhs, const FPoint& rhs) noexcept;

}
