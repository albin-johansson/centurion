#include <SDL.h>

#include <catch.hpp>

#include "centurion_utils.h"

#include <centurion.h>

using namespace centurion;

TEST_CASE("Convert C++ bool to SDL bool", "[utilities]") {
  CHECK(convert_bool(true) == SDL_TRUE);
  CHECK(convert_bool(false) == SDL_FALSE);
}