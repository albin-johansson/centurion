#include "image.h"
#include <SDL_image.h>
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {

Image::Image(gsl::owner<SDL_Texture*> texture) {
  if (!texture) {
    throw CenturionException{"Image can't be created from null SDL texture!"};
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
    throw CenturionException{"Failed to create image from surface! " + Error::msg()};
  }
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer,
             uint32_t format,
             TextureAccess access,
             int width,
             int height) {
  texture = SDL_CreateTexture(renderer, format, static_cast<int>(access), width, height);
  if (!texture) {
    throw CenturionException{"Failed to create image! " + Error::msg()};
  }
}

Image::Image(gsl::not_null<SDL_Renderer*> renderer,
             PixelFormat format,
             TextureAccess access,
             int width,
             int height) {
  texture = SDL_CreateTexture(renderer,
                              static_cast<uint32_t>(format),
                              static_cast<int>(access),
                              width,
                              height);
  if (!texture) {
    throw CenturionException{"Failed to create image! " + Error::msg()};
  }
}

Image::Image(Image&& other) noexcept {
  SDL_DestroyTexture(texture);

  texture = other.texture;
  other.texture = nullptr;
}

Image::~Image() noexcept {
  if (texture) {
    SDL_DestroyTexture(texture);
  }
}

Image& Image::operator=(Image&& other) noexcept {
  SDL_DestroyTexture(texture);

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

std::unique_ptr<Image> Image::unique(gsl::not_null<SDL_Renderer*> renderer,
                                     PixelFormat format,
                                     TextureAccess access,
                                     int width,
                                     int height) {
  return std::make_unique<Image>(renderer, format, access, width, height);
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

std::shared_ptr<Image> Image::shared(gsl::not_null<SDL_Renderer*> renderer,
                                     uint32_t format,
                                     TextureAccess access,
                                     int width,
                                     int height) {
  return std::make_shared<Image>(renderer, format, access, width, height);
}

std::shared_ptr<Image> Image::shared(gsl::not_null<SDL_Renderer*> renderer,
                                     PixelFormat format,
                                     TextureAccess access,
                                     int width,
                                     int height) {
  return std::make_shared<Image>(renderer, format, access, width, height);
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
  const auto address = CenturionUtils::address(this);
  const auto width = std::to_string(get_width());
  const auto height = std::to_string(get_height());
  return "[Image@" + address + " | Width: " + width + ", Height: " + height + "]";
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

bool operator==(PixelFormat lhs, SDL_PixelFormatEnum rhs) noexcept {
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

bool operator==(SDL_PixelFormatEnum lhs, PixelFormat rhs) noexcept {
  return lhs == static_cast<SDL_PixelFormatEnum>(rhs);
}

bool operator!=(PixelFormat lhs, SDL_PixelFormatEnum rhs) noexcept {
  return static_cast<SDL_PixelFormatEnum>(lhs) != rhs;
}

bool operator!=(SDL_PixelFormatEnum lhs, PixelFormat rhs) noexcept {
  return lhs != static_cast<SDL_PixelFormatEnum>(rhs);
}

}
