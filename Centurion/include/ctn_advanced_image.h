#pragma once
#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include <string>
#include "ctn_color.h"
#include "ctn_image_interface.h"
#include "ctn_rectangle.h"

namespace centurion {
namespace visuals {

// FIXME rename this class

/**
\brief The AdvancedImage class is an implementation of the IIMage interface.
\since 2.0.0
*/
class AdvancedImage final : public IImage {
 private:
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = nullptr;

  void* pixels = nullptr;
  Uint32 pixelFormat = 0;
  int pitch = 0;

  SDL_BlendMode blendMode;
  Color modColor;
  Uint8 alpha;
  int width;
  int height;

  void Lock();

  void Unlock();

 public:
  /**
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \param pixelFormat - the pixel format to be used by the created image.
  \throws invalid_argument if the supplied SDL_Renderer pointer is null.
  \since 2.0.0
  */
  AdvancedImage(const std::string& path, SDL_Renderer* renderer,
                Uint32 pixelFormat);

  /**
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \throws invalid_argument if the supplied SDL_Renderer pointer is null.
  \since 2.0.0
  */
  AdvancedImage(const std::string& path, SDL_Renderer* renderer);

  ~AdvancedImage();

  /**
  \brief Resets the state of this image to its original state.
  \param renderer - a pointer to the SDL_Renderer used to reset the image.
  \since 2.0.0
  */
  void Reset(SDL_Renderer* renderer) override;

  /**
  \brief Revalidates this image by reloading it.
  \param renderer - a pointer to the SDL_Renderer used to revalidate the image.
  \note This method will reset any previous pixel modifications.
  \since 2.0.0
  */
  void Revalidate(SDL_Renderer* renderer) override;

  /**
  \brief Modulates the color of this image.
  \param color - the color that will be used.
  \since 2.0.0
  */
  void ModulateColor(Color color) noexcept override;

  /**
  \brief Sets the color of the pixel at the supplied coordinates.
  \param x - the x-coordinate of the pixel to modify.
  \param y - the y-coordinate of the pixel to modify.
  \param color - the color to assign the pixel.
  \note If the supplied coordinates are outside the image bounds, this method
  has no effect.
  \since 2.0.0
  */
  void SetPixel(int x, int y, Color color) override;

  /**
  \brief Sets the alpha value of this image.
  \param alpha - the alpha value to be used, in the range [0, 255].
  \since 2.0.0
  */
  void SetAlpha(Uint8 alpha) noexcept override;

  /**
  \brief Sets the blend mode of this image.
  \param blendMode - the SDL_BlendMode value to be used.
  \since 2.0.0
  */
  void SetBlendMode(SDL_BlendMode blendMode) noexcept override;

  /**
  \brief Returns the width of this image.
  \since 2.0.0
  */
  inline int GetWidth() const noexcept override { return width; }

  /**
  \brief Returns the height of this image.
  \since 2.0.0
  */
  inline int GetHeight() const noexcept override { return height; }

  /**
  \brief Returns a pointer to the internal representation of this image.
  \since 2.0.0
  */
  inline SDL_Texture* GetSDLTexture() noexcept override { return texture; }

  /**
  \brief Returns a shared pointer that points at an AdvancedImage instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \param pixelFormat - the pixel format to be used by the created image.
  \since 2.0.0
  */
  static IImage_sptr CreateShared(const std::string& path,
                                  SDL_Renderer* renderer, Uint32 pixelFormat);

  /**
  \brief Returns a shared pointer that points at an AdvancedImage instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \since 2.0.0
  */
  static IImage_sptr CreateShared(const std::string& path,
                                  SDL_Renderer* renderer);

  /**
  \brief Returns a unique pointer that points at an AdvancedImage instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \param pixelFormat - the pixel format to be used by the created image.
  \since 2.0.0
  */
  static IImage_uptr CreateUnique(const std::string& path,
                                  SDL_Renderer* renderer, Uint32 pixelFormat);

  /**
  \brief Returns a unique pointer that points at an AdvancedImage instance.
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \since 2.0.0
  */
  static IImage_uptr CreateUnique(const std::string& path,
                                  SDL_Renderer* renderer);
};

}  // namespace visuals
}  // namespace centurion