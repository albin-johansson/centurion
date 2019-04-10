#pragma once
#include <SDL_rect.h>
#include <memory>
#include "positionable.h"

namespace centurion {
namespace geo {

/**
\brief The Point class represents a two-dimensional point.
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
  */
  static std::shared_ptr<centurion::geo::Point> Create(int x, int y);

  /**
  \brief Assigns the location of this point.
  \param x - the new x-coordinate.
  \param y - the new y-coordinate.
  */
  void SetLocation(int x, int y) override;

  /**
  \brief Assigns the x-coordinate of this point.
  \param x - the new x-coordinate.
  */
  void SetX(int x) override;

  /**
  \brief Assigns the y-coordinate of this point.
  \param y - the new y-coordinate.
  */
  void SetY(int y) override;

  /**
  \brief Returns the x-coordinate of this point.
  */
  inline int GetX() const override { return point.x; };

  /**
  \brief Returns the y-coordinate of this point.
  */
  inline int GetY() const override { return point.y; };

  /**
  \brief Returns a copy of the internal representation of this Point.
  */
  inline SDL_Point GetSDLVersion() const { return point; }
};

}  // namespace geo
}  // namespace centurion