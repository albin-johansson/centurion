#pragma once
#include <SDL_render.h>
#include <memory>
#include "dimensioned.h"

namespace centurion {
namespace visuals {

class Texture;
typedef std::shared_ptr<Texture> Texture_sptr;
typedef std::unique_ptr<Texture> Texture_uptr;
typedef std::weak_ptr<Texture> Texture_wptr;

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
  \brief Returns a referene to the internal represenation of this Texture.
  \since 1.0.0
  */
  SDL_Texture& GetSDLVersion() noexcept;

  /**
  \brief Returns the width of this texture.
  \since 1.0.0
  */
  inline int GetWidth() const noexcept override { return width; };

  /**
  \brief Returns the height of this texture.
  \since 1.0.0
  */
  inline int GetHeight() const noexcept override { return height; };

  /**
  \brief Returns a shared pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that will be the internal
  representation of the Texture.
  \param width - the width of the Texture.
  \param height - the height of the Texture.
  \since 1.1.0
  */
  static Texture_sptr CreateShared(SDL_Texture* texture, int width, int height);

  /**
  \brief Returns a unique pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that will be the internal
  representation of the Texture.
  \param width - the width of the Texture.
  \param height - the height of the Texture.
  \since 1.1.0
  */
  static Texture_uptr CreateUnique(SDL_Texture* texture, int width, int height);

  /**
  \brief Returns a weak pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that will be the internal
  representation of the Texture.
  \param width - the width of the Texture.
  \param height - the height of the Texture.
  \since 1.1.0
  */
  static Texture_wptr CreateWeak(SDL_Texture* texture, int width, int height);
};

}  // namespace visuals
}  // namespace centurion