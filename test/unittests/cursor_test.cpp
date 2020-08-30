#include "cursor.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "exception.hpp"
#include "log.hpp"

TEST_CASE("cursor(system_cursor)", "[cursor]")
{
  CHECK_NOTHROW(cen::cursor{cen::system_cursor::crosshair});

  const auto invalid = static_cast<cen::system_cursor>(83948);
  CHECK_THROWS_AS(cen::cursor{invalid}, cen::sdl_error);
}

TEST_CASE("cursor(nn_owner<SDL_Cursor*>)", "[cursor]")
{
  auto* sdlCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  CHECK_NOTHROW(cen::cursor{sdlCursor});
}

TEST_CASE("cursor(surface, ipoint)", "[cursor]")
{
  const cen::surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  CHECK_NOTHROW(cen::cursor{surface, hotspot});

  const cen::ipoint outside{8341, 2342};
  CHECK_THROWS_AS(cen::cursor(surface, outside), cen::sdl_error);
}

TEST_CASE("cursor(cursor&&)", "[cursor]")
{
  const cen::surface surface{"resources/panda.png"};
  const cen::ipoint hotspot{12, 14};
  cen::cursor cursor{surface, hotspot};

  cen::cursor other{std::move(cursor)};

  CHECK(!cursor.get());
  CHECK(other.get());
}

TEST_CASE("cursor::operator=(cursor&&)", "[cursor]")
{
  SECTION("Self-assignment")
  {
    const cen::surface surface{"resources/panda.png"};
    const cen::ipoint hotspot{12, 14};
    cen::cursor cursor{surface, hotspot};

    cursor = std::move(cursor);

    CHECK(cursor.get());
  }

  SECTION("Normal usage")
  {
    const cen::surface surface{"resources/panda.png"};
    const cen::ipoint hotspot{12, 14};
    cen::cursor cursor{surface, hotspot};
    cen::cursor other{surface, hotspot};

    other = std::move(cursor);

    CHECK(!cursor.get());
    CHECK(other.get());
  }
}

TEST_CASE("cursor::unique", "[cursor]")
{
  CHECK(cen::cursor::unique(cen::system_cursor::arrow_all));
  CHECK(cen::cursor::unique(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)));
  CHECK(cen::cursor::unique(cen::surface{"resources/panda.png"}, {10, 10}));

  SECTION("Out-of-bounds hotspot")
  {
    cen::surface surface{"resources/panda.png"};
    cen::ipoint hotspot{1, surface.height() + 1};
    CHECK_THROWS_AS(cen::cursor::unique(surface, hotspot), cen::exception);
  }
}

TEST_CASE("cursor::shared", "[cursor]")
{
  CHECK(cen::cursor::shared(cen::system_cursor::hand));

  CHECK(cen::cursor::shared(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE)));

  CHECK(cen::cursor::shared(cen::surface{"resources/panda.png"}, {8, 28}));

  SECTION("Out-of-bounds hotspot")
  {
    cen::surface surface{"resources/panda.png"};
    cen::ipoint hotspot{surface.width() + 1, 1};
    CHECK_THROWS_AS(cen::cursor::shared(surface, hotspot), cen::exception);
  }
}

TEST_CASE("cursor::enable", "[cursor]")
{
  cen::cursor cursor{cen::system_cursor::wait};

  cursor.enable();
  CHECK(cursor.is_enabled());

  SECTION("Special case where two instances have the same type")
  {
    const auto id = cen::system_cursor::arrow_ne_sw;
    cen::cursor first{id};
    cen::cursor second{id};

    first.enable();

    CHECK(first.is_enabled());
    CHECK(!second.is_enabled());

    second.enable();

    CHECK(!first.is_enabled());
    CHECK(second.is_enabled());
  }
}

TEST_CASE("cursor::force_redraw", "[cursor]")
{
  cen::cursor cursor{cen::system_cursor::ibeam};
  cursor.enable();

  CHECK_NOTHROW(cen::cursor::force_redraw());

  CHECK(cursor.is_enabled());  // ensure state of active cursor
}

TEST_CASE("cursor::reset", "[cursor]")
{
  cen::cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());

  cen::cursor cursor{cen::system_cursor::crosshair};
  cursor.enable();

  CHECK(SDL_GetDefaultCursor() != SDL_GetCursor());

  cen::cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());
}

TEST_CASE("cursor::set_visible", "[cursor]")
{
  CHECK(cen::cursor::visible());

  cen::cursor::set_visible(false);
  CHECK(!cen::cursor::visible());

  cen::cursor::set_visible(true);
  CHECK(cen::cursor::visible());
}

TEST_CASE("SystemCursor enum values", "[cursor]")
{
  CHECK(cen::system_cursor::arrow == SDL_SYSTEM_CURSOR_ARROW);
  CHECK(cen::system_cursor::ibeam == SDL_SYSTEM_CURSOR_IBEAM);
  CHECK(cen::system_cursor::wait == SDL_SYSTEM_CURSOR_WAIT);
  CHECK(cen::system_cursor::crosshair == SDL_SYSTEM_CURSOR_CROSSHAIR);
  CHECK(cen::system_cursor::wait_arrow == SDL_SYSTEM_CURSOR_WAITARROW);
  CHECK(cen::system_cursor::arrow_nw_se == SDL_SYSTEM_CURSOR_SIZENWSE);
  CHECK(cen::system_cursor::arrow_ne_sw == SDL_SYSTEM_CURSOR_SIZENESW);
  CHECK(cen::system_cursor::arrow_w_e == SDL_SYSTEM_CURSOR_SIZEWE);
  CHECK(cen::system_cursor::arrow_n_s == SDL_SYSTEM_CURSOR_SIZENS);
  CHECK(cen::system_cursor::arrow_all == SDL_SYSTEM_CURSOR_SIZEALL);
  CHECK(cen::system_cursor::no == SDL_SYSTEM_CURSOR_NO);
  CHECK(cen::system_cursor::hand == SDL_SYSTEM_CURSOR_HAND);

  CHECK(SDL_SYSTEM_CURSOR_ARROW == cen::system_cursor::arrow);
  CHECK(SDL_SYSTEM_CURSOR_IBEAM == cen::system_cursor::ibeam);
  CHECK(SDL_SYSTEM_CURSOR_WAIT == cen::system_cursor::wait);
  CHECK(SDL_SYSTEM_CURSOR_CROSSHAIR == cen::system_cursor::crosshair);
  CHECK(SDL_SYSTEM_CURSOR_WAITARROW == cen::system_cursor::wait_arrow);
  CHECK(SDL_SYSTEM_CURSOR_SIZENWSE == cen::system_cursor::arrow_nw_se);
  CHECK(SDL_SYSTEM_CURSOR_SIZENESW == cen::system_cursor::arrow_ne_sw);
  CHECK(SDL_SYSTEM_CURSOR_SIZEWE == cen::system_cursor::arrow_w_e);
  CHECK(SDL_SYSTEM_CURSOR_SIZENS == cen::system_cursor::arrow_n_s);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL == cen::system_cursor::arrow_all);
  CHECK(SDL_SYSTEM_CURSOR_NO == cen::system_cursor::no);
  CHECK(SDL_SYSTEM_CURSOR_HAND == cen::system_cursor::hand);

  CHECK(cen::system_cursor::arrow_all != SDL_SYSTEM_CURSOR_WAIT);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL != cen::system_cursor::hand);
}
