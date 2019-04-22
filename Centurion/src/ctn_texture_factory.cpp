#include <SDL_image.h>
#include <stdexcept>
#include "ctn_texture_factory.h"

namespace centurion {
namespace visuals {

SDL_Texture* TextureFactory::CreateSDLTexture(SDL_Surface* surface,
                                              SDL_Renderer* renderer) {
  if (surface == nullptr || renderer == nullptr) {
    throw std::invalid_argument("Failed to create SDL_Texture!");
  } else {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
      SDL_Log("Failed to create texture from surface!");
    }
    return texture;
  }
}

Texture_sptr TextureFactory::CreateTexture(const std::string& path,
                                           SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    throw std::invalid_argument("Null SDL_Renderer when creating Image!");
  } else {
    // TODO error msg when invalid path is used
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = TextureFactory::CreateSDLTexture(surface, renderer);
    int width = surface->w;
    int height = surface->h;
    SDL_FreeSurface(surface);
    return Image::CreateShared(texture, width, height);
  }
}

}  // namespace visuals
}  // namespace centurion