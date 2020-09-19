#include "cpu.hpp"

#include <catch.hpp>

TEST_CASE("cpu::cache_line_size", "[cpu]")
{
  CHECK(cen::cpu::cache_line_size() == SDL_GetCPUCacheLineSize());
}

TEST_CASE("cpu::cores", "[cpu]")
{
  CHECK(cen::cpu::cores() == SDL_GetCPUCount());
}

TEST_CASE("cpu::is_little_endian", "[cpu]")
{
  CHECK(cen::cpu::is_little_endian() == (SDL_BYTEORDER == SDL_LIL_ENDIAN));
}

TEST_CASE("cpu::is_big_endian", "[cpu]")
{
  CHECK(cen::cpu::is_big_endian() == (SDL_BYTEORDER == SDL_BIG_ENDIAN));
}

TEST_CASE("cpu::has_rdtsc", "[cpu]")
{
  CHECK(cen::cpu::has_rdtsc() == static_cast<bool>(SDL_HasRDTSC()));
}

TEST_CASE("cpu::has_altivec", "[cpu]")
{
  CHECK(cen::cpu::has_altivec() == static_cast<bool>(SDL_HasAltiVec()));
}

TEST_CASE("cpu::has_mmx", "[cpu]")
{
  CHECK(cen::cpu::has_mmx() == static_cast<bool>(SDL_HasMMX()));
}

TEST_CASE("cpu::has_3dnow", "[cpu]")
{
  CHECK(cen::cpu::has_3dnow() == static_cast<bool>(SDL_Has3DNow()));
}

TEST_CASE("cpu::has_sse", "[cpu]")
{
  CHECK(cen::cpu::has_sse() == static_cast<bool>(SDL_HasSSE()));
}

TEST_CASE("cpu::has_sse2", "[cpu]")
{
  CHECK(cen::cpu::has_sse2() == static_cast<bool>(SDL_HasSSE2()));
}

TEST_CASE("cpu::has_sse3", "[cpu]")
{
  CHECK(cen::cpu::has_sse3() == static_cast<bool>(SDL_HasSSE3()));
}

TEST_CASE("cpu::has_sse41", "[cpu]")
{
  CHECK(cen::cpu::has_sse41() == static_cast<bool>(SDL_HasSSE41()));
}

TEST_CASE("cpu::has_sse42", "[cpu]")
{
  CHECK(cen::cpu::has_sse42() == static_cast<bool>(SDL_HasSSE42()));
}

TEST_CASE("cpu::has_avx", "[cpu]")
{
  CHECK(cen::cpu::has_avx() == static_cast<bool>(SDL_HasAVX()));
}

TEST_CASE("cpu::has_avx2", "[cpu]")
{
  CHECK(cen::cpu::has_avx2() == static_cast<bool>(SDL_HasAVX2()));
}

TEST_CASE("cpu::has_avx512f", "[cpu]")
{
  CHECK(cen::cpu::has_avx512f() == static_cast<bool>(SDL_HasAVX512F()));
}

TEST_CASE("cpu::has_neon", "[cpu]")
{
  CHECK(cen::cpu::has_neon() == static_cast<bool>(SDL_HasNEON()));
}

TEST_CASE("cpu::has_arm_simd", "[cpu]")
{
  CHECK(cen::cpu::has_arm_simd() == static_cast<bool>(SDL_HasARMSIMD()));
}

TEST_CASE("cpu::simd_alignment", "[cpu]")
{
  CHECK(cen::cpu::simd_alignment() == SDL_SIMDGetAlignment());
}