#include "texture.hpp"

#include <SDL_image.h>

#include "centurion_exception.hpp"
#include "detail/utils.hpp"
#include "surface.hpp"

namespace centurion {

texture::texture(nn_owner<SDL_Texture*> sdlTexture) noexcept
    : basic_texture{sdlTexture}
{}

auto texture::unique(nn_owner<SDL_Texture*> sdlTexture) -> uptr
{
  return std::make_unique<texture>(sdlTexture);
}

auto texture::shared(nn_owner<SDL_Texture*> sdlTexture) -> sptr
{
  return std::make_shared<texture>(sdlTexture);
}

auto to_string(const texture& texture) -> std::string
{
  const auto ptr = detail::address_of(texture.get());
  const auto w = std::to_string(texture.width());
  const auto h = std::to_string(texture.height());
  return "[texture | ptr: " + ptr + ", width: " + w + ", height: " + h + "]";
}

auto operator<<(std::ostream& stream, const texture& texture) -> std::ostream&
{
  stream << to_string(texture);
  return stream;
}

auto texture::release() noexcept -> SDL_Texture*
{
  return get_storage().release();
}

}  // namespace centurion
