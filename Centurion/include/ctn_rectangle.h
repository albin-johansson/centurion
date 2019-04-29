#pragma once
#include <SDL_rect.h>
#include <memory>
#include "ctn_point.h"

namespace centurion {
namespace geo {

class Rectangle;
using Rectangle_sptr = std::shared_ptr<Rectangle>;
using Rectangle_uptr = std::unique_ptr<Rectangle>;
using Rectangle_wptr = std::weak_ptr<Rectangle>;

/**
\brief The Rectangle class quite simply represents a rectangle.
\since 1.0.0
*/
class Rectangle final {
 private:
  SDL_Rect rect = {0, 0, 1, 1};

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

  Rectangle();

  ~Rectangle();

  /**
  \brief Assigns the x-coordinate of this rectangle.
  \param x - the new x-coordinate.
  \since 1.0.0
  */
  void SetX(int x) noexcept;

  /**
  \brief Assigns the y-coordinate of this rectangle.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  void SetY(int y) noexcept;

  /**
  \brief Indicates whether or not this rectangle intersects another rectangle.
  Returns true if the supplied rectangle intersects this rectangle, returns
  false otherwise.
  \param rect - the rectangle that will be checked with this rectangle.
  \since 1.0.0
  */
  bool Intersects(Rectangle rect) const noexcept;

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
  bool Contains(Point point) const noexcept;

  /**
  \brief Returns the x-coordinate of this rectangle.
  \since 1.0.0
  */
  inline int GetX() const noexcept { return rect.x; }

  /**
  \brief Returns the y-coordinate of this rectangle.
  \since 1.0.0
  */
  inline int GetY() const noexcept { return rect.y; }

  /**
  \brief Returns the maximum x-coordinate of this rectangle.
  \since 2.0.0
  */
  inline int GetMaxX() const noexcept { return (rect.x + rect.w); }

  /**
  \brief Returns the maximum y-coordinate of this rectangle.
  \since 2.0.0
  */
  inline int GetMaxY() const noexcept { return (rect.y + rect.h); }

  /**
  \brief Returns the width of this rectangle.
  \since 1.0.0
  */
  inline int GetWidth() const noexcept { return rect.w; }

  /**
  \brief Returns the height of this rectangle.
  \since 1.0.0
  */
  inline int GetHeight() const noexcept { return rect.h; }

  /**
  \brief Creates and returns an SDL_Rect that represents this rectangle.
  \since 1.0.0
  */
  inline SDL_Rect GetSDLVersion() const noexcept { return rect; }

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