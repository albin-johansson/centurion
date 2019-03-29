#pragma once
#include <SDL_image.h>
#include "centurion.h"
#include "dimensioned.h"

/**
\brief The Texture class represents textures such as images.
*/
class centurion::visuals::Texture : public centurion::Dimensioned {
 private:
  SDL_Texture* sdl_texture;
  const int width;
  const int height;

 public:
  Texture(SDL_Texture* texture, int width, int height);

  ~Texture();

  SDL_Texture& GetSDLTexture();

  /**
  \brief Returns the width of this texture.
  */
  int GetWidth() const override;

  /**
  \brief Returns the height of this texture.
  */
  int GetHeight() const override;
};