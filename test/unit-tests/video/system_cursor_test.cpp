#include "video/system_cursor.hpp"

#include <gtest/gtest.h>

TEST(SystemCursor, Values)
{
  ASSERT_EQ(cen::system_cursor::arrow, SDL_SYSTEM_CURSOR_ARROW);
  ASSERT_EQ(cen::system_cursor::ibeam, SDL_SYSTEM_CURSOR_IBEAM);
  ASSERT_EQ(cen::system_cursor::wait, SDL_SYSTEM_CURSOR_WAIT);
  ASSERT_EQ(cen::system_cursor::crosshair, SDL_SYSTEM_CURSOR_CROSSHAIR);
  ASSERT_EQ(cen::system_cursor::wait_arrow, SDL_SYSTEM_CURSOR_WAITARROW);
  ASSERT_EQ(cen::system_cursor::arrow_nw_se, SDL_SYSTEM_CURSOR_SIZENWSE);
  ASSERT_EQ(cen::system_cursor::arrow_ne_sw, SDL_SYSTEM_CURSOR_SIZENESW);
  ASSERT_EQ(cen::system_cursor::arrow_w_e, SDL_SYSTEM_CURSOR_SIZEWE);
  ASSERT_EQ(cen::system_cursor::arrow_n_s, SDL_SYSTEM_CURSOR_SIZENS);
  ASSERT_EQ(cen::system_cursor::arrow_all, SDL_SYSTEM_CURSOR_SIZEALL);
  ASSERT_EQ(cen::system_cursor::no, SDL_SYSTEM_CURSOR_NO);
  ASSERT_EQ(cen::system_cursor::hand, SDL_SYSTEM_CURSOR_HAND);

  ASSERT_EQ(SDL_SYSTEM_CURSOR_ARROW, cen::system_cursor::arrow);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_IBEAM, cen::system_cursor::ibeam);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAIT, cen::system_cursor::wait);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_CROSSHAIR, cen::system_cursor::crosshair);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAITARROW, cen::system_cursor::wait_arrow);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENWSE, cen::system_cursor::arrow_nw_se);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENESW, cen::system_cursor::arrow_ne_sw);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEWE, cen::system_cursor::arrow_w_e);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENS, cen::system_cursor::arrow_n_s);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEALL, cen::system_cursor::arrow_all);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_NO, cen::system_cursor::no);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_HAND, cen::system_cursor::hand);

  ASSERT_NE(cen::system_cursor::arrow_all, SDL_SYSTEM_CURSOR_WAIT);
  ASSERT_NE(SDL_SYSTEM_CURSOR_SIZEALL, cen::system_cursor::hand);
}
