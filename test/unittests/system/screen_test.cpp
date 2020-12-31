#include "screen.hpp"

#include <gtest/gtest.h>

TEST(Screen, SetScreenSaverEnabled)
{
  EXPECT_FALSE(cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(true);
  EXPECT_TRUE(cen::screen::screen_saver_enabled());

  cen::screen::set_screen_saver_enabled(false);
  EXPECT_FALSE(cen::screen::screen_saver_enabled());
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

    EXPECT_EQ(diagonal, dpi->diagonal);
    EXPECT_EQ(horizontal, dpi->horizontal);
    EXPECT_EQ(vertical, dpi->vertical);
  }

  {  // Explicit display index
    const auto amount = cen::screen::amount();
    EXPECT_FALSE(cen::screen::dpi(amount));
    EXPECT_TRUE(cen::screen::dpi(amount - 1).has_value());
  }
}

TEST(Screen, DiagonalDPI)
{
  const auto diagonal = cen::screen::diagonal_dpi();
  ASSERT_TRUE(diagonal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, &expected, nullptr, nullptr);

  EXPECT_EQ(expected, *diagonal);
  EXPECT_FALSE(cen::screen::diagonal_dpi(cen::screen::amount()));
}

TEST(Screen, HorizontalDPI)
{
  const auto horizontal = cen::screen::horizontal_dpi();
  ASSERT_TRUE(horizontal.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, &expected, nullptr);

  EXPECT_EQ(expected, *horizontal);
  EXPECT_FALSE(cen::screen::diagonal_dpi(cen::screen::amount()));
}

TEST(Screen, VerticalDPI)
{
  const auto vertical = cen::screen::vertical_dpi();
  ASSERT_TRUE(vertical.has_value());

  float expected{};
  SDL_GetDisplayDPI(0, nullptr, nullptr, &expected);

  EXPECT_EQ(expected, *vertical);
  EXPECT_FALSE(cen::screen::diagonal_dpi(cen::screen::amount()));
}

TEST(Screen, Bounds)
{
  const auto bounds = cen::screen::bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  EXPECT_EQ(0, SDL_GetDisplayBounds(0, &rect));

  EXPECT_EQ(rect.x, bounds->x());
  EXPECT_EQ(rect.y, bounds->y());
  EXPECT_EQ(rect.w, bounds->width());
  EXPECT_EQ(rect.h, bounds->height());

  EXPECT_FALSE(cen::screen::bounds(cen::screen::amount()).has_value());
}

TEST(Screen, UsableBounds)
{
  const auto bounds = cen::screen::usable_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  EXPECT_EQ(0, SDL_GetDisplayUsableBounds(0, &rect));

  EXPECT_EQ(rect.x, bounds->x());
  EXPECT_EQ(rect.y, bounds->y());
  EXPECT_EQ(rect.w, bounds->width());
  EXPECT_EQ(rect.h, bounds->height());

  EXPECT_FALSE(cen::screen::usable_bounds(cen::screen::amount()).has_value());
}

TEST(Screen, GetOrientation)
{
  {  // Default index
    const auto orientation = cen::screen::get_orientation();
    EXPECT_EQ(SDL_GetDisplayOrientation(0),
              static_cast<SDL_DisplayOrientation>(orientation));
  }

  EXPECT_EQ(cen::screen::orientation::unknown,
            cen::screen::get_orientation(cen::screen::amount()));
}

TEST(Screen, Amount)
{
  EXPECT_EQ(SDL_GetNumVideoDisplays(), cen::screen::amount());
}

TEST(Screen, Name)
{
  EXPECT_STREQ(SDL_GetDisplayName(0), cen::screen::name());
  EXPECT_FALSE(cen::screen::name(cen::screen::amount()));
}

TEST(Screen, Width)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  EXPECT_EQ(mode.w, cen::screen::width());
}

TEST(Screen, Height)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  EXPECT_EQ(mode.h, cen::screen::height());
}

TEST(Screen, Size)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = cen::screen::size();
  EXPECT_EQ(mode.w, size.width);
  EXPECT_EQ(mode.h, size.height);
}

TEST(Screen, RefreshRate)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  EXPECT_EQ(mode.refresh_rate, cen::screen::refresh_rate());
}

TEST(Screen, GetPixelFormat)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  EXPECT_EQ(static_cast<cen::pixel_format>(mode.format),
            cen::screen::get_pixel_format());
}

TEST(Screen, OrientationEnum)
{
  using sdl_orientation = SDL_DisplayOrientation;
  using cen::screen::orientation;

  EXPECT_EQ(SDL_ORIENTATION_UNKNOWN,
            static_cast<sdl_orientation>(orientation::unknown));

  EXPECT_EQ(SDL_ORIENTATION_LANDSCAPE,
            static_cast<sdl_orientation>(orientation::landscape));

  EXPECT_EQ(SDL_ORIENTATION_LANDSCAPE_FLIPPED,
            static_cast<sdl_orientation>(orientation::landscape_flipped));

  EXPECT_EQ(SDL_ORIENTATION_PORTRAIT,
            static_cast<sdl_orientation>(orientation::portrait));

  EXPECT_EQ(SDL_ORIENTATION_PORTRAIT_FLIPPED,
            static_cast<sdl_orientation>(orientation::portrait_flipped));
}
