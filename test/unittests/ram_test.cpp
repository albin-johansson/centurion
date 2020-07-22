#include "ram.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("amount_mb", "[ram]")
{
  CHECK(ctn::ram::amount_mb() == SDL_GetSystemRAM());
}

TEST_CASE("amount_gb", "[ram]")
{
  CHECK(ctn::ram::amount_gb() == SDL_GetSystemRAM() / 1'000);
}