#include "video/screen.hpp"

#include <gtest/gtest.h>

TEST(Screen, SetScreenSaverEnabled)
{
  ASSERT_FALSE(cen::is_screen_saver_enabled());

  cen::set_screen_saver_enabled(true);
  ASSERT_TRUE(cen::is_screen_saver_enabled());

  cen::set_screen_saver_enabled(false);
  ASSERT_FALSE(cen::is_screen_saver_enabled());
}

TEST(Screen, DPI)
{
  {  // Default display
    const auto dpi = cen::screen::dpi();
    ASSERT_TRUE(dpi.has_value());

    float diagonal{};
    float horizontal{};
    float vertical{};
    SDL_GetDisplayDPI(0, &diagonal, &horizontal, &vertical);

    ASSERT_EQ(diagonal, dpi->diagonal);
    ASSERT_EQ(horizontal, dpi->horizontal);
    ASSERT_EQ(vertical, dpi->vertical);
  }

  {  // Explicit display index
    const auto amount = cen::screen::count();
    ASSERT_FALSE(cen::screen::dpi(amount));
    ASSERT_TRUE(cen::screen::dpi(amount - 1).has_value());
  }
}

TEST(Screen, DiagonalDPI)
{
  const auto diagonal = cen::screen::diagonal_dpi();
  ASSERT_TRUE(diagonal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, &expected, nullptr, nullptr);

  ASSERT_EQ(expected, *diagonal);
  ASSERT_FALSE(cen::screen::diagonal_dpi(cen::screen::count()));
}

TEST(Screen, HorizontalDPI)
{
  const auto horizontal = cen::screen::horizontal_dpi();
  ASSERT_TRUE(horizontal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, &expected, nullptr);

  ASSERT_EQ(expected, *horizontal);
  ASSERT_FALSE(cen::screen::diagonal_dpi(cen::screen::count()));
}

TEST(Screen, VerticalDPI)
{
  const auto vertical = cen::screen::vertical_dpi();
  ASSERT_TRUE(vertical.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, nullptr, &expected);

  ASSERT_EQ(expected, *vertical);
  ASSERT_FALSE(cen::screen::diagonal_dpi(cen::screen::count()));
}

TEST(Screen, Bounds)
{
  const auto bounds = cen::screen::bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::screen::bounds(cen::screen::count()).has_value());
}

TEST(Screen, UsableBounds)
{
  const auto bounds = cen::screen::usable_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayUsableBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::screen::usable_bounds(cen::screen::count()).has_value());
}

TEST(Screen, GetOrientation)
{
  {  // Default index
    const auto orientation = cen::screen::get_orientation();
    ASSERT_EQ(SDL_GetDisplayOrientation(0), static_cast<SDL_DisplayOrientation>(orientation));
  }

  ASSERT_EQ(cen::screen_orientation::unknown,
            cen::screen::get_orientation(cen::screen::count()));
}

TEST(Screen, Amount)
{
  ASSERT_EQ(SDL_GetNumVideoDisplays(), cen::screen::count());
}

TEST(Screen, Name)
{
  ASSERT_STREQ(SDL_GetDisplayName(0), cen::screen::name(0));
  ASSERT_FALSE(cen::screen::name(cen::screen::count()));
}

TEST(Screen, Width)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(mode.w, cen::screen::width());
}

TEST(Screen, Height)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(mode.h, cen::screen::height());
}

TEST(Screen, Size)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = cen::screen::size();
  ASSERT_TRUE(size);
  ASSERT_EQ(mode.w, size->width);
  ASSERT_EQ(mode.h, size->height);
}

TEST(Screen, RefreshRate)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(mode.refresh_rate, cen::screen::refresh_rate());
}

TEST(Screen, GetPixelFormat)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(static_cast<cen::pixel_format>(mode.format), cen::screen::get_pixel_format());
}
