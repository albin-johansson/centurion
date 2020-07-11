#ifndef CENTURION_SURFACE_SOURCE
#define CENTURION_SURFACE_SOURCE

#include "surface.hpp"

#include <SDL_image.h>

#include "error.hpp"

namespace centurion {

CENTURION_DEF
Surface::Surface(czstring file)
{
  if (!file) {
    throw centurion_exception{"Can't create Surface from null path!"};
  }
  m_surface = IMG_Load(file);
  if (!m_surface) {
    throw detail::Error::from_image("Failed to create Surface!");
  }
}

CENTURION_DEF
Surface::Surface(owner<SDL_Surface*> surface)
{
  if (!surface) {
    throw centurion_exception{"Cannot create Surface from null SDL_Surface!"};
  } else {
    this->m_surface = surface;
  }
}

CENTURION_DEF
Surface::Surface(const Surface& other)
{
  copy(other);
}

CENTURION_DEF
Surface::Surface(Surface&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Surface::~Surface() noexcept
{
  destroy();
}

CENTURION_DEF
auto Surface::operator=(Surface&& other) noexcept -> Surface&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
auto Surface::operator=(const Surface& other) -> Surface&
{
  if (this != &other) {
    copy(other);
  }
  return *this;
}

CENTURION_DEF
void Surface::destroy() noexcept
{
  if (m_surface) {
    SDL_FreeSurface(m_surface);
  }
}

CENTURION_DEF
void Surface::move(Surface&& other) noexcept
{
  destroy();
  m_surface = other.m_surface;
  other.m_surface = nullptr;
}

CENTURION_DEF
void Surface::copy(const Surface& other) noexcept
{
  destroy();
  m_surface = other.copy_surface();
}

CENTURION_DEF
auto Surface::in_bounds(const point_i& point) const noexcept -> bool
{
  return !(point.x() < 0 || point.y() < 0 || point.x() >= width() ||
           point.y() >= height());
}

CENTURION_DEF
auto Surface::must_lock() const noexcept -> bool
{
  return SDL_MUSTLOCK(m_surface);
}

CENTURION_DEF
auto Surface::lock() noexcept -> bool
{
  if (must_lock()) {
    const auto result = SDL_LockSurface(m_surface);
    return result == 0;
  } else {
    return true;
  }
}

CENTURION_DEF
void Surface::unlock() noexcept
{
  if (must_lock()) {
    SDL_UnlockSurface(m_surface);
  }
}

CENTURION_DEF
auto Surface::copy_surface() const -> SDL_Surface*
{
  auto* copy = SDL_DuplicateSurface(m_surface);
  if (!copy) {
    throw detail::Error::from_core("Failed to duplicate Surface!");
  } else {
    return copy;
  }
}

CENTURION_DEF
void Surface::set_pixel(const point_i& pixel, const color& color) noexcept
{
  if (!in_bounds(pixel)) {
    return;
  }

  const auto success = lock();
  if (!success) {
    return;
  }

  const int nPixels = (m_surface->pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    const auto value = SDL_MapRGBA(m_surface->format,
                                   color.red(),
                                   color.green(),
                                   color.blue(),
                                   color.alpha());
    auto* pixels = reinterpret_cast<u32*>(m_surface->pixels);
    pixels[index] = value;
  }

  unlock();
}

CENTURION_DEF
void Surface::set_alpha(u8 alpha) noexcept
{
  SDL_SetSurfaceAlphaMod(m_surface, alpha);
}

CENTURION_DEF
void Surface::set_color_mod(const color& color) noexcept
{
  SDL_SetSurfaceColorMod(m_surface, color.red(), color.green(), color.blue());
}

CENTURION_DEF
void Surface::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetSurfaceBlendMode(m_surface, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
auto Surface::alpha() const noexcept -> u8
{
  u8 alpha = 0xFF;
  SDL_GetSurfaceAlphaMod(m_surface, &alpha);
  return alpha;
}

CENTURION_DEF
auto Surface::color_mod() const noexcept -> color
{
  u8 r = 0, g = 0, b = 0;
  SDL_GetSurfaceColorMod(m_surface, &r, &g, &b);
  return color{r, g, b};
}

CENTURION_DEF
auto Surface::blend_mode() const noexcept -> enum blend_mode  //
{                                                             //
  SDL_BlendMode mode;                                         //
  SDL_GetSurfaceBlendMode(m_surface, &mode);
  return static_cast<enum blend_mode>(mode);
}

// CENTURION_DEF
// Texture Surface::to_texture(const Renderer& renderer) const noexcept
//{
//  return Texture{SDL_CreateTextureFromSurface(renderer.get(), m_surface)};
//}

CENTURION_DEF
auto Surface::convert(pixel_format format) const -> Surface
{
  const auto pixelFormat = static_cast<u32>(format);
  auto* converted = SDL_ConvertSurfaceFormat(m_surface, pixelFormat, 0);
  SDL_SetSurfaceBlendMode(converted, static_cast<SDL_BlendMode>(blend_mode()));
  return Surface{converted};
}

}  // namespace centurion

#endif  // CENTURION_SURFACE_SOURCE