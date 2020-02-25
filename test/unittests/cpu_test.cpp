#include <catch.hpp>

#include "system.h"

using namespace centurion::system;

TEST_CASE("CPU::get_cache_line_size", "[CPU]")
{
  const auto size = CPU::get_cache_line_size();
  const auto sdlSize = SDL_GetCPUCacheLineSize();
  CHECK(size == sdlSize);
}

TEST_CASE("CPU::get_cores", "[CPU]")
{
  const auto size = CPU::get_cores();
  const auto sdlSize = SDL_GetCPUCount();
  CHECK(size == sdlSize);
}

TEST_CASE("CPU::is_little_endian", "[CPU]")
{
  CHECK(CPU::is_little_endian() == (SDL_BYTEORDER == SDL_LIL_ENDIAN));
}

TEST_CASE("CPU::is_big_endian", "[CPU]")
{
  CHECK(CPU::is_big_endian() == (SDL_BYTEORDER == SDL_BIG_ENDIAN));
}

TEST_CASE("CPU::has_rdtsc", "[CPU]")
{
  CHECK(CPU::has_rdtsc() == SDL_HasRDTSC());
}

TEST_CASE("CPU::has_altivec", "[CPU]")
{
  CHECK(CPU::has_altivec() == SDL_HasAltiVec());
}

TEST_CASE("CPU::has_mmx", "[CPU]")
{
  CHECK(CPU::has_mmx() == SDL_HasMMX());
}

TEST_CASE("CPU::has_3dnow", "[CPU]")
{
  CHECK(CPU::has_3dnow() == SDL_Has3DNow());
}

TEST_CASE("CPU::has_sse", "[CPU]")
{
  CHECK(CPU::has_sse() == SDL_HasSSE());
}

TEST_CASE("CPU::has_sse2", "[CPU]")
{
  CHECK(CPU::has_sse2() == SDL_HasSSE2());
}

TEST_CASE("CPU::has_sse3", "[CPU]")
{
  CHECK(CPU::has_sse3() == SDL_HasSSE3());
}

TEST_CASE("CPU::has_sse41", "[CPU]")
{
  CHECK(CPU::has_sse41() == SDL_HasSSE41());
}

TEST_CASE("CPU::has_sse42", "[CPU]")
{
  CHECK(CPU::has_sse42() == SDL_HasSSE42());
}

TEST_CASE("CPU::has_avx", "[CPU]")
{
  CHECK(CPU::has_avx() == SDL_HasAVX());
}

TEST_CASE("CPU::has_avx2", "[CPU]")
{
  CHECK(CPU::has_avx2() == SDL_HasAVX2());
}

TEST_CASE("CPU::has_avx512f", "[CPU]")
{
  CHECK(CPU::has_avx512f() == SDL_HasAVX512F());
}

TEST_CASE("CPU::has_neon", "[CPU]")
{
  CHECK(CPU::has_neon() == SDL_HasNEON());
}