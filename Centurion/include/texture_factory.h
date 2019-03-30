#pragma once
#include <SDL_video.h>
#include <memory>
#include <string>
#include "renderer.h"
#include "texture.h"
#include "centurion.h"

namespace centurion {
namespace visuals {

class TextureFactory final {
 private:
  TextureFactory() = delete;

  static SDL_Texture* CreateSDLTexture(SDL_Surface* surface,
                                       SDL_Renderer* renderer);

 public:
  ~TextureFactory() = default;

  static std::shared_ptr<centurion::visuals::Texture> CreateTexture(
      const std::string& path, SDL_Renderer* renderer);

  static std::shared_ptr<centurion::visuals::Texture> CreateTexture(
      const std::string& path, const centurion::visuals::Renderer& renderer);
};

}  // namespace visuals
}  // namespace centurion