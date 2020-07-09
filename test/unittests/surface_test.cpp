#include "surface.hpp"

#include <SDL_image.h>

#include <catch.hpp>
#include <utility>

#include "centurion_exception.hpp"
#include "colors.hpp"
#include "graphics.hpp"
#include "window.hpp"

using namespace centurion;

static constexpr czstring path = "resources/panda.png";

TEST_CASE("Surface(CZString)", "[Surface]")
{
  SECTION("Null path")
  {
    czstring c = nullptr;
    CHECK_THROWS_AS(Surface{c}, CenturionException);
  }

  SECTION("Bad path") { CHECK_THROWS_AS(Surface{""}, CenturionException); }

  CHECK_NOTHROW(Surface{path});
}

TEST_CASE("Surface(SDL_Surface*)", "[Surface]")
{
  SECTION("Null surface")
  {
    SDL_Surface* s = nullptr;
    CHECK_THROWS_AS(Surface{s}, CenturionException);
  }

  SDL_Surface* surface = IMG_Load(path);
  CHECK_NOTHROW(Surface{surface});
}

TEST_CASE("Surface(const Surface&)", "[Surface]")
{
  const Surface surface{path};
  const Surface copy{surface};

  CHECK(surface.get() != copy.get());
  CHECK(surface.get());
  CHECK(copy.get());
}

TEST_CASE("Surface(Surface&&)", "[Surface]")
{
  Surface surface{path};
  Surface other{std::move(surface)};

  CHECK(!surface.get());
  CHECK(other.get());
}

TEST_CASE("Surface::operator=(const Surface&)", "[Surface]")
{
  Surface fst{path};
  Surface copy{path};

  copy = fst;

  CHECK(fst.get() != copy.get());
}

TEST_CASE("Surface::operator=(Surface&&)", "[Surface]")
{
  SECTION("Self-assignment")
  {
    Surface surface{path};

    surface = std::move(surface);
    CHECK(surface.get());
  }

  SECTION("Normal usage")
  {
    Surface surface{path};
    Surface other{path};

    other = std::move(surface);

    CHECK(!surface.get());
    CHECK(other.get());
  }
}

TEST_CASE("Surface::set_pixel", "[Surface]")
{
  Surface surface{path};

  CHECK_NOTHROW(surface.set_pixel({-1, 0}, color::red));
  CHECK_NOTHROW(surface.set_pixel({0, -1}, color::red));
  CHECK_NOTHROW(surface.set_pixel({surface.width(), 0}, color::red));
  CHECK_NOTHROW(surface.set_pixel({0, surface.height()}, color::red));

  CHECK_NOTHROW(surface.set_pixel({43, 12}, color::orange));
}

TEST_CASE("Surface::set_alpha", "[Surface]")
{
  Surface surface{path};

  const auto alpha = 0xCF;
  surface.set_alpha(alpha);

  CHECK(alpha == surface.alpha());
}

TEST_CASE("Surface::set_color_mod", "[Surface]")
{
  Surface surface{path};

  const auto& color = color::hot_pink;
  surface.set_color_mod(color);

  CHECK(color == surface.color_mod());
}

TEST_CASE("Surface::set_blend_mode", "[Surface]")
{
  Surface surface{path};

  const auto mode = BlendMode::Mod;
  surface.set_blend_mode(mode);

  CHECK(mode == surface.blend_mode());
}

TEST_CASE("Surface::width", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.width() == 200);
}

TEST_CASE("Surface::height", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.height() == 150);
}

TEST_CASE("Surface::pitch", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.pitch() == (4 * surface.width()));
}

TEST_CASE("Surface::clip", "[Surface]")
{
  const rect_i rect{{48, 29}, {34, 89}};

  SECTION("Non-const")
  {
    Surface surface{path};
    surface.get()->clip_rect = static_cast<SDL_Rect>(rect);
    CHECK(surface.clip() == rect);
  }

  SECTION("Const")
  {
    const Surface surface{path};
    surface.get()->clip_rect = static_cast<SDL_Rect>(rect);
    CHECK(surface.clip() == rect);
  }
}

TEST_CASE("Surface::pixels", "[Surface]")
{
  SECTION("Const")
  {
    const Surface surface{path};
    CHECK(surface.pixels());
  }
  SECTION("Non-const")
  {
    Surface surface{path};
    CHECK(surface.pixels());
  }
}

TEST_CASE("Surface::to_texture", "[Surface]")
{
  // TODO replace with other API
  //  const Surface surface{path};
  //  const Window window;
  //  const Renderer renderer{window};
  //
  //  CHECK(surface.to_texture(renderer));
}

TEST_CASE("Surface::convert", "[Surface]")
{
  Surface original{path};
  original.set_blend_mode(BlendMode::Blend);
  original.set_alpha(0xAE);
  original.set_color_mod(color::red);

  const auto pixelFormat = PixelFormat::RGBA8888;
  Surface converted = original.convert(pixelFormat);

  CHECK(converted.blend_mode() == original.blend_mode());
  CHECK(converted.alpha() == original.alpha());
  CHECK(converted.color_mod() == original.color_mod());
}

TEST_CASE("Surface::get", "[Surface]")
{
  Surface surface{path};
  CHECK(surface.get());
}

TEST_CASE("Surface to SDL_Surface*", "[Surface]")
{
  SECTION("Const")
  {
    const Surface surface{path};
    CHECK(surface.operator const SDL_Surface*());
  }

  SECTION("Non-const")
  {
    Surface surface{path};
    CHECK(surface.operator SDL_Surface*());
  }
}