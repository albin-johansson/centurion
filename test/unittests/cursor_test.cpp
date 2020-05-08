#include "cursor.h"

#include <catch.hpp>

#include "centurion_exception.h"

using namespace centurion;

TEST_CASE("Cursor(SystemCursor)", "[Cursor]")
{
  CHECK_NOTHROW(Cursor{SystemCursor::Crosshair});
}

TEST_CASE("Cursor(gsl::owner<SDL_Cursor*>)", "[Cursor]")
{
  SDL_Cursor* sdlCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  Cursor cursor{sdlCursor};

  CHECK_THROWS_AS(Cursor{nullptr}, CenturionException);
}

TEST_CASE("Cursor(Surface, IPoint)", "[Cursor]")
{
  const Surface surface{"resources/panda.png"};
  const IPoint hotspot{12, 14};
  Cursor cursor{surface, hotspot};
}

TEST_CASE("Cursor move semantics", "[Cursor]")
{
  SECTION("Move constructor")
  {
    Cursor cursor{SystemCursor::Arrow_N_S};
    Cursor other{std::move(cursor)};
  }

  SECTION("Move assignment")
  {
    Cursor cursor{SystemCursor::Arrow_N_S};
    Cursor other{SystemCursor::No};

    other = std::move(cursor);
  }
}

TEST_CASE("Cursor::unique", "[Cursor]")
{
  CHECK(Cursor::unique(SystemCursor::ArrowAll));

  CHECK(Cursor::unique(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)));
  CHECK_THROWS_AS(Cursor::unique(nullptr), CenturionException);

  CHECK(Cursor::unique(Surface{"resources/panda.png"}, {10, 10}));

  SECTION("Out-of-bounds hotspot")
  {
    Surface surface{"resources/panda.png"};
    IPoint hotspot{1, surface.height() + 1};
    CHECK_THROWS_AS(Cursor::unique(surface, hotspot), CenturionException);
  }
}

TEST_CASE("Cursor::shared", "[Cursor]")
{
  CHECK(Cursor::shared(SystemCursor::Hand));

  CHECK(Cursor::shared(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE)));
  CHECK_THROWS_AS(Cursor::shared(nullptr), CenturionException);

  CHECK(Cursor::shared(Surface{"resources/panda.png"}, {8, 28}));

  SECTION("Out-of-bounds hotspot")
  {
    Surface surface{"resources/panda.png"};
    IPoint hotspot{surface.width() + 1, 1};
    CHECK_THROWS_AS(Cursor::shared(surface, hotspot), CenturionException);
  }
}

TEST_CASE("Cursor::enable", "[Cursor]")
{
  Cursor cursor{SystemCursor::Wait};

  cursor.enable();
  CHECK(cursor.is_enabled());

  SECTION("Special case where two instances have the same type")
  {
    const auto id = SystemCursor::Arrow_NE_SW;
    Cursor first{id};
    Cursor second{id};

    first.enable();

    CHECK(first.is_enabled());
    CHECK(!second.is_enabled());

    second.enable();

    CHECK(!first.is_enabled());
    CHECK(second.is_enabled());
  }
}

TEST_CASE("Cursor::force_redraw", "[Cursor]")
{
  Cursor cursor{SystemCursor::IBeam};
  cursor.enable();

  CHECK_NOTHROW(Cursor::force_redraw());

  CHECK(cursor.is_enabled());  // ensure state of active cursor
}

TEST_CASE("Cursor::reset", "[Cursor]")
{
  Cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());

  Cursor cursor{SystemCursor::Crosshair};
  cursor.enable();

  CHECK(SDL_GetDefaultCursor() != SDL_GetCursor());

  Cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());
}

TEST_CASE("Cursor::set_visible", "[Cursor]")
{
  CHECK(Cursor::visible());

  Cursor::set_visible(false);
  CHECK(!Cursor::visible());

  Cursor::set_visible(true);
  CHECK(Cursor::visible());
}

TEST_CASE("SystemCursor enum values", "[Cursor]")
{
  CHECK(SystemCursor::Arrow == SDL_SYSTEM_CURSOR_ARROW);
  CHECK(SystemCursor::IBeam == SDL_SYSTEM_CURSOR_IBEAM);
  CHECK(SystemCursor::Wait == SDL_SYSTEM_CURSOR_WAIT);
  CHECK(SystemCursor::Crosshair == SDL_SYSTEM_CURSOR_CROSSHAIR);
  CHECK(SystemCursor::WaitArrow == SDL_SYSTEM_CURSOR_WAITARROW);
  CHECK(SystemCursor::Arrow_NW_SE == SDL_SYSTEM_CURSOR_SIZENWSE);
  CHECK(SystemCursor::Arrow_NE_SW == SDL_SYSTEM_CURSOR_SIZENESW);
  CHECK(SystemCursor::Arrow_W_E == SDL_SYSTEM_CURSOR_SIZEWE);
  CHECK(SystemCursor::Arrow_N_S == SDL_SYSTEM_CURSOR_SIZENS);
  CHECK(SystemCursor::ArrowAll == SDL_SYSTEM_CURSOR_SIZEALL);
  CHECK(SystemCursor::No == SDL_SYSTEM_CURSOR_NO);
  CHECK(SystemCursor::Hand == SDL_SYSTEM_CURSOR_HAND);

  CHECK(SDL_SYSTEM_CURSOR_ARROW == SystemCursor::Arrow);
  CHECK(SDL_SYSTEM_CURSOR_IBEAM == SystemCursor::IBeam);
  CHECK(SDL_SYSTEM_CURSOR_WAIT == SystemCursor::Wait);
  CHECK(SDL_SYSTEM_CURSOR_CROSSHAIR == SystemCursor::Crosshair);
  CHECK(SDL_SYSTEM_CURSOR_WAITARROW == SystemCursor::WaitArrow);
  CHECK(SDL_SYSTEM_CURSOR_SIZENWSE == SystemCursor::Arrow_NW_SE);
  CHECK(SDL_SYSTEM_CURSOR_SIZENESW == SystemCursor::Arrow_NE_SW);
  CHECK(SDL_SYSTEM_CURSOR_SIZEWE == SystemCursor::Arrow_W_E);
  CHECK(SDL_SYSTEM_CURSOR_SIZENS == SystemCursor::Arrow_N_S);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL == SystemCursor::ArrowAll);
  CHECK(SDL_SYSTEM_CURSOR_NO == SystemCursor::No);
  CHECK(SDL_SYSTEM_CURSOR_HAND == SystemCursor::Hand);

  CHECK(SystemCursor::ArrowAll != SDL_SYSTEM_CURSOR_WAIT);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL != SystemCursor::Hand);
}
