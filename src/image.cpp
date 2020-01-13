#include "image.h"
#include <sstream>
#include <type_traits>
#include <SDL_image.h>
#include "centurion_exception.h"

namespace centurion {

static_assert(std::is_nothrow_move_constructible_v<Image>);
static_assert(std::is_nothrow_move_assignable_v<Image>);

static_assert(!std::is_nothrow_copy_constructible_v<Image>);
static_assert(!std::is_nothrow_copy_assignable_v<Image>);

static_assert(!std::is_final_v<Image>);
static_assert(std::has_virtual_destructor_v<Image>);

Image::Image(gsl::owner<SDL_Texture*> texture) {
  if (!texture) {
    throw std::invalid_argument{"Image can't be created from null SDL texture!"};
  }
  this->texture = texture;
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer, const std::string& path) {
  texture = IMG_LoadTexture(renderer, path.c_str());
  if (!texture) {
    throw CenturionException{"Failed to load image from " + path};
  }
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer, gsl::not_null<SDL_Surface*> surface) {
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    throw CenturionException{"Failed to create image from surface!"};
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

std::unique_ptr<Image> Image::unique(gsl::owner<SDL_Texture*> texture) {
  return std::make_unique<Image>(texture);
}

std::unique_ptr<Image> Image::unique(gsl::not_null<SDL_Renderer*> renderer,
                                     const std::string& path) {
  return std::make_unique<Image>(renderer, path);
}

std::unique_ptr<Image> Image::unique(gsl::not_null<SDL_Renderer*> renderer,
                                     gsl::not_null<SDL_Surface*> surface) {
  return std::make_unique<Image>(renderer, surface);
}

std::shared_ptr<Image> Image::shared(gsl::owner<SDL_Texture*> texture) {
  return std::make_shared<Image>(texture);
}

std::shared_ptr<Image> Image::shared(gsl::not_null<SDL_Renderer*> renderer,
                                     const std::string& path) {
  return std::make_shared<Image>(renderer, path);
}

std::shared_ptr<Image> Image::shared(gsl::not_null<SDL_Renderer*> renderer,
                                     gsl::not_null<SDL_Surface*> surface) {
  return std::make_shared<Image>(renderer, surface);
}

void Image::set_alpha(uint8_t alpha) noexcept {
  SDL_SetTextureAlphaMod(texture, alpha);
}

void Image::set_blend_mode(SDL_BlendMode mode) noexcept {
  SDL_SetTextureBlendMode(texture, mode);
}

void Image::set_color_mod(SDL_Color color) noexcept {
  SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
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

  const auto w = std::to_string(get_width());
  const auto h = std::to_string(get_height());

  return "(Image@" + address.str() + " | Width: " + w + ", Height: " + h + ")";
}

Image::operator SDL_Texture*() const noexcept {
  return texture;
}

}