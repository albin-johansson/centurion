#include "sharing_texture.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("sharing_texture implicit sharing semantics", "[sharing_texture]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::sharing_texture fst{renderer, "resources/panda.png"};
  ctn::sharing_texture snd{fst};

  CHECK(fst.get() == snd.get());

  const auto alpha = 0x34;
  fst.set_alpha(alpha);

  CHECK(fst.alpha() == alpha);
  CHECK(snd.alpha() == alpha);
}

TEST_CASE("sharing_texture from texture", "[sharing_texture]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::texture fst{renderer, "resources/panda.png"};
  ctn::sharing_texture snd{std::move(fst)};

  CHECK(!fst.get());
}