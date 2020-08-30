#include "ram.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("amount_mb", "[ram]")
{
  CHECK(cen::ram::amount_mb() == SDL_GetSystemRAM());
}

TEST_CASE("amount_gb", "[ram]")
{
  CHECK(cen::ram::amount_gb() == SDL_GetSystemRAM() / 1'000);
}