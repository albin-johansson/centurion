#include "ctn_dynamic_texture.h"

namespace centurion {
namespace visuals {

// ----------------------------------- Public ----------------------------------

DynamicTexture::DynamicTexture(SDL_Surface* sdlSurface, SDL_Renderer* renderer)
    : AbstractTexture(SDL_CreateTextureFromSurface(renderer, sdlSurface)) {
  this->sdlSurface = sdlSurface;
}

DynamicTexture::DynamicTexture(const std::string& path, SDL_Renderer* renderer)
    : AbstractTexture(AbstractTexture::CreateTextureFromPath(path, renderer)) {}

DynamicTexture::~DynamicTexture() {
  if (sdlSurface != nullptr) {
    SDL_FreeSurface(sdlSurface);
  }
}

void DynamicTexture::Revalidate(SDL_Renderer* renderer) {
  if (renderer != nullptr) {
    SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;
    SDL_CreateTextureFromSurface(renderer, sdlSurface);
  }
}

DynamicTexture_sptr DynamicTexture::CreateShared(SDL_Surface* surf,
                                                 SDL_Renderer* renderer) {
  return std::make_shared<DynamicTexture>(surf, renderer);
}

DynamicTexture_sptr DynamicTexture::CreateShared(const std::string& path,
                                                 SDL_Renderer* renderer) {
  return std::make_shared<DynamicTexture>(path, renderer);
}

DynamicTexture_uptr DynamicTexture::CreateUnique(SDL_Surface* surf,
                                                 SDL_Renderer* renderer) {
  return std::make_unique<DynamicTexture>(surf, renderer);
}

DynamicTexture_uptr DynamicTexture::CreateUnique(const std::string& path,
                                                 SDL_Renderer* renderer) {
  return std::make_unique<DynamicTexture>(path, renderer);
}

DynamicTexture_wptr DynamicTexture::CreateWeak(SDL_Surface* surf,
                                               SDL_Renderer* renderer) {
  return CreateShared(surf, renderer);
}

DynamicTexture_wptr DynamicTexture::CreateWeak(const std::string& path,
                                               SDL_Renderer* renderer) {
  return CreateShared(path, renderer);
}

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion