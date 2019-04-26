#include "ctn_rectangle.h"
#include <stdexcept>
#include "ctn_bool_converter.h"
#include "ctn_point.h"

using centurion::tools::BoolConverter;
using std::invalid_argument;

namespace centurion {
namespace geo {

Rectangle::Rectangle(int x, int y, int w, int h) {
  if (w < 1 || h < 1) {
    throw invalid_argument("Invalid dimensions for rectangle!");
  }
  rect = {x, y, w, h};
}

Rectangle::Rectangle(int w, int h) : Rectangle(0, 0, w, h) {}

Rectangle::Rectangle() = default;

Rectangle::~Rectangle() = default;

void Rectangle::SetLocation(int x, int y) noexcept {
  SetX(x);
  SetY(y);
}

void Rectangle::SetX(int x) noexcept { rect.x = x; }

void Rectangle::SetY(int y) noexcept { rect.y = y; }

bool Rectangle::Intersects(Rectangle otherRect) const noexcept {
  SDL_bool result = SDL_HasIntersection(&this->rect, &otherRect.rect);
  return BoolConverter::Convert(result);
}

bool Rectangle::Contains(SDL_Point point) const noexcept {
  SDL_bool result = SDL_PointInRect(&point, &rect);
  return BoolConverter::Convert(result);
}

bool Rectangle::Contains(int x, int y) const noexcept {
  SDL_Point point = {x, y};
  return Contains(point);
}

bool Rectangle::Contains(const Point point) const noexcept {
  return Contains(point.GetSDLVersion());
}

Rectangle_sptr Rectangle::CreateShared(int x, int y, int w, int h) {
  return std::make_shared<Rectangle>(x, y, w, h);
}

Rectangle_sptr Rectangle::CreateShared(int w, int h) {
  return std::make_shared<Rectangle>(w, h);
}

Rectangle_uptr Rectangle::CreateUnique(int x, int y, int w, int h) {
  return std::make_unique<Rectangle>(x, y, w, h);
}

Rectangle_uptr Rectangle::CreateUnique(int w, int h) {
  return std::make_unique<Rectangle>(w, h);
}

Rectangle_wptr Rectangle::CreateWeak(int x, int y, int w, int h) {
  return CreateShared(x, y, w, h);
}

Rectangle_wptr Rectangle::CreateWeak(int w, int h) {
  return CreateShared(w, h);
}

}  // namespace geo
}  // namespace centurion