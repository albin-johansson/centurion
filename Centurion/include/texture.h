#pragma once
#include <SDL_render.h>
#include <memory>
#include "dimensioned.h"

namespace centurion {
namespace visuals {

/**
\brief The Texture class represents textures such as images.
\since 1.0.0
*/
class Texture : public centurion::geo::Dimensioned {
 private:
  SDL_Texture* sdl_texture;
  const int width;
  const int height;

 public:
  /**
  \param texture - a pointer to the SDL_Texture that will be the internal
  representation of the Texture.
  \param width - the width of the Texture.
  \param height - the height of the Texture.
  */
  Texture(SDL_Texture* texture, int width, int height);

  ~Texture();

  /**
  \brief Creates and returns a heap allocated Texture instance.
  \param texture - a pointer to the SDL_Texture that will be the internal
  representation of the Texture.
  \param width - the width of the Texture.
  \param height - the height of the Texture.
  */
  static std::shared_ptr<centurion::visuals::Texture> Create(
      SDL_Texture* texture, int width, int height);

  /**
  \brief Returns a referene to the internal represenation of this Texture.
  */
  SDL_Texture& GetSDLVersion() noexcept;

  /**
  \brief Returns the width of this texture.
  */
  inline int GetWidth() const noexcept override { return width; };

  /**
  \brief Returns the height of this texture.
  */
  inline int GetHeight() const noexcept override { return height; };
};

typedef std::shared_ptr<centurion::visuals::Texture> Texture_sptr;
typedef std::unique_ptr<centurion::visuals::Texture> Texture_uptr;
typedef std::weak_ptr<centurion::visuals::Texture> Texture_wptr;

}  // namespace visuals
}  // namespace centurion