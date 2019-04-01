#include "point.h"

namespace centurion {
namespace geo {

Point::Point(int x, int y) { point = {x, y}; }

void Point::SetLocation(int x, int y) {
  SetX(x);
  SetY(y);
}

void Point::SetX(int x) { point.x = x; }

void Point::SetY(int y) { point.y = y; }

}  // namespace geo
}  // namespace centurion