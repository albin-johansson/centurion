#include "screen.hpp"

#include <catch.hpp>

#include "cen.hpp"

TEST_CASE("screen::set_screen_saver_enabled", "[screen]")
{
  CHECK(!cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(true);
  CHECK(cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(false);
  CHECK(!cen::screen::screen_saver_enabled());
}

TEST_CASE("screen::width", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(cen::screen::width() == mode.w);
}

TEST_CASE("screen::height", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(cen::screen::height() == mode.h);
}

TEST_CASE("screen::size", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = cen::screen::size();
  CHECK(size.width == mode.w);
  CHECK(size.height == mode.h);
}

TEST_CASE("screen::refresh_rate", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(cen::screen::refresh_rate() == mode.refresh_rate);
}

TEST_CASE("screen::get_pixel_format", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(cen::screen::get_pixel_format() ==
        static_cast<cen::pixel_format>(mode.format));
}