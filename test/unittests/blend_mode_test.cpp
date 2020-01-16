#include "catch.hpp"
#include "blend_mode.h"

using namespace centurion;

TEST_CASE("BlendMode enum values", "[BlendMode]") {
  CHECK(static_cast<SDL_BlendMode>(BlendMode::None) == SDL_BLENDMODE_NONE);
  CHECK(static_cast<SDL_BlendMode>(BlendMode::Blend) == SDL_BLENDMODE_BLEND);
  CHECK(static_cast<SDL_BlendMode>(BlendMode::Add) == SDL_BLENDMODE_ADD);
  CHECK(static_cast<SDL_BlendMode>(BlendMode::Mod) == SDL_BLENDMODE_MOD);
  CHECK(static_cast<SDL_BlendMode>(BlendMode::Invalid) == SDL_BLENDMODE_INVALID);
}
