#pragma once
#include <SDL_render.h>
#include <string>
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

class AbstractTexture : public ITexture {
 private:
  Uint32 format = 0;
  int width = 0;
  int height = 0;
  int access = 0;

 protected:
  SDL_Texture* sdlTexture = nullptr;

  AbstractTexture(SDL_Texture* sdlTexture);

  static SDL_Texture* CreateTextureFromPath(const std::string& path,
                                            SDL_Renderer* renderer);

 public:
  virtual ~AbstractTexture();

  inline int GetWidth() const override { return width; }

  inline int GetHeight() const override { return height; }

  inline int GetAccess() const override { return access; }

  inline Uint32 GetFormat() const override { return format; }

  inline SDL_Texture* GetSDLVersion() override { return sdlTexture; }
};

}  // namespace visuals
}  // namespace centurion