#include "sharing_texture.hpp"

#include "texture.hpp"

namespace centurion {

sharing_texture::sharing_texture(nn_owner<SDL_Texture*> sdlTexture) noexcept
    : basic_texture{sdlTexture, get_deleter()}
{}

sharing_texture::sharing_texture(texture&& texture) noexcept
    : sharing_texture{texture.release()}
{}

}  // namespace centurion
