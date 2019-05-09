#pragma once
#include <SDL_surface.h>
#include <memory>

namespace centurion {
namespace visuals {

class Surface;
using Surface_sptr = std::shared_ptr<Surface>;
using Surface_uptr = std::unique_ptr<Surface>;
using Surface_wptr = std::weak_ptr<Surface>;

/**
\brief The Surface class is based on the SDL_Surface struct.
\since 2.0.0
*/
class Surface final {
 private:
  SDL_Surface* sdlSurface;

 public:
  /**
  \param sdlSurface - a pointer to the
  \throws invalid_argument if the supplied pointer is null.
  \since 2.0.0
  */
  Surface(SDL_Surface* sdlSurface);

  ~Surface();

  /**
  \brief Returns the width of this surface.
  \since 2.0.0
  */
  int GetWidth() const noexcept;

  /**
  \brief Returns the height of this surface.
  \since 2.0.0
  */
  int GetHeight() const noexcept;

  /**
  \brief Returns a pointer to the internal representation of this Surface
  instance.
  \since 2.0.0
  */
  SDL_Surface* GetSDLVersion();

  /**
  \brief Creates and returns a shared pointer that points at an SDL_Surface.
  \param sdlSurface - a pointer to the SDL_Surface instance used as the internal
  representation of the new Surface instance.
  \since 2.0.0
  */
  static Surface_sptr CreateShared(SDL_Surface* sdlSurface);

  /**
  \brief Creates and returns a unique pointer that points at an SDL_Surface.
  \param sdlSurface - a pointer to the SDL_Surface instance used as the internal
  representation of the new Surface instance.
  \since 2.0.0
  */
  static Surface_uptr CreateUnique(SDL_Surface* sdlSurface);
};

}  // namespace visuals
}  // namespace centurion