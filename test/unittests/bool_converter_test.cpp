#include <SDL.h>
#include <centurion.h>

#include <catch.hpp>

#include "centurion_utils.h"

using namespace centurion;

TEST_CASE("Convert C++ bool to SDL bool", "[utilities]")
{
  CHECK(detail::convert_bool(true) == SDL_TRUE);
  CHECK(detail::convert_bool(false) == SDL_FALSE);
}