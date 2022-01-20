#include <gtest/gtest.h>

#include <iostream>  // cout

#include "mouse.hpp"

TEST(SystemCursor, SystemCursorCount)
{
  ASSERT_EQ(SDL_NUM_SYSTEM_CURSORS, cen::system_cursor_count());
}

TEST(SystemCursor, Values)
{
  ASSERT_EQ(SDL_SYSTEM_CURSOR_ARROW, to_underlying(cen::system_cursor::arrow));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_IBEAM, to_underlying(cen::system_cursor::ibeam));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAIT, to_underlying(cen::system_cursor::wait));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_CROSSHAIR, to_underlying(cen::system_cursor::crosshair));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAITARROW, to_underlying(cen::system_cursor::wait_arrow));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENWSE, to_underlying(cen::system_cursor::size_nw_se));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENESW, to_underlying(cen::system_cursor::size_ne_sw));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEWE, to_underlying(cen::system_cursor::size_we));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENS, to_underlying(cen::system_cursor::size_ns));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEALL, to_underlying(cen::system_cursor::size_all));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_NO, to_underlying(cen::system_cursor::no));
  ASSERT_EQ(SDL_SYSTEM_CURSOR_HAND, to_underlying(cen::system_cursor::hand));
}

TEST(SystemCursor, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::system_cursor>(cen::system_cursor_count())),
               cen::exception);

  ASSERT_EQ("arrow", to_string(cen::system_cursor::arrow));
  ASSERT_EQ("ibeam", to_string(cen::system_cursor::ibeam));
  ASSERT_EQ("wait", to_string(cen::system_cursor::wait));
  ASSERT_EQ("crosshair", to_string(cen::system_cursor::crosshair));
  ASSERT_EQ("wait_arrow", to_string(cen::system_cursor::wait_arrow));
  ASSERT_EQ("size_nw_se", to_string(cen::system_cursor::size_nw_se));
  ASSERT_EQ("size_ne_sw", to_string(cen::system_cursor::size_ne_sw));
  ASSERT_EQ("size_we", to_string(cen::system_cursor::size_we));
  ASSERT_EQ("size_ns", to_string(cen::system_cursor::size_ns));
  ASSERT_EQ("size_all", to_string(cen::system_cursor::size_all));
  ASSERT_EQ("no", to_string(cen::system_cursor::no));
  ASSERT_EQ("hand", to_string(cen::system_cursor::hand));

  std::cout << "system_cursor == " << cen::system_cursor::hand << '\n';
}
