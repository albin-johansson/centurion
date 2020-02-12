#include "point.h"

#include <cmath>

namespace centurion {

Point::Point() noexcept = default;

Point::Point(int x, int y) noexcept : x{x}, y{y} {}

Point::Point(SDL_Point point) noexcept : x{point.x}, y{point.y} {}

void Point::set_x(int x) noexcept { this->x = x; }

void Point::set_y(int y) noexcept { this->y = y; }

void Point::set(const Point& other) noexcept {
  x = other.x;
  y = other.y;
}

void Point::set(int px, int py) noexcept {
  x = px;
  y = py;
}

int Point::get_x() const noexcept { return x; }

int Point::get_y() const noexcept { return y; }

int Point::distance(const Point& a, const Point& b) noexcept {
  return static_cast<int>(
      std::round(std::sqrt(std::abs(a.x - b.x) + std::abs(a.y - b.y))));
}

std::string Point::to_string() const {
  return "[Point | X: " + std::to_string(x) + ", Y: " + std::to_string(y) + "]";
}

Point::operator SDL_Point() const noexcept { return {x, y}; }

bool operator==(const Point& lhs, const Point& rhs) noexcept {
  return lhs.get_x() == rhs.get_x() && lhs.get_y() == rhs.get_y();
}

bool operator!=(const Point& lhs, const Point& rhs) noexcept {
  return !(lhs == rhs);
}

Point operator+(const Point& lhs, const Point& rhs) noexcept {
  return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y()};
}

Point operator-(const Point& lhs, const Point& rhs) noexcept {
  return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y()};
}

FPoint::FPoint() noexcept = default;

FPoint::FPoint(float x, float y) noexcept : x{x}, y{y} {}

FPoint::FPoint(SDL_FPoint point) noexcept : x{point.x}, y{point.y} {}

void FPoint::set_x(float x) noexcept { this->x = x; }

void FPoint::set_y(float y) noexcept { this->y = y; }

void FPoint::set(const FPoint& other) noexcept {
  x = other.x;
  y = other.y;
}

void FPoint::set(float px, float py) noexcept {
  x = px;
  y = py;
}

float FPoint::get_x() const noexcept { return x; }

float FPoint::get_y() const noexcept { return y; }

float FPoint::distance(const FPoint& a, const FPoint& b) noexcept {
  return std::sqrt(std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

std::string FPoint::to_string() const {
  return "[FPoint | X: " + std::to_string(x) + ", Y: " + std::to_string(y) +
         "]";
}

FPoint::operator SDL_FPoint() const noexcept { return {x, y}; }

bool FPoint::equals(const FPoint& lhs, const FPoint& rhs,
                    float epsilon) noexcept {
  return std::abs(lhs.get_x() - rhs.get_x()) < epsilon &&
         std::abs(lhs.get_x() - rhs.get_x()) < epsilon;
}

bool operator==(const FPoint& lhs, const FPoint& rhs) noexcept {
  return FPoint::equals(lhs, rhs);
}

bool operator!=(const FPoint& lhs, const FPoint& rhs) noexcept {
  return !(lhs == rhs);
}

FPoint operator+(const FPoint& lhs, const FPoint& rhs) noexcept {
  return {lhs.get_x() + rhs.get_x(), lhs.get_y() + rhs.get_y()};
}

FPoint operator-(const FPoint& lhs, const FPoint& rhs) noexcept {
  return {lhs.get_x() - rhs.get_x(), lhs.get_y() - rhs.get_y()};
}

}  // namespace centurion
