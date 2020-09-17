#include "texture.hpp"

#include <SDL_image.h>

#include "detail/to_string.hpp"
#include "exception.hpp"

namespace centurion {

texture::texture(nn_owner<SDL_Texture*> sdlTexture) noexcept
    : basic_texture{sdlTexture}
{}

auto to_string(const texture& texture) -> std::string
{
  const auto ptr = detail::address_of(texture.get());
  const auto w = detail::to_string(texture.width()).value();
  const auto h = detail::to_string(texture.height()).value();
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
