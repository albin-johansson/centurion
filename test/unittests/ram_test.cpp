#include "ram.h"

#include <catch.hpp>

using namespace centurion::system;

TEST_CASE("RAM::size_mb", "[RAM]")
{
  CHECK(RAM::size_mb() == SDL_GetSystemRAM());
}

TEST_CASE("RAM::size_gb", "[RAM]")
{
  CHECK(RAM::size_gb() == SDL_GetSystemRAM() / 1'000);
}