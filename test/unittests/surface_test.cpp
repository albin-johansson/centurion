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

static constexpr auto* path = "resources/panda.png";

TEST_CASE("Surface(const char*)", "[Surface]")
{
  SECTION("Null path")
  {
    const char* c = nullptr;
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

  const auto& color = hot_pink;
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

TEST_CASE("Surface::to_texture", "[Surface]")
{
  const Surface surface{path};
  const Window window;
  const Renderer renderer{window};

  CHECK(surface.to_texture(renderer));
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