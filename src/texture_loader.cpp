#ifndef CENTURION_IMAGE_GENERATOR_SOURCE
#define CENTURION_IMAGE_GENERATOR_SOURCE

#include "texture_loader.h"

#include "centurion_exception.h"
#include "renderer.h"
#include "texture.h"

namespace centurion {

CENTURION_DEF
TextureLoader::TextureLoader(const SharedPtr<Renderer>& renderer)
{
  if (renderer) {
    this->m_renderer = renderer;
  } else {
    throw CenturionException{"Null renderer argument!"};
  }
}

CENTURION_DEF
TextureLoader::~TextureLoader() noexcept = default;

CENTURION_DEF
UniquePtr<Texture> TextureLoader::unique_img(CZString file) const
{
  return Texture::unique(*m_renderer, file);
}

CENTURION_DEF
UniquePtr<Texture> TextureLoader::unique_img(PixelFormat format,
                                             Texture::Access access,
                                             int width,
                                             int height) const
{
  return Texture::unique(*m_renderer, format, access, width, height);
}

CENTURION_DEF
SharedPtr<Texture> TextureLoader::shared_img(CZString file) const
{
  return Texture::shared(*m_renderer, file);
}

CENTURION_DEF
SharedPtr<Texture> TextureLoader::shared_img(PixelFormat format,
                                             Texture::Access access,
                                             int width,
                                             int height) const
{
  return Texture::shared(*m_renderer, format, access, width, height);
}

}  // namespace centurion

#endif  // CENTURION_IMAGE_GENERATOR_SOURCE
