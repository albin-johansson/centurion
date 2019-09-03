#pragma once
#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <memory>
#include "ctn_color.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

/**
\brief The IImage class is an interface for objects that represent an image.
\since 2.0.0
*/
class IImage : public ITexture {
 protected:
  IImage() = default;

 public:
  virtual ~IImage() = default;

  /**
  \brief Resets the state of this image to its original state.
  \param renderer - a pointer to the SDL_Renderer used to reset the image.
  \note If the supplied pointer is null, this method has no effect.
  \since 2.0.0
  */
  virtual void Reset(SDL_Renderer* renderer) = 0;

  /**
  \brief Revalidates this image by reloading it.
  \param renderer - a pointer to the SDL_Renderer used to revalidate the image.
  \note This method will reset any previous pixel modifications.
  \note If the supplied pointer is null, this method has no effect.
  \since 2.0.0
  */
  virtual void Revalidate(SDL_Renderer* renderer) = 0;

  /**
  \brief Modulates the color of this image.
  \param color - the color that will be used.
  \since 2.0.0
  */
  virtual void ModulateColor(Color color) = 0;

  /**
  \brief Sets the color of the pixel at the supplied coordinates.
  \param x - the x-coordinate of the pixel to modify.
  \param y - the y-coordinate of the pixel to modify.
  \param color - the color to assign the pixel.
  \note If the supplied coordinates are outside the image bounds, this method
  has no effect.
  \since 2.0.0
  */
  virtual void SetPixel(int x, int y, Color color) = 0;

  /**
  \brief Sets the alpha value of this image.
  \param alpha - the alpha value to be used, in the range [0, 255].
  \since 2.0.0
  */
  virtual void SetAlpha(Uint8 alpha) = 0;

  /**
  \brief Sets the blend mode of this image.
  \param blendMode - the SDL_BlendMode value to be used.
  \since 2.0.0
  */
  virtual void SetBlendMode(SDL_BlendMode blendMode) = 0;
};

using IImage_sptr = std::shared_ptr<IImage>;
using IImage_uptr = std::unique_ptr<IImage>;
using IImage_wptr = std::weak_ptr<IImage>;

}  // namespace visuals
}  // namespace centurion