#include "texture.h"

#include <catch.hpp>

#include "centurion_exception.h"
#include "colors.h"
#include "log.h"
#include "renderer.h"
#include "surface.h"
#include "window.h"

using namespace centurion;

static constexpr auto* pandaPath = "resources/panda.png";
static constexpr int pandaWidth = 200;
static constexpr int pandaHeight = 150;

TEST_CASE("TextureAccess enum values", "[TextureAccess]")
{
  CHECK(TextureAccess::Static == SDL_TEXTUREACCESS_STATIC);
  CHECK(TextureAccess::Streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(TextureAccess::Target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == TextureAccess::Static);
  CHECK(SDL_TEXTUREACCESS_STREAMING == TextureAccess::Streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == TextureAccess::Target);

  CHECK(TextureAccess::Static != SDL_TEXTUREACCESS_STREAMING);
  CHECK(SDL_TEXTUREACCESS_STREAMING != TextureAccess::Static);
}

TEST_CASE("Texture(SDL_Texture*)", "[Texture]")
{
  CHECK_THROWS_AS(Texture(nullptr), CenturionException);

  Window window;
  Renderer renderer{window};
  SDL_Texture* sdlTexture = IMG_LoadTexture(renderer.get(), pandaPath);
  CHECK_NOTHROW(Texture(sdlTexture));
}

TEST_CASE("Texture(Renderer&, char*)", "[Texture]")
{
  Window window;
  Renderer renderer{window};

  CHECK_THROWS_AS(Texture(renderer, nullptr), CenturionException);
  CHECK_THROWS_AS(Texture(renderer, "badpath"), CenturionException);

  Texture texture{renderer, pandaPath};
  CHECK(texture.width() == pandaWidth);
  CHECK(texture.height() == pandaHeight);
}

TEST_CASE("Texture(Renderer&, Surface&", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Surface surface{pandaPath};
  CHECK_NOTHROW(Texture{renderer, surface});
}

TEST_CASE("Texture(Renderer&, PixelFormat, TextureAccess, int, int)",
          "[Texture]")
{
  Window window;
  Renderer renderer{window};

  const auto pixelFormat = PixelFormat::RGBA32;
  const auto access = TextureAccess::Static;
  const auto width = 145;
  const auto height = 85;
  Texture texture{renderer, pixelFormat, access, width, height};
  CHECK(pixelFormat == texture.format());
  CHECK(access == texture.access());
  CHECK(width == texture.width());
  CHECK(height == texture.height());
}

TEST_CASE("Texture(Texture&&)", "[Texture]")
{
  Window window;
  Renderer renderer{window};

  Texture texture{renderer, pandaPath};
  Texture other = std::move(texture);

  CHECK(!texture.get());
  CHECK(other.get());
}

TEST_CASE("Texture::operator=(Texture&&)", "[Texture]")
{
  SECTION("Self-assignment")
  {
    Window window;
    Renderer renderer{window};

    Texture texture{renderer, pandaPath};

    texture = std::move(texture);
    CHECK(texture.get());
  }

  SECTION("Normal usage")
  {
    Window window;
    Renderer renderer{window};

    Texture texture{renderer, pandaPath};
    Texture other{renderer, pandaPath};

    other = std::move(texture);

    CHECK(!texture.get());
    CHECK(other.get());
  }
}

TEST_CASE("Texture::unique", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  CHECK_THROWS_AS(Texture::unique(nullptr), CenturionException);
  CHECK(Texture::unique(renderer, pandaPath));
  CHECK(Texture::unique(
      renderer, window.pixel_format(), TextureAccess::Static, 100, 100));
}

TEST_CASE("Texture:::shared", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  CHECK_THROWS_AS(Texture::shared(nullptr), CenturionException);
  CHECK(Texture::shared(renderer, pandaPath));
  CHECK(Texture::shared(
      renderer, window.pixel_format(), TextureAccess::Static, 100, 100));
}

TEST_CASE("Texture::format", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};
  SDL_Texture* sdlTexture = texture.get();

  Uint32 format = 0;
  SDL_QueryTexture(sdlTexture, &format, nullptr, nullptr, nullptr);

  CHECK(texture.format() == static_cast<PixelFormat>(format));
}

TEST_CASE("Texture::access", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};
  SDL_Texture* sdlTexture = texture.get();

  int access = 0;
  SDL_QueryTexture(sdlTexture, nullptr, &access, nullptr, nullptr);

  CHECK(texture.access() == static_cast<TextureAccess>(access));
}

TEST_CASE("Texture::width", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture(renderer, pandaPath);
  SDL_Texture* sdlTexture = texture.get();

  CHECK(texture.width() == pandaWidth);

  int width = 0;
  SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, nullptr);
  CHECK(texture.width() == width);
}

TEST_CASE("Texture::height", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};
  SDL_Texture* sdlTexture = texture.get();

  CHECK(texture.height() == pandaHeight);

  int height = 0;
  SDL_QueryTexture(sdlTexture, nullptr, nullptr, nullptr, &height);
  CHECK(texture.height() == height);
}

TEST_CASE("Texture::set_blend_mode", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};

  const auto mode = BlendMode::Blend;
  texture.set_blend_mode(mode);

  CHECK(mode == texture.blend_mode());
}

TEST_CASE("Texture::set_alpha", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};

  const auto alpha = 0x3A;
  texture.set_alpha(alpha);

  CHECK(alpha == texture.alpha());
}

TEST_CASE("Texture::set_color_mod", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};

  const auto color = misty_rose;
  texture.set_color_mod(color);

  const auto actual = texture.color_mod();
  CHECK(color.red() == actual.red());
  CHECK(color.green() == actual.green());
  CHECK(color.blue() == actual.blue());
  CHECK(color.alpha() == actual.alpha());
}

TEST_CASE("Texture::is_static", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{
      renderer, window.pixel_format(), TextureAccess::Static, 10, 10};
  CHECK(texture.is_static());
}

TEST_CASE("Texture::is_streaming", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{
      renderer, window.pixel_format(), TextureAccess::Streaming, 10, 10};
  CHECK(texture.is_streaming());
}

TEST_CASE("Texture::is_target", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{
      renderer, window.pixel_format(), TextureAccess::Target, 10, 10};
  CHECK(texture.is_target());
}

TEST_CASE("Texture::to_string", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};
  Log::msgf(Category::Test, "%s", texture.to_string().c_str());
}

TEST_CASE("Texture::get", "[Texture]")
{
  Window window;
  Renderer renderer{window};
  Texture texture{renderer, pandaPath};
  CHECK(texture.get());
}

TEST_CASE("Texture to SDL_Texture*", "[Texture]")
{
  SECTION("Const")
  {
    Window window;
    Renderer renderer{window};
    const Texture texture{renderer, pandaPath};
    CHECK(texture.operator const SDL_Texture*());
  }

  SECTION("Non-const")
  {
    Window window;
    Renderer renderer{window};
    Texture texture{renderer, pandaPath};
    CHECK(texture.operator SDL_Texture*());
  }
}