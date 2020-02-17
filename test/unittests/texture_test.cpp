#include "catch.hpp"
#include "centurion_exception.h"
#include "colors.h"
#include "log.h"
#include "renderer.h"
#include "system.h"
#include "texture.h"
#include "window.h"

using namespace centurion;
using namespace centurion::video;

static constexpr auto path = "resources/grass.png";

TEST_CASE("Texture(string)", "[Texture]") {
  Window window;
  Renderer renderer{window};

  CHECK_THROWS_AS(Texture(renderer, "badpath"), CenturionException);

  Texture texture{renderer, path};
  CHECK(texture.get_width() == 108);
  CHECK(texture.get_height() == 108);
}

TEST_CASE("Texture(Texture&&)", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};

  Texture moved_img = std::move(texture);

  CHECK(!texture.get_internal());
}

TEST_CASE(
    "Texture(gsl::not_null<SDL_Renderer*>, PixelFormat, TextureAccess, int, "
    "int)",
    "[Texture]") {
  Window window;
  Renderer renderer{window};
  CHECK_NOTHROW(Texture{renderer.get_internal(), PixelFormat::RGBA32,
                        TextureAccess::Static, 50, 50});
}

TEST_CASE("Texture::unique", "[Texture]") {
  const Window window;
  const Renderer renderer{window};
  CHECK_THROWS_AS(Texture::unique(nullptr), CenturionException);
  CHECK(Texture::unique(renderer.get_internal(), path));
  CHECK(Texture::unique(renderer.get_internal(),
                        static_cast<PixelFormat>(window.get_pixel_format()),
                        TextureAccess::Static, 100, 100));
}

TEST_CASE("Texture:::shared", "[Texture]") {
  const Window window;
  const Renderer renderer{window};
  CHECK_THROWS_AS(Texture::shared(nullptr), CenturionException);
  CHECK(Texture::shared(renderer.get_internal(), path));
  CHECK(Texture::shared(renderer.get_internal(),
                        static_cast<PixelFormat>(window.get_pixel_format()),
                        TextureAccess::Static, 100, 100));
}

TEST_CASE("Texture::get_format", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};
  SDL_Texture* sdlTexture = texture.get_internal();

  uint32_t format = 0;
  SDL_QueryTexture(sdlTexture, &format, nullptr, nullptr, nullptr);

  CHECK(texture.get_format() == format);
}

TEST_CASE("Texture::get_access", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};
  SDL_Texture* sdlTexture = texture.get_internal();

  int access = 0;
  SDL_QueryTexture(sdlTexture, nullptr, &access, nullptr, nullptr);

  CHECK(texture.get_access() == static_cast<TextureAccess>(access));
}

TEST_CASE("Texture::get_width", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture(renderer, path);
  SDL_Texture* sdlTexture = texture.get_internal();

  CHECK(texture.get_width() == 108);

  int width = 0;
  SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, nullptr);
  CHECK(texture.get_width() == width);
}

TEST_CASE("Texture::get_height", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};
  SDL_Texture* sdlTexture = texture.get_internal();

  CHECK(texture.get_height() == 108);

  int height = 0;
  SDL_QueryTexture(sdlTexture, nullptr, nullptr, nullptr, &height);
  CHECK(texture.get_height() == height);
}

TEST_CASE("Texture::set_blend_mode", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};

  const auto mode = BlendMode::Blend;
  texture.set_blend_mode(mode);

  CHECK(mode == texture.get_blend_mode());
}

TEST_CASE("Texture::set_alpha", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};

  const auto alpha = 0x3A;
  texture.set_alpha(alpha);

  CHECK(alpha == texture.get_alpha());
}

TEST_CASE("Texture::set_color_mod", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};

  const auto color = misty_rose;
  texture.set_color_mod(color);

  const auto actual = texture.get_color_mod();
  CHECK(color.get_red() == actual.get_red());
  CHECK(color.get_green() == actual.get_green());
  CHECK(color.get_blue() == actual.get_blue());
  CHECK(color.get_alpha() == actual.get_alpha());
}

TEST_CASE("Texture::is_static", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer.get_internal(), window.get_pixel_format(),
                  TextureAccess::Static, 10, 10};
  CHECK(texture.is_static());
}

TEST_CASE("Texture::is_streaming", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer.get_internal(), window.get_pixel_format(),
                  TextureAccess::Streaming, 10, 10};
  CHECK(texture.is_streaming());
}

TEST_CASE("Texture::is_target", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer.get_internal(), window.get_pixel_format(),
                  TextureAccess::Target, 10, 10};
  CHECK(texture.is_target());
}

TEST_CASE("Texture::to_string", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};
  Log::msgf(Category::Test, "%s", texture.to_string().c_str());
}

TEST_CASE("Texture::get_internal", "[Texture]") {
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, path};
  CHECK(texture.get_internal());
}

TEST_CASE("TextureAccess enum values", "[TextureAccess]") {
  CHECK(TextureAccess::Static == SDL_TEXTUREACCESS_STATIC);
  CHECK(TextureAccess::Streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(TextureAccess::Target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == TextureAccess::Static);
  CHECK(SDL_TEXTUREACCESS_STREAMING == TextureAccess::Streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == TextureAccess::Target);
}