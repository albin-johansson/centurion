#include "catch.hpp"
#include "system.h"

using namespace centurion;

TEST_CASE("CPU::get_cache_line_size", "[CPU]") {
  const auto size = CPU::get_cache_line_size();
  const auto sdlSize = SDL_GetCPUCacheLineSize();
  CHECK(size == sdlSize);
}

TEST_CASE("CPU::get_cores", "[CPU]") {
  const auto size = CPU::get_cores();
  const auto sdlSize = SDL_GetCPUCount();
  CHECK(size == sdlSize);
}

TEST_CASE("CPU::is_little_endian", "[CPU]") {
  CHECK(CPU::is_little_endian() == (SDL_BYTEORDER == SDL_LIL_ENDIAN));
}

TEST_CASE("CPU::is_big_endian", "[CPU]") {
  CHECK(CPU::is_big_endian() == (SDL_BYTEORDER == SDL_BIG_ENDIAN));
}