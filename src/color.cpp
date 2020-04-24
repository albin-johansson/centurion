#ifndef CENTURION_COLOR_SOURCE
#define CENTURION_COLOR_SOURCE

#include "color.h"

namespace centurion {
namespace video {

CENTURION_DEF
const uint8_t Color::max = 0xFF;

CENTURION_DEF
Color::Color(const SDL_Color& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{color.a}
{}

CENTURION_DEF
Color::Color(SDL_Color&& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{color.a}
{}

CENTURION_DEF
Color::Color(const SDL_MessageBoxColor& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{max}
{}

CENTURION_DEF
Color::Color(SDL_MessageBoxColor&& color) noexcept
    : red{color.r}, green{color.g}, blue{color.b}, alpha{max}
{}

CENTURION_DEF
void Color::set_red(uint8_t r) noexcept
{
  this->red = r;
}

CENTURION_DEF
void Color::set_green(uint8_t g) noexcept
{
  this->green = g;
}

CENTURION_DEF
void Color::set_blue(uint8_t b) noexcept
{
  this->blue = b;
}

CENTURION_DEF
void Color::set_alpha(uint8_t a) noexcept
{
  this->alpha = a;
}

CENTURION_DEF
std::string Color::to_string() const
{
  return "[Color | R: " + std::to_string(red) +
         ", G: " + std::to_string(green) + ", B: " + std::to_string(blue) +
         ", A: " + std::to_string(alpha) + "]";
}

CENTURION_DEF
bool operator==(const Color& color, const Color& other) noexcept
{
  return color.get_red() == other.get_red() &&
         color.get_green() == other.get_green() &&
         color.get_blue() == other.get_blue() &&
         color.get_alpha() == other.get_alpha();
}

CENTURION_DEF
bool operator==(const Color& color, const SDL_Color& sdlColor) noexcept
{
  return color.get_red() == sdlColor.r && color.get_green() == sdlColor.g &&
         color.get_blue() == sdlColor.b && color.get_alpha() == sdlColor.a;
}

CENTURION_DEF
bool operator==(const SDL_Color& sdlColor, const Color& color) noexcept
{
  return color == sdlColor;
}

CENTURION_DEF
bool operator==(const Color& color,
                const SDL_MessageBoxColor& msgColor) noexcept
{
  return color.get_red() == msgColor.r && color.get_green() == msgColor.g &&
         color.get_blue() == msgColor.b;
}

CENTURION_DEF
bool operator==(const SDL_MessageBoxColor& msgColor,
                const Color& color) noexcept
{
  return color == msgColor;
}

CENTURION_DEF
bool operator!=(const Color& color, const Color& other) noexcept
{
  return !(color == other);
}

CENTURION_DEF
bool operator!=(const Color& color, const SDL_Color& sdlColor) noexcept
{
  return !(color == sdlColor);
}

CENTURION_DEF
bool operator!=(const SDL_Color& sdlColor, const Color& color) noexcept
{
  return !(sdlColor == color);
}

CENTURION_DEF
bool operator!=(const Color& color,
                const SDL_MessageBoxColor& msgColor) noexcept
{
  return !(color == msgColor);
}

CENTURION_DEF
bool operator!=(const SDL_MessageBoxColor& msgColor,
                const Color& color) noexcept
{
  return !(msgColor == color);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_COLOR_SOURCE