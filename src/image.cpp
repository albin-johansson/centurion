#include "image.h"
#include <sstream>
#include <type_traits>
#include <SDL_image.h>
#include "centurion_exception.h"

namespace centurion {

static_assert(std::is_final_v<Image>);

static_assert(std::is_nothrow_move_constructible_v<Image>);
static_assert(std::is_nothrow_move_assignable_v<Image>);

static_assert(!std::is_nothrow_copy_constructible_v<Image>);
static_assert(!std::is_nothrow_copy_assignable_v<Image>);

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

Image::Image(gsl::not_null<SDL_Renderer*> renderer,
             uint32_t format,
             TextureAccess access,
             int width,
             int height) {
  texture = SDL_CreateTexture(renderer, format, static_cast<int>(access), width, height);
  if (!texture) {
    throw CenturionException{"Failed to create image! Error: " + std::string{SDL_GetError()}};
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

std::unique_ptr<Image> Image::unique(gsl::not_null<SDL_Renderer*> renderer,
                                     uint32_t format,
                                     TextureAccess access,
                                     int width,
                                     int height) {
  return std::make_unique<Image>(renderer, format, access, width, height);
}

std::shared_ptr<Image> Image::shared(gsl::not_null<SDL_Renderer*> renderer,
                                     uint32_t format,
                                     TextureAccess access,
                                     int width,
                                     int height) {
  return std::make_shared<Image>(renderer, format, access, width, height);
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

void Image::set_blend_mode(BlendMode mode) noexcept {
  SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(mode));
}

void Image::set_color_mod(Color color) noexcept {
  SDL_SetTextureColorMod(texture, color.get_red(), color.get_green(), color.get_blue());
}

uint32_t Image::get_format() const noexcept {
  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return format;
}

TextureAccess Image::get_access() const noexcept {
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return static_cast<TextureAccess>(access);
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

bool Image::is_target() const noexcept {
  return get_access() == TextureAccess::Target;
}

bool Image::is_static() const noexcept {
  return get_access() == TextureAccess::Static;
}

bool Image::is_streaming() const noexcept {
  return get_access() == TextureAccess::Streaming;
}

uint8_t Image::get_alpha() const noexcept {
  uint8_t alpha;
  SDL_GetTextureAlphaMod(texture, &alpha);
  return alpha;
}

BlendMode Image::get_blend_mode() const noexcept {
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(texture, &mode);
  return static_cast<BlendMode>(mode);
}

Color Image::get_color_mod() const noexcept {
  uint8_t r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(texture, &r, &g, &b);
  return {r, g, b, 0xFF};
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

bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept {
  return static_cast<SDL_TextureAccess>(a) == b;
}

bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept {
  return a == static_cast<SDL_TextureAccess>(b);
}

bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept {
  return static_cast<SDL_TextureAccess>(a) != b;
}

bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept {
  return a != static_cast<SDL_TextureAccess>(b);
}

}