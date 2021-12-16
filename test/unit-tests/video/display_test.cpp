#include <gtest/gtest.h>

#include "video.hpp"

TEST(Display, SetScreenSaverEnabled)
{
  ASSERT_FALSE(cen::IsScreenSaverEnabled());

  cen::SetScreenSaverEnabled(true);
  ASSERT_TRUE(cen::IsScreenSaverEnabled());

  cen::SetScreenSaverEnabled(false);
  ASSERT_FALSE(cen::IsScreenSaverEnabled());
}

TEST(Display, GetDPI)
{
  {  // Default display
    const auto dpi = cen::GetDisplayDPI();
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
    const auto amount = cen::GetNumDisplays();
    ASSERT_TRUE(cen::GetDisplayDPI(amount - 1));
    ASSERT_FALSE(cen::GetDisplayDPI(amount));
  }
}

TEST(Display, GetBounds)
{
  const auto bounds = cen::GetDisplayBounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->GetX());
  ASSERT_EQ(rect.y, bounds->GetY());
  ASSERT_EQ(rect.w, bounds->GetWidth());
  ASSERT_EQ(rect.h, bounds->GetHeight());

  ASSERT_FALSE(cen::GetDisplayBounds(cen::GetNumDisplays()).has_value());
}

TEST(Display, GetDisplayUsableBounds)
{
  const auto bounds = cen::GetDisplayUsableBounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect{};
  ASSERT_EQ(0, SDL_GetDisplayUsableBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->GetX());
  ASSERT_EQ(rect.y, bounds->GetY());
  ASSERT_EQ(rect.w, bounds->GetWidth());
  ASSERT_EQ(rect.h, bounds->GetHeight());

  ASSERT_FALSE(cen::GetDisplayUsableBounds(cen::GetNumDisplays()).has_value());
}

TEST(Display, GetOrientation)
{
  {  // Default index
    const auto orientation = cen::GetDisplayOrientation();
    ASSERT_EQ(SDL_GetDisplayOrientation(0), static_cast<SDL_DisplayOrientation>(orientation));
  }

  ASSERT_EQ(cen::DisplayOrientation::Unknown,
            cen::GetDisplayOrientation(cen::GetNumDisplays()));
}

TEST(Display, GetNumDisplays)
{
  ASSERT_EQ(SDL_GetNumVideoDisplays(), cen::GetNumDisplays());
}

TEST(Display, GetName)
{
  ASSERT_EQ(SDL_GetDisplayName(0), cen::GetDisplayName());
  ASSERT_FALSE(cen::GetDisplayName(cen::GetNumDisplays()));
}

TEST(Display, GetSize)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);

  const auto size = cen::GetDisplaySize();
  ASSERT_TRUE(size);
  ASSERT_EQ(mode.w, size->width);
  ASSERT_EQ(mode.h, size->height);
}

TEST(Display, GetRefreshRate)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(mode.refresh_rate, cen::GetDisplayRefreshRate());
}

TEST(Display, GetPixelFormat)
{
  SDL_DisplayMode mode;
  SDL_GetDesktopDisplayMode(0, &mode);
  ASSERT_EQ(static_cast<cen::PixelFormat>(mode.format), cen::GetDisplayPixelFormat());
}
