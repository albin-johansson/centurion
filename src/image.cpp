#include "image.h"
#include "centurion_exception.h"
#include <SDL_image.h>
#include <sstream>

namespace centurion {

Image::Image(gsl::owner<SDL_Texture*> texture) {
  if (!texture) {
    throw std::invalid_argument("Image can't be created from null SDL texture!");
  }
  this->texture = texture;
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer, const std::string& path) {
  texture = IMG_LoadTexture(renderer, path.c_str());
  if (!texture) {
    throw CenturionException("Failed to load image from " + path);
  }
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer, gsl::not_null<SDL_Surface*> surface) {
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    throw CenturionException("Failed to create image from surface!");
  }
}

Image::Image(Image&& other) noexcept
    : texture{other.texture} {
  other.texture = nullptr;
}

Image::~Image() noexcept {
  if (texture) {
    SDL_DestroyTexture(texture);
  }
}

Image& Image::operator=(Image&& other) noexcept {
  texture = other.texture;
  other.texture = nullptr;
  return *this;
}

void Image::set_alpha(uint8_t alpha) noexcept {
  SDL_SetTextureAlphaMod(texture, alpha);
}

uint32_t Image::get_format() const noexcept {
  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return format;
}

int Image::get_access() const noexcept {
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return access;
}

int Image::get_width() const noexcept {
  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  return width;
}

int Image::get_height() const noexcept {
  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  return height;
}

SDL_Texture* Image::get_texture() noexcept {
  return texture;
}

std::string Image::to_string() const {
  std::ostringstream address;
  address << static_cast<void const*>(this);

  auto w = std::to_string(get_width());
  auto h = std::to_string(get_height());

  return "(Image@" + address.str() + " | Width: " + w + ", Height: " + h + ")";
}

Image::operator SDL_Texture*() const noexcept {
  return texture;
}

Image::operator std::string() {
  return to_string();
}

}