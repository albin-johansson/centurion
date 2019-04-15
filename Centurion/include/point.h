#pragma once
#include <SDL_rect.h>
#include <memory>
#include "positionable.h"

namespace centurion {
namespace geo {

/**
\brief The Point class represents a two-dimensional point.
\since 1.0.0
*/
class Point : public centurion::geo::Positionable {
 private:
  SDL_Point point;

 public:
  /**
  \param x - the desired initial x-coordinate.
  \param y - the desired initial y-coordinate.
  */
  Point(int x, int y);

  ~Point() override = default;

  /**
  \brief Creates and returns a heap allocated Point instance.
  \param x - the desired initial x-coordinate.
  \param y - the desired initial y-coordinate.
  \since 1.0.0 ? // FIXME
  */
  static std::shared_ptr<centurion::geo::Point> Create(int x, int y);

  /**
  \brief Assigns the location of this point.
  \param x - the new x-coordinate.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetLocation(int x, int y) noexcept override;

  /**
  \brief Assigns the x-coordinate of this point.
  \param x - the new x-coordinate.
  \since 1.0.0
  */
  void SetX(int x) noexcept override;

  /**
  \brief Assigns the y-coordinate of this point.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetY(int y) noexcept override;

  /**
  \brief Returns the x-coordinate of this point.
  \since 1.0.0
  */
  inline int GetX() const noexcept override { return point.x; };

  /**
  \brief Returns the y-coordinate of this point.
  \since 1.0.0
  */
  inline int GetY() const noexcept override { return point.y; };

  /**
  \brief Returns a copy of the internal representation of this Point.
  \since 1.0.0
  */
  inline SDL_Point GetSDLVersion() const noexcept { return point; }
};

typedef std::shared_ptr<centurion::geo::Point> Point_sptr;
typedef std::unique_ptr<centurion::geo::Point> Point_uptr;
typedef std::weak_ptr<centurion::geo::Point> Point_wptr;

}  // namespace geo
}  // namespace centurion