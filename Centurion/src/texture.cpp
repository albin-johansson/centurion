#include "texture.h"
#include <stdexcept>

using std::invalid_argument;

namespace centurion {
namespace visuals {

Texture::Texture(SDL_Texture* texture, int width, int height)
    : width(width), height(height) {
  if (texture == nullptr) {
    throw invalid_argument("Null SDL_Texture!");
  } else {
    this->sdl_texture = texture;
  }
}

Texture::~Texture() { SDL_DestroyTexture(sdl_texture); }

SDL_Texture& Texture::GetSDLVersion() noexcept { return *sdl_texture; }

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