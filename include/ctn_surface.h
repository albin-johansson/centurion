#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include "ctn_color.h"

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
  \brief Sets the alpha (opacity) component value of this surface.
  \param alpha - the new alpha value that will be used, in the range [0, 255].
  \throws invalid_argument if the supplied alpha value is less than 0 or greater
  than 255.
  \since 2.0.0
  */
  void SetAlpha(int alpha);

  /**
  \brief Sets the blend mode that will be used by this surface.
  \param mode - the value that represents the blend mode that will be used.
  \since 2.0.0
  */
  void SetBlendMode(SDL_BlendMode mode) noexcept;

  /**
  \brief Modulates the colors used by this surface.
  \param color - the color used for the modulation.
  \since 2.0.0
  */
  void SetColorModulation(Color color) noexcept;

  /**
  \brief Locks this surface, which prepares the surface for pixel manipulation.
  \since 2.0.0
  */
  void Lock() noexcept;

  /**
  \brief Unlocks this surface.
  \since 2.0.0
  */
  void Unlock() noexcept;

  /**
  \brief Returns a pointer to a duplicated surface instance.
  \since 2.0.0
  */
  Surface_uptr Duplicate() const;

  /**
  \brief Creates and returns a pointer to an SDL_Texture equivalent of this
  surface.
  \param renderer - a pointer to the SDL_Renderer used to create the texture.
  \throws invalid_argument if the supplied pointer is nullptr.
  \since 2.0.0
  */
  SDL_Texture* ToTexture(SDL_Renderer* renderer) const;

  /**
  \brief Returns true if this surface is locked, returns false otherwise.
  \since 2.0.0
  */
  inline bool IsLocked() const noexcept { return sdlSurface->locked; }

  /**
  \brief Returns the width of this surface.
  \since 2.0.0
  */
  inline int GetWidth() const noexcept { return sdlSurface->w; }

  /**
  \brief Returns the height of this surface.
  \since 2.0.0
  */
  inline int GetHeight() const noexcept { return sdlSurface->h; }

  /**
  \brief Returns a pointer to the internal representation of this Surface
  instance.
  \since 2.0.0
  */
  inline SDL_Surface* GetSDLVersion() noexcept { return sdlSurface; }

  /**
  \brief Returns the blend mode for this surface.
  \since 2.0.0
  */
  inline SDL_BlendMode GetBlendMode() const noexcept {
    SDL_BlendMode result;
    SDL_GetSurfaceBlendMode(sdlSurface, &result);
    return result;
  }

  /**
  \brief Returns the alpha (opacity) value used by this surface.
  \since 2.0.0
  */
  inline int GetAlpha() const noexcept {
    Uint8 result;
    SDL_GetSurfaceAlphaMod(sdlSurface, &result);
    return static_cast<int>(result);
  }

  /**
  \brief Returns a color that represents the color modulation that this surface
  uses.
  \since 2.0.0
  */
  Color GetColorModulation() const noexcept;

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