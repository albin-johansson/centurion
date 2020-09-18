#include "surface.hpp"

#include <SDL_image.h>

#include <catch.hpp>
#include <iostream>
#include <utility>

#include "cen.hpp"
#include "colors.hpp"
#include "exception.hpp"
#include "log.hpp"

static constexpr cen::czstring path = "resources/panda.png";

TEST_CASE("surface(nn_czstring)", "[surface]")
{
  SECTION("Bad path") { CHECK_THROWS_AS(cen::surface{""}, cen::exception); }

  CHECK_NOTHROW(cen::surface{path});
}

TEST_CASE("surface(owner<SDL_Surface*>)", "[surface]")
{
  CHECK_NOTHROW(cen::surface{IMG_Load(path)});
  
  SDL_Surface* bad{};
  CHECK_THROWS_AS(cen::surface{bad}, cen::exception);
}

TEST_CASE("surface(const surface&)", "[surface]")
{
  const cen::surface surface{path};
  const cen::surface copy{surface};

  CHECK(surface.get() != copy.get());
  CHECK(surface.get());
  CHECK(copy.get());
}

TEST_CASE("surface(surface&&)", "[surface]")
{
  cen::surface surface{path};
  cen::surface other{std::move(surface)};

  CHECK(!surface.get());
  CHECK(other.get());
}

TEST_CASE("surface::operator=(const surface&)", "[surface]")
{
  cen::surface fst{path};
  cen::surface copy{path};

  copy = fst;

  CHECK(fst.get() != copy.get());
}

TEST_CASE("surface::operator=(surface&&)", "[surface]")
{
  SECTION("Self-assignment")
  {
    cen::surface surface{path};

    surface = std::move(surface);
    CHECK(surface.get());
  }

  SECTION("Normal usage")
  {
    cen::surface surface{path};
    cen::surface other{path};

    other = std::move(surface);

    CHECK(!surface.get());
    CHECK(other.get());
  }
}

TEST_CASE("surface::set_pixel", "[surface]")
{
  cen::surface surface{path};

  CHECK_NOTHROW(surface.set_pixel({-1, 0}, cen::colors::red));
  CHECK_NOTHROW(surface.set_pixel({0, -1}, cen::colors::red));
  CHECK_NOTHROW(surface.set_pixel({surface.width(), 0}, cen::colors::red));
  CHECK_NOTHROW(surface.set_pixel({0, surface.height()}, cen::colors::red));

  CHECK_NOTHROW(surface.set_pixel({43, 12}, cen::colors::orange));
}

TEST_CASE("surface::set_alpha", "[surface]")
{
  cen::surface surface{path};

  const auto alpha = 0xCF;
  surface.set_alpha(alpha);

  CHECK(alpha == surface.alpha());
}

TEST_CASE("surface::set_color_mod", "[surface]")
{
  cen::surface surface{path};

  const auto& color = cen::colors::hot_pink;
  surface.set_color_mod(color);

  CHECK(color == surface.color_mod());
}

TEST_CASE("surface::set_blend_mode", "[surface]")
{
  cen::surface surface{path};

  const auto mode = cen::blend_mode::mod;
  surface.set_blend_mode(mode);

  CHECK(mode == surface.get_blend_mode());
}

TEST_CASE("surface::width", "[surface]")
{
  const cen::surface surface{path};
  CHECK(surface.width() == 200);
}

TEST_CASE("surface::height", "[surface]")
{
  const cen::surface surface{path};
  CHECK(surface.height() == 150);
}

TEST_CASE("surface::pitch", "[surface]")
{
  const cen::surface surface{path};
  CHECK(surface.pitch() == (4 * surface.width()));
}

TEST_CASE("surface::clip", "[surface]")
{
  const cen::irect rect{{48, 29}, {34, 89}};

  SECTION("Non-const")
  {
    cen::surface surface{path};
    surface.get()->clip_rect = rect.get();
    CHECK(surface.clip() == rect);
  }

  SECTION("Const")
  {
    const cen::surface surface{path};
    surface.get()->clip_rect = rect.get();
    CHECK(surface.clip() == rect);
  }
}

TEST_CASE("surface::pixels", "[surface]")
{
  SECTION("Const")
  {
    const cen::surface surface{path};
    CHECK(surface.pixels());
  }
  SECTION("Non-const")
  {
    cen::surface surface{path};
    CHECK(surface.pixels());
  }
}

TEST_CASE("surface::convert", "[surface]")
{
  cen::surface original{path};
  original.set_blend_mode(cen::blend_mode::blend);
  original.set_alpha(0xAE);
  original.set_color_mod(cen::colors::red);

  const auto pixelFormat = cen::pixel_format::rgba8888;
  cen::surface converted = original.convert(pixelFormat);

  CHECK(converted.get_blend_mode() == original.get_blend_mode());
  CHECK(converted.alpha() == original.alpha());
  CHECK(converted.color_mod() == original.color_mod());
}

TEST_CASE("surface::get", "[surface]")
{
  cen::surface surface{path};
  CHECK(surface.get());
}

TEST_CASE("surface to SDL_Surface*", "[surface]")
{
  SECTION("Const")
  {
    const cen::surface surface{path};
    CHECK(surface.operator const SDL_Surface*());
  }

  SECTION("Non-const")
  {
    cen::surface surface{path};
    CHECK(surface.operator SDL_Surface*());
  }
}

TEST_CASE("surface to_string", "[surface]")
{
  const cen::surface surface{path};
  cen::log::put(cen::to_string(surface));
}

TEST_CASE("surface stream operator", "[surface]")
{
  const cen::surface surface{path};
  std::cout << "COUT: " << surface << '\n';
}