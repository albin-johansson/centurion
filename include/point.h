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
   * Converts the point into an SDL_FPoint.
   *
   * @return an SDL_FPoint instance, based on the point.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API /*implicit*/ operator SDL_FPoint() const noexcept;
};

}
