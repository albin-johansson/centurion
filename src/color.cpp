#ifndef CENTURION_COLOR_SOURCE
#define CENTURION_COLOR_SOURCE

#include "color.h"

namespace centurion {
namespace video {

CENTURION_DEF
const Uint8 Color::max = 0xFF;

CENTURION_DEF
Color::Color(const SDL_Color& color) noexcept
    : m_red{color.r}, m_green{color.g}, m_blue{color.b}, m_alpha{color.a}
{}

CENTURION_DEF
Color::Color(SDL_Color&& color) noexcept
    : m_red{color.r}, m_green{color.g}, m_blue{color.b}, m_alpha{color.a}
{}

CENTURION_DEF
Color::Color(const SDL_MessageBoxColor& color) noexcept
    : m_red{color.r}, m_green{color.g}, m_blue{color.b}, m_alpha{max}
{}

CENTURION_DEF
Color::Color(SDL_MessageBoxColor&& color) noexcept
    : m_red{color.r}, m_green{color.g}, m_blue{color.b}, m_alpha{max}
{}

CENTURION_DEF
void Color::set_red(Uint8 r) noexcept
{
  this->m_red = r;
}

CENTURION_DEF
void Color::set_green(Uint8 g) noexcept
{
  this->m_green = g;
}

CENTURION_DEF
void Color::set_blue(Uint8 b) noexcept
{
  this->m_blue = b;
}

CENTURION_DEF
void Color::set_alpha(Uint8 a) noexcept
{
  this->m_alpha = a;
}

CENTURION_DEF
Uint8 Color::red() const noexcept
{
  return m_red;
}

CENTURION_DEF
Uint8 Color::green() const noexcept
{
  return m_green;
}

CENTURION_DEF
Uint8 Color::blue() const noexcept
{
  return m_blue;
}

CENTURION_DEF
Uint8 Color::alpha() const noexcept
{
  return m_alpha;
}

CENTURION_DEF
std::string Color::to_string() const
{
  return "[Color | R: " + std::to_string(m_red) +
         ", G: " + std::to_string(m_green) + ", B: " + std::to_string(m_blue) +
         ", A: " + std::to_string(m_alpha) + "]";
}

CENTURION_DEF
Color::operator SDL_Color() const noexcept
{
  return {m_red, m_green, m_blue, m_alpha};
}

CENTURION_DEF
Color::operator const SDL_Color*() const noexcept
{
  return reinterpret_cast<const SDL_Color*>(this);
}

CENTURION_DEF
Color::operator SDL_MessageBoxColor() const noexcept
{
  return {m_red, m_green, m_blue};
}

CENTURION_DEF
bool operator==(const Color& color, const Color& other) noexcept
{
  return color.red() == other.red() && color.green() == other.green() &&
         color.blue() == other.blue() && color.alpha() == other.alpha();
}

CENTURION_DEF
bool operator==(const Color& color, const SDL_Color& sdlColor) noexcept
{
  return color.red() == sdlColor.r && color.green() == sdlColor.g &&
         color.blue() == sdlColor.b && color.alpha() == sdlColor.a;
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
  return color.red() == msgColor.r && color.green() == msgColor.g &&
         color.blue() == msgColor.b;
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