#include <SDL_image.h>

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "colors.hpp"
#include "log.hpp"
#include "surface.hpp"
#include "window.hpp"

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

TEST_CASE("texture::access enum values", "[texture]")
{
  using tex_access = ctn::texture::access;
  CHECK(tex_access::no_lock == SDL_TEXTUREACCESS_STATIC);
  CHECK(tex_access::streaming == SDL_TEXTUREACCESS_STREAMING);
  CHECK(tex_access::target == SDL_TEXTUREACCESS_TARGET);

  CHECK(SDL_TEXTUREACCESS_STATIC == tex_access::no_lock);
  CHECK(SDL_TEXTUREACCESS_STREAMING == tex_access::streaming);
  CHECK(SDL_TEXTUREACCESS_TARGET == tex_access::target);

  CHECK(tex_access::no_lock != SDL_TEXTUREACCESS_STREAMING);
  CHECK(SDL_TEXTUREACCESS_STREAMING != tex_access::no_lock);
}

TEST_CASE("texture::scale_mode enum values", "[texture]")
{
  using tex_scale = ctn::texture::scale_mode;
  CHECK(tex_scale::linear == SDL_ScaleModeLinear);
  CHECK(tex_scale::nearest == SDL_ScaleModeNearest);
  CHECK(tex_scale::best == SDL_ScaleModeBest);

  CHECK(SDL_ScaleModeLinear == tex_scale::linear);
  CHECK(SDL_ScaleModeNearest == tex_scale::nearest);
  CHECK(SDL_ScaleModeBest == tex_scale::best);

  CHECK(tex_scale::linear != SDL_ScaleModeNearest);
  CHECK(SDL_ScaleModeBest != tex_scale::nearest);
}

TEST_CASE("texture(SDL_Texture*)", "[texture]")
{
  CHECK_THROWS_AS(ctn::texture(nullptr), ctn::centurion_exception);

  test([](ctn::renderer& renderer) {
    SDL_Texture* sdlTexture = IMG_LoadTexture(renderer.get(), pandaPath);
    CHECK_NOTHROW(ctn::texture(sdlTexture));
  });
}

TEST_CASE("texture(Renderer&, char*)", "[texture]")
{
  test([](ctn::renderer& renderer) {
    CHECK_THROWS_AS(ctn::texture(renderer, nullptr), ctn::centurion_exception);
    CHECK_THROWS_AS(ctn::texture(renderer, "badpath"),
                    ctn::centurion_exception);

    ctn::texture texture{renderer, pandaPath};
    CHECK(texture.width() == pandaWidth);
    CHECK(texture.height() == pandaHeight);
  });
}

TEST_CASE("texture(Renderer&, Surface&", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::surface surface{pandaPath};
    CHECK_NOTHROW(ctn::texture{renderer, surface});
  });
}

TEST_CASE("texture(Renderer&, PixelFormat, Access, int, int)", "[texture]")
{
  test([](ctn::renderer& renderer) {
    const auto pixelFormat = ctn::pixel_format::rgba32;
    const auto access = ctn::texture::access::no_lock;
    const auto width = 145;
    const auto height = 85;

    ctn::texture texture{renderer, pixelFormat, access, {width, height}};

    CHECK(pixelFormat == texture.format());
    CHECK(access == texture.get_access());
    CHECK(width == texture.width());
    CHECK(height == texture.height());
  });
}

TEST_CASE("texture(texture&&)", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
    ctn::texture other = std::move(texture);

    CHECK(!texture.get());
    CHECK(other.get());
  });
}

TEST_CASE("texture::operator=(texture&&)", "[texture]")
{
  SECTION("Self-assignment")
  {
    test([](ctn::renderer& renderer) {
      ctn::texture texture{renderer, pandaPath};

      texture = std::move(texture);
      CHECK(texture.get());
    });
  }

  SECTION("Normal usage")
  {
    test([](ctn::renderer& renderer) {
      ctn::texture texture{renderer, pandaPath};
      ctn::texture other{renderer, pandaPath};

      other = std::move(texture);

      CHECK(!texture.get());
      CHECK(other.get());
    });
  }
}

TEST_CASE("texture::unique", "[texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    const ctn::surface surface{pandaPath};

    CHECK_THROWS_AS(ctn::texture::unique(nullptr), ctn::centurion_exception);

    CHECK(ctn::texture::unique(renderer, pandaPath));
    CHECK(ctn::texture::unique(renderer, surface));
    CHECK(ctn::texture::unique(renderer,
                               window.get_pixel_format(),
                               ctn::texture::access::no_lock,
                               {100, 100}));
  });
}

TEST_CASE("texture:::shared", "[texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    const ctn::surface surface{pandaPath};

    CHECK_THROWS_AS(ctn::texture::shared(nullptr), ctn::centurion_exception);

    CHECK(ctn::texture::shared(renderer, pandaPath));
    CHECK(ctn::texture::shared(renderer, surface));
    CHECK(ctn::texture::shared(renderer,
                               window.get_pixel_format(),
                               ctn::texture::access::no_lock,
                               {100, 100}));
  });
}

TEST_CASE("texture::streaming", "[texture]")
{
  test([](ctn::renderer& renderer) {
    const auto pixelFormat = ctn::pixel_format::rgba8888;
    auto texture = ctn::texture::streaming(renderer, pandaPath, pixelFormat);

    CHECK(texture->format() == pixelFormat);

    CHECK_THROWS_AS(
        ctn::texture::streaming(renderer, "", ctn::pixel_format::yuy2),
        ctn::centurion_exception);
  });
}

TEST_CASE("texture::set_pixel", "[texture]")
{
  test([](ctn::renderer& renderer) {
    const auto texture = ctn::texture::streaming(
        renderer, pandaPath, ctn::pixel_format::rgba8888);

    const auto [width, height] = texture->size();

    CHECK_NOTHROW(texture->set_pixel({-1, -1}, ctn::black));
    CHECK_NOTHROW(texture->set_pixel({-1, 0}, ctn::black));
    CHECK_NOTHROW(texture->set_pixel({0, -1}, ctn::black));
    CHECK_NOTHROW(texture->set_pixel({width, 0}, ctn::black));
    CHECK_NOTHROW(texture->set_pixel({0, height}, ctn::black));
    CHECK_NOTHROW(texture->set_pixel({width, height}, ctn::black));

    CHECK_NOTHROW(texture->set_pixel({45, 23}, ctn::orange));
  });
}

TEST_CASE("texture::set_blend_mode", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    const auto mode = ctn::blend_mode::blend;
    texture.set_blend_mode(mode);

    CHECK(mode == texture.get_blend_mode());
  });
}

TEST_CASE("texture::set_alpha", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    const auto alpha = 0x3A;
    texture.set_alpha(alpha);

    CHECK(alpha == texture.alpha());
  });
}

TEST_CASE("texture::set_color_mod", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    const auto color = ctn::misty_rose;
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
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    texture.set_scale_mode(ctn::texture::scale_mode::nearest);
    CHECK(texture.get_scale_mode() == ctn::texture::scale_mode::nearest);

    texture.set_scale_mode(ctn::texture::scale_mode::linear);
    CHECK(texture.get_scale_mode() == ctn::texture::scale_mode::linear);

    texture.set_scale_mode(ctn::texture::scale_mode::best);
    CHECK(texture.get_scale_mode() == ctn::texture::scale_mode::best);
  });
}

TEST_CASE("texture::is_static", "[texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    ctn::texture texture{renderer,
                         window.get_pixel_format(),
                         ctn::texture::access::no_lock,
                         {10, 10}};
    CHECK(texture.is_static());
  });
}

TEST_CASE("texture::is_streaming", "[texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    ctn::texture texture{renderer,
                         window.get_pixel_format(),
                         ctn::texture::access::streaming,
                         {10, 10}};
    CHECK(texture.is_streaming());
  });
}

TEST_CASE("texture::is_target", "[texture]")
{
  test_with_window([](ctn::renderer& renderer, const ctn::window& window) {
    ctn::texture texture{renderer,
                         window.get_pixel_format(),
                         ctn::texture::access::target,
                         {10, 10}};
    CHECK(texture.is_target());
  });
}

TEST_CASE("texture::to_string", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
    ctn::log::info(ctn::log::category::test, "%s", texture.to_string().c_str());
  });
}

TEST_CASE("texture::get", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
    CHECK(texture.get());
  });
}

TEST_CASE("texture::format", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    ctn::u32 format = 0;
    SDL_QueryTexture(sdlTexture, &format, nullptr, nullptr, nullptr);

    CHECK(texture.format() == static_cast<ctn::pixel_format>(format));
  });
}

TEST_CASE("texture::get_access", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
    SDL_Texture* sdlTexture = texture.get();

    int access = 0;
    SDL_QueryTexture(sdlTexture, nullptr, &access, nullptr, nullptr);

    CHECK(texture.get_access() == static_cast<ctn::texture::access>(access));
  });
}

TEST_CASE("texture::color_mod", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    CHECK(texture.color_mod() == ctn::white);
  });
}

TEST_CASE("texture::get_scale_mode", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};

    SDL_ScaleMode mode;
    SDL_GetTextureScaleMode(texture.get(), &mode);
    CHECK(static_cast<SDL_ScaleMode>(texture.get_scale_mode()) == mode);
  });
}

TEST_CASE("texture::width", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture(renderer, pandaPath);
    SDL_Texture* sdlTexture = texture.get();

    CHECK(texture.width() == pandaWidth);

    int width = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &width, nullptr);
    CHECK(texture.width() == width);
  });
}

TEST_CASE("texture::height", "[texture]")
{
  test([](ctn::renderer& renderer) {
    ctn::texture texture{renderer, pandaPath};
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
    test([](ctn::renderer& renderer) {
      const ctn::texture texture{renderer, pandaPath};
      CHECK(texture.operator const SDL_Texture*());
    });
  }

  SECTION("Non-const")
  {
    test([](ctn::renderer& renderer) {
      ctn::texture texture{renderer, pandaPath};
      CHECK(texture.operator SDL_Texture*());
    });
  }
}