#include "catch.hpp"
#include "system.h"

using namespace centurion::system;

TEST_CASE("RAM::get_size_mb", "[RAM]")
{
  CHECK(RAM::get_size_mb() == SDL_GetSystemRAM());
}

TEST_CASE("RAM::get_size_gb", "[RAM]")
{
  CHECK(RAM::get_size_gb() == SDL_GetSystemRAM() / 1'000);
}