#include "ctn_point.h"

namespace centurion {
namespace geo {

Point::Point(int x, int y) { point = {x, y}; }

Point::Point() = default;

Point::~Point() = default;

void Point::SetX(int x) noexcept { point.x = x; }

void Point::SetY(int y) noexcept { point.y = y; }

Point_sptr Point::CreateShared(int x, int y) {
  return std::make_shared<Point>(x, y);
}

Point_uptr Point::CreateUnique(int x, int y) {
  return std::make_unique<Point>(x, y);
}

}  // namespace geo
}  // namespace centurion