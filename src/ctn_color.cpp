#include "ctn_color.h"

namespace centurion {
namespace visuals {

const Color Color::RED = Color(MAX_VAL, MIN_VAL, MIN_VAL, MAX_VAL);

const Color Color::GREEN = Color(MIN_VAL, MAX_VAL, MIN_VAL, MAX_VAL);

const Color Color::BLUE = Color(MIN_VAL, MIN_VAL, MAX_VAL, MAX_VAL);

const Color Color::WHITE = Color(MAX_VAL, MAX_VAL, MAX_VAL, MAX_VAL);

const Color Color::BLACK = Color(MIN_VAL, MIN_VAL, MIN_VAL, MAX_VAL);

const Color Color::GRAY = Color(70, 70, 70, MAX_VAL);

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; }

Color::Color(Uint8 r, Uint8 g, Uint8 b) : Color(r, g, b, MAX_VAL) {}

Color::Color() : Color(0, 0, 0, MAX_VAL) {}

Color::~Color() = default;

bool Color::Equals(const Color& c) const noexcept {
  return (color.r == c.GetRed()) && (color.g == c.GetGreen()) &&
         (color.b == c.GetBlue()) && (color.a == c.GetAlpha());
}

Color_sptr Color::CreateShared(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  return std::make_shared<Color>(r, g, b, a);
}

Color_uptr Color::CreateUnique(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  return std::make_unique<Color>(r, g, b, a);
}

}  // namespace visuals
}  // namespace centurion