#include "blend_mode.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("BlendMode enum values", "[BlendMode]")
{
  CHECK(blend_mode::none == SDL_BLENDMODE_NONE);
  CHECK(blend_mode::blend == SDL_BLENDMODE_BLEND);
  CHECK(blend_mode::add == SDL_BLENDMODE_ADD);
  CHECK(blend_mode::mod == SDL_BLENDMODE_MOD);
  CHECK(blend_mode::mul == SDL_BLENDMODE_MUL);
  CHECK(blend_mode::invalid == SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_NONE == blend_mode::none);
  CHECK(SDL_BLENDMODE_BLEND == blend_mode::blend);
  CHECK(SDL_BLENDMODE_ADD == blend_mode::add);
  CHECK(SDL_BLENDMODE_MOD == blend_mode::mod);
  CHECK(SDL_BLENDMODE_MUL == blend_mode::mul);
  CHECK(SDL_BLENDMODE_INVALID == blend_mode::invalid);
}

TEST_CASE("BlendMode operator!=", "[BlendMode]")
{
  CHECK(blend_mode::none != SDL_BLENDMODE_MOD);
  CHECK(blend_mode::blend != SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_ADD != blend_mode::blend);
  CHECK(SDL_BLENDMODE_MOD != blend_mode::add);
}