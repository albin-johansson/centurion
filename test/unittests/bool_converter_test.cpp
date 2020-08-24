#include <catch.hpp>

#include "detail/centurion_utils.hpp"

using namespace centurion;

TEST_CASE("Convert C++ bool to SDL bool", "[utilities]")
{
  CHECK(detail::convert_bool(true) == SDL_TRUE);
  CHECK(detail::convert_bool(false) == SDL_FALSE);
}