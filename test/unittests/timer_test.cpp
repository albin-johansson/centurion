#include "timer.h"

#include <SDL.h>

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Timer::sleep", "[Timer]")
{
  CHECK_NOTHROW(Timer::sleep(10));
  CHECK_NOTHROW(Timer::sleep(0));
}

TEST_CASE("Timer::high_res", "[Timer]")
{
  CHECK_NOTHROW(Timer::high_res());
}

TEST_CASE("Timer::high_res_freq", "[Timer]")
{
  CHECK(Timer::high_res_freq() == SDL_GetPerformanceFrequency());
}

TEST_CASE("Timer::millis", "[Timer]")
{
  CHECK_NOTHROW(Timer::millis());
}