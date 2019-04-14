#include "rectangle.h"
#include <stdexcept>
#include "boolean_converter.h"
#include "point.h"

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

std::shared_ptr<Rectangle> Rectangle::Create(int x, int y, int w, int h) {
  return std::make_shared<Rectangle>(x, y, w, h);
}

std::shared_ptr<Rectangle> Rectangle::Create(int w, int h) {
  return std::make_shared<Rectangle>(w, h);
}

void Rectangle::SetLocation(int x, int y) noexcept {
  SetX(x);
  SetY(y);
}

void Rectangle::SetX(int x) noexcept { rect.x = x; }

void Rectangle::SetY(int y) noexcept { rect.y = y; }

bool Rectangle::Intersects(const Rectangle otherRect) const noexcept {
  SDL_bool result = SDL_HasIntersection(&this->rect, &otherRect.rect);
  return BooleanConverter::Convert(result);
}

bool Rectangle::Contains(SDL_Point point) const noexcept {
  SDL_bool result = SDL_PointInRect(&point, &rect);
  return BooleanConverter::Convert(result);
}

bool Rectangle::Contains(int x, int y) const noexcept {
  SDL_Point point = {x, y};
  return Contains(point);
}

bool Rectangle::Contains(const Point point) const noexcept {
  return Contains(point.GetSDLVersion());
}