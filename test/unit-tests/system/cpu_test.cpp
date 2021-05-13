#include "system/cpu.hpp"

#include <gtest/gtest.h>

TEST(CPU, CacheLineSize)
{
  ASSERT_EQ(SDL_GetCPUCacheLineSize(), cen::cpu::cache_line_size());
}

TEST(CPU, Cores)
{
  ASSERT_EQ(SDL_GetCPUCount(), cen::cpu::cores());
}

TEST(CPU, IsLittleEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_LIL_ENDIAN, cen::cpu::is_little_endian());
}

TEST(CPU, IsBigEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_BIG_ENDIAN, cen::cpu::is_big_endian());
}

TEST(CPU, HasRDTSC)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasRDTSC()), cen::cpu::has_rdtsc());
}

TEST(CPU, HasAltiVec)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasAltiVec()), cen::cpu::has_altivec());
}

TEST(CPU, HasMMX)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasMMX()), cen::cpu::has_mmx());
}

TEST(CPU, Has3DNow)
{
  ASSERT_EQ(static_cast<bool>(SDL_Has3DNow()), cen::cpu::has_3dnow());
}

TEST(CPU, HasSSE)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasSSE()), cen::cpu::has_sse());
}

TEST(CPU, HasSSE2)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasSSE2()), cen::cpu::has_sse2());
}

TEST(CPU, HasSSE3)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasSSE3()), cen::cpu::has_sse3());
}

TEST(CPU, HasSSE41)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasSSE41()), cen::cpu::has_sse41());
}

TEST(CPU, HasSSE42)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasSSE42()), cen::cpu::has_sse42());
}

TEST(CPU, HasAVX)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasAVX()), cen::cpu::has_avx());
}

TEST(CPU, HasAVX2)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasAVX2()), cen::cpu::has_avx2());
}

TEST(CPU, HasAVX512f)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasAVX512F()), cen::cpu::has_avx512f());
}

TEST(CPU, HasNEON)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasNEON()), cen::cpu::has_neon());
}

TEST(CPU, SIMDAlignment)
{
  ASSERT_EQ(SDL_SIMDGetAlignment(), cen::cpu::simd_alignment());
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(CPU, HasARMSIMD)
{
  ASSERT_EQ(static_cast<bool>(SDL_HasARMSIMD()), cen::cpu::has_arm_simd());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
