#include "video/cursor.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "core/exception.hpp"

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
  ASSERT_NO_THROW(cen::cursor{cen::system_cursor::crosshair});

  const auto invalid = static_cast<cen::system_cursor>(83'948);
  ASSERT_THROW(cen::cursor{invalid}, cen::sdl_error);
}

TEST(Cursor, SurfaceConstructor)
{
  const cen::surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  ASSERT_NO_THROW(cen::cursor(surface, hotspot));

  const cen::ipoint outside{8341, 2342};
  ASSERT_THROW(cen::cursor(surface, outside), cen::sdl_error);
}

TEST(Cursor, Enable)
{
  {  // Normal usage
    cen::cursor cursor{cen::system_cursor::wait};

    cursor.enable();
    ASSERT_TRUE(cursor.is_enabled());
  }

  {  // Special case where two instances have the same type
    const auto id = cen::system_cursor::arrow_ne_sw;
    cen::cursor first{id};
    cen::cursor second{id};

    first.enable();
    ASSERT_TRUE(first.is_enabled());
    ASSERT_FALSE(second.is_enabled());

    second.enable();
    ASSERT_TRUE(second.is_enabled());
    ASSERT_FALSE(first.is_enabled());
  }
}

TEST(Cursor, ForceRedraw)
{
  cen::cursor cursor{cen::system_cursor::ibeam};
  cursor.enable();

  ASSERT_NO_THROW(cen::cursor::force_redraw());

  ASSERT_TRUE(cursor.is_enabled());  // ensure state of active cursor
}

TEST(Cursor, Reset)
{
  cen::cursor::reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor cursor{cen::system_cursor::crosshair};
  cursor.enable();
  ASSERT_NE(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::cursor::reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());
}

TEST(Cursor, SetVisible)
{
  ASSERT_TRUE(cen::cursor::visible());

  cen::cursor::set_visible(false);
  ASSERT_FALSE(cen::cursor::visible());

  cen::cursor::set_visible(true);
  ASSERT_TRUE(cen::cursor::visible());
}

TEST(Cursor, Count)
{
  ASSERT_EQ(cen::cursor::count(), static_cast<int>(SDL_NUM_SYSTEM_CURSORS));
}

TEST(Cursor, SystemCursorEnumValues)
{
  using syscursor = cen::system_cursor;

  ASSERT_EQ(syscursor::arrow, SDL_SYSTEM_CURSOR_ARROW);
  ASSERT_EQ(syscursor::ibeam, SDL_SYSTEM_CURSOR_IBEAM);
  ASSERT_EQ(syscursor::wait, SDL_SYSTEM_CURSOR_WAIT);
  ASSERT_EQ(syscursor::crosshair, SDL_SYSTEM_CURSOR_CROSSHAIR);
  ASSERT_EQ(syscursor::wait_arrow, SDL_SYSTEM_CURSOR_WAITARROW);
  ASSERT_EQ(syscursor::arrow_nw_se, SDL_SYSTEM_CURSOR_SIZENWSE);
  ASSERT_EQ(syscursor::arrow_ne_sw, SDL_SYSTEM_CURSOR_SIZENESW);
  ASSERT_EQ(syscursor::arrow_w_e, SDL_SYSTEM_CURSOR_SIZEWE);
  ASSERT_EQ(syscursor::arrow_n_s, SDL_SYSTEM_CURSOR_SIZENS);
  ASSERT_EQ(syscursor::arrow_all, SDL_SYSTEM_CURSOR_SIZEALL);
  ASSERT_EQ(syscursor::no, SDL_SYSTEM_CURSOR_NO);
  ASSERT_EQ(syscursor::hand, SDL_SYSTEM_CURSOR_HAND);

  ASSERT_EQ(SDL_SYSTEM_CURSOR_ARROW, syscursor::arrow);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_IBEAM, syscursor::ibeam);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAIT, syscursor::wait);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_CROSSHAIR, syscursor::crosshair);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_WAITARROW, syscursor::wait_arrow);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENWSE, syscursor::arrow_nw_se);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENESW, syscursor::arrow_ne_sw);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEWE, syscursor::arrow_w_e);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZENS, syscursor::arrow_n_s);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_SIZEALL, syscursor::arrow_all);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_NO, syscursor::no);
  ASSERT_EQ(SDL_SYSTEM_CURSOR_HAND, syscursor::hand);

  ASSERT_NE(syscursor::arrow_all, SDL_SYSTEM_CURSOR_WAIT);
  ASSERT_NE(SDL_SYSTEM_CURSOR_SIZEALL, syscursor::hand);
}
