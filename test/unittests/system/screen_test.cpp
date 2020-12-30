#include "screen.hpp"

#include <catch.hpp>

TEST_CASE("screen::orientation enum", "[screen]")
{
  using sdl_orientation = SDL_DisplayOrientation;
  using cen::screen::orientation;
  CHECK(static_cast<sdl_orientation>(orientation::unknown) ==
        SDL_ORIENTATION_UNKNOWN);
  CHECK(static_cast<sdl_orientation>(orientation::landscape) ==
        SDL_ORIENTATION_LANDSCAPE);
  CHECK(static_cast<sdl_orientation>(orientation::landscape_flipped) ==
        SDL_ORIENTATION_LANDSCAPE_FLIPPED);
  CHECK(static_cast<sdl_orientation>(orientation::portrait) ==
        SDL_ORIENTATION_PORTRAIT);
  CHECK(static_cast<sdl_orientation>(orientation::portrait_flipped) ==
        SDL_ORIENTATION_PORTRAIT_FLIPPED);
}

TEST_CASE("screen::set_screen_saver_enabled", "[screen]")
{
  CHECK(!cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(true);
  CHECK(cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(false);
  CHECK(!cen::screen::screen_saver_enabled());
}

TEST_CASE("screen::dpi", "[screen]")
{
  SECTION("Default screen")
  {
    const auto dpi = cen::screen::dpi();
    REQUIRE(dpi.has_value());

    float diagonal{};
    float horizontal{};
    float vertical{};
    SDL_GetDisplayDPI(0, &diagonal, &horizontal, &vertical);

    CHECK(dpi->diagonal == diagonal);
    CHECK(dpi->horizontal == horizontal);
    CHECK(dpi->vertical == vertical);
  }

  SECTION("With explicit display index")
  {
    const auto amount = cen::screen::amount();
    CHECK(!cen::screen::dpi(amount));
    CHECK(cen::screen::dpi(amount - 1));
  }
}

TEST_CASE("screen::diagonal_dpi", "[screen]")
{
  const auto diagonal = cen::screen::diagonal_dpi();
  REQUIRE(diagonal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, &expected, nullptr, nullptr);

  CHECK(*diagonal == expected);
  CHECK_FALSE(cen::screen::diagonal_dpi(cen::screen::amount()));
}

TEST_CASE("screen::horizontal_dpi", "[screen]")
{
  const auto horizontal = cen::screen::horizontal_dpi();
  REQUIRE(horizontal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, &expected, nullptr);

  CHECK(*horizontal == expected);
  CHECK_FALSE(cen::screen::horizontal_dpi(cen::screen::amount()));
}

TEST_CASE("screen::vertical_dpi", "[screen]")
{
  const auto vertical = cen::screen::vertical_dpi();
  REQUIRE(vertical.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, nullptr, &expected);

  CHECK(*vertical == expected);
  CHECK_FALSE(cen::screen::vertical_dpi(cen::screen::amount()));
}

TEST_CASE("screen::bounds", "[screen]")
{
  const auto bounds = cen::screen::bounds();
  REQUIRE(bounds.has_value());

  SDL_Rect rect{};
  CHECK(SDL_GetDisplayBounds(0, &rect) == 0);

  CHECK(bounds->x() == rect.x);
  CHECK(bounds->y() == rect.y);
  CHECK(bounds->width() == rect.w);
  CHECK(bounds->height() == rect.h);

  CHECK_FALSE(cen::screen::bounds(cen::screen::amount()).has_value());
}

TEST_CASE("screen::usable_bounds", "[screen]")
{
  const auto bounds = cen::screen::usable_bounds();
  REQUIRE(bounds.has_value());

  SDL_Rect rect{};
  CHECK(SDL_GetDisplayUsableBounds(0, &rect) == 0);

  CHECK(bounds->x() == rect.x);
  CHECK(bounds->y() == rect.y);
  CHECK(bounds->width() == rect.w);
  CHECK(bounds->height() == rect.h);

  CHECK_FALSE(cen::screen::usable_bounds(cen::screen::amount()).has_value());
}

TEST_CASE("screen::get_orientation", "[screen]")
{
  SECTION("Default index")
  {
    const auto orientation = cen::screen::get_orientation();
    CHECK(static_cast<SDL_DisplayOrientation>(orientation) ==
          SDL_GetDisplayOrientation(0));
  }

  CHECK(cen::screen::get_orientation(cen::screen::amount()) ==
        cen::screen::orientation::unknown);
}

TEST_CASE("screen::amount", "[screen]")
{
  CHECK(cen::screen::amount() == SDL_GetNumVideoDisplays());
}

TEST_CASE("screen::name", "[screen]")
{
  const auto name = cen::screen::name();
  CHECK(std::strcmp(SDL_GetDisplayName(0), name) == 0);
  CHECK_FALSE(cen::screen::name(cen::screen::amount()));
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