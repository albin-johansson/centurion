//#ifndef CENTURION_IMAGE_GENERATOR_SOURCE
//#define CENTURION_IMAGE_GENERATOR_SOURCE
//
//#include "texture_loader.hpp"
//
//#include "centurion_exception.hpp"
//#include "renderer.hpp"
//#include "texture.hpp"
//
//namespace centurion {
//
//CENTURION_DEF
//TextureLoader::TextureLoader(const SharedPtr<Renderer>& renderer)
//{
//  if (renderer) {
//    this->m_renderer = renderer;
//  } else {
//    throw CenturionException{"Cannot create TextureLoader from null renderer!"};
//  }
//}
//
//CENTURION_DEF
//TextureLoader::~TextureLoader() noexcept = default;
//
//CENTURION_DEF
//UniquePtr<Texture> TextureLoader::unique_img(CZString file) const
//{
//  return Texture::unique(*m_renderer, file);
//}
//
//CENTURION_DEF
//UniquePtr<Texture> TextureLoader::unique_img(PixelFormat format,
//                                             Texture::Access access,
//                                             area_i size) const
//{
//  return Texture::unique(*m_renderer, format, access, size);
//}
//
//CENTURION_DEF
//SharedPtr<Texture> TextureLoader::shared_img(CZString file) const
//{
//  return Texture::shared(*m_renderer, file);
//}
//
//CENTURION_DEF
//SharedPtr<Texture> TextureLoader::shared_img(PixelFormat format,
//                                             Texture::Access access,
//                                             area_i size) const
//{
//  return Texture::shared(*m_renderer, format, access, size);
//}
//
//}  // namespace centurion
//
//#endif  // CENTURION_IMAGE_GENERATOR_SOURCE
