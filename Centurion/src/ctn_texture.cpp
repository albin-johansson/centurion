#include "ctn_texture.h"
#include <SDL_error.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <stdexcept>

namespace centurion {
namespace visuals {

// ----------------------------------- Public ----------------------------------

Texture::Texture(SDL_Texture* texture) : AbstractTexture(texture) {}

Texture::Texture(const std::string& path, SDL_Renderer* renderer)
    : AbstractTexture(AbstractTexture::CreateTextureFromPath(path, renderer)) {}

Texture::~Texture() = default;

Texture_sptr Texture::CreateShared(SDL_Texture* texture) {
  return std::make_shared<Texture>(texture);
}

Texture_sptr Texture::CreateShared(const std::string& path,
                                   SDL_Renderer* renderer) {
  SDL_Texture* tex = AbstractTexture::CreateTextureFromPath(path, renderer);
  return CreateShared(tex);
}

Texture_uptr Texture::CreateUnique(SDL_Texture* texture) {
  return std::make_unique<Texture>(texture);
}

Texture_uptr Texture::CreateUnique(const std::string& path,
                                   SDL_Renderer* renderer) {
  SDL_Texture* tex = AbstractTexture::CreateTextureFromPath(path, renderer);
  return CreateUnique(tex);
}

Texture_wptr Texture::CreateWeak(SDL_Texture* texture) {
  return CreateShared(texture);
}

Texture_wptr Texture::CreateWeak(const std::string& path,
                                 SDL_Renderer* renderer) {
  return CreateShared(path, renderer);
}

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion