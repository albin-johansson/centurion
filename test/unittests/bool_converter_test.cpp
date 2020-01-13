#include "catch.hpp"
#include "bool_converter.h"

using namespace centurion;

TEST_CASE("BoolConverter::convert", "[BoolConverter]") {
  CHECK(BoolConverter::convert(true) == SDL_TRUE);
  CHECK(BoolConverter::convert(false) == SDL_FALSE);
}