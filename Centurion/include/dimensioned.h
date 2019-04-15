#pragma once
#include <memory>

namespace centurion {
namespace geo {

/**
\brief The Dimensioned class acts as an interface for objects that have both
width and height.
\since 1.0.0
*/
class Dimensioned {
 protected:
  Dimensioned() = default;

 public:
  virtual ~Dimensioned() = default;

  /**
  \brief Returns the width of this object.
  \since 1.0.0
  */
  virtual int GetWidth() const = 0;

  /**
  \brief Returns the height of this object.
  \since 1.0.0
  */
  virtual int GetHeight() const = 0;
};

typedef std::shared_ptr<centurion::geo::Dimensioned> Dimensioned_sptr;
typedef std::unique_ptr<centurion::geo::Dimensioned> Dimensioned_uptr;
typedef std::weak_ptr<centurion::geo::Dimensioned> Dimensioned_wptr;

}  // namespace geo
}  // namespace centurion