#include "ctn_abstract_texture.h"
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <stdexcept>

namespace centurion {
namespace visuals {

// --------------------------------- Protected ---------------------------------

AbstractTexture::AbstractTexture(SDL_Texture* sdlTexture) {
  if (sdlTexture == nullptr) {
    throw std::invalid_argument("Null texture!");
  } else {
    this->sdlTexture = sdlTexture;
    SDL_QueryTexture(sdlTexture, &format, &access, &width, &height);
  }
}

SDL_Texture* AbstractTexture::CreateTextureFromPath(const std::string& path,
                                                    SDL_Renderer* renderer) {
  SDL_Surface* tmp = IMG_Load(path.c_str());
  if (tmp == nullptr) {
    throw std::exception(IMG_GetError());
  }
  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
  if (tex == nullptr) {
    throw std::exception(SDL_GetError());
  }
  SDL_FreeSurface(tmp);
  return tex;
}

// ------------------------------- End protected -------------------------------

// ----------------------------------- Public ----------------------------------

AbstractTexture::~AbstractTexture() {
  if (sdlTexture != nullptr) {
    SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;
  }
}

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion