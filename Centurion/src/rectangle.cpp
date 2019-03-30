#include "rectangle.h"
#include <stdexcept>
#include "ctn_tools.h"
#include "point.h"
#include "positionable.h"

using centurion::geo::Point;
using centurion::geo::Rectangle;
using centurion::tools::BooleanConverter;
using std::invalid_argument;

Rectangle::Rectangle(int x, int y, int w, int h) {
  if (w < 1 || h < 1) {
    throw invalid_argument("Invalid dimensions for rectangle!");
  }
  rect = {x, y, w, h};
}

Rectangle::Rectangle(int w, int h) : Rectangle(0, 0, w, h) {}

Rectangle::~Rectangle() = default;

void Rectangle::SetLocation(int x, int y) {
  SetX(x);
  SetY(y);
}

void Rectangle::SetX(int x) { rect.x = x; }

void Rectangle::SetY(int y) { rect.y = y; }

bool Rectangle::Intersects(const Rectangle& otherRect) const {
  SDL_bool result = SDL_HasIntersection(&this->rect, &otherRect.rect);
  return BooleanConverter::Convert(result);
}

bool Rectangle::Contains(int x, int y) const {
  SDL_Point point = {x, y};
  SDL_bool result = SDL_PointInRect(&point, &this->rect);
  return BooleanConverter::Convert(result);
}

bool Rectangle::Contains(const Point& point) const {
  return Contains(point.GetX(), point.GetY());
}