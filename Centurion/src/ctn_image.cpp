#include "ctn_image.h"
#include <SDL_image.h>
#include <stdexcept>

namespace centurion {
namespace visuals {

Image::Image(SDL_Surface* surface, SDL_Renderer* renderer) {
  this->width = surface->w;
  this->height = surface->h;
  this->sdlSurface = surface;
  sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
}

Image::Image(std::string path, SDL_Renderer* renderer) {
  sdlSurface = IMG_Load(path.c_str());
  sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
  width = sdlSurface->w;
  height = sdlSurface->h;
}

Image::~Image() {
  SDL_DestroyTexture(sdlTexture);
  SDL_FreeSurface(sdlSurface);
}

void Image::Revalidate(SDL_Renderer* renderer) {
  SDL_DestroyTexture(sdlTexture);
  sdlTexture = nullptr;
  sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
}

Texture_sptr Image::CreateShared(SDL_Surface* surface, SDL_Renderer* renderer) {
  return std::make_shared<Image>(surface, renderer);
}

Texture_sptr Image::CreateShared(std::string path, SDL_Renderer* renderer) {
  return std::make_shared<Image>(path, renderer);
}

Texture_uptr Image::CreateUnique(SDL_Surface* surface, SDL_Renderer* renderer) {
  return std::make_unique<Image>(surface, renderer);
}

Texture_uptr Image::CreateUnique(std::string path, SDL_Renderer* renderer) {
  return std::make_unique<Image>(path, renderer);
}

Texture_wptr Image::CreateWeak(SDL_Surface* surface, SDL_Renderer* renderer) {
  return CreateShared(surface, renderer);
}

Texture_wptr Image::CreateWeak(std::string path, SDL_Renderer* renderer) {
  return CreateShared(path, renderer);
}

}  // namespace visuals
}  // namespace centurion