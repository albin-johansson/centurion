/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
  // Default display
  const auto dpi = cen::display_dpi();
  if (dpi.has_value()) {
    float diagonal {};
    float horizontal {};
    float vertical {};
    SDL_GetDisplayDPI(0, &diagonal, &horizontal, &vertical);

    ASSERT_EQ(diagonal, dpi->diagonal);
    ASSERT_EQ(horizontal, dpi->horizontal);
    ASSERT_EQ(vertical, dpi->vertical);

    {  // Explicit display index
      const auto amount = cen::display_count().value();
      ASSERT_TRUE(cen::display_dpi(amount - 1).has_value());
      ASSERT_FALSE(cen::display_dpi(amount).has_value());
    }
  }
}

TEST(Display, DisplayBounds)
{
  const auto bounds = cen::display_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect {};
  ASSERT_EQ(0, SDL_GetDisplayBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::display_bounds(cen::display_count().value()).has_value());
}

TEST(Display, DisplayUsableBounds)
{
  const auto bounds = cen::display_usable_bounds();
  ASSERT_TRUE(bounds.has_value());

  SDL_Rect rect {};
  ASSERT_EQ(0, SDL_GetDisplayUsableBounds(0, &rect));

  ASSERT_EQ(rect.x, bounds->x());
  ASSERT_EQ(rect.y, bounds->y());
  ASSERT_EQ(rect.w, bounds->width());
  ASSERT_EQ(rect.h, bounds->height());

  ASSERT_FALSE(cen::display_usable_bounds(cen::display_count().value()).has_value());
}

TEST(Display, DisplayOrientation)
{
  ASSERT_EQ(cen::orientation::unknown, cen::display_orientation(cen::display_count().value()));
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
  ASSERT_FALSE(cen::display_name(cen::display_count().value()));
}
