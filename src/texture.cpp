#include "texture.hpp"

#include <SDL_image.h>

#include "centurion_exception.hpp"
#include "centurion_utils.hpp"
#include "error.hpp"
#include "renderer.hpp"
#include "surface.hpp"

namespace centurion {

texture::texture(gsl::owner<SDL_Texture*> sdlTexture)
{
  if (!sdlTexture) {
    throw centurion_exception{
        "Texture can't be created from null SDL texture!"};
  }
  this->m_texture = sdlTexture;
}

texture::texture(const renderer& renderer, const surface& surface)
{
  this->m_texture = SDL_CreateTextureFromSurface(renderer.get(), surface.get());
  if (!m_texture) {
    throw detail::core_error("Failed to create texture from surface!");
  }
}

texture::texture(const renderer& renderer,
                 pixel_format format,
                 texture::access access,
                 const area_i& size)
{
  m_texture = SDL_CreateTexture(renderer.get(),
                                static_cast<u32>(format),
                                static_cast<int>(access),
                                size.width,
                                size.height);
  if (!m_texture) {
    throw detail::core_error("Failed to create texture!");
  }
}

texture::texture(const renderer& renderer, czstring path)
{
  if (!path) {
    throw centurion_exception{"Can't load texture from null path!"};
  }

  m_texture = IMG_LoadTexture(renderer.get(), path);
  if (!m_texture) {
    throw detail::img_error("Failed to create texture!");
  }
}

texture::texture(texture&& other) noexcept
{
  move(std::move(other));
}

texture::~texture() noexcept
{
  destroy();
}

auto texture::unique(const renderer& renderer, czstring path)
    -> std::unique_ptr<texture>
{
  return std::make_unique<texture>(renderer, path);
}

auto texture::unique(const renderer& renderer, const surface& surface)
    -> std::unique_ptr<texture>
{
  return std::make_unique<texture>(renderer, surface);
}

auto texture::unique(const renderer& renderer,
                     pixel_format format,
                     texture::access access,
                     const area_i& size) -> std::unique_ptr<texture>
{
  return std::make_unique<texture>(renderer, format, access, size);
}

auto texture::shared(const renderer& renderer, czstring path)
    -> std::shared_ptr<texture>
{
  return std::make_shared<texture>(renderer, path);
}

auto texture::shared(const renderer& renderer, const surface& surface)
    -> std::shared_ptr<texture>
{
  return std::make_shared<texture>(renderer, surface);
}

auto texture::shared(const renderer& renderer,
                     pixel_format format,
                     texture::access access,
                     const area_i& size) -> std::shared_ptr<texture>
{
  return std::make_shared<texture>(renderer, format, access, size);
}

auto texture::streaming(const renderer& renderer,
                        czstring path,
                        pixel_format format) -> std::unique_ptr<texture>
{
  const auto blendMode = blend_mode::blend;
  const auto createSurface = [=](czstring path, pixel_format format) {
    surface source{path};
    source.set_blend_mode(blendMode);
    return source.convert(format);
  };
  const auto surface = createSurface(path, format);
  auto texture = texture::unique(
      renderer, format, access::streaming, {surface.width(), surface.height()});
  texture->set_blend_mode(blendMode);

  u32* pixels = nullptr;
  const auto success = texture->lock(&pixels);
  if (!success) {
    throw centurion_exception{"Failed to lock texture!"};
  }

  const auto maxCount = static_cast<size_t>(surface.pitch()) *
                        static_cast<size_t>(surface.height());
  memcpy(pixels, surface.pixels(), maxCount);

  texture->unlock();

  return texture;
}

auto texture::from_surface(const renderer& renderer, const surface& surface)
    -> texture
{
  return texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get())};
}

auto texture::operator=(texture&& other) noexcept -> texture&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

void texture::destroy() noexcept
{
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
  }
}

void texture::move(texture&& other) noexcept
{
  destroy();
  m_texture = other.m_texture;
  other.m_texture = nullptr;
}

auto texture::lock(u32** pixels, int* pitch) noexcept -> bool
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

void texture::unlock() noexcept
{
  SDL_UnlockTexture(m_texture);
}

auto texture::unique(gsl::owner<SDL_Texture*> sdlTexture)
    -> std::unique_ptr<texture>
{
  return std::make_unique<texture>(sdlTexture);
}

auto texture::shared(gsl::owner<SDL_Texture*> sdlTexture)
    -> std::shared_ptr<texture>
{
  return std::make_shared<texture>(sdlTexture);
}

void texture::set_pixel(point_i pixel, const color& color) noexcept
{
  if (get_access() != access::streaming || pixel.x() < 0 || pixel.y() < 0 ||
      pixel.x() >= width() || pixel.y() >= height()) {
    return;
  }

  u32* pixels = nullptr;
  int pitch;
  const auto success = lock(&pixels, &pitch);
  if (!success) {
    return;
  }

  const int nPixels = (pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    auto* pixelFormat = SDL_AllocFormat(static_cast<u32>(format()));
    const auto value = SDL_MapRGBA(
        pixelFormat, color.red(), color.green(), color.blue(), color.alpha());

    SDL_FreeFormat(pixelFormat);

    pixels[index] = value;
  }

  unlock();
}

void texture::set_alpha(u8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(m_texture, alpha);
}

void texture::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetTextureBlendMode(m_texture, static_cast<SDL_BlendMode>(mode));
}

void texture::set_color_mod(color color) noexcept
{
  SDL_SetTextureColorMod(m_texture, color.red(), color.green(), color.blue());
}

void texture::set_scale_mode(enum scale_mode mode) noexcept
{
  SDL_SetTextureScaleMode(m_texture, static_cast<SDL_ScaleMode>(mode));
}

auto texture::format() const noexcept -> pixel_format
{
  u32 format = 0;
  SDL_QueryTexture(m_texture, &format, nullptr, nullptr, nullptr);
  return static_cast<pixel_format>(format);
}

auto texture::get_access() const noexcept -> texture::access
{
  int access = 0;
  SDL_QueryTexture(m_texture, nullptr, &access, nullptr, nullptr);
  return static_cast<enum access>(access);
}

auto texture::width() const noexcept -> int
{
  int width = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, nullptr);
  return width;
}

auto texture::height() const noexcept -> int
{
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, nullptr, &height);
  return height;
}

auto texture::size() const noexcept -> area_i
{
  int width = 0;
  int height = 0;
  SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
  return {width, height};
}

auto texture::is_target() const noexcept -> bool
{
  return get_access() == access::target;
}

auto texture::is_static() const noexcept -> bool
{
  return get_access() == access::no_lock;
}

auto texture::is_streaming() const noexcept -> bool
{
  return get_access() == access::streaming;
}

auto texture::alpha() const noexcept -> u8
{
  u8 alpha;
  SDL_GetTextureAlphaMod(m_texture, &alpha);
  return alpha;
}

auto texture::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(m_texture, &mode);
  return static_cast<enum blend_mode>(mode);
}

auto texture::color_mod() const noexcept -> color
{
  u8 r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(m_texture, &r, &g, &b);
  return {r, g, b, 0xFF};
}

auto texture::get_scale_mode() const noexcept -> texture::scale_mode
{
  SDL_ScaleMode mode;
  SDL_GetTextureScaleMode(m_texture, &mode);
  return static_cast<enum scale_mode>(mode);
}

auto texture::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto w = std::to_string(width());
  const auto h = std::to_string(height());
  return "[Texture@" + address + " | Width: " + w + ", Height: " + h + "]";
}

}  // namespace centurion
