#include "color.h"

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

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  color = {r, g, b, a};
}

Color::~Color() = default;

Color_sptr Color::CreateShared(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return std::make_shared<Color>(r, g, b, a);
}

Color_uptr Color::CreateUnique(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return std::make_unique<Color>(r, g, b, a);
}

Color_wptr Color::CreateWeak(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return CreateShared(r, g, b, a);
}

}  // namespace visuals
}  // namespace centurion