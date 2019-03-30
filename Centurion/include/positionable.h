#pragma once

namespace centurion {
namespace geo {

class Positionable {
 protected:
  Positionable() = default;

 public:
  virtual ~Positionable() = default;

  virtual void SetX(int x) = 0;

  virtual void SetY(int y) = 0;

  virtual void SetLocation(int x, int y) = 0;

  virtual int GetX() const = 0;

  virtual int GetY() const = 0;
};

}  // namespace geo
}  // namespace centurion