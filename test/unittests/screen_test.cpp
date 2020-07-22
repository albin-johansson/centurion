#include "screen.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("screen::set_screen_saver_enabled", "[screen]")
{
  CHECK(!ctn::screen::screen_saver_enabled());

  ctn::screen::set_screen_saver_enabled(true);
  CHECK(ctn::screen::screen_saver_enabled());

  ctn::screen::set_screen_saver_enabled(false);
  CHECK(!ctn::screen::screen_saver_enabled());
}

TEST_CASE("screen::width", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(ctn::screen::width() == mode.w);
}

TEST_CASE("screen::height", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(ctn::screen::height() == mode.h);
}

TEST_CASE("screen::size", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = ctn::screen::size();
  CHECK(size.width == mode.w);
  CHECK(size.height == mode.h);
}

TEST_CASE("screen::refresh_rate", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(ctn::screen::refresh_rate() == mode.refresh_rate);
}

TEST_CASE("screen::get_pixel_format", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(ctn::screen::get_pixel_format() ==
        static_cast<ctn::pixel_format>(mode.format));
}