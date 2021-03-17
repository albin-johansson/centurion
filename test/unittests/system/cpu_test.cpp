#include "system/cpu.hpp"

#include <gtest/gtest.h>

TEST(CPU, CacheLineSize)
{
  EXPECT_EQ(SDL_GetCPUCacheLineSize(), cen::cpu::cache_line_size());
}

TEST(CPU, Cores)
{
  EXPECT_EQ(SDL_GetCPUCount(), cen::cpu::cores());
}

TEST(CPU, IsLittleEndian)
{
  EXPECT_EQ(SDL_BYTEORDER == SDL_LIL_ENDIAN, cen::cpu::is_little_endian());
}

TEST(CPU, IsBigEndian)
{
  EXPECT_EQ(SDL_BYTEORDER == SDL_BIG_ENDIAN, cen::cpu::is_big_endian());
}

TEST(CPU, HasRDTSC)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasRDTSC()), cen::cpu::has_rdtsc());
}

TEST(CPU, HasAltiVec)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasAltiVec()), cen::cpu::has_altivec());
}

TEST(CPU, HasMMX)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasMMX()), cen::cpu::has_mmx());
}

TEST(CPU, Has3DNow)
{
  EXPECT_EQ(static_cast<bool>(SDL_Has3DNow()), cen::cpu::has_3dnow());
}

TEST(CPU, HasSSE)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasSSE()), cen::cpu::has_sse());
}

TEST(CPU, HasSSE2)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasSSE2()), cen::cpu::has_sse2());
}

TEST(CPU, HasSSE3)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasSSE3()), cen::cpu::has_sse3());
}

TEST(CPU, HasSSE41)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasSSE41()), cen::cpu::has_sse41());
}

TEST(CPU, HasSSE42)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasSSE42()), cen::cpu::has_sse42());
}

TEST(CPU, HasAVX)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasAVX()), cen::cpu::has_avx());
}

TEST(CPU, HasAVX2)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasAVX2()), cen::cpu::has_avx2());
}

TEST(CPU, HasAVX512f)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasAVX512F()), cen::cpu::has_avx512f());
}

TEST(CPU, HasNEON)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasNEON()), cen::cpu::has_neon());
}

TEST(CPU, HasARMSIMD)
{
  EXPECT_EQ(static_cast<bool>(SDL_HasARMSIMD()), cen::cpu::has_arm_simd());
}

TEST(CPU, SIMDAlignment)
{
  EXPECT_EQ(SDL_SIMDGetAlignment(), cen::cpu::simd_alignment());
}
