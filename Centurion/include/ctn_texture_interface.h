#pragma once
#include <SDL_render.h>
#include <memory>

namespace centurion {
namespace visuals {

/**
\brief The ITexture class is an interface for objects that represent an
hardware-accelerated image.
\since 2.0.0
*/
class ITexture {
 protected:
  ITexture() = default;

 public:
  virtual ~ITexture() = default;

  /**
  \brief Returns the width of this texture.
  \since 2.0.0
  */
  virtual int GetWidth() const = 0;

  /**
  \brief Returns the height of this texture.
  \since 2.0.0
  */
  virtual int GetHeight() const = 0;

  /**
  \brief Returns a pointer to the internal SDL_Texture of this texture.
  \since 2.0.0
  */
  virtual SDL_Texture* GetSDLTexture() = 0;
};

typedef std::shared_ptr<ITexture> ITexture_sptr;
typedef std::unique_ptr<ITexture> ITexture_uptr;
typedef std::weak_ptr<ITexture> ITexture_wptr;

}  // namespace visuals
}  // namespace centurion