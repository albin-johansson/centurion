#pragma once
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <memory>

namespace centurion {
namespace visuals {

/**
\brief The ITexture class is an interface for objects that represent some sort
of texture.
\since 2.0.0
*/
class ITexture {
 protected:
  ITexture() = default;

 public:
  virtual ~ITexture() = default;

  /**
  \brief Returns the width of the texture.
  \since 2.0.0
  */
  virtual int GetWidth() const = 0;

  /**
  \brief Returns the height of the texture.
  \since 2.0.0
  */
  virtual int GetHeight() const = 0;

  /**
  \brief Returns the access of this texture, see SDL_TEXTUREACCESS_x for
  possible values.
  \since 2.0.0
  */
  virtual int GetAccess() const = 0;

  /**
  \brief Returns the pixel format of this texture, see SDL_PIXELFORMAT_x for
  possible values.
  \since 2.0.0
  */
  virtual Uint32 GetFormat() const = 0;

  /**
  \brief Returns a pointer to the internal SDL_Texture instance.
  \since 2.0.0
  */
  virtual SDL_Texture* GetSDLVersion() = 0;
};

typedef std::shared_ptr<ITexture> ITexture_sptr;
typedef std::unique_ptr<ITexture> ITexture_uptr;
typedef std::weak_ptr<ITexture> ITexture_wptr;

}  // namespace visuals
}  // namespace centurion