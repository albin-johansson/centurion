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
  ASSERT_THROW(cen::cursor{invalid}, cen::SDLError);
}

TEST(Cursor, SurfaceConstructor)
{
  const cen::Surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  ASSERT_NO_THROW(cen::cursor(surface, hotspot));

  const cen::ipoint outside{8341, 2342};
  ASSERT_THROW(cen::cursor(surface, outside), cen::SDLError);
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
  ASSERT_EQ(SDL_NUM_SYSTEM_CURSORS, cen::cursor::count());
}
