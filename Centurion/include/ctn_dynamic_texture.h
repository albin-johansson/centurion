#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include "ctn_abstract_texture.h"

namespace centurion {
namespace visuals {

class DynamicTexture;
typedef std::shared_ptr<DynamicTexture> DynamicTexture_sptr;
typedef std::unique_ptr<DynamicTexture> DynamicTexture_uptr;
typedef std::weak_ptr<DynamicTexture> DynamicTexture_wptr;

/**
\brief The DynamicTexture class represents a texture which is capable of
dynamically revalidating itself.
\since 2.0.0
*/
class DynamicTexture final : public AbstractTexture {
 private:
  SDL_Surface* sdlSurface = nullptr;

 public:
  /**
  \param sdlSurface - a pointer to the SDL_Surface that the DynamicTexture will
  represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  DynamicTexture(SDL_Surface* sdlSurface, SDL_Renderer* renderer);

  /**
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  DynamicTexture(const std::string& path, SDL_Renderer* renderer);

  ~DynamicTexture();

  /**
  \brief Revalidates this texture by reloading the internal SDL_Texture.

  * This method has no effect if the argument is nullptr.

  \param renderer - a pointer to the SDL_Renderer used to recreate the texture.
  \since 2.0.0
  */
  void Revalidate(SDL_Renderer* renderer);

  /**
  \brief Returns a shared pointer that points to a DynamicTexture instance.
  \param sdlSurface - a pointer to the SDL_Surface that the DynamicTexture will
  represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_sptr CreateShared(SDL_Surface* sdlSurface,
                                          SDL_Renderer* renderer);

  /**
  \brief Returns a shared pointer to a DynamicTexture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_sptr CreateShared(const std::string& path,
                                          SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer that points to a DynamicTexture instance.
  \param sdlSurface - a pointer to the SDL_Surface that the DynamicTexture will
  represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_uptr CreateUnique(SDL_Surface* sdlSurface,
                                          SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer to a DynamicTexture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_uptr CreateUnique(const std::string& path,
                                          SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer that points to a DynamicTexture instance.
  \param sdlSurface - a pointer to the SDL_Surface that the DynamicTexture will
  represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_wptr CreateWeak(SDL_Surface* sdlSurface,
                                        SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer to a DynamicTexture instance.
  \param path - the file path of the texture that the texture will represent.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \since 2.0.0
  */
  static DynamicTexture_wptr CreateWeak(const std::string& path,
                                        SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion