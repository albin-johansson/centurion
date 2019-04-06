#include "texture_factory.h"
#include <SDL_image.h>
#include <stdexcept>
#include "null_checker.h"

using centurion::tools::NullChecker;

namespace centurion {
namespace visuals {

SDL_Texture* TextureFactory::CreateSDLTexture(SDL_Surface* surface,
                                              SDL_Renderer* renderer) {
  if (NullChecker::IsNull(surface) || NullChecker::IsNull(renderer)) {
    throw std::invalid_argument(
        "Null renderer or surface when creating texture!");
  } else {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
      SDL_Log("Failed to create texture from surface!");
    }
    return texture;
  }
}

std::shared_ptr<Texture> TextureFactory::CreateTexture(const std::string& path,
                                                       SDL_Renderer* renderer) {
  if (NullChecker::IsNull(renderer)) {
    throw std::invalid_argument("Null SDL_Renderer when creating Texture!");
  } else {
    SDL_Surface* surface =
        IMG_Load(path.c_str());  // TODO error msg when invalid path is used
    SDL_Texture* texture = TextureFactory::CreateSDLTexture(surface, renderer);
    int width = surface->w;
    int height = surface->h;
    SDL_FreeSurface(surface);
    return std::make_shared<Texture>(texture, width, height);
  }
}

std::shared_ptr<Texture> TextureFactory::CreateTexture(
    const std::string& path, const Renderer& renderer) {
  return TextureFactory::CreateTexture(path, renderer.GetSDLRenderer());
}

}  // namespace visuals
}  // namespace centurion