#pragma once
#include <SDL_rect.h>
#include <memory>

namespace centurion {
namespace geo {

class Point;
using Point_sptr = std::shared_ptr<Point>;
using Point_uptr = std::unique_ptr<Point>;
using Point_wptr = std::weak_ptr<Point>;

/**
\brief The Point class represents a two-dimensional point.
\since 1.0.0
*/
class Point final {
 private:
  SDL_Point point = {0, 0};

 public:
  /**
  \param x - the desired initial x-coordinate.
  \param y - the desired initial y-coordinate.
  */
  Point(int x, int y);

  Point();

  ~Point();

  /**
  \brief Assigns the x-coordinate of this point.
  \param x - the new x-coordinate.
  \since 1.0.0
  */
  void SetX(int x) noexcept;

  /**
  \brief Assigns the y-coordinate of this point.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetY(int y) noexcept;

  /**
  \brief Returns the x-coordinate of this point.
  \since 1.0.0
  */
  inline int GetX() const noexcept { return point.x; };

  /**
  \brief Returns the y-coordinate of this point.
  \since 1.0.0
  */
  inline int GetY() const noexcept { return point.y; };

  /**
  \brief Returns a copy of the internal representation of this Point.
  \since 1.0.0
  */
  inline SDL_Point GetSDLVersion() const noexcept { return point; }

  /**
  \brief Returns a shared pointer to a Point instance.
  \param x - the initial x-coordinate of the point.
  \param y - the initial y-coordinate of the point.
  \since 1.1.0
  */
  static Point_sptr CreateShared(int x, int y);

  /**
  \brief Returns a unique pointer to a Point instance.
  \param x - the initial x-coordinate of the point.
  \param y - the initial y-coordinate of the point.
  \since 1.1.0
  */
  static Point_uptr CreateUnique(int x, int y);
};

}  // namespace geo
}  // namespace centurion