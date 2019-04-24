#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>
#include "ctn_color.h"
#include "ctn_surface.h"
#include "ctn_texture.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

// TODO documentation

class Image : public ITexture {
 private:
  Surface_sptr surface;
  Texture_sptr texture;

 public:
  Image(const std::string& path, SDL_Renderer* renderer);

  ~Image();

  void Revalidate(SDL_Renderer* renderer);

  void SetPixel(int x, int y, Color color);

  int GetWidth() const override;

  int GetHeight() const override;

  SDL_Texture* GetSDLTexture() override;
};

}  // namespace visuals
}  // namespace centurion