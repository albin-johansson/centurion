#include "texture.h"
#include <stdexcept>
#include "null_checker.h"

using centurion::tools::NullChecker;
using centurion::visuals::Texture;
using std::invalid_argument;

Texture::Texture(SDL_Texture* texture, int width, int height)
    : width(width), height(height) {
  if (NullChecker::IsNull(texture)) {
    throw invalid_argument("Null SDL_Texture!");
  } else {
    this->sdl_texture = texture;
  }
}

Texture::~Texture() { SDL_DestroyTexture(sdl_texture); }

SDL_Texture& Texture::GetSDLTexture() { return *sdl_texture; }

int Texture::GetWidth() const { return width; }

int Texture::GetHeight() const { return height; }