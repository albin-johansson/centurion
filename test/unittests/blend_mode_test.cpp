#include "blend_mode.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("blend_mode enum values", "[blend_mode]")
{
  CHECK(cen::blend_mode::none == SDL_BLENDMODE_NONE);
  CHECK(cen::blend_mode::blend == SDL_BLENDMODE_BLEND);
  CHECK(cen::blend_mode::add == SDL_BLENDMODE_ADD);
  CHECK(cen::blend_mode::mod == SDL_BLENDMODE_MOD);
  CHECK(cen::blend_mode::mul == SDL_BLENDMODE_MUL);
  CHECK(cen::blend_mode::invalid == SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_NONE == cen::blend_mode::none);
  CHECK(SDL_BLENDMODE_BLEND == cen::blend_mode::blend);
  CHECK(SDL_BLENDMODE_ADD == cen::blend_mode::add);
  CHECK(SDL_BLENDMODE_MOD == cen::blend_mode::mod);
  CHECK(SDL_BLENDMODE_MUL == cen::blend_mode::mul);
  CHECK(SDL_BLENDMODE_INVALID == cen::blend_mode::invalid);
}

TEST_CASE("blend_mode operator!=", "[blend_mode]")
{
  CHECK(cen::blend_mode::none != SDL_BLENDMODE_MOD);
  CHECK(cen::blend_mode::blend != SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_ADD != cen::blend_mode::blend);
  CHECK(SDL_BLENDMODE_MOD != cen::blend_mode::add);
}