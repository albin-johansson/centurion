#pragma once
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include <string>
#include "ctn_renderer.h"
#include "texture.h"

namespace centurion {
namespace visuals {

/**
\brief The TextureFactory class provides factory methods for creating instances
of the Texture class.
\since 1.0.0
*/
class TextureFactory final {
 private:
  TextureFactory() = delete;

  static SDL_Texture* CreateSDLTexture(SDL_Surface* surface,
                                       SDL_Renderer* renderer);

 public:
  ~TextureFactory() = default;

  /**
  \brief Creates and returns a Texture instance.
  \param path - the path of the image file that the Texture will represent.
  \param renderer - the SDL_Renderer instance used to create the Texture.
  \since 1.0.0
  */
  static std::shared_ptr<centurion::visuals::Texture> CreateTexture(
      const std::string& path, SDL_Renderer* renderer);

  /**
   * DEPRECATED *
  \brief Creates and returns a Texture instance.
  \param path - the path of the image file that the Texture will represent.
  \param renderer - the Renderer instance used to create the Texture.
  \since 1.0.0
  */
  static std::shared_ptr<centurion::visuals::Texture> CreateTexture(
      const std::string& path, const centurion::visuals::Renderer& renderer);
};

}  // namespace visuals
}  // namespace centurion