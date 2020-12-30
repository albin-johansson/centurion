#include "cursor.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "exception.hpp"

static_assert(std::is_move_constructible_v<cen::cursor>);
static_assert(std::is_move_assignable_v<cen::cursor>);

static_assert(!std::is_copy_constructible_v<cen::cursor>);
static_assert(!std::is_copy_assignable_v<cen::cursor>);

static_assert(std::is_move_constructible_v<cen::cursor_handle>);
static_assert(std::is_move_assignable_v<cen::cursor_handle>);

static_assert(std::is_copy_constructible_v<cen::cursor_handle>);
static_assert(std::is_copy_assignable_v<cen::cursor_handle>);

TEST(Cursor, SystemCursorConstructor)
{
  EXPECT_NO_THROW(cen::cursor{cen::system_cursor::crosshair});

  const auto invalid = static_cast<cen::system_cursor>(83'948);
  EXPECT_THROW(cen::cursor{invalid}, cen::sdl_error);
}

TEST(Cursor, SurfaceConstructor)
{
  const cen::surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  EXPECT_NO_THROW(cen::cursor(surface, hotspot));

  const cen::ipoint outside{8341, 2342};
  EXPECT_THROW(cen::cursor(surface, outside), cen::sdl_error);
}

TEST(Cursor, Enable)
{
  {  // Normal usage
    cen::cursor cursor{cen::system_cursor::wait};

    cursor.enable();
    EXPECT_TRUE(cursor.is_enabled());
  }

  {  // Special case where two instances have the same type
    const auto id = cen::system_cursor::arrow_ne_sw;
    cen::cursor first{id};
    cen::cursor second{id};

    first.enable();
    EXPECT_TRUE(first.is_enabled());
    EXPECT_FALSE(second.is_enabled());

    second.enable();
    EXPECT_TRUE(second.is_enabled());
    EXPECT_FALSE(first.is_enabled());
  }
}

TEST(Cursor, ForceRedraw)
{
  cen::cursor cursor{cen::system_cursor::ibeam};
  cursor.enable();

  EXPECT_NO_THROW(cen::cursor::force_redraw());

  EXPECT_TRUE(cursor.is_enabled());  // ensure state of active cursor
}

TEST(Cursor, Reset)
{
  cen::cursor::reset();
  EXPECT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor cursor{cen::system_cursor::crosshair};
  cursor.enable();
  EXPECT_NE(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor::reset();
  EXPECT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());
}

TEST(Cursor, SetVisible)
{
  EXPECT_TRUE(cen::cursor::visible());

  cen::cursor::set_visible(false);
  EXPECT_FALSE(cen::cursor::visible());

  cen::cursor::set_visible(true);
  EXPECT_TRUE(cen::cursor::visible());
}

TEST(Cursor, NumSystemCursors)
{
  EXPECT_EQ(cen::cursor::num_system_cursors(),
            static_cast<int>(SDL_NUM_SYSTEM_CURSORS));
}

TEST(Cursor, SystemCursorEnumValues)
{
  using syscursor = cen::system_cursor;

  EXPECT_EQ(syscursor::arrow, SDL_SYSTEM_CURSOR_ARROW);
  EXPECT_EQ(syscursor::ibeam, SDL_SYSTEM_CURSOR_IBEAM);
  EXPECT_EQ(syscursor::wait, SDL_SYSTEM_CURSOR_WAIT);
  EXPECT_EQ(syscursor::crosshair, SDL_SYSTEM_CURSOR_CROSSHAIR);
  EXPECT_EQ(syscursor::wait_arrow, SDL_SYSTEM_CURSOR_WAITARROW);
  EXPECT_EQ(syscursor::arrow_nw_se, SDL_SYSTEM_CURSOR_SIZENWSE);
  EXPECT_EQ(syscursor::arrow_ne_sw, SDL_SYSTEM_CURSOR_SIZENESW);
  EXPECT_EQ(syscursor::arrow_w_e, SDL_SYSTEM_CURSOR_SIZEWE);
  EXPECT_EQ(syscursor::arrow_n_s, SDL_SYSTEM_CURSOR_SIZENS);
  EXPECT_EQ(syscursor::arrow_all, SDL_SYSTEM_CURSOR_SIZEALL);
  EXPECT_EQ(syscursor::no, SDL_SYSTEM_CURSOR_NO);
  EXPECT_EQ(syscursor::hand, SDL_SYSTEM_CURSOR_HAND);

  EXPECT_EQ(SDL_SYSTEM_CURSOR_ARROW, syscursor::arrow);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_IBEAM, syscursor::ibeam);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_WAIT, syscursor::wait);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_CROSSHAIR, syscursor::crosshair);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_WAITARROW, syscursor::wait_arrow);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_SIZENWSE, syscursor::arrow_nw_se);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_SIZENESW, syscursor::arrow_ne_sw);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_SIZEWE, syscursor::arrow_w_e);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_SIZENS, syscursor::arrow_n_s);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_SIZEALL, syscursor::arrow_all);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_NO, syscursor::no);
  EXPECT_EQ(SDL_SYSTEM_CURSOR_HAND, syscursor::hand);

  EXPECT_NE(syscursor::arrow_all, SDL_SYSTEM_CURSOR_WAIT);
  EXPECT_NE(SDL_SYSTEM_CURSOR_SIZEALL, syscursor::hand);
}
