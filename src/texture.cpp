#ifndef CENTURION_IMAGE_SOURCE
#define CENTURION_IMAGE_SOURCE

#include "texture.hpp"

#include <SDL_image.h>

#include "centurion_exception.hpp"
#include "centurion_utils.hpp"
#include "renderer.hpp"
#include "surface.hpp"

namespace centurion {

CENTURION_DEF
Texture::Texture(Owner<SDL_Texture*> texture)
{
  if (!texture) {
    throw CenturionException{"Texture can't be created from null SDL texture!"};
  }
  this->m_texture = texture;
}

CENTURION_DEF
Texture::Texture(Texture&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Texture::~Texture() noexcept
{
  destroy();
}

CENTURION_DEF
Texture& Texture::operator=(Texture&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void Texture::destroy() noexcept
{
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
  }
}

CENTURION_DEF
void Texture::move(Texture&& other) noexcept
{
  destroy();
  m_texture = other.m_texture;
  other.m_texture = nullptr;
}

CENTURION_DEF
bool Texture::lock(Uint32** pixels, int* pitch) noexcept
{
  if (pitch) {
    const auto result = SDL_LockTexture(
        m_texture, nullptr, reinterpret_cast<void**>(pixels), pitch);
    return result == 0;
  } else {
    int dummyPitch;
    const auto result = SDL_LockTexture(
        m_texture, nullptr, reinterpret_cast<void**>(pixels), &dummyPitch);
    return result == 0;
  }
}

CENTURION_DEF
void Texture::unlock() noexcept
{
  SDL_UnlockTexture(m_texture);
}

CENTURION_DEF
UniquePtr<Texture> Texture::unique(Owner<SDL_Texture*> texture)
{
  return std::make_unique<Texture>(texture);
}

CENTURION_DEF
SharedPtr<Texture> Texture::shared(Owner<SDL_Texture*> texture)
{
  return std::make_shared<Texture>(texture);
}

CENTURION_DEF
void Texture::set_pixel(IPoint pixel, const Color& color) noexcept
{
  if (access() != Access::Streaming || pixel.x() < 0 || pixel.y() < 0 ||
      pixel.x() >= width() || pixel.y() >= height()) {
    return;
  }

  Uint32* pixels = nullptr;
  int pitch;
  const auto success = lock(&pixels, &pitch);
  if (!success) {
    return;
  }

  const int nPixels = (pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    auto* pixelFormat = SDL_AllocFormat(static_cast<Uint32>(format()));
    const auto value = SDL_MapRGBA(
        pixelFormat, color.red(), color.green(), color.blue(), color.alpha());

    SDL_FreeFormat(pixelFormat);

    pixels[index] = value;
  }

  unlock();
}

CENTURION_DEF
void Texture::set_alpha(Uint8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(m_texture, alpha);
}

CENTURION_DEF
void Texture::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetTextureBlendMode(m_texture, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
void Texture::set_color_mod(Color color) noexcept
{
  SDL_SetTextureColorMod(m_texture, color.red(), color.green(), color.blue());
}

CENTURION_DEF
void Texture::set_scale_mode(ScaleMode mode) noexcept
{
  SDL_SetTextureScaleMode(m_texture, static_cast<SDL_ScaleMode>(mode));
}

CENTURION_DEF
PixelFormat Texture::format() const noexcept
{
  Uint32 format = 0;
  SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr);
  return static_cast<PixelFormat>(format);
}

CENTURION_DEF
Texture::Access Texture::access() const noexcept
{
  int access = 0;
  SDL_QueryTexture(m_texture, nullptr, &access, nullptr, nullptr);
  return static_cast<Access>(access);
}

CENTURION_DEF
int Texture::width() const noexcept
{
  int width = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, nullptr);
  return width;
}

CENTURION_DEF
int Texture::height() const noexcept
{
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, nullptr, &height);
  return height;
}

CENTURION_DEF
area_i Texture::size() const noexcept
{
  int width = 0;
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
  return {width, height};
}

CENTURION_DEF
bool Texture::is_target() const noexcept
{
  return access() == Access::Target;
}

CENTURION_DEF
bool Texture::is_static() const noexcept
{
  return access() == Access::Static;
}

CENTURION_DEF
bool Texture::is_streaming() const noexcept
{
  return access() == Access::Streaming;
}

CENTURION_DEF
Uint8 Texture::alpha() const noexcept
{
  Uint8 alpha;
  SDL_GetTextureAlphaMod(m_texture, &alpha);
  return alpha;
}

CENTURION_DEF
BlendMode Texture::blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(m_texture, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
Color Texture::color_mod() const noexcept
{
  Uint8 r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(m_texture, &r, &g, &b);
  return {r, g, b, 0xFF};
}

CENTURION_DEF
Texture::ScaleMode Texture::scale_mode() const noexcept
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(m_texture, &mode);
  return static_cast<ScaleMode>(mode);
}

CENTURION_DEF
std::string Texture::to_string() const
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Texture@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion

#endif  // CENTURION_IMAGE_SOURCE