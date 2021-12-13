#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/common.hpp"
#include "video/cursor.hpp"

TEST(SystemCursor, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Arrow), SDL_SYSTEM_CURSOR_ARROW);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::IBeam), SDL_SYSTEM_CURSOR_IBEAM);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Wait), SDL_SYSTEM_CURSOR_WAIT);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Crosshair), SDL_SYSTEM_CURSOR_CROSSHAIR);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::WaitArrow), SDL_SYSTEM_CURSOR_WAITARROW);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Size_NW_SE), SDL_SYSTEM_CURSOR_SIZENWSE);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Size_NE_SW), SDL_SYSTEM_CURSOR_SIZENESW);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Size_W_E), SDL_SYSTEM_CURSOR_SIZEWE);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Size_N_S), SDL_SYSTEM_CURSOR_SIZENS);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::SizeAll), SDL_SYSTEM_CURSOR_SIZEALL);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::No), SDL_SYSTEM_CURSOR_NO);
  ASSERT_EQ(cen::to_underlying(cen::SystemCursor::Hand), SDL_SYSTEM_CURSOR_HAND);
}

TEST(SystemCursor, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::SystemCursor>(SDL_NUM_SYSTEM_CURSORS)),
               cen::Error);

  ASSERT_EQ("Arrow", cen::to_string(cen::SystemCursor::Arrow));
  ASSERT_EQ("IBeam", cen::to_string(cen::SystemCursor::IBeam));
  ASSERT_EQ("Wait", cen::to_string(cen::SystemCursor::Wait));
  ASSERT_EQ("Crosshair", cen::to_string(cen::SystemCursor::Crosshair));
  ASSERT_EQ("WaitArrow", cen::to_string(cen::SystemCursor::WaitArrow));
  ASSERT_EQ("Size_NW_SE", cen::to_string(cen::SystemCursor::Size_NW_SE));
  ASSERT_EQ("Size_NE_SW", cen::to_string(cen::SystemCursor::Size_NE_SW));
  ASSERT_EQ("Size_W_E", cen::to_string(cen::SystemCursor::Size_W_E));
  ASSERT_EQ("Size_N_S", cen::to_string(cen::SystemCursor::Size_N_S));
  ASSERT_EQ("SizeAll", cen::to_string(cen::SystemCursor::SizeAll));
  ASSERT_EQ("No", cen::to_string(cen::SystemCursor::No));
  ASSERT_EQ("Hand", cen::to_string(cen::SystemCursor::Hand));

  std::clog << "System cursor example: " << cen::SystemCursor::Hand << '\n';
}
