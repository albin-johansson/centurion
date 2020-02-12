#include "image_generator.h"

#include "centurion_exception.h"
#include "image.h"
#include "renderer.h"

namespace centurion {

ImageGenerator::ImageGenerator(const std::shared_ptr<Renderer>& renderer) {
  if (renderer) {
    this->renderer = renderer;
  } else {
    throw CenturionException{"Null renderer argument!"};
  }
}

ImageGenerator::~ImageGenerator() noexcept = default;

std::unique_ptr<Image> ImageGenerator::unique_img(
    const std::string& file) const {
  return Image::unique(*renderer, file);
}

std::unique_ptr<Image> ImageGenerator::unique_img(uint32_t format,
                                                  TextureAccess access,
                                                  int width, int height) const {
  return std::make_unique<Image>(*renderer, format, access, width, height);
}

std::unique_ptr<Image> ImageGenerator::unique_img(PixelFormat format,
                                                  TextureAccess access,
                                                  int width, int height) const {
  return std::make_unique<Image>(*renderer, format, access, width, height);
}

std::shared_ptr<Image> ImageGenerator::shared_img(
    const std::string& file) const {
  return Image::shared(*renderer, file);
}

std::shared_ptr<Image> ImageGenerator::shared_img(uint32_t format,
                                                  TextureAccess access,
                                                  int width, int height) const {
  return std::make_shared<Image>(*renderer, format, access, width, height);
}

std::shared_ptr<Image> ImageGenerator::shared_img(PixelFormat format,
                                                  TextureAccess access,
                                                  int width, int height) const {
  return std::make_shared<Image>(*renderer, format, access, width, height);
}

}  // namespace centurion
