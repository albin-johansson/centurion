#include "centurion/endian.hpp"

#include <gtest/gtest.h>

TEST(Endian, IsLittleEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_LIL_ENDIAN, cen::is_little_endian());
}

TEST(Endian, IsBigEndian)
{
  ASSERT_EQ(SDL_BYTEORDER == SDL_BIG_ENDIAN, cen::is_big_endian());
}

TEST(Endian, SwapByteOrderU16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_Swap16(source), cen::swap_byte_order(source));
}

TEST(Endian, SwapByteOrderU32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_Swap32(source), cen::swap_byte_order(source));
}

TEST(Endian, SwapByteOrderU64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_Swap64(source), cen::swap_byte_order(source));
}

TEST(Endian, SwapByteOrderFloat)
{
  const auto source = 123.4f;
  ASSERT_EQ(SDL_SwapFloat(source), cen::swap_byte_order(source));
}

TEST(Endian, SwapLittleEndianU16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_SwapLE16(source), cen::swap_little_endian(source));
}

TEST(Endian, SwapLittleEndianU32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_SwapLE32(source), cen::swap_little_endian(source));
}

TEST(Endian, SwapLittleEndianU64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_SwapLE64(source), cen::swap_little_endian(source));
}

TEST(Endian, SwapLittleEndianFloat)
{
  const float source = 123.4f;
  ASSERT_EQ(SDL_SwapFloatLE(source), cen::swap_little_endian(source));
}

TEST(Endian, SwapBigEndianU16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_SwapBE16(source), cen::swap_big_endian(source));
}

TEST(Endian, SwapBigEndianU32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_SwapBE32(source), cen::swap_big_endian(source));
}

TEST(Endian, SwapBigEndianU64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_SwapBE64(source), cen::swap_big_endian(source));
}

TEST(Endian, SwapBigEndianFloat)
{
  const float source = 123.4f;
  ASSERT_EQ(SDL_SwapFloatBE(source), cen::swap_big_endian(source));
}