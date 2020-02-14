#ifndef CENTURION_IMAGE_SOURCE
#define CENTURION_IMAGE_SOURCE

#include "image.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {

CENTURION_DEF Image::Image(gsl::owner<SDL_Texture*> texture) {
  if (!texture) {
    throw CenturionException{"Image can't be created from null SDL texture!"};
  }
  this->texture = texture;
}

CENTURION_DEF Image::Image(gsl::not_null<SDL_Renderer*> renderer,
                           const std::string& path) {
  texture = IMG_LoadTexture(renderer, path.c_str());
  if (!texture) {
    throw CenturionException{"Failed to load image from " + path};
  }
}

CENTURION_DEF Image::Image(gsl::not_null<SDL_Renderer*> renderer,
                           gsl::not_null<SDL_Surface*> surface) {
  this->texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    throw CenturionException{"Failed to create image from surface! " +
                             Error::msg()};
  }
}

CENTURION_DEF Image::Image(gsl::not_null<SDL_Renderer*> renderer,
                           uint32_t format, TextureAccess access, int width,
                           int height) {
  texture = SDL_CreateTexture(renderer, format, static_cast<int>(access), width,
                              height);
  if (!texture) {
    throw CenturionException{"Failed to create image! " + Error::msg()};
  }
}

CENTURION_DEF Image::Image(gsl::not_null<SDL_Renderer*> renderer,
                           PixelFormat format, TextureAccess access, int width,
                           int height) {
  texture = SDL_CreateTexture(renderer, static_cast<uint32_t>(format),
                              static_cast<int>(access), width, height);
  if (!texture) {
    throw CenturionException{"Failed to create image! " + Error::msg()};
  }
}

CENTURION_DEF Image::Image(Image&& other) noexcept {
  SDL_DestroyTexture(texture);

  texture = other.texture;
  other.texture = nullptr;
}

CENTURION_DEF Image::~Image() noexcept {
  if (texture) {
    SDL_DestroyTexture(texture);
  }
}

CENTURION_DEF Image& Image::operator=(Image&& other) noexcept {
  SDL_DestroyTexture(texture);

  texture = other.texture;
  other.texture = nullptr;

  return *this;
}

CENTURION_DEF std::unique_ptr<Image> Image::unique(
    gsl::owner<SDL_Texture*> texture) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(texture);
#else
  return centurion::make_unique<Image>(texture);
#endif
}

CENTURION_DEF std::unique_ptr<Image> Image::unique(
    gsl::not_null<SDL_Renderer*> renderer, const std::string& path) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer, path);
#else
  return centurion::make_unique<Image>(renderer, path);
#endif
}

CENTURION_DEF std::unique_ptr<Image> Image::unique(
    gsl::not_null<SDL_Renderer*> renderer,
    gsl::not_null<SDL_Surface*> surface) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer, surface);
#else
  return centurion::make_unique<Image>(renderer, surface);
#endif
}

CENTURION_DEF std::unique_ptr<Image> Image::unique(
    gsl::not_null<SDL_Renderer*> renderer, uint32_t format,
    TextureAccess access, int width, int height) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer, format, access, width, height);
#else
  return centurion::make_unique<Image>(renderer, format, access, width, height);
#endif
}

CENTURION_DEF std::unique_ptr<Image> Image::unique(
    gsl::not_null<SDL_Renderer*> renderer, PixelFormat format,
    TextureAccess access, int width, int height) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Image>(renderer, format, access, width, height);
#else
  return centurion::make_unique<Image>(renderer, format, access, width, height);
#endif
}

CENTURION_DEF std::shared_ptr<Image> Image::shared(
    gsl::owner<SDL_Texture*> texture) {
  return std::make_shared<Image>(texture);
}

CENTURION_DEF std::shared_ptr<Image> Image::shared(
    gsl::not_null<SDL_Renderer*> renderer, const std::string& path) {
  return std::make_shared<Image>(renderer, path);
}

CENTURION_DEF std::shared_ptr<Image> Image::shared(
    gsl::not_null<SDL_Renderer*> renderer,
    gsl::not_null<SDL_Surface*> surface) {
  return std::make_shared<Image>(renderer, surface);
}

CENTURION_DEF std::shared_ptr<Image> Image::shared(
    gsl::not_null<SDL_Renderer*> renderer, uint32_t format,
    TextureAccess access, int width, int height) {
  return std::make_shared<Image>(renderer, format, access, width, height);
}

CENTURION_DEF std::shared_ptr<Image> Image::shared(
    gsl::not_null<SDL_Renderer*> renderer, PixelFormat format,
    TextureAccess access, int width, int height) {
  return std::make_shared<Image>(renderer, format, access, width, height);
}

CENTURION_DEF void Image::set_alpha(uint8_t alpha) noexcept {
  SDL_SetTextureAlphaMod(texture, alpha);
}

CENTURION_DEF void Image::set_blend_mode(BlendMode mode) noexcept {
  SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF void Image::set_color_mod(Color color) noexcept {
  SDL_SetTextureColorMod(texture, color.get_red(), color.get_green(),
                         color.get_blue());
}

CENTURION_DEF uint32_t Image::get_format() const noexcept {
  uint32_t format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return format;
}

CENTURION_DEF TextureAccess Image::get_access() const noexcept {
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return static_cast<TextureAccess>(access);
}

CENTURION_DEF int Image::get_width() const noexcept {
  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  return width;
}

CENTURION_DEF int Image::get_height() const noexcept {
  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  return height;
}

CENTURION_DEF bool Image::is_target() const noexcept {
  return get_access() == TextureAccess::Target;
}

CENTURION_DEF bool Image::is_static() const noexcept {
  return get_access() == TextureAccess::Static;
}

CENTURION_DEF bool Image::is_streaming() const noexcept {
  return get_access() == TextureAccess::Streaming;
}

CENTURION_DEF uint8_t Image::get_alpha() const noexcept {
  uint8_t alpha;
  SDL_GetTextureAlphaMod(texture, &alpha);
  return alpha;
}

CENTURION_DEF BlendMode Image::get_blend_mode() const noexcept {
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(texture, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF Color Image::get_color_mod() const noexcept {
  uint8_t r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(texture, &r, &g, &b);
  return {r, g, b, 0xFF};
}

CENTURION_DEF SDL_Texture* Image::get_texture() noexcept { return texture; }

CENTURION_DEF std::string Image::to_string() const {
  const auto address = CenturionUtils::address(this);
  const auto width = std::to_string(get_width());
  const auto height = std::to_string(get_height());
  return "[Image@" + address + " | Width: " + width + ", Height: " + height +
         "]";
}

CENTURION_DEF Image::operator SDL_Texture*() const noexcept { return texture; }

CENTURION_DEF bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept {
  return static_cast<SDL_TextureAccess>(a) == b;
}

CENTURION_DEF bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept {
  return a == static_cast<SDL_TextureAccess>(b);
}

CENTURION_DEF bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept {
  return static_cast<SDL_TextureAccess>(a) != b;
}

CENTURION_DEF bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept {
  return a != static_cast<SDL_TextureAccess>(b);
}

CENTURION_DEF bool operator==(PixelFormat lhs,
                              SDL_PixelFormatEnum rhs) noexcept {
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

CENTURION_DEF bool operator==(SDL_PixelFormatEnum lhs,
                              PixelFormat rhs) noexcept {
  return lhs == static_cast<SDL_PixelFormatEnum>(rhs);
}

CENTURION_DEF bool operator!=(PixelFormat lhs,
                              SDL_PixelFormatEnum rhs) noexcept {
  return static_cast<SDL_PixelFormatEnum>(lhs) != rhs;
}

CENTURION_DEF bool operator!=(SDL_PixelFormatEnum lhs,
                              PixelFormat rhs) noexcept {
  return lhs != static_cast<SDL_PixelFormatEnum>(rhs);
}

}  // namespace centurion

#endif // CENTURION_IMAGE_SOURCE