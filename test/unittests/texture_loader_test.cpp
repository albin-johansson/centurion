#include "texture_loader.h"

#include <string>

#include "catch.hpp"
#include "centurion_exception.h"
#include "renderer.h"
#include "window.h"

using namespace centurion;
using namespace centurion::video;
using namespace std::literals;

static const auto* good_path = "resources/ctn_icon_1.png";

TEST_CASE("TextureLoader(Renderer)", "[Renderer]")
{
  CHECK_THROWS_AS(TextureLoader{nullptr}, CenturionException);
}

TEST_CASE("TextureLoader::unique_img(std::string&)", "[TextureLoader]")
{
  const Window window;
  const auto renderer = Renderer::shared(window.get_internal());
  const TextureLoader loader{renderer};

  CHECK_THROWS_AS(loader.unique_img("badpath"), CenturionException);
  CHECK_NOTHROW(loader.unique_img(good_path));
}

TEST_CASE("TextureLoader::unique_img(PixelFormat, TextureAccess, int, int)",
          "[TextureLoader]")
{
  const Window window;
  const auto renderer = Renderer::shared(window.get_internal());
  const TextureLoader loader{renderer};

  CHECK_NOTHROW(
      loader.unique_img(PixelFormat::RGBA32, TextureAccess::Static, 10, 10));
}

TEST_CASE("TextureLoader::shared_img(std::string&)", "[TextureLoader]")
{
  const Window window;
  const auto renderer = Renderer::shared(window.get_internal());
  const TextureLoader loader{renderer};

  CHECK_THROWS_AS(loader.shared_img("badpath"), CenturionException);
  CHECK_NOTHROW(loader.shared_img(good_path));
}

TEST_CASE("TextureLoader::shared_img(PixelFormat, TextureAccess, int, int)",
          "[TextureLoader]")
{
  const Window window;
  const auto renderer = Renderer::shared(window.get_internal());
  const TextureLoader loader{renderer};

  CHECK_NOTHROW(
      loader.shared_img(PixelFormat::RGBA32, TextureAccess::Static, 10, 10));
}