#include "ctn_texture.h"
#include <stdexcept>

namespace centurion {
namespace visuals {

Texture::Texture(SDL_Texture* texture, int width, int height)
    : width(width), height(height) {
  if (texture == nullptr) {
    throw std::invalid_argument("Null SDL_Texture!");
  } else {
    this->sdlTexture = texture;
  }
}

Texture::~Texture() { SDL_DestroyTexture(sdlTexture); }

SDL_Texture* Texture::GetSDLVersion() noexcept { return sdlTexture; }

Texture_sptr Texture::CreateShared(SDL_Texture* texture, int w, int h) {
  return std::make_shared<Texture>(texture, w, h);
}

Texture_uptr Texture::CreateUnique(SDL_Texture* texture, int w, int h) {
  return std::make_unique<Texture>(texture, w, h);
}

Texture_wptr Texture::CreateWeak(SDL_Texture* texture, int width, int height) {
  return CreateShared(texture, width, height);
}

}  // namespace visuals
}  // namespace centurion