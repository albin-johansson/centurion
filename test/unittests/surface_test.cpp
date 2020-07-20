#include "surface.hpp"

#include <SDL_image.h>

#include <catch.hpp>
#include <utility>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "colors.hpp"
#include "renderer.hpp"
#include "window.hpp"

static constexpr ctn::czstring path = "resources/panda.png";

TEST_CASE("Surface(CZString)", "[surface]")
{
  SECTION("Null path")
  {
    ctn::czstring c = nullptr;
    CHECK_THROWS_AS(ctn::surface{c}, ctn::centurion_exception);
  }

  SECTION("Bad path")
  {
    CHECK_THROWS_AS(ctn::surface{""}, ctn::centurion_exception);
  }

  CHECK_NOTHROW(ctn::surface{path});
}

TEST_CASE("Surface(SDL_Surface*)", "[surface]")
{
  SECTION("Null surface")
  {
    SDL_Surface* s = nullptr;
    CHECK_THROWS_AS(ctn::surface{s}, ctn::centurion_exception);
  }

  SDL_Surface* surface = IMG_Load(path);
  CHECK_NOTHROW(ctn::surface{surface});
}

TEST_CASE("Surface(const Surface&)", "[surface]")
{
  const ctn::surface surface{path};
  const ctn::surface copy{surface};

  CHECK(surface.get() != copy.get());
  CHECK(surface.get());
  CHECK(copy.get());
}

TEST_CASE("Surface(Surface&&)", "[surface]")
{
  ctn::surface surface{path};
  ctn::surface other{std::move(surface)};

  CHECK(!surface.get());
  CHECK(other.get());
}

TEST_CASE("Surface::operator=(const Surface&)", "[surface]")
{
  ctn::surface fst{path};
  ctn::surface copy{path};

  copy = fst;

  CHECK(fst.get() != copy.get());
}

TEST_CASE("Surface::operator=(Surface&&)", "[surface]")
{
  SECTION("Self-assignment")
  {
    ctn::surface surface{path};

    surface = std::move(surface);
    CHECK(surface.get());
  }

  SECTION("Normal usage")
  {
    ctn::surface surface{path};
    ctn::surface other{path};

    other = std::move(surface);

    CHECK(!surface.get());
    CHECK(other.get());
  }
}

TEST_CASE("Surface::set_pixel", "[surface]")
{
  ctn::surface surface{path};

  CHECK_NOTHROW(surface.set_pixel({-1, 0}, ctn::colors::red));
  CHECK_NOTHROW(surface.set_pixel({0, -1}, ctn::colors::red));
  CHECK_NOTHROW(surface.set_pixel({surface.width(), 0}, ctn::colors::red));
  CHECK_NOTHROW(surface.set_pixel({0, surface.height()}, ctn::colors::red));

  CHECK_NOTHROW(surface.set_pixel({43, 12}, ctn::colors::orange));
}

TEST_CASE("Surface::set_alpha", "[surface]")
{
  ctn::surface surface{path};

  const auto alpha = 0xCF;
  surface.set_alpha(alpha);

  CHECK(alpha == surface.alpha());
}

TEST_CASE("Surface::set_color_mod", "[surface]")
{
  ctn::surface surface{path};

  const auto& color = ctn::colors::hot_pink;
  surface.set_color_mod(color);

  CHECK(color == surface.color_mod());
}

TEST_CASE("Surface::set_blend_mode", "[surface]")
{
  ctn::surface surface{path};

  const auto mode = ctn::blend_mode::mod;
  surface.set_blend_mode(mode);

  CHECK(mode == surface.get_blend_mode());
}

TEST_CASE("Surface::width", "[surface]")
{
  const ctn::surface surface{path};
  CHECK(surface.width() == 200);
}

TEST_CASE("Surface::height", "[surface]")
{
  const ctn::surface surface{path};
  CHECK(surface.height() == 150);
}

TEST_CASE("Surface::pitch", "[surface]")
{
  const ctn::surface surface{path};
  CHECK(surface.pitch() == (4 * surface.width()));
}

TEST_CASE("Surface::clip", "[surface]")
{
  const ctn::rect_i rect{{48, 29}, {34, 89}};

  SECTION("Non-const")
  {
    ctn::surface surface{path};
    surface.get()->clip_rect = static_cast<SDL_Rect>(rect);
    CHECK(surface.clip() == rect);
  }

  SECTION("Const")
  {
    const ctn::surface surface{path};
    surface.get()->clip_rect = static_cast<SDL_Rect>(rect);
    CHECK(surface.clip() == rect);
  }
}

TEST_CASE("Surface::pixels", "[surface]")
{
  SECTION("Const")
  {
    const ctn::surface surface{path};
    CHECK(surface.pixels());
  }
  SECTION("Non-const")
  {
    ctn::surface surface{path};
    CHECK(surface.pixels());
  }
}

TEST_CASE("Surface::to_texture", "[surface]")
{
  const ctn::surface surface{path};
  const ctn::window window;
  const ctn::renderer renderer{window};

  CHECK(surface.to_texture(renderer).get());
}

TEST_CASE("Surface::convert", "[surface]")
{
  ctn::surface original{path};
  original.set_blend_mode(ctn::blend_mode::blend);
  original.set_alpha(0xAE);
  original.set_color_mod(ctn::colors::red);

  const auto pixelFormat = ctn::pixel_format::rgba8888;
  ctn::surface converted = original.convert(pixelFormat);

  CHECK(converted.get_blend_mode() == original.get_blend_mode());
  CHECK(converted.alpha() == original.alpha());
  CHECK(converted.color_mod() == original.color_mod());
}

TEST_CASE("Surface::get", "[surface]")
{
  ctn::surface surface{path};
  CHECK(surface.get());
}

TEST_CASE("Surface to SDL_Surface*", "[surface]")
{
  SECTION("Const")
  {
    const ctn::surface surface{path};
    CHECK(surface.operator const SDL_Surface*());
  }

  SECTION("Non-const")
  {
    ctn::surface surface{path};
    CHECK(surface.operator SDL_Surface*());
  }
}