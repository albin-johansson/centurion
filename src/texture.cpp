#ifndef CENTURION_IMAGE_SOURCE
#define CENTURION_IMAGE_SOURCE

#include "texture.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"
#include "renderer.h"
#include "surface.h"

namespace centurion {
namespace video {

CENTURION_DEF
Texture::Texture(gsl::owner<SDL_Texture*> texture)
{
  if (!texture) {
    throw CenturionException{"Texture can't be created from null SDL texture!"};
  }
  this->m_texture = texture;
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer, const char* path)
{
  if (!path) {
    throw CenturionException{"Can't load texture from null path!"};
  }

  m_texture = IMG_LoadTexture(renderer.internal(), path);

  if (!m_texture) {
    const auto strPath = std::string{path};
    throw CenturionException{"Failed to load texture from " + strPath};
  }
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer, const Surface& surface)
{
  this->m_texture = SDL_CreateTextureFromSurface(renderer.internal(),
                                                 surface.get_internal());
  if (!m_texture) {
    throw CenturionException{"Failed to create texture from surface! " +
                             Error::msg()};
  }
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer,
                 PixelFormat format,
                 TextureAccess access,
                 int width,
                 int height)
{
  m_texture = SDL_CreateTexture(renderer,
                                static_cast<Uint32>(format),
                                static_cast<int>(access),
                                width,
                                height);
  if (!m_texture) {
    throw CenturionException{"Failed to create texture! " + Error::msg()};
  }
}

CENTURION_DEF
Texture::Texture(Texture&& other) noexcept
{
  if (this != &other) {
    destroy();
    m_texture = other.m_texture;
    other.m_texture = nullptr;
  }
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
    destroy();
    m_texture = other.m_texture;
    other.m_texture = nullptr;
  }
  return *this;
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(gsl::owner<SDL_Texture*> texture)
{
  return centurion::make_unique<Texture>(texture);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         const char* path)
{
  return centurion::make_unique<Texture>(renderer, path);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         const Surface& surface)
{
  return centurion::make_unique<Texture>(renderer, surface);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height)
{
  return centurion::make_unique<Texture>(
      renderer, format, access, width, height);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(gsl::owner<SDL_Texture*> texture)
{
  return std::make_shared<Texture>(texture);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         const char* path)
{
  return std::make_shared<Texture>(renderer, path);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         const Surface& surface)
{
  return std::make_shared<Texture>(renderer, surface);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height)
{
  return std::make_shared<Texture>(renderer, format, access, width, height);
}

CENTURION_DEF
void Texture::destroy() noexcept
{
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
  }
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
PixelFormat Texture::format() const noexcept
{
  Uint32 format = 0;
  SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr);
  return static_cast<PixelFormat>(format);
}

CENTURION_DEF
TextureAccess Texture::access() const noexcept
{
  int access = 0;
  SDL_QueryTexture(m_texture, nullptr, &access, nullptr, nullptr);
  return static_cast<TextureAccess>(access);
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
bool Texture::is_target() const noexcept
{
  return access() == TextureAccess::Target;
}

CENTURION_DEF
bool Texture::is_static() const noexcept
{
  return access() == TextureAccess::Static;
}

CENTURION_DEF
bool Texture::is_streaming() const noexcept
{
  return access() == TextureAccess::Streaming;
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
SDL_Texture* Texture::get_internal() noexcept
{
  return m_texture;
}

CENTURION_DEF
std::string Texture::to_string() const
{
  const auto address = address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Texture@" + address + " | Width: " + w + ", Height: " + h + "]";
}

CENTURION_DEF
Texture::operator SDL_Texture*() const noexcept
{
  return m_texture;
}

CENTURION_DEF
bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept
{
  return static_cast<SDL_TextureAccess>(a) == b;
}

CENTURION_DEF
bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept
{
  return a == static_cast<SDL_TextureAccess>(b);
}

CENTURION_DEF
bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept
{
  return static_cast<SDL_TextureAccess>(a) != b;
}

CENTURION_DEF
bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept
{
  return a != static_cast<SDL_TextureAccess>(b);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_IMAGE_SOURCE