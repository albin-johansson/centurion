#include "ctn_image.h"
#include <SDL_image.h>

namespace centurion {
namespace visuals {

// ----------------------------------- Public ----------------------------------

Image::Image(const std::string& path, SDL_Renderer* renderer) {
  SDL_Surface* surf = IMG_Load(path.c_str());
  SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
  surface = Surface::CreateShared(surf);
  texture = Texture::CreateShared(tex);
}

Image::~Image() = default;

void Image::Revalidate(SDL_Renderer* renderer) {
  if (renderer != nullptr) {
    texture.reset();
    SDL_Texture* tex =
        SDL_CreateTextureFromSurface(renderer, surface->GetSDLVersion());
    texture = Texture::CreateShared(tex);
  }
}

int Image::GetWidth() const { return texture->GetWidth(); }

int Image::GetHeight() const { return texture->GetHeight(); }

SDL_Texture* Image::GetSDLTexture() { return texture->GetSDLTexture(); }

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion