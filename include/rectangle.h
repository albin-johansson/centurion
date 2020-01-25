#pragma once
#include <string>
#include <SDL.h>
#include "centurion_api.h"
#include "point.h"

namespace centurion {

/**
 * The Rect class is a wrapper around an SDL_Rect struct.
 *
 * @since 3.0.0
 */
class CENTURION_API Rect final {
 private:
  SDL_Rect rect{0, 0, 0, 0};

 public:
  /**
   * Creates a rectangle with the components (0, 0, 0, 0).
   *
   * @since 3.0.0
   */
  CENTURION_API Rect() noexcept;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API Rect(int x, int y, int width, int height) noexcept;

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
  CENTURION_API bool intersects(const Rect& other) const noexcept;

  /**
   * Indicates whether or not the rectangle contains the supplied point.
   *
   * @param px the x-coordinate of the point that will be checked.
   * @param py the y-coordinate of the point that will be checked.
   * @return true if the point is contained in the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(int px, int py) const noexcept;

  /**
   * Indicates whether or not the rectangle contains the supplied point.
   *
   * @param point th point that will be checked.
   * @return true if the point is contained in the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(Point point) const noexcept;

  /**
   * Indicates whether or not the rectangle has an area. A rectangle has an area if the width and
   * height are both greater than zero.
   *
   * @return true if the rectangle has an area; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool has_area() const noexcept;

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

  /**
   * Returns a textual representation of the rectangle.
   *
   * @return a textual representation of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  [[nodiscard]]
  CENTURION_API /*implicit*/ operator const SDL_Rect&() const noexcept;

};

/**
 * The FRect class is a wrapper around the SDL_FRect struct.
 *
 * @since 3.0.0
 */
class FRect final {
 private:
  SDL_FRect rect{0, 0, 0, 0};

 public:
  /**
   * Creates a rectangle with all of the components set to 0.
   *
   * @since 3.0.0
   */
  CENTURION_API FRect() noexcept;

  /**
   * @param x the x-coordinate of the rectangle.
   * @param y the y-coordinate of the rectangle.
   * @param width the width of the rectangle.
   * @param height the height of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API FRect(float x, float y, float width, float height) noexcept;

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_x(float x) noexcept;

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param y the new y-coordinate of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_y(float y) noexcept;

  /**
   * Sets the width of the rectangle.
   *
   * @param width the new width of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_width(float width) noexcept;

  /**
   * Sets the height of the rectangle.
   *
   * @param height the new height of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API void set_height(float height) noexcept;

  /**
   * Indicates whether or not the rectangle intersects the supplied rectangle.
   *
   * @param other the rectangle to check for an intersection with.
   * @return true if the rectangles intersect; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool intersects(const FRect& other) const noexcept;

  /**
   * Indicates whether or not the rectangle contains the specified point.
   *
   * @param px the x-coordinate of the point.
   * @param py the y-coordinate of the point.
   * @return true if the point is contained within the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(float px, float py) const noexcept;

  /**
   * Indicates whether or not the rectangle contains the specified point.
   *
   * @param point the point that will be checked.
   * @return true if the point is contained within the rectangle; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool contains(FPoint point) const noexcept;

  /**
   * Indicates whether or not the rectangle has an area. A rectangle has an area if its width and
   * height are both greater than zero.
   *
   * @return true if the rectangle has an area; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool has_area() const noexcept;

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_x() const noexcept;

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_y() const noexcept;

  /**
   * Returns the x-coordinate of the center point of the rectangle.
   *
   * @return the x-coordinate of the center point of the rectangle.
   * @since 3.0.0
   */
  CENTURION_API float get_center_x() const noexcept;

  /**
   * Returns the y-coordinate of the center point of the rectangle.
   *
   * @return the y-coordinate of the center point of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_center_y() const noexcept;

  /**
   * Returns the maximum x-coordinate of the rectangle, which is equivalent to the sum
   * of the x-coordinate and width of the rectangle.
   *
   * @return the maximum x-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_max_x() const noexcept;

  /**
   * Returns the maximum y-coordinate of the rectangle, which is equivalent to the sum
   * of the y-coordinate and height of the rectangle.
   *
   * @return the maximum y-coordinate of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_max_y() const noexcept;

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_width() const noexcept;

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API float get_height() const noexcept;

  /**
   * Returns a textual representation of the rectangle.
   *
   * @return a textual representation of the rectangle.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Returns a reference to the internal SDL_FRect instance.
   *
   * @return a reference to the internal SDL_FRect instance.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API /*implicit*/ operator const SDL_FRect&() const noexcept;
};

}
