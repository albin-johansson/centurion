#include "catch.hpp"
#include "system.h"

using namespace centurion;

TEST_CASE("Screen::get_width", "[Screen]") {
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::get_width() == mode.w);
}

TEST_CASE("Screen::get_height", "[Screen]") {
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::get_height() == mode.h);
}

TEST_CASE("Screen::get_refresh_rate", "[Screen]") {
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::get_refresh_rate() == mode.refresh_rate);
}

TEST_CASE("Screen::get_pixel_format", "[Screen]") {
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  CHECK(Screen::get_pixel_format() == mode.format);
}