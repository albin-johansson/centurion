#pragma once
#include <SDL_render.h>
#include <memory>
#include <string>
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

class Texture;
typedef std::shared_ptr<Texture> Texture_sptr;
typedef std::unique_ptr<Texture> Texture_uptr;
typedef std::weak_ptr<Texture> Texture_wptr;

/**
\brief The Texture class is based on the SDL_Texture struct.
* The Texture class is a subclass of ITexture.
\since 2.0.0  (Overhauled earlier version)
*/
class Texture : public ITexture {
 private:
  SDL_Texture* sdlTexture = nullptr;
  int width = 0;
  int height = 0;
  int access = 0;
  Uint32 format = 0;

 public:
  /**
  \param sdlTexture - a pointer to the SDL_Texture used as the internal
  representation of this Texture.
  \throws invalid_argument if the supplied pointer is null.
  \since 2.0.0
  */
  Texture(SDL_Texture* sdlTexture);

  /**
  \param path - the file path of the image file to base the texture on.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \throws exception if the creation of the Texture is unsuccessful.
  \since 2.0.0
  */
  Texture(const std::string& path, SDL_Renderer* renderer);

  ~Texture();

  /**
  \brief Returns the pixel format of this texture.
  \since 2.0.0
  */
  inline Uint32 GetFormat() const noexcept { return format; }

  /**
  \brief Returns the access identifier of this texture. See SDL_TEXTUREACCESS_x
  for possible values.
  \since 2.0.0
  */
  inline int GetAccess() const noexcept { return access; }

  /**
  \brief Returns the width of this texture.
  \since 2.0.0
  */
  inline int GetWidth() const noexcept override { return width; }

  /**
  \brief Returns the height of this texture.
  \since 2.0.0
  */
  inline int GetHeight() const override { return height; }

  /**
  \brief Returns a pointer to the internal representation of this texture.
  \since 2.0.0
  */
  inline SDL_Texture* GetSDLTexture() override { return sdlTexture; }

  /**
  \brief Creates and returns a shared pointer to a Texture instance.
  \param sdlTexture - a pointer to the SDL_Texture used as the internal
  representation of this Texture.
  \throws invalid_argument if the supplied pointer is null.
  \since 2.0.0
  */
  static Texture_sptr CreateShared(SDL_Texture* sdlTexture);

  /**
  \brief Creates and returns a shared pointer to a Texture instance.
  \param path - the file path of the image file to base the texture on.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \throws exception if the creation of the Texture is unsuccessful.
  \since 2.0.0
  */
  static Texture_sptr CreateShared(const std::string& path,
                                   SDL_Renderer* renderer);

  /**
  \brief Creates and returns a unique pointer to a Texture instance.
  \param sdlTexture - a pointer to the SDL_Texture used as the internal
  representation of this Texture.
  \throws invalid_argument if the supplied pointer is null.
  \since 2.0.0
  */
  static Texture_uptr CreateUnique(SDL_Texture* sdlTexture);

  /**
  \brief Creates and returns a unique pointer to a Texture instance.
  \param path - the file path of the image file to base the texture on.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \throws exception if the creation of the Texture is unsuccessful.
  \since 2.0.0
  */
  static Texture_uptr CreateUnique(const std::string& path,
                                   SDL_Renderer* renderer);

  /**
  \brief Creates and returns a weak pointer to a Texture instance.
  \param sdlTexture - a pointer to the SDL_Texture used as the internal
  representation of this Texture.
  \throws invalid_argument if the supplied pointer is null.
  \since 2.0.0
  */
  static Texture_wptr CreateWeak(SDL_Texture* sdlTexture);

  /**
  \brief Creates and returns a weak pointer to a Texture instance.
  \param path - the file path of the image file to base the texture on.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \throws exception if the creation of the Texture is unsuccessful.
  \since 2.0.0
  */
  static Texture_wptr CreateWeak(const std::string& path,
                                 SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion