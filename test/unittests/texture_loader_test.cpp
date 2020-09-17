#include "texture_loader.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "renderer.hpp"
#include "video.hpp"
#include "window.hpp"

TEST_CASE("texture_loader::create", "[texture_loader]")
{
  cen::window window;
  cen::renderer renderer{window};

  cen::texture_loader loader{renderer};

  auto texture = loader.create("resources/panda.png");
  CHECK(texture.get());
}

TEST_CASE("texture_loader from renderer_handle", "[texture_loader]")
{
  cen::window window;
  cen::renderer renderer{window};
  cen::renderer_handle handle{renderer};

  cen::texture_loader loader{handle};

  auto texture = loader.create("resources/panda.png");
  CHECK(texture.get());
}