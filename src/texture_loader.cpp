#ifndef CENTURION_IMAGE_GENERATOR_SOURCE
#define CENTURION_IMAGE_GENERATOR_SOURCE

#include "texture_loader.h"

#include "centurion_exception.h"
#include "renderer.h"
#include "texture.h"

namespace centurion {
namespace video {

CENTURION_DEF
TextureLoader::TextureLoader(const std::shared_ptr<Renderer>& renderer) {
  if (renderer) {
    this->renderer = renderer;
  } else {
    throw CenturionException{"Null renderer argument!"};
  }
}

CENTURION_DEF
TextureLoader::~TextureLoader() noexcept = default;

CENTURION_DEF
std::unique_ptr<Texture> TextureLoader::unique_img(const char* file) const {
  return Texture::unique(*renderer, file);
}

CENTURION_DEF
std::unique_ptr<Texture> TextureLoader::unique_img(PixelFormat format,
                                                   TextureAccess access,
                                                   int width,
                                                   int height) const {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Texture>(*renderer, format, access, width, height);
#else
  return make_unique<Image>(*renderer, format, access, width, height);
#endif
}

CENTURION_DEF
std::shared_ptr<Texture> TextureLoader::shared_img(const char* file) const {
  return Texture::shared(*renderer, file);
}

CENTURION_DEF
std::shared_ptr<Texture> TextureLoader::shared_img(PixelFormat format,
                                                   TextureAccess access,
                                                   int width,
                                                   int height) const {
  return std::make_shared<Texture>(*renderer, format, access, width, height);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_IMAGE_GENERATOR_SOURCE
