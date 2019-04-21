#include "ctn_color.h"

namespace centurion {
namespace visuals {

const Color Color::RED =
    Color(Color::MAX_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);

const Color Color::GREEN =
    Color(Color::MIN_VAL, Color::MAX_VAL, Color::MIN_VAL, Color::MAX_VAL);

const Color Color::BLUE =
    Color(Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL, Color::MAX_VAL);

const Color Color::WHITE =
    Color(Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL);

const Color Color::BLACK =
    Color(Color::MIN_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);

const Color Color::GRAY = Color(70, 70, 70, Color::MAX_VAL);

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { color = {r, g, b, a}; }

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

}  // namespace visuals
}  // namespace centurion