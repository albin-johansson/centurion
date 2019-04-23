#pragma once
#include <SDL_render.h>
#include <memory>
#include <string>
#include "ctn_abstract_texture.h"

namespace centurion {
namespace visuals {

class Texture;
typedef std::shared_ptr<Texture> Texture_sptr;
typedef std::unique_ptr<Texture> Texture_uptr;
typedef std::weak_ptr<Texture> Texture_wptr;

/**
\brief The Texture class is a basic representation of an SDL_Texture.

* Texture is a subclass of AbstractTexture.

\since 1.0.0 (2.0.0)
*/
class Texture final : public AbstractTexture {
 public:
  /**
  \param texture - a pointer to the SDL_Texture that the texture will be based
   on.
  \since 2.0.0
  */
  Texture(SDL_Texture* texture);

  /**
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  Texture(const std::string& path, SDL_Renderer* renderer);

  ~Texture();

  /**
  \brief Returns a shared pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that the texture will be based
  on.
  \since 1.1.0 (2.0.0)
  */
  static Texture_sptr CreateShared(SDL_Texture* texture);

  /**
  \brief Returns a shared pointer to a Texture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static Texture_sptr CreateShared(const std::string& path,
                                   SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that the texture will be based
  on.
  \since 1.1.0 (2.0.0)
  */
  static Texture_uptr CreateUnique(SDL_Texture* texture);

  /**
  \brief Returns a unique pointer to a Texture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static Texture_uptr CreateUnique(const std::string& path,
                                   SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer to a Texture instance.
  \param texture - a pointer to the SDL_Texture that the texture will be based
  on.
  \since 1.1.0 (2.0.0)
  */
  static Texture_wptr CreateWeak(SDL_Texture* texture);

  /**
  \brief Returns a weak pointer to a Texture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static Texture_wptr CreateWeak(const std::string& path,
                                 SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion