#ifndef CENTURION_SURFACE_SOURCE
#define CENTURION_SURFACE_SOURCE

#include "surface.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "renderer.h"
#include "texture.h"

namespace centurion {

CENTURION_DEF
Surface::Surface(CZString file)
{
  if (!file) {
    throw CenturionException{"Can't create surface from null path!"};
  }
  m_surface = IMG_Load(file);
  if (!m_surface) {
    throw CenturionException{"Failed to load surface!"};
  }
}

CENTURION_DEF
Surface::Surface(Owner<SDL_Surface*> surface)
{
  if (!surface) {
    throw CenturionException{"Cannot create surface from null SDL_Surface!"};
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
  move(std::forward<Surface>(other));
}

CENTURION_DEF
Surface::~Surface() noexcept
{
  destroy();
}

CENTURION_DEF
Surface& Surface::operator=(Surface&& other) noexcept
{
  if (this != &other) {
    move(std::forward<Surface>(other));
  }
  return *this;
}

CENTURION_DEF
Surface& Surface::operator=(const Surface& other)
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
SDL_Surface* Surface::copy_surface() const
{
  auto* copy = SDL_DuplicateSurface(m_surface);
  if (!copy) {
    throw CenturionException{"Failed to duplicate SDL surface!"};
  } else {
    return copy;
  }
}

CENTURION_DEF
void Surface::set_alpha(Uint8 alpha) noexcept
{
  SDL_SetSurfaceAlphaMod(m_surface, alpha);
}

CENTURION_DEF
void Surface::set_color_mod(const Color& color) noexcept
{
  SDL_SetSurfaceColorMod(m_surface, color.red(), color.green(), color.blue());
}

CENTURION_DEF
void Surface::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetSurfaceBlendMode(m_surface, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
Uint8 Surface::alpha() const noexcept
{
  Uint8 alpha = 0xFF;
  SDL_GetSurfaceAlphaMod(m_surface, &alpha);
  return alpha;
}

CENTURION_DEF
Color Surface::color_mod() const noexcept
{
  Uint8 r = 0, g = 0, b = 0;
  SDL_GetSurfaceColorMod(m_surface, &r, &g, &b);
  return Color{r, g, b};
}

CENTURION_DEF
BlendMode Surface::blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetSurfaceBlendMode(m_surface, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
Texture Surface::to_texture(const Renderer& renderer) const noexcept
{
  return Texture{SDL_CreateTextureFromSurface(renderer.get(), m_surface)};
}

CENTURION_DEF
Surface Surface::convert(PixelFormat format) const
{
  const auto pixelFormat = static_cast<Uint32>(format);
  auto* converted = SDL_ConvertSurfaceFormat(m_surface, pixelFormat, 0);
  SDL_SetSurfaceBlendMode(converted, static_cast<SDL_BlendMode>(blend_mode()));
  return Surface{converted};
}

}  // namespace centurion

#endif  // CENTURION_SURFACE_SOURCE