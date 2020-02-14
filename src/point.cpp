#ifndef CENTURION_POINT_SOURCE
#define CENTURION_POINT_SOURCE

#include "point.h"

#include <cmath>

namespace centurion {

CENTURION_DEF Point::Point() noexcept = default;

CENTURION_DEF Point::Point(int x, int y) noexcept : x{x}, y{y} {}

CENTURION_DEF Point::Point(SDL_Point point) noexcept : x{point.x}, y{point.y} {}

CENTURION_DEF void Point::set_x(int x) noexcept { this->x = x; }

CENTURION_DEF void Point::set_y(int y) noexcept { this->y = y; }

CENTURION_DEF void Point::set(const Point& other) noexcept {
  x = other.x;
  y = other.y;
}

CENTURION_DEF void Point::set(int px, int py) noexcept {
  x = px;
  y = py;
}

CENTURION_DEF int Point::get_x() const noexcept { return x; }

CENTURION_DEF int Point::get_y() const noexcept { return y; }

CENTURION_DEF int Point::distance(const Point& a, const Point& b) noexcept {
  return static_cast<int>(
      std::round(std::sqrt(std::abs(a.x - b.x) + std::abs(a.y - b.y))));
}

CENTURION_DEF std::string Point::to_string() const {
  return "[Point | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + "]";
}

CENTURION_DEF Point::operator SDL_Point() const noexcept { return {x, y}; }

CENTURION_DEF bool operator==(const Point& lhs, const Point& rhs) noexcept {
  return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
}

CENTURION_DEF bool operator!=(const Point& lhs, const Point& rhs) noexcept {
  return !(lhs == rhs);
}

CENTURION_DEF Point operator+(const Point& lhs, const Point& rhs) noexcept {
  return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y()};
}

CENTURION_DEF Point operator-(const Point& lhs, const Point& rhs) noexcept {
  return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y()};
}

CENTURION_DEF FPoint::FPoint() noexcept = default;

CENTURION_DEF FPoint::FPoint(float x, float y) noexcept : x{x}, y{y} {}

CENTURION_DEF FPoint::FPoint(SDL_FPoint point) noexcept
    : x{point.x}, y{point.y} {}

CENTURION_DEF void FPoint::set_x(float x) noexcept { this->x = x; }

CENTURION_DEF void FPoint::set_y(float y) noexcept { this->y = y; }

CENTURION_DEF void FPoint::set(const FPoint& other) noexcept {
  x = other.x;
  y = other.y;
}

CENTURION_DEF void FPoint::set(float px, float py) noexcept {
  x = px;
  y = py;
}

CENTURION_DEF float FPoint::get_x() const noexcept { return x; }

CENTURION_DEF float FPoint::get_y() const noexcept { return y; }

CENTURION_DEF float FPoint::distance(const FPoint& a,
                                     const FPoint& b) noexcept {
  return std::sqrt(std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

CENTURION_DEF std::string FPoint::to_string() const {
  return "[FPoint | X: " + std::to_string(x) + ", Y: " + std::to_string(y) +
         "]";
}

CENTURION_DEF FPoint::operator SDL_FPoint() const noexcept { return {x, y}; }

CENTURION_DEF bool FPoint::equals(const FPoint& lhs, const FPoint& rhs,
                                  float epsilon) noexcept {
  return std::abs(lhs.get_x() - rhs.get_x()) < epsilon &&
         std::abs(lhs.get_x() - rhs.get_x()) < epsilon;
}

CENTURION_DEF bool operator==(const FPoint& lhs, const FPoint& rhs) noexcept {
  return FPoint::equals(lhs, rhs);
}

CENTURION_DEF bool operator!=(const FPoint& lhs, const FPoint& rhs) noexcept {
  return !(lhs == rhs);
}

CENTURION_DEF FPoint operator+(const FPoint& lhs, const FPoint& rhs) noexcept {
  return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y()};
}

CENTURION_DEF FPoint operator-(const FPoint& lhs, const FPoint& rhs) noexcept {
  return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y()};
}

}  // namespace centurion

#endif  // CENTURION_POINT_SOURCE