#include <gtest/gtest.h>

#include <type_traits>

#include "common.hpp"
#include "mouse.hpp"

static_assert(std::is_move_constructible_v<cen::Cursor>);
static_assert(std::is_move_assignable_v<cen::Cursor>);

static_assert(!std::is_copy_constructible_v<cen::Cursor>);
static_assert(!std::is_copy_assignable_v<cen::Cursor>);

static_assert(std::is_move_constructible_v<cen::CursorHandle>);
static_assert(std::is_move_assignable_v<cen::CursorHandle>);

static_assert(std::is_copy_constructible_v<cen::CursorHandle>);
static_assert(std::is_copy_assignable_v<cen::CursorHandle>);

TEST(Cursor, SystemCursorConstructor)
{
  ASSERT_NO_THROW(cen::Cursor{cen::SystemCursor::Crosshair});

  const auto invalid = static_cast<cen::SystemCursor>(83'948);
  ASSERT_THROW(cen::Cursor{invalid}, cen::sdl_error);
}

TEST(Cursor, SurfaceConstructor)
{
  const cen::Surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  ASSERT_NO_THROW(cen::Cursor(surface, hotspot));

  const cen::ipoint outside{8341, 2342};
  ASSERT_THROW(cen::Cursor(surface, outside), cen::sdl_error);
}

TEST(Cursor, Enable)
{
  {  // Normal usage
    cen::Cursor cursor{cen::SystemCursor::Wait};

    cursor.Enable();
    ASSERT_TRUE(cursor.IsEnabled());
  }

  {  // Special case where two instances have the same type
    const auto id = cen::SystemCursor::Size_NE_SW;
    cen::Cursor first{id};
    cen::Cursor second{id};

    first.Enable();
    ASSERT_TRUE(first.IsEnabled());
    ASSERT_FALSE(second.IsEnabled());

    second.Enable();
    ASSERT_TRUE(second.IsEnabled());
    ASSERT_FALSE(first.IsEnabled());
  }
}

TEST(Cursor, ForceRedraw)
{
  cen::Cursor cursor{cen::SystemCursor::IBeam};
  cursor.Enable();

  ASSERT_NO_THROW(cen::Cursor::ForceRedraw());

  ASSERT_TRUE(cursor.IsEnabled());  // ensure state of active cursor
}

TEST(Cursor, Reset)
{
  cen::Cursor::Reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::Cursor cursor{cen::SystemCursor::Crosshair};
  cursor.Enable();
  ASSERT_NE(SDL_GetDefaultCursor(), SDL_GetCursor());

  cen::Cursor::Reset();
  ASSERT_EQ(SDL_GetDefaultCursor(), SDL_GetCursor());
}

TEST(Cursor, SetVisible)
{
  ASSERT_TRUE(cen::Cursor::IsVisible());

  cen::Cursor::SetVisible(false);
  ASSERT_FALSE(cen::Cursor::IsVisible());

  cen::Cursor::SetVisible(true);
  ASSERT_TRUE(cen::Cursor::IsVisible());
}

TEST(Cursor, GetSystemCursors)
{
  ASSERT_EQ(SDL_NUM_SYSTEM_CURSORS, cen::Cursor::GetSystemCursors());
}
