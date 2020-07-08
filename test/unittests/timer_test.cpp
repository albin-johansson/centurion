#include "timer.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Timer::delay", "[Timer]")
{
  CHECK_NOTHROW(Timer::delay(milliseconds<u32>(10)));
  CHECK_NOTHROW(Timer::delay(milliseconds<u32>(0)));
}

TEST_CASE("Timer::high_res", "[Timer]")
{
  CHECK_NOTHROW(Timer::now());
}

TEST_CASE("Timer::high_res_freq", "[Timer]")
{
  CHECK(Timer::high_res_freq() == SDL_GetPerformanceFrequency());
}

TEST_CASE("Timer::now", "[Timer]")
{
  CHECK_NOTHROW(Timer::now_ms());
}