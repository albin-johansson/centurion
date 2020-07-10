#include "ram.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("amount_mb", "[ram]")
{
  CHECK(ram::amount_mb() == SDL_GetSystemRAM());
}

TEST_CASE("amount_gb", "[ram]")
{
  CHECK(ram::amount_gb() == SDL_GetSystemRAM() / 1'000);
}