#include <gtest/gtest.h>

#include "endian.hpp"

TEST(SwapByteOrder, U16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_Swap16(source), cen::swap_byte_order(source));
}

TEST(SwapByteOrder, U32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_Swap32(source), cen::swap_byte_order(source));
}

TEST(SwapByteOrder, U64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_Swap64(source), cen::swap_byte_order(source));
}

TEST(SwapByteOrder, Float)
{
  const auto source = 123.4f;
  ASSERT_EQ(SDL_SwapFloat(source), cen::swap_byte_order(source));
}

TEST(SwapBigEndian, U16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_SwapBE16(source), cen::swap_big_endian(source));
}

TEST(SwapBigEndian, U32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_SwapBE32(source), cen::swap_big_endian(source));
}

TEST(SwapBigEndian, U64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_SwapBE64(source), cen::swap_big_endian(source));
}

TEST(SwapBigEndian, Float)
{
  const float source = 123.4f;
  ASSERT_EQ(SDL_SwapFloatBE(source), cen::swap_big_endian(source));
}

TEST(SwapLittleEndian, U16)
{
  const Uint16 source = 1234;
  ASSERT_EQ(SDL_SwapLE16(source), cen::swap_little_endian(source));
}

TEST(SwapLittleEndian, U32)
{
  const Uint32 source = 1234;
  ASSERT_EQ(SDL_SwapLE32(source), cen::swap_little_endian(source));
}

TEST(SwapLittleEndian, U64)
{
  const Uint64 source = 1234;
  ASSERT_EQ(SDL_SwapLE64(source), cen::swap_little_endian(source));
}

TEST(SwapLittleEndian, Float)
{
  const float source = 123.4f;
  ASSERT_EQ(SDL_SwapFloatLE(source), cen::swap_little_endian(source));
}