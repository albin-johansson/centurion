#include <SDL_image.h>

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "colors.hpp"
#include "graphics.hpp"
#include "log.hpp"
#include "surface.hpp"
#include "window.hpp"

using namespace centurion;

static constexpr auto* pandaPath = "resources/panda.png";
static constexpr int pandaWidth = 200;
static constexpr int pandaHeight = 150;

namespace {

template <typename Lambda>
inline void test(Lambda&& lambda)
{
  ctn::window window;
  ctn::renderer renderer{window};
  lambda(renderer);
}

template <typename Lambda>
inline void test_with_window(Lambda&& lambda)
{
  ctn::window window;
  ctn::renderer renderer{window};
  lambda(renderer, window);
}

}  // namespace

TEST_CASE("Access enum values", "[Texture]")
{
  CHECK(Texture::Access::Static == SDL_TEXTUREACCESS_STATIC);
  CHECK(Texture::Access::Streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(Texture::Access::Target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == Texture::Access::Static);
  CHECK(SDL_TEXTUREACCESS_STREAMING == Texture::Access::Streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == Texture::Access::Target);

  CHECK(Texture::Access::Static != SDL_TEXTUREACCESS_STREAMING);
  CHECK(SDL_TEXTUREACCESS_STREAMING != Texture::Access::Static);
}

TEST_CASE("ScaleMode enum values", "[ScaleMode]")
{
  CHECK(Texture::ScaleMode::Linear == SDL_ScaleModeLinear);
  CHECK(Texture::ScaleMode::Nearest == SDL_ScaleModeNearest);
  CHECK(Texture::ScaleMode::Best == SDL_ScaleModeBest);

  CHECK(SDL_ScaleModeLinear == Texture::ScaleMode::Linear);
  CHECK(SDL_ScaleModeNearest == Texture::ScaleMode::Nearest);
  CHECK(SDL_ScaleModeBest == Texture::ScaleMode::Best);

  CHECK(Texture::ScaleMode::Linear != SDL_ScaleModeNearest);
  CHECK(SDL_ScaleModeBest != Texture::ScaleMode::Nearest);
}

TEST_CASE("Texture(SDL_Texture*)", "[Texture]")
{
  CHECK_THROWS_AS(Texture(nullptr), centurion_exception);

  test([](ctn::renderer& renderer) {
    SDL_Texture* sdlTexture = IMG_LoadTexture(renderer.get(), pandaPath);
    CHECK_NOTHROW(Texture(sdlTexture));
  });
}

TEST_CASE("Texture(Renderer&, char*)", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    CHECK_THROWS_AS(Texture(renderer, nullptr), centurion_exception);
    CHECK_THROWS_AS(Texture(renderer, "badpath"), centurion_exception);

    Texture texture{renderer, pandaPath};
    CHECK(texture.width() == pandaWidth);
    CHECK(texture.height() == pandaHeight);
  });
}

TEST_CASE("Texture(Renderer&, Surface&", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Surface surface{pandaPath};
    CHECK_NOTHROW(Texture{renderer, surface});
  });
}

TEST_CASE("Texture(Renderer&, PixelFormat, Access, int, int)", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    const auto pixelFormat = PixelFormat::RGBA32;
    const auto access = Texture::Access::Static;
    const auto width = 145;
    const auto height = 85;

    Texture texture{renderer, pixelFormat, access, {width, height}};

    CHECK(pixelFormat == texture.format());
    CHECK(access == texture.access());
    CHECK(width == texture.width());
    CHECK(height == texture.height());
  });
}

TEST_CASE("Texture(Texture&&)", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    Texture other = std::move(texture);

    CHECK(!texture.get());
    CHECK(other.get());
  });
}

TEST_CASE("Texture::operator=(Texture&&)", "[Texture]")
{
  SECTION("Self-assignment")
  {
    test([](ctn::renderer& renderer) {
      Texture texture{renderer, pandaPath};

      texture = std::move(texture);
      CHECK(texture.get());
    });
  }

  SECTION("Normal usage")
  {
    test([](ctn::renderer& renderer) {
      Texture texture{renderer, pandaPath};
      Texture other{renderer, pandaPath};

      other = std::move(texture);

      CHECK(!texture.get());
      CHECK(other.get());
    });
  }
}

TEST_CASE("Texture::unique", "[Texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    const Surface surface{pandaPath};

    CHECK_THROWS_AS(Texture::unique(nullptr), centurion_exception);

    CHECK(Texture::unique(renderer, pandaPath));
    CHECK(Texture::unique(renderer, surface));
    CHECK(Texture::unique(
        renderer, window.pixel_format(), Texture::Access::Static, {100, 100}));
  });
}

TEST_CASE("Texture:::shared", "[Texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    const Surface surface{pandaPath};

    CHECK_THROWS_AS(Texture::shared(nullptr), centurion_exception);

    CHECK(Texture::shared(renderer, pandaPath));
    CHECK(Texture::shared(renderer, surface));
    CHECK(Texture::shared(
        renderer, window.pixel_format(), Texture::Access::Static, {100, 100}));
  });
}

TEST_CASE("Texture::streaming", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    const auto pixelFormat = PixelFormat::RGBA8888;
    auto texture = Texture::streaming(renderer, pandaPath, pixelFormat);

    CHECK(texture->format() == pixelFormat);

    CHECK_THROWS_AS(Texture::streaming(renderer, "", PixelFormat::YUY2),
                    centurion_exception);
  });
}

TEST_CASE("Texture::set_pixel", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    const auto texture =
        Texture::streaming(renderer, pandaPath, PixelFormat::RGBA8888);

    const auto [width, height] = texture->size();

    CHECK_NOTHROW(texture->set_pixel({-1, -1}, color::black));
    CHECK_NOTHROW(texture->set_pixel({-1, 0}, color::black));
    CHECK_NOTHROW(texture->set_pixel({0, -1}, color::black));
    CHECK_NOTHROW(texture->set_pixel({width, 0}, color::black));
    CHECK_NOTHROW(texture->set_pixel({0, height}, color::black));
    CHECK_NOTHROW(texture->set_pixel({width, height}, color::black));

    CHECK_NOTHROW(texture->set_pixel({45, 23}, color::orange));
  });
}

TEST_CASE("Texture::set_blend_mode", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    const auto mode = blend_mode::blend;
    texture.set_blend_mode(mode);

    CHECK(mode == texture.blend_mode());
  });
}

TEST_CASE("Texture::set_alpha", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    const auto alpha = 0x3A;
    texture.set_alpha(alpha);

    CHECK(alpha == texture.alpha());
  });
}

TEST_CASE("Texture::set_color_mod", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    const auto color = color::misty_rose;
    texture.set_color_mod(color);

    const auto actual = texture.color_mod();
    CHECK(color.red() == actual.red());
    CHECK(color.green() == actual.green());
    CHECK(color.blue() == actual.blue());
    CHECK(color.alpha() == actual.alpha());
  });
}

TEST_CASE("Texture::set_scale_mode", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    texture.set_scale_mode(Texture::ScaleMode::Nearest);
    CHECK(texture.scale_mode() == Texture::ScaleMode::Nearest);

    texture.set_scale_mode(Texture::ScaleMode::Linear);
    CHECK(texture.scale_mode() == Texture::ScaleMode::Linear);

    texture.set_scale_mode(Texture::ScaleMode::Best);
    CHECK(texture.scale_mode() == Texture::ScaleMode::Best);
  });
}

TEST_CASE("Texture::is_static", "[Texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    Texture texture{
        renderer, window.pixel_format(), Texture::Access::Static, {10, 10}};
    CHECK(texture.is_static());
  });
}

TEST_CASE("Texture::is_streaming", "[Texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    Texture texture{
        renderer, window.pixel_format(), Texture::Access::Streaming, {10, 10}};
    CHECK(texture.is_streaming());
  });
}

TEST_CASE("Texture::is_target", "[Texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    Texture texture{
        renderer, window.pixel_format(), Texture::Access::Target, {10, 10}};
    CHECK(texture.is_target());
  });
}

TEST_CASE("Texture::to_string", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    log::info(log::category::test, "%s", texture.to_string().c_str());
  });
}

TEST_CASE("Texture::get", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    CHECK(texture.get());
  });
}

TEST_CASE("Texture::format", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    Uint32 format = 0;
    SDL_QueryTexture(sdlTexture, &format, nullptr, nullptr, nullptr);

    CHECK(texture.format() == static_cast<PixelFormat>(format));
  });
}

TEST_CASE("Texture::access", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    int access = 0;
    SDL_QueryTexture(sdlTexture, nullptr, &access, nullptr, nullptr);

    CHECK(texture.access() == static_cast<Texture::Access>(access));
  });
}

TEST_CASE("Texture::color_mod", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    CHECK(texture.color_mod() == color::white);
  });
}

TEST_CASE("Texture::scale_mode", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};

    SDL_ScaleMode mode;
    SDL_GetTextureScaleMode(texture.get(), &mode);
    CHECK(static_cast<SDL_ScaleMode>(texture.scale_mode()) == mode);
  });
}

TEST_CASE("Texture::width", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture(renderer, pandaPath);
    SDL_Texture* sdlTexture = texture.get();

    CHECK(texture.width() == pandaWidth);

    int width = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, nullptr);
    CHECK(texture.width() == width);
  });
}

TEST_CASE("Texture::height", "[Texture]")
{
  test([](ctn::renderer& renderer) {
    Texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    CHECK(texture.height() == pandaHeight);

    int height = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, nullptr, &height);
    CHECK(texture.height() == height);
  });
}

TEST_CASE("Texture to SDL_Texture*", "[Texture]")
{
  SECTION("Const")
  {
    test([](ctn::renderer& renderer) {
      const Texture texture{renderer, pandaPath};
      CHECK(texture.operator const SDL_Texture*());
    });
  }

  SECTION("Non-const")
  {
    test([](ctn::renderer& renderer) {
      Texture texture{renderer, pandaPath};
      CHECK(texture.operator SDL_Texture*());
    });
  }
}