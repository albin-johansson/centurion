#include "sharing_texture.hpp"

#include "exception.hpp"
#include "texture.hpp"

namespace centurion {

sharing_texture::sharing_texture(nn_owner<SDL_Texture*> sdlTexture)
    : basic_texture{sdlTexture, get_deleter()}
{
  if (!get()) {
    throw exception{"Cannot create sharing_texture from null texture!"};
  }
}

sharing_texture::sharing_texture(texture&& texture) noexcept
    : sharing_texture{texture.release()}
{}

}  // namespace centurion
