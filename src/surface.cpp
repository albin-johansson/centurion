#ifndef CENTURION_SURFACE_SOURCE
#define CENTURION_SURFACE_SOURCE

#include "surface.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "renderer.h"
#include "texture.h"

namespace centurion {
namespace video {

CENTURION_DEF
Surface::Surface(const char* file)
{
  if (!file) {
    throw CenturionException{"Can't create surface from null path!"};
  }
  surface = IMG_Load(file);
  if (!surface) {
    throw CenturionException{"Failed to load surface!"};
  }
}

CENTURION_DEF
Surface::Surface(gsl::owner<SDL_Surface*> surface)
{
  if (!surface) {
    throw CenturionException{"Cannot create surface from null SDL_Surface!"};
  } else {
    this->surface = surface;
  }
}

CENTURION_DEF
Surface::Surface(const Surface& other)
{
  surface = other.copy_surface();
}

CENTURION_DEF
Surface::Surface(Surface&& other) noexcept
{
  destroy();
  surface = other.surface;
  other.surface = nullptr;
}

CENTURION_DEF
Surface::~Surface() noexcept
{
  destroy();
}

CENTURION_DEF
Surface& Surface::operator=(Surface&& other) noexcept
{
  destroy();

  surface = other.surface;
  other.surface = nullptr;

  return *this;
}

CENTURION_DEF
Surface& Surface::operator=(const Surface& other)
{
  if (this != &other) {
    destroy();
    surface = other.copy_surface();
  }
  return *this;
}

CENTURION_DEF
void Surface::destroy() noexcept
{
  if (surface) {
    SDL_FreeSurface(surface);
  }
}

CENTURION_DEF
SDL_Surface* Surface::copy_surface() const
{
  auto* copy = SDL_DuplicateSurface(surface);
  if (!copy) {
    throw CenturionException{"Failed to duplicate SDL surface!"};
  } else {
    return copy;
  }
}

CENTURION_DEF
void Surface::set_alpha(uint8_t alpha) noexcept
{
  SDL_SetSurfaceAlphaMod(surface, alpha);
}

CENTURION_DEF
void Surface::set_color_mod(const Color& color) noexcept
{
  SDL_SetSurfaceColorMod(
      surface, color.get_red(), color.get_green(), color.get_blue());
}

CENTURION_DEF
void Surface::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetSurfaceBlendMode(surface, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
uint8_t Surface::get_alpha() const noexcept
{
  uint8_t alpha = 0xFF;
  SDL_GetSurfaceAlphaMod(surface, &alpha);
  return alpha;
}

CENTURION_DEF
Color Surface::get_color_mod() const noexcept
{
  uint8_t r = 0, g = 0, b = 0;
  SDL_GetSurfaceColorMod(surface, &r, &g, &b);
  return Color{r, g, b};
}

CENTURION_DEF
BlendMode Surface::get_blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetSurfaceBlendMode(surface, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
int Surface::get_width() const noexcept
{
  return surface->w;
}

CENTURION_DEF
int Surface::get_height() const noexcept
{
  return surface->h;
}

CENTURION_DEF
int Surface::get_pitch() const noexcept
{
  return surface->pitch;
}

CENTURION_DEF
Texture Surface::to_texture(const Renderer& renderer) const noexcept
{
  return Texture{
      SDL_CreateTextureFromSurface(renderer.get_internal(), surface)};
}

CENTURION_DEF
SDL_Surface* Surface::get_internal() const noexcept
{
  return surface;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_SURFACE_SOURCE