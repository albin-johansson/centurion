#include "ctn_surface.h"
#include <stdexcept>

namespace centurion {
namespace visuals {

// TODO expand this class

Surface::Surface(SDL_Surface* sdlSurface) {
  if (sdlSurface == nullptr) {
    throw std::invalid_argument("Null surface pointer!");
  } else {
    this->sdlSurface = sdlSurface;
  }
}

Surface::~Surface() {
  if (sdlSurface != nullptr) {
    SDL_FreeSurface(sdlSurface);
  }
}

void Surface::SetAlpha(int alpha) {
  if ((alpha < 0) || (alpha > 255)) {
    throw std::invalid_argument("Invalid alpha argument!");
  }
  SDL_SetSurfaceAlphaMod(sdlSurface, alpha);
}

void Surface::SetBlendMode(SDL_BlendMode mode) noexcept {
  SDL_SetSurfaceBlendMode(sdlSurface, mode);
}

void Surface::SetColorModulation(Color c) noexcept {
  SDL_SetSurfaceColorMod(sdlSurface, c.GetRed(), c.GetGreen(), c.GetBlue());
}

// TODO remove? (if kept, add pixel modification)
void Surface::Lock() noexcept { SDL_LockSurface(sdlSurface); }

void Surface::Unlock() noexcept { SDL_UnlockSurface(sdlSurface); }

Surface_uptr Surface::Duplicate() const {
  return CreateUnique(SDL_DuplicateSurface(sdlSurface));
}

Color Surface::GetColorModulation() const noexcept {
  Uint8 red = 0;
  Uint8 green = 0;
  Uint8 blue = 0;
  SDL_GetSurfaceColorMod(sdlSurface, &red, &green, &blue);
  return Color(red, green, blue);
}

Surface_sptr Surface::CreateShared(SDL_Surface* sdlSurface) {
  return std::make_shared<Surface>(sdlSurface);
}

Surface_uptr Surface::CreateUnique(SDL_Surface* sdlSurface) {
  return std::make_unique<Surface>(sdlSurface);
}

}  // namespace visuals
}  // namespace centurion