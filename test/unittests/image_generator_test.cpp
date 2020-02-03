#include "catch.hpp"
#include "image_generator.h"
#include "centurion_exception.h"
#include "window.h"
#include "renderer.h"
#include <string>

using namespace centurion;
using namespace std::literals;

static const auto good_path = "resources/ctn_icon_1.png"s;

TEST_CASE("ImageGenerator(Renderer)", "[Renderer]") {
  CHECK_THROWS_AS(ImageGenerator{nullptr}, CenturionException);
}

TEST_CASE("ImageGenerator::unique_img(std::string&)", "[ImageGenerator]") {
  const Window window;
  const auto renderer = Renderer::shared(window);
  const ImageGenerator imgGen{renderer};

  CHECK_THROWS_AS(imgGen.unique_img("badpath"s), CenturionException);
  CHECK_NOTHROW(imgGen.unique_img(good_path));
}

TEST_CASE("ImageGenerator::unique_img(PixelFormat, TextureAccess, int, int)", "[ImageGenerator]") {
  const Window window;
  const auto renderer = Renderer::shared(window);
  const ImageGenerator imgGen{renderer};

  CHECK_NOTHROW(imgGen.unique_img(PixelFormat::RGBA32, TextureAccess::Static, 10, 10));
}

TEST_CASE("ImageGenerator::shared_img(std::string&)", "[ImageGenerator]") {
  const Window window;
  const auto renderer = Renderer::shared(window);
  const ImageGenerator imgGen{renderer};

  CHECK_THROWS_AS(imgGen.shared_img("badpath"s), CenturionException);
  CHECK_NOTHROW(imgGen.shared_img(good_path));
}

TEST_CASE("ImageGenerator::shared_img(PixelFormat, TextureAccess, int, int)", "[ImageGenerator]") {
  const Window window;
  const auto renderer = Renderer::shared(window);
  const ImageGenerator imgGen{renderer};

  CHECK_NOTHROW(imgGen.shared_img(PixelFormat::RGBA32, TextureAccess::Static, 10, 10));
}