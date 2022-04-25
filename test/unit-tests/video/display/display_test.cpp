#include <gtest/gtest.h>

#include "centurion/video.hpp"

TEST(Display, SetScreenSaverEnabled)
{
  ASSERT_FALSE(cen::is_screen_saver_enabled());

  cen::set_screen_saver_enabled(true);
  ASSERT_TRUE(cen::is_screen_saver_enabled());

  cen::set_screen_saver_enabled(false);
  ASSERT_FALSE(cen::is_screen_saver_enabled());
}

TEST(Display, DisplayDPI)
{
  {  // Default display
    const auto dpi = cen::display_dpi();
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
    const auto amount = cen::display_count();
    ASSERT_TRUE(cen::display_dpi(amount - 1));
    ASSERT_FALSE(cen::display_dpi(amount));
  }
}

TEST(Display, DisplayBounds)
{
  const auto bounds = cen::display_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::display_bounds(cen::display_count()).has_value());
}

TEST(Display, DisplayUsableBounds)
{
  const auto bounds = cen::display_usable_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayUsableBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::display_usable_bounds(cen::display_count()).has_value());
}

TEST(Display, DisplayOrientation)
{
  ASSERT_EQ(cen::orientation::unknown, cen::display_orientation(cen::display_count()));
  ASSERT_EQ(SDL_GetDisplayOrientation(0),
            static_cast<SDL_DisplayOrientation>(cen::display_orientation()));
}

TEST(Display, DisplayCount)
{
  ASSERT_EQ(SDL_GetNumVideoDisplays(), cen::display_count());
}

TEST(Display, DisplayName)
{
  ASSERT_EQ(SDL_GetDisplayName(0), cen::display_name());
  ASSERT_FALSE(cen::display_name(cen::display_count()));
}
