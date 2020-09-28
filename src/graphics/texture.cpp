#include "texture.hpp"

#include <SDL_image.h>

#include <type_traits>

#include "exception.hpp"

namespace cen {

static_assert(std::is_final_v<texture>);
static_assert(std::is_nothrow_move_constructible_v<texture>);
static_assert(std::is_nothrow_move_assignable_v<texture>);
static_assert(!std::is_nothrow_copy_constructible_v<texture>);
static_assert(!std::is_nothrow_copy_assignable_v<texture>);

texture::texture(owner<SDL_Texture*> sdlTexture) : basic_texture{sdlTexture}
{
  if (!get()) {
    throw exception{"Cannot create texture from null pointer!"};
  }
}

auto to_string(const texture& texture) -> std::string
{
  return "[texture | ptr: " + detail::address_of(texture.get()) +
         ", width: " + std::to_string(texture.width()) +
         ", height: " + std::to_string(texture.height()) + "]";
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

}  // namespace cen
