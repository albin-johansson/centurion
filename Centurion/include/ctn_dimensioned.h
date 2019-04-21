#pragma once
#include <memory>

namespace centurion {
namespace geo {

/**
\brief The IDimensioned class is an interface for objects that have both width
and height.
\since 1.0.0
*/
class IDimensioned {
 protected:
  IDimensioned() = default;

 public:
  virtual ~IDimensioned() = default;

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

typedef std::shared_ptr<IDimensioned> IDimensioned_sptr;
typedef std::unique_ptr<IDimensioned> IDimensioned_uptr;
typedef std::weak_ptr<IDimensioned> IDimensioned_wptr;

}  // namespace geo
}  // namespace centurion