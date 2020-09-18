#include <catch.hpp>

#include "detail/utils.hpp"

TEST_CASE("Convert C++ bool to SDL bool", "[utilities]")
{
  CHECK(cen::detail::convert_bool(true) == SDL_TRUE);
  CHECK(cen::detail::convert_bool(false) == SDL_FALSE);
}