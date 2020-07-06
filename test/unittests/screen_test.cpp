#include "screen.hpp"

#include <catch.hpp>

using namespace centurion;

TEST_CASE("Screen::set_screen_saver_enabled", "[Screen]")
{
  CHECK(!Screen::screen_saver_enabled());

  Screen::set_screen_saver_enabled(true);
  CHECK(Screen::screen_saver_enabled());

  Screen::set_screen_saver_enabled(false);
  CHECK(!Screen::screen_saver_enabled());
}

TEST_CASE("Screen::width", "[Screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::width() == mode.w);
}

TEST_CASE("Screen::height", "[Screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::height() == mode.h);
}

TEST_CASE("Screen::size", "[Screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = Screen::size();
  CHECK(size.width == mode.w);
  CHECK(size.height == mode.h);
}

TEST_CASE("Screen::refresh_rate", "[Screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::refresh_rate() == mode.refresh_rate);
}

TEST_CASE("Screen::pixel_format", "[Screen]")
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::pixel_format() == static_cast<PixelFormat>(mode.format));
}