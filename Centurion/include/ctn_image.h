#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include <string>
#include "ctn_color.h"
#include "ctn_surface.h"
#include "ctn_texture.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

class Image;
typedef std::shared_ptr<Image> Image_sptr;
typedef std::unique_ptr<Image> Image_uptr;
typedef std::weak_ptr<Image> Image_wptr;

/**
\brief The Image class serves as a combination of the Texture and Surface
classes.
\since 2.0.0
*/
class Image : public ITexture {
 private:
  Surface_sptr surface;
  Texture_sptr texture;

 public:
  /**
  \param path - the file path of the image file.
  \param renderer - a pointer to the SDL_Renderer used to create the image.
  \throws exception... if the image isn't found or if the supplied pointer is
  null.
  \since 2.0.0
  */
  Image(const std::string& path, SDL_Renderer* renderer);

  ~Image();

  /**
  \brief Revalidates this image by reloading it.
  \param renderer - a pointer to the SDL_Renderer used to recreate the image.
  \since 2.0.0
  */
  void Revalidate(SDL_Renderer* renderer);

  /**
  \brief Returns the width of this image.
  \since 2.0.0
  */
  int GetWidth() const override;

  /**
  \brief Returns the height of this image.
  \since 2.0.0
  */
  int GetHeight() const override;

  /**
  \brief Returns a pointer to the internal SDL_Texture representation of this
  image.
  \since 2.0.0
  */
  SDL_Texture* GetSDLTexture() override;
};

}  // namespace visuals
}  // namespace centurion