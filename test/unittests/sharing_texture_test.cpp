#include "sharing_texture.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("sharing_texture pointer ctor", "[sharing_texture]")
{
  CHECK_THROWS_AS(cen::sharing_texture{nullptr}, cen::exception);
}

TEST_CASE("sharing_texture implicit sharing semantics", "[sharing_texture]")
{
  cen::window window;
  cen::renderer renderer{window};

  cen::sharing_texture fst{renderer, "resources/panda.png"};
  cen::sharing_texture snd{fst};

  CHECK(fst.get() == snd.get());

  const auto alpha = 0x34;
  fst.set_alpha(alpha);

  CHECK(fst.alpha() == alpha);
  CHECK(snd.alpha() == alpha);
}

TEST_CASE("sharing_texture from texture", "[sharing_texture]")
{
  cen::window window;
  cen::renderer renderer{window};

  cen::texture fst{renderer, "resources/panda.png"};
  cen::sharing_texture snd{std::move(fst)};

  CHECK(!fst.get());
}