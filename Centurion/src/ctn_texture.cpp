#include "ctn_texture.h"
#include <SDL_image.h>
#include <SDL_surface.h>
#include <stdexcept>

namespace centurion {
namespace visuals {

// TODO expand this class

Texture::Texture(SDL_Texture* sdlTexture) {
  if (sdlTexture == nullptr) {
    throw std::invalid_argument("Null texture pointer!");
  } else {
    this->sdlTexture = sdlTexture;
    SDL_QueryTexture(sdlTexture, &format, &access, &width, &height);
  }
}

Texture::Texture(const std::string& path, SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    throw std::exception("Null SDL_Renderer pointer!");
  }

  SDL_Surface* tmpSurf = IMG_Load(path.c_str());
  if (tmpSurf == nullptr) {
    throw std::exception(IMG_GetError());
  }

  sdlTexture = SDL_CreateTextureFromSurface(renderer, tmpSurf);
  SDL_FreeSurface(tmpSurf);

  if (sdlTexture == nullptr) {
    throw std::exception(SDL_GetError());
  }
  
  SDL_QueryTexture(sdlTexture, &format, &access, &width, &height);
}

// TODO alphaMod, blendMode, colorMod

Texture::~Texture() {
  if (sdlTexture != nullptr) {
    SDL_DestroyTexture(sdlTexture);
  }
}

Texture_sptr Texture::CreateShared(SDL_Texture* sdlTexture) {
  return std::make_shared<Texture>(sdlTexture);
}

Texture_sptr Texture::CreateShared(const std::string& path,
                                   SDL_Renderer* renderer) {
  return std::make_shared<Texture>(path, renderer);
}

Texture_uptr Texture::CreateUnique(SDL_Texture* sdlTexture) {
  return std::make_unique<Texture>(sdlTexture);
}

Texture_uptr Texture::CreateUnique(const std::string& path,
                                   SDL_Renderer* renderer) {
  return std::make_unique<Texture>(path, renderer);
}

}  // namespace visuals
}  // namespace centurion