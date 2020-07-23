#include "cursor.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"

TEST_CASE("cursor(system_cursor)", "[cursor]")
{
  CHECK_NOTHROW(ctn::cursor{ctn::system_cursor::crosshair});
}

TEST_CASE("cursor(owner<SDL_Cursor*>)", "[cursor]")
{
  auto* sdlCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
  CHECK_NOTHROW(ctn::cursor{sdlCursor});
}

TEST_CASE("cursor(surface, point_i)", "[cursor]")
{
  const ctn::surface surface{"resources/panda.png"};
  const ctn::point_i hotspot{12, 14};
  CHECK_NOTHROW(ctn::cursor{surface, hotspot});
}

TEST_CASE("cursor(cursor&&)", "[cursor]")
{
  const ctn::surface surface{"resources/panda.png"};
  const ctn::point_i hotspot{12, 14};
  ctn::cursor cursor{surface, hotspot};

  ctn::cursor other{std::move(cursor)};

  CHECK(!cursor.get());
  CHECK(other.get());
}

TEST_CASE("cursor::operator=(cursor&&)", "[cursor]")
{
  SECTION("Self-assignment")
  {
    const ctn::surface surface{"resources/panda.png"};
    const ctn::point_i hotspot{12, 14};
    ctn::cursor cursor{surface, hotspot};

    cursor = std::move(cursor);

    CHECK(cursor.get());
  }

  SECTION("Normal usage")
  {
    const ctn::surface surface{"resources/panda.png"};
    const ctn::point_i hotspot{12, 14};
    ctn::cursor cursor{surface, hotspot};
    ctn::cursor other{surface, hotspot};

    other = std::move(cursor);

    CHECK(!cursor.get());
    CHECK(other.get());
  }
}

TEST_CASE("cursor::unique", "[cursor]")
{
  CHECK(ctn::cursor::unique(ctn::system_cursor::arrow_all));
  CHECK(ctn::cursor::unique(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW)));
  CHECK(ctn::cursor::unique(ctn::surface{"resources/panda.png"}, {10, 10}));

  SECTION("Out-of-bounds hotspot")
  {
    ctn::surface surface{"resources/panda.png"};
    ctn::point_i hotspot{1, surface.height() + 1};
    CHECK_THROWS_AS(ctn::cursor::unique(surface, hotspot),
                    ctn::centurion_exception);
  }
}

TEST_CASE("cursor::shared", "[cursor]")
{
  CHECK(ctn::cursor::shared(ctn::system_cursor::hand));

  CHECK(ctn::cursor::shared(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE)));

  CHECK(ctn::cursor::shared(ctn::surface{"resources/panda.png"}, {8, 28}));

  SECTION("Out-of-bounds hotspot")
  {
    ctn::surface surface{"resources/panda.png"};
    ctn::point_i hotspot{surface.width() + 1, 1};
    CHECK_THROWS_AS(ctn::cursor::shared(surface, hotspot),
                    ctn::centurion_exception);
  }
}

TEST_CASE("cursor::enable", "[cursor]")
{
  ctn::cursor cursor{ctn::system_cursor::wait};

  cursor.enable();
  CHECK(cursor.is_enabled());

  SECTION("Special case where two instances have the same type")
  {
    const auto id = ctn::system_cursor::arrow_ne_sw;
    ctn::cursor first{id};
    ctn::cursor second{id};

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
  ctn::cursor cursor{ctn::system_cursor::ibeam};
  cursor.enable();

  CHECK_NOTHROW(ctn::cursor::force_redraw());

  CHECK(cursor.is_enabled());  // ensure state of active cursor
}

TEST_CASE("cursor::reset", "[cursor]")
{
  ctn::cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());

  ctn::cursor cursor{ctn::system_cursor::crosshair};
  cursor.enable();

  CHECK(SDL_GetDefaultCursor() != SDL_GetCursor());

  ctn::cursor::reset();
  CHECK(SDL_GetDefaultCursor() == SDL_GetCursor());
}

TEST_CASE("cursor::set_visible", "[cursor]")
{
  CHECK(ctn::cursor::visible());

  ctn::cursor::set_visible(false);
  CHECK(!ctn::cursor::visible());

  ctn::cursor::set_visible(true);
  CHECK(ctn::cursor::visible());
}

TEST_CASE("SystemCursor enum values", "[cursor]")
{
  CHECK(ctn::system_cursor::arrow == SDL_SYSTEM_CURSOR_ARROW);
  CHECK(ctn::system_cursor::ibeam == SDL_SYSTEM_CURSOR_IBEAM);
  CHECK(ctn::system_cursor::wait == SDL_SYSTEM_CURSOR_WAIT);
  CHECK(ctn::system_cursor::crosshair == SDL_SYSTEM_CURSOR_CROSSHAIR);
  CHECK(ctn::system_cursor::wait_arrow == SDL_SYSTEM_CURSOR_WAITARROW);
  CHECK(ctn::system_cursor::arrow_nw_se == SDL_SYSTEM_CURSOR_SIZENWSE);
  CHECK(ctn::system_cursor::arrow_ne_sw == SDL_SYSTEM_CURSOR_SIZENESW);
  CHECK(ctn::system_cursor::arrow_w_e == SDL_SYSTEM_CURSOR_SIZEWE);
  CHECK(ctn::system_cursor::arrow_n_s == SDL_SYSTEM_CURSOR_SIZENS);
  CHECK(ctn::system_cursor::arrow_all == SDL_SYSTEM_CURSOR_SIZEALL);
  CHECK(ctn::system_cursor::no == SDL_SYSTEM_CURSOR_NO);
  CHECK(ctn::system_cursor::hand == SDL_SYSTEM_CURSOR_HAND);

  CHECK(SDL_SYSTEM_CURSOR_ARROW == ctn::system_cursor::arrow);
  CHECK(SDL_SYSTEM_CURSOR_IBEAM == ctn::system_cursor::ibeam);
  CHECK(SDL_SYSTEM_CURSOR_WAIT == ctn::system_cursor::wait);
  CHECK(SDL_SYSTEM_CURSOR_CROSSHAIR == ctn::system_cursor::crosshair);
  CHECK(SDL_SYSTEM_CURSOR_WAITARROW == ctn::system_cursor::wait_arrow);
  CHECK(SDL_SYSTEM_CURSOR_SIZENWSE == ctn::system_cursor::arrow_nw_se);
  CHECK(SDL_SYSTEM_CURSOR_SIZENESW == ctn::system_cursor::arrow_ne_sw);
  CHECK(SDL_SYSTEM_CURSOR_SIZEWE == ctn::system_cursor::arrow_w_e);
  CHECK(SDL_SYSTEM_CURSOR_SIZENS == ctn::system_cursor::arrow_n_s);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL == ctn::system_cursor::arrow_all);
  CHECK(SDL_SYSTEM_CURSOR_NO == ctn::system_cursor::no);
  CHECK(SDL_SYSTEM_CURSOR_HAND == ctn::system_cursor::hand);

  CHECK(ctn::system_cursor::arrow_all != SDL_SYSTEM_CURSOR_WAIT);
  CHECK(SDL_SYSTEM_CURSOR_SIZEALL != ctn::system_cursor::hand);
}
