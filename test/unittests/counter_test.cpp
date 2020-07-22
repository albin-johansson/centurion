#include "counter.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("counter::high_res_freq", "[counter]")
{
  CHECK(ctn::counter::high_res_freq() == SDL_GetPerformanceFrequency());
}

TEST_CASE("counter::now", "[counter]")
{
  CHECK_NOTHROW(ctn::counter::now());
}

TEST_CASE("counter::now_sec", "[counter]")
{
  CHECK_NOTHROW(ctn::counter::now_sec<double>());
}

TEST_CASE("counter::ticks", "[counter]")
{
  CHECK_NOTHROW(ctn::counter::ticks());
}