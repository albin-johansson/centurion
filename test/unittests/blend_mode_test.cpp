#include "blend_mode.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("blend_mode enum values", "[blend_mode]")
{
  CHECK(ctn::blend_mode::none == SDL_BLENDMODE_NONE);
  CHECK(ctn::blend_mode::blend == SDL_BLENDMODE_BLEND);
  CHECK(ctn::blend_mode::add == SDL_BLENDMODE_ADD);
  CHECK(ctn::blend_mode::mod == SDL_BLENDMODE_MOD);
  CHECK(ctn::blend_mode::mul == SDL_BLENDMODE_MUL);
  CHECK(ctn::blend_mode::invalid == SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_NONE == ctn::blend_mode::none);
  CHECK(SDL_BLENDMODE_BLEND == ctn::blend_mode::blend);
  CHECK(SDL_BLENDMODE_ADD == ctn::blend_mode::add);
  CHECK(SDL_BLENDMODE_MOD == ctn::blend_mode::mod);
  CHECK(SDL_BLENDMODE_MUL == ctn::blend_mode::mul);
  CHECK(SDL_BLENDMODE_INVALID == ctn::blend_mode::invalid);
}

TEST_CASE("blend_mode operator!=", "[blend_mode]")
{
  CHECK(ctn::blend_mode::none != SDL_BLENDMODE_MOD);
  CHECK(ctn::blend_mode::blend != SDL_BLENDMODE_INVALID);

  CHECK(SDL_BLENDMODE_ADD != ctn::blend_mode::blend);
  CHECK(SDL_BLENDMODE_MOD != ctn::blend_mode::add);
}