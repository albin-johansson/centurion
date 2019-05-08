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

int Surface::GetWidth() const noexcept { return sdlSurface->w; }

int Surface::GetHeight() const noexcept { return sdlSurface->h; }

SDL_Surface* Surface::GetSDLVersion() { return sdlSurface; }

Surface_sptr Surface::CreateShared(SDL_Surface* sdlSurface) {
  return std::make_shared<Surface>(sdlSurface);
}

Surface_uptr Surface::CreateUnique(SDL_Surface* sdlSurface) {
  return std::make_unique<Surface>(sdlSurface);
}

Surface_wptr Surface::CreateWeak(SDL_Surface* sdlSurface) {
  return CreateShared(sdlSurface);
}

}  // namespace visuals
}  // namespace centurion