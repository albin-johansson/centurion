#include "texture.hpp"

#include <SDL_image.h>

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "colors.hpp"
#include "exception.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "video.hpp"
#include "window.hpp"

static constexpr auto* pandaPath = "resources/panda.png";
static constexpr int pandaWidth = 200;
static constexpr int pandaHeight = 150;

namespace {

template <typename Lambda>
inline void test(Lambda&& lambda)
{
  cen::window window;
  cen::renderer renderer{window};
  lambda(renderer);
}

template <typename Lambda>
inline void test_with_window(Lambda&& lambda)
{
  cen::window window;
  cen::renderer renderer{window};
  lambda(renderer, window);
}

}  // namespace

TEST_CASE("texture_access enum values", "[texture]")
{
  CHECK(cen::texture_access::no_lock == SDL_TEXTUREACCESS_STATIC);
  CHECK(cen::texture_access::streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(cen::texture_access::target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == cen::texture_access::no_lock);
  CHECK(SDL_TEXTUREACCESS_STREAMING == cen::texture_access::streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == cen::texture_access::target);

  CHECK(cen::texture_access::no_lock != SDL_TEXTUREACCESS_STREAMING);
  CHECK(SDL_TEXTUREACCESS_STREAMING != cen::texture_access::no_lock);
}

TEST_CASE("texture::scale_mode enum values", "[texture]")
{
  CHECK(cen::scale_mode::linear == SDL_ScaleModeLinear);
  CHECK(cen::scale_mode::nearest == SDL_ScaleModeNearest);
  CHECK(cen::scale_mode::best == SDL_ScaleModeBest);

  CHECK(SDL_ScaleModeLinear == cen::scale_mode::linear);
  CHECK(SDL_ScaleModeNearest == cen::scale_mode::nearest);
  CHECK(SDL_ScaleModeBest == cen::scale_mode::best);

  CHECK(cen::scale_mode::linear != SDL_ScaleModeNearest);
  CHECK(SDL_ScaleModeBest != cen::scale_mode::nearest);
}

TEST_CASE("texture(owner<SDL_Texture*>)", "[texture]")
{
  test([](cen::renderer& renderer) {
    CHECK_NOTHROW(cen::texture(IMG_LoadTexture(renderer.get(), pandaPath)));
    CHECK_THROWS_AS(cen::texture(nullptr), cen::exception);
  });
}

TEST_CASE("texture(renderer&, nn_czstring)", "[texture]")
{
  test([](cen::renderer& renderer) {
    CHECK_THROWS_AS(cen::texture(renderer, "badpath"), cen::img_error);

    cen::texture texture{renderer, pandaPath};
    CHECK(texture.width() == pandaWidth);
    CHECK(texture.height() == pandaHeight);
  });
}

TEST_CASE("texture(renderer&, surface&", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::surface surface{pandaPath};
    CHECK_NOTHROW(cen::texture{renderer, surface});
  });
}

TEST_CASE("texture(renderer&, pixel_format, access, int, int)", "[texture]")
{
  test([](cen::renderer& renderer) {
    const auto pixelFormat = cen::pixel_format::rgba32;
    const auto access = cen::texture_access::no_lock;
    const auto width = 145;
    const auto height = 85;

    cen::texture texture{renderer, pixelFormat, access, {width, height}};

    CHECK(pixelFormat == texture.format());
    CHECK(access == texture.access());
    CHECK(width == texture.width());
    CHECK(height == texture.height());
  });
}

TEST_CASE("texture(texture&&)", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    cen::texture other = std::move(texture);

    CHECK(!texture.get());
    CHECK(other.get());
  });
}

TEST_CASE("texture::operator=(texture&&)", "[texture]")
{
  SECTION("Self-assignment")
  {
    test([](cen::renderer& renderer) {
      cen::texture texture{renderer, pandaPath};

      texture = std::move(texture);
      CHECK(texture.get());
    });
  }

  SECTION("Normal usage")
  {
    test([](cen::renderer& renderer) {
      cen::texture texture{renderer, pandaPath};
      cen::texture other{renderer, pandaPath};

      other = std::move(texture);

      CHECK(!texture.get());
      CHECK(other.get());
    });
  }
}

TEST_CASE("texture::streaming", "[texture]")
{
  test([](cen::renderer& renderer) {
    const auto pixelFormat = cen::pixel_format::rgba8888;
    auto texture = cen::texture::streaming(renderer, pandaPath, pixelFormat);

    CHECK(texture.format() == pixelFormat);

    CHECK_THROWS_AS(
        cen::texture::streaming(renderer, "", cen::pixel_format::yuy2),
        cen::exception);
  });
}

TEST_CASE("texture::set_pixel", "[texture]")
{
  test([](cen::renderer& renderer) {
    auto texture = cen::texture::streaming(
        renderer, pandaPath, cen::pixel_format::rgba8888);

    const auto [width, height] = texture.size();

    CHECK_NOTHROW(texture.set_pixel({-1, -1}, cen::colors::black));
    CHECK_NOTHROW(texture.set_pixel({-1, 0}, cen::colors::black));
    CHECK_NOTHROW(texture.set_pixel({0, -1}, cen::colors::black));
    CHECK_NOTHROW(texture.set_pixel({width, 0}, cen::colors::black));
    CHECK_NOTHROW(texture.set_pixel({0, height}, cen::colors::black));
    CHECK_NOTHROW(texture.set_pixel({width, height}, cen::colors::black));

    CHECK_NOTHROW(texture.set_pixel({45, 23}, cen::colors::orange));
  });
}

TEST_CASE("texture::set_blend_mode", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    const auto mode = cen::blend_mode::blend;
    texture.set_blend_mode(mode);

    CHECK(mode == texture.get_blend_mode());
  });
}

TEST_CASE("texture::set_alpha", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    const auto alpha = 0x3A;
    texture.set_alpha(alpha);

    CHECK(alpha == texture.alpha());
  });
}

TEST_CASE("texture::set_color_mod", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    const auto color = cen::colors::misty_rose;
    texture.set_color_mod(color);

    const auto actual = texture.color_mod();
    CHECK(color.red() == actual.red());
    CHECK(color.green() == actual.green());
    CHECK(color.blue() == actual.blue());
    CHECK(color.alpha() == actual.alpha());
  });
}

TEST_CASE("texture::set_scale_mode", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    texture.set_scale_mode(cen::scale_mode::nearest);
    CHECK(texture.get_scale_mode() == cen::scale_mode::nearest);

    texture.set_scale_mode(cen::scale_mode::linear);
    CHECK(texture.get_scale_mode() == cen::scale_mode::linear);

    texture.set_scale_mode(cen::scale_mode::best);
    CHECK(texture.get_scale_mode() == cen::scale_mode::best);
  });
}

TEST_CASE("texture::is_static", "[texture]")
{
  test_with_window([](cen::renderer& renderer, const cen::window& window) {
    cen::texture texture{renderer,
                         window.get_pixel_format(),
                         cen::texture_access::no_lock,
                         {10, 10}};
    CHECK(texture.is_static());
  });
}

TEST_CASE("texture::is_streaming", "[texture]")
{
  test_with_window([](cen::renderer& renderer, const cen::window& window) {
    cen::texture texture{renderer,
                         window.get_pixel_format(),
                         cen::texture_access::streaming,
                         {10, 10}};
    CHECK(texture.is_streaming());
  });
}

TEST_CASE("texture::is_target", "[texture]")
{
  test_with_window([](cen::renderer& renderer, const cen::window& window) {
    cen::texture texture{renderer,
                         window.get_pixel_format(),
                         cen::texture_access::target,
                         {10, 10}};
    CHECK(texture.is_target());
  });
}

TEST_CASE("texture to_string", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    cen::log::put(cen::to_string(texture));
  });
}

TEST_CASE("texture stream operator", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    std::cout << "COUT: " << texture << '\n';
  });
}

TEST_CASE("texture::get", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    CHECK(texture.get());
  });
}

TEST_CASE("texture::format", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    cen::u32 format = 0;
    SDL_QueryTexture(sdlTexture, &format, nullptr, nullptr, nullptr);

    CHECK(texture.format() == static_cast<cen::pixel_format>(format));
  });
}

TEST_CASE("texture::access", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    int access = 0;
    SDL_QueryTexture(sdlTexture, nullptr, &access, nullptr, nullptr);

    CHECK(texture.access() == static_cast<cen::texture_access>(access));
  });
}

TEST_CASE("texture::color_mod", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    CHECK(texture.color_mod() == cen::colors::white);
  });
}

TEST_CASE("texture::get_scale_mode", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};

    SDL_ScaleMode mode;
    SDL_GetTextureScaleMode(texture.get(), &mode);
    CHECK(static_cast<SDL_ScaleMode>(texture.get_scale_mode()) == mode);
  });
}

TEST_CASE("texture::width", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture(renderer, pandaPath);
    SDL_Texture* sdlTexture = texture.get();

    CHECK(texture.width() == pandaWidth);

    int width = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, nullptr);
    CHECK(texture.width() == width);
  });
}

TEST_CASE("texture::height", "[texture]")
{
  test([](cen::renderer& renderer) {
    cen::texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    CHECK(texture.height() == pandaHeight);

    int height = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, nullptr, &height);
    CHECK(texture.height() == height);
  });
}

TEST_CASE("texture to SDL_Texture*", "[texture]")
{
  SECTION("Const")
  {
    test([](cen::renderer& renderer) {
      const cen::texture texture{renderer, pandaPath};
      CHECK(texture.operator const SDL_Texture*());
    });
  }

  SECTION("Non-const")
  {
    test([](cen::renderer& renderer) {
      cen::texture texture{renderer, pandaPath};
      CHECK(texture.operator SDL_Texture*());
    });
  }
}