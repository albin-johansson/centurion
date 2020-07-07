//#include "texture_loader.hpp"
//
//#include <catch.hpp>
//#include <string>
//
//#include "centurion_exception.hpp"
//#include "renderer.hpp"
//#include "window.hpp"
//
//using namespace centurion;
//using namespace std::literals;
//
//static const auto* good_path = "resources/panda.png";
//
//TEST_CASE("TextureLoader(Renderer)", "[Renderer]")
//{
//  CHECK_THROWS_AS(TextureLoader{nullptr}, CenturionException);
//}
//
//TEST_CASE("TextureLoader::unique_img(std::string&)", "[TextureLoader]")
//{
//  const Window window;
//  const auto renderer = Renderer::shared(window);
//  const TextureLoader loader{renderer};
//
//  CHECK_THROWS_AS(loader.unique_img("badpath"), CenturionException);
//  CHECK_NOTHROW(loader.unique_img(good_path));
//}
//
//TEST_CASE("TextureLoader::unique_img(PixelFormat, Texture::Access, Area)",
//          "[TextureLoader]")
//{
//  const Window window;
//  const auto renderer = Renderer::shared(window);
//  const TextureLoader loader{renderer};
//
//  CHECK_NOTHROW(loader.unique_img(
//      PixelFormat::RGBA32, Texture::Access::Static, {10, 10}));
//}
//
//TEST_CASE("TextureLoader::shared_img(std::string&)", "[TextureLoader]")
//{
//  const Window window;
//  const auto renderer = Renderer::shared(window);
//  const TextureLoader loader{renderer};
//
//  CHECK_THROWS_AS(loader.shared_img("badpath"), CenturionException);
//  CHECK_NOTHROW(loader.shared_img(good_path));
//}
//
//TEST_CASE("TextureLoader::shared_img(PixelFormat, Texture::Access, Area)",
//          "[TextureLoader]")
//{
//  const Window window;
//  const auto renderer = Renderer::shared(window);
//  const TextureLoader loader{renderer};
//
//  CHECK_NOTHROW(loader.shared_img(
//      PixelFormat::RGBA32, Texture::Access::Static, {10, 10}));
//}