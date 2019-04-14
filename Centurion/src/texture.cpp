#include "texture.h"
#include <stdexcept>
#include "null_checker.h"

using centurion::tools::NullChecker;
using std::invalid_argument;

namespace centurion {
namespace visuals {

Texture::Texture(SDL_Texture* texture, int width, int height)
    : width(width), height(height) {
  if (NullChecker::IsNull(texture)) {
    throw invalid_argument("Null SDL_Texture!");
  } else {
    this->sdl_texture = texture;
  }
}

Texture::~Texture() { SDL_DestroyTexture(sdl_texture); }

std::shared_ptr<Texture> Texture::Create(SDL_Texture* texture, int width,
                                         int height) {
  return std::make_shared<Texture>(texture, width, height);
}

SDL_Texture& Texture::GetSDLVersion() noexcept { return *sdl_texture; }

}  // namespace visuals
}  // namespace centurion