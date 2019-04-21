#pragma once
#include <memory>

namespace centurion {
namespace geo {

/**
\brief The IPositionable class is an interface for objects that are positionable
(in two dimensions).
\since 1.0.0
*/
class IPositionable {
 protected:
  IPositionable() = default;

 public:
  virtual ~IPositionable() = default;

  /**
  \brief Sets the x-coordinate of this object.
  \param x - the new x-coordinate.
  \since 1.0.0
  */
  virtual void SetX(int x) = 0;

  /**
  \brief Sets the y-coordinate of this object.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  virtual void SetY(int y) = 0;

  /**
  \brief Sets the location of this object.
  \param x - the new x-coordinate.
  \param y - the new y-coordinate.
  \since 1.0.0
  */
  virtual void SetLocation(int x, int y) = 0;

  /**
  \brief Returns the x-coordinate of this object.
  \since 1.0.0
  */
  virtual int GetX() const = 0;

  /**
  \brief Returns the y-coordinate of this object.
  \since 1.0.0
  */
  virtual int GetY() const = 0;
};

typedef std::shared_ptr<IPositionable> IPositionable_sptr;
typedef std::unique_ptr<IPositionable> IPositionable_uptr;
typedef std::weak_ptr<IPositionable> IPositionable_wptr;

}  // namespace geo
}  // namespace centurion