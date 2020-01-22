#pragma once
#include <SDL.h>
#include "centurion_api.h"
#include "point.h"

namespace centurion {

/**
 * The Rectangle class is a wrapper around an SDL_Rect struct.
 *
 * @since 3.0.0
 */
class CENTURION_API Rectangle final {
 private:
  SDL_Rect rect{0, 0, 0, 0};

 public:
  /**
   * Creates a rectangle with the components (0, 0, 0, 0).
   *
   * @since 3.0.0
   */
  CENTURION_API Rectangle() noexcept;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API Rectangle(int x, int y, int width, int height) noexcept;

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param x the x-coordinate of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_x(int x) noexcept;

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param y the y-coordinate of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_y(int y) noexcept;

  /**
   * Sets the width of the rectangle.
   *
   * @param width the width of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_width(int width) noexcept;

  /**
   * Sets the height of the rectangle.
   *
   * @param height the height of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_height(int height) noexcept;

  /**
   * Indicates whether or not the supplied rectangle intersects this rectangle.
   *
   * @param other the rectangle that will be checked with this rectangle.
   * @return true if the rectangles intersect; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool intersects(const Rectangle& other) noexcept;

  /**
   * Indicates whether or not the rectangle contains the supplied point.
   *
   * @param px the x-coordinate of the point that will be checked.
   * @param py the y-coordinate of the point that will be checked.
   * @return true if the point is contained in the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(int px, int py) noexcept;

  /**
   * Indicates whether or not the rectangle contains the supplied point.
   *
   * @param point th point that will be checked.
   * @return true if the point is contained in the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(Point point) noexcept;

  /**
   * Indicates whether or not the rectangle has an area. A rectangle has an area if the width and
   * height are both greater than zero.
   *
   * @return true if the rectangle has an area; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool has_no_area() const noexcept;

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_x() const noexcept;

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_y() const noexcept;

  /**
   * Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_center_x() const noexcept;

  /**
   * Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_center_y() const noexcept;

  /**
   * Returns the maximum x-coordinate of the rectangle. The returned value is the same as the
   * x-coordinate added with the width of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_max_x() const noexcept;

  /**
   * Returns the maximum y-coordinate of the rectangle. The returned value is the same as the
   * y-coordinate added with the width of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_max_y() const noexcept;

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_width() const noexcept;

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_height() const noexcept;

  [[nodiscard]]
  CENTURION_API /*implicit*/ operator const SDL_Rect&() const noexcept;

};

class FRectangle final {
 private:
  float x = 0;
  float y = 0;
  float width = 0;
  float height = 0;

};

}
