#include "screen.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("screen::set_screen_saver_enabled", "[screen]")
{
  CHECK(!screen::screen_saver_enabled());

  screen::set_screen_saver_enabled(true);
  CHECK(screen::screen_saver_enabled());

  screen::set_screen_saver_enabled(false);
  CHECK(!screen::screen_saver_enabled());
}

TEST_CASE("screen::width", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(screen::width() == mode.w);
}

TEST_CASE("screen::height", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(screen::height() == mode.h);
}

TEST_CASE("screen::size", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = screen::size();
  CHECK(size.width == mode.w);
  CHECK(size.height == mode.h);
}

TEST_CASE("screen::refresh_rate", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(screen::refresh_rate() == mode.refresh_rate);
}

TEST_CASE("screen::pixel_format", "[screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(screen::get_pixel_format() == static_cast<pixel_format>(mode.format));
}