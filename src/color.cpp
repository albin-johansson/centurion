#ifndef CENTURION_COLOR_SOURCE
#define CENTURION_COLOR_SOURCE

#include "color.h"

namespace centurion {
namespace video {

CENTURION_DEF const uint8_t Color::max = 0xFF;

CENTURION_DEF Color::Color(Color&& other) noexcept
    : red{other.red}, green{other.green}, blue{other.blue}, alpha{other.alpha}
{}

CENTURION_DEF Color::Color(const SDL_Color& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{color.a}
{}

CENTURION_DEF Color::Color(SDL_Color&& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{color.a}
{}

CENTURION_DEF Color::Color(const SDL_MessageBoxColor& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{max}
{}

CENTURION_DEF Color::Color(SDL_MessageBoxColor&& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{max}
{}

CENTURION_DEF Color& Color::operator=(const Color& other) noexcept
{
  this->red = other.red;
  this->green = other.green;
  this->blue = other.blue;
  this->alpha = other.alpha;
  return *this;
}

CENTURION_DEF Color& Color::operator=(Color&& other) noexcept
{
  this->red = other.red;
  this->green = other.green;
  this->blue = other.blue;
  this->alpha = other.alpha;
  return *this;
}

CENTURION_DEF void Color::set_red(uint8_t r) noexcept
{
  this->red = r;
}

CENTURION_DEF void Color::set_green(uint8_t g) noexcept
{
  this->green = g;
}

CENTURION_DEF void Color::set_blue(uint8_t b) noexcept
{
  this->blue = b;
}

CENTURION_DEF void Color::set_alpha(uint8_t a) noexcept
{
  this->alpha = a;
}

CENTURION_DEF std::string Color::to_string() const
{
  return "[Color | R: " + std::to_string(red) +
         ", G: " + std::to_string(green) + ", B: " + std::to_string(blue) +
         ", A: " + std::to_string(alpha) + "]";
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_COLOR_SOURCE