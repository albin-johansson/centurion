#include "ctn_color.h"

namespace centurion {
namespace visuals {

// ----------------------------------- Public ----------------------------------

const Color Color::RED = Color(MAX_VAL, MIN_VAL, MIN_VAL, MAX_VAL);

const Color Color::GREEN = Color(MIN_VAL, MAX_VAL, MIN_VAL, MAX_VAL);

const Color Color::BLUE = Color(MIN_VAL, MIN_VAL, MAX_VAL, MAX_VAL);

const Color Color::WHITE = Color(MAX_VAL, MAX_VAL, MAX_VAL, MAX_VAL);

const Color Color::BLACK = Color(MIN_VAL, MIN_VAL, MIN_VAL, MAX_VAL);

const Color Color::GRAY = Color(70, 70, 70, MAX_VAL);

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; }

Color::Color(Uint8 r, Uint8 g, Uint8 b) : Color(r, g, b, MAX_VAL) {}

Color::~Color() = default;

Color_sptr Color::CreateShared(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  return std::make_shared<Color>(r, g, b, a);
}

Color_uptr Color::CreateUnique(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  return std::make_unique<Color>(r, g, b, a);
}

Color_wptr Color::CreateWeak(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  return CreateShared(r, g, b, a);
}

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion