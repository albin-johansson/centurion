#include "cpu.h"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("CPU::cache_line_size", "[CPU]")
{
  CHECK(CPU::cache_line_size() == SDL_GetCPUCacheLineSize());
}

TEST_CASE("CPU::cores", "[CPU]")
{
  CHECK(CPU::cores() == SDL_GetCPUCount());
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