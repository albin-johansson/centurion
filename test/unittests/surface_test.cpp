#include "surface.h"

#include <SDL_image.h>

#include <catch.hpp>
#include <utility>

#include "centurion_exception.h"
#include "colors.h"
#include "renderer.h"
#include "texture.h"
#include "window.h"

using namespace centurion;
using namespace centurion::video;

static constexpr auto* path = "resources/ctn_icon_1.png";

TEST_CASE("Surface(const char*)", "[Surface]")
{
  SECTION("Null path")
  {
    const char* c = nullptr;
    CHECK_THROWS_AS(Surface{c}, CenturionException);
  }

  SECTION("Bad path")
  {
    CHECK_THROWS_AS(Surface{""}, CenturionException);
  }

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
  const Surface fst{path};
  const Surface copy{fst};
  CHECK(fst.get_internal() != copy.get_internal());
}

TEST_CASE("Surface(Surface&&)", "[Surface]")
{
  Surface fst{path};
  Surface copy{std::move(fst)};
  CHECK(!fst.get_internal());
}

TEST_CASE("Surface::operator=(const Surface&)", "[Surface]")
{
  Surface fst{path};
  Surface copy{path};

  copy = fst;

  CHECK(fst.get_internal() != copy.get_internal());
}

TEST_CASE("Surface::operator=(Surface&&)", "[Surface]")
{
  Surface fst{path};
  Surface copy{path};

  copy = std::move(fst);

  CHECK(!fst.get_internal());
}

TEST_CASE("Surface::set_alpha", "[Surface]")
{
  Surface surface{path};

  const auto alpha = 0xCF;
  surface.set_alpha(alpha);

  CHECK(alpha == surface.get_alpha());
}

TEST_CASE("Surface::set_color_mod", "[Surface]")
{
  Surface surface{path};

  const auto& color = hot_pink;
  surface.set_color_mod(color);

  CHECK(color == surface.get_color_mod());
}

TEST_CASE("Surface::set_blend_mode", "[Surface]")
{
  Surface surface{path};

  const auto mode = BlendMode::Mod;
  surface.set_blend_mode(mode);

  CHECK(mode == surface.get_blend_mode());
}

TEST_CASE("Surface::get_width", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.get_width() == 32);
}

TEST_CASE("Surface::get_height", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.get_height() == 32);
}

TEST_CASE("Surface::get_pitch", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.get_pitch() == 128);
}

TEST_CASE("Surface::to_texture", "[Surface]")
{
  const Surface surface{path};
  const Window window;
  const Renderer renderer{window};

  CHECK(surface.to_texture(renderer));
}

TEST_CASE("Surface::get_internal", "[Surface]")
{
  const Surface surface{path};
  CHECK(surface.get_internal());
}
