#pragma once

namespace centurion {
namespace geo {

class Dimensioned {
 protected:
  Dimensioned() = default;

 public:
  virtual ~Dimensioned() = default;

  virtual int GetWidth() const = 0;

  virtual int GetHeight() const = 0;
};

}  // namespace geo
}  // namespace centurion