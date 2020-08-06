#include "sharing_texture.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("sharing_texture::", "[sharing_texture]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  // todo enable creating sharing_texture from rvalue texture

  ctn::texture fst{renderer, "resources/panda.png"};
  ctn::sharing_texture snd{std::move(fst)};

  CHECK(!fst.get());

//  CHECK(fst.get() == snd.get());

//  const auto alpha = 0x34;
//  fst.set_alpha(alpha);
//
//  CHECK(fst.alpha() == alpha);
//  CHECK(snd.alpha() == alpha);
}