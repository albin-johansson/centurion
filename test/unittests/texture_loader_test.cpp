#include "texture_loader.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "graphics.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("texture_loader::unique", "[texture_loader]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::texture_loader loader{renderer};

  auto texture = loader.unique("resources/panda.png");
  CHECK(texture.get());
}

TEST_CASE("texture_loader::shared", "[texture_loader]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::texture_loader loader{renderer};

  auto texture = loader.shared("resources/panda.png");
  CHECK(texture.get());
}

TEST_CASE("texture_loader::create", "[texture_loader]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::texture_loader loader{renderer};

  auto texture = loader.create("resources/panda.png");
  CHECK(texture.get());
}
