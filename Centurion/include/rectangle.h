#pragma once
#include <SDL_rect.h>
#include <memory>
#include "dimensioned.h"
#include "point.h"
#include "positionable.h"

namespace centurion {
namespace geo {

class Rectangle;
typedef std::shared_ptr<Rectangle> Rectangle_sptr;
typedef std::unique_ptr<Rectangle> Rectangle_uptr;
typedef std::weak_ptr<Rectangle> Rectangle_wptr;

/**
\brief The Rectangle class quite simply represents a rectangle.
\since 1.0.0
*/
class Rectangle : public centurion::geo::Positionable,
                  public centurion::geo::Dimensioned {
 private:
  SDL_Rect rect;

  bool Contains(SDL_Point point) const noexcept;

 public:
  /**
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \param w - the width of the rectangle.
  \param h - the height of the rectangle.
  */
  Rectangle(int x, int y, int w, int h);

  /**
  \param w - the width of the rectangle.
  \param h - the height of the rectangle.
  */
  Rectangle(int w, int h);

  ~Rectangle() override;

  /**
  \brief Assigns the location of this rectangle.
  \param x - the new x-coordinate.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetLocation(int x, int y) noexcept override;

  /**
  \brief Assigns the x-coordinate of this rectangle.
  \param x - the new x-coordinate.
  \since 1.0.0
  */
  void SetX(int x) noexcept override;

  /**
  \brief Assigns the y-coordinate of this rectangle.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetY(int y) noexcept override;

  /**
  \brief Indicates whether or not this rectangle intersects another rectangle.
  Returns true if the supplied rectangle intersects this rectangle, returns
  false otherwise.
  \param rect - the rectangle that will be checked with this rectangle.
  \since 1.0.0
  */
  bool Intersects(const centurion::geo::Rectangle rect) const noexcept;

  /**
  \brief Indicates whether or not this rectangle contains the specified point.
  Returns true if the point is contained in this rectangle, returns false
  otherwise.
  \param x - the x-coordinate of the point to check.
  \param y - the y-coordinate of the point to check.
  \since 1.0.0
  */
  bool Contains(int x, int y) const noexcept;

  /**
  \brief Indicates whether or not this rectangle contains the specified point.
  Returns true if the point is contained in this rectangle, returns false
  otherwise.
  \param point - the point that will be checked.
  \since 1.0.0
  */
  bool Contains(centurion::geo::Point point) const noexcept;

  /**
  \brief Returns the x-coordinate of this rectangle.
  \since 1.0.0
  */
  int GetX() const noexcept override { return rect.x; };

  /**
  \brief Returns the y-coordinate of this rectangle.
  \since 1.0.0
  */
  int GetY() const noexcept override { return rect.y; };

  /**
  \brief Returns the width of this rectangle.
  \since 1.0.0
  */
  int GetWidth() const noexcept override { return rect.w; };

  /**
  \brief Returns the height of this rectangle.
  \since 1.0.0
  */
  int GetHeight() const noexcept override { return rect.h; };

  /**
  \brief Creates and returns an SDL_Rect that represents this rectangle.
  \since 1.0.0
  */
  SDL_Rect GetSDLVersion() const noexcept { return rect; };

  /**
  \brief Returns a shared pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \param w - the width of the rectangle.
  \param h - the height of the rectangle.
  \since 1.1.0
  */
  static Rectangle_sptr CreateShared(int x, int y, int w, int h);

  /**
  \brief Returns a shared pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \since 1.1.0
  */
  static Rectangle_sptr CreateShared(int x, int y);

  /**
  \brief Returns a unique pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \param w - the width of the rectangle.
  \param h - the height of the rectangle.
  \since 1.1.0
  */
  static Rectangle_uptr CreateUnique(int x, int y, int w, int h);

  /**
  \brief Returns a unique pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \since 1.1.0
  */
  static Rectangle_uptr CreateUnique(int x, int y);

  /**
  \brief Returns a weak pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \param w - the width of the rectangle.
  \param h - the height of the rectangle.
  \since 1.1.0
  */
  static Rectangle_wptr CreateWeak(int x, int y, int w, int h);

  /**
  \brief Returns a weak pointer that points to a Rectangle.
  \param x - the initial x-coordinate of the rectangle.
  \param y - the initial y-coordinate of the rectangle.
  \since 1.1.0
  */
  static Rectangle_wptr CreateWeak(int x, int y);
};

}  // namespace geo
}  // namespace centurion