#pragma once
#include <SDL_render.h>
#include <memory>
#include <string>
#include "ctn_dimensioned.h"

namespace centurion {
namespace visuals {

class Image;
typedef std::shared_ptr<Image> Texture_sptr;
typedef std::unique_ptr<Image> Texture_uptr;
typedef std::weak_ptr<Image> Texture_wptr;

/**
\brief The Image class is a container for an SDL_Texture and SDL_Surface.
\since 1.0.0
*/
class Image : public centurion::geo::IDimensioned {
 private:
  SDL_Texture* sdlTexture;
  SDL_Surface* sdlSurface;
  int width;
  int height;

 public:
  /**
  \param surface - a pointer to the SDL_Surface that the image will be based on.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 2.0.0
  */
  Image(SDL_Surface* surface, SDL_Renderer* renderer);

  /**
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 2.0.0
  */
  Image(std::string path, SDL_Renderer* renderer);

  ~Image();

  /**
  \brief Revalidates this texture by reloading it.
  \param renderer - a pointer to the SDL_Renderer used to recreate the texture.
  \since 2.0.0
  */
  void Revalidate(SDL_Renderer* renderer);

  /**
  \brief Returns the width of this texture.
  \since 1.0.0
  */
  inline int GetWidth() const noexcept override { return width; }

  /**
  \brief Returns the height of this texture.
  \since 1.0.0
  */
  inline int GetHeight() const noexcept override { return height; }

  /**
  \brief Returns a pointer to the internal represenation of this Image.
  \since 1.0.0
  */
  inline SDL_Texture* Image::GetSDLVersion() noexcept { return sdlTexture; }

  /**
  \brief Returns a shared pointer to a Image instance.
  \param surface - a pointer to the SDL_Surface that the image will be based on.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 1.1.0
  */
  static Texture_sptr CreateShared(SDL_Surface* surface,
                                   SDL_Renderer* renderer);

  /**
  \brief Returns a shared pointer to a Image instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 2.0.0
  */
  static Texture_sptr CreateShared(std::string path, SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer to a Image instance.
  \param surface - a pointer to the SDL_Surface that the image will be based on.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 1.1.0
  */
  static Texture_uptr CreateUnique(SDL_Surface* surface,
                                   SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer to a Image instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 2.0.0
  */
  static Texture_uptr CreateUnique(std::string path, SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer to a Image instance.
  \param surface - a pointer to the SDL_Surface that the image will be based on.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 1.1.0
  */
  static Texture_wptr CreateWeak(SDL_Surface* surface, SDL_Renderer* renderer);

  /**
  \brief Returns a weak pointer to a Image instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to initialize the image.
  \since 2.0.0
  */
  static Texture_wptr CreateWeak(std::string path, SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion