#include "point.h"

namespace centurion {
namespace geo {

Point::Point(int x, int y) { point = {x, y}; }

std::shared_ptr<Point> Point::Create(int x, int y) {
  return std::make_shared<Point>(x, y);
}

void Point::SetLocation(int x, int y) noexcept {
  SetX(x);
  SetY(y);
}

void Point::SetX(int x) noexcept { point.x = x; }

void Point::SetY(int y) noexcept { point.y = y; }

}  // namespace geo
}  // namespace centurion