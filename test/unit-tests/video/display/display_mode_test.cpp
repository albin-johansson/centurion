/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

namespace {

[[nodiscard]] auto get_sdl_desktop_display_mode(const int index) -> SDL_DisplayMode
{
  SDL_DisplayMode mode {};
  SDL_GetDesktopDisplayMode(index, &mode);
  return mode;
}

[[nodiscard]] auto get_sdl_current_display_mode(const int index) -> SDL_DisplayMode
{
  SDL_DisplayMode mode {};
  SDL_GetCurrentDisplayMode(index, &mode);
  return mode;
}

void verify(const SDL_DisplayMode& expected, const cen::display_mode& mode)
{
  ASSERT_EQ(expected.refresh_rate, mode.refresh_rate().value_or(0));

  ASSERT_EQ(expected.w, mode.width());
  ASSERT_EQ(expected.h, mode.height());

  ASSERT_EQ(expected.w, mode.size().width);
  ASSERT_EQ(expected.h, mode.size().height);

  ASSERT_EQ(expected.format, cen::to_underlying(mode.format()));
  ASSERT_EQ(expected.driverdata, mode.driver_data());
}

}  // namespace

TEST(DisplayMode, InvalidDisplayIndex)
{
  ASSERT_THROW(cen::display_mode::desktop(cen::display_count().value()), cen::sdl_error);
  ASSERT_THROW(cen::display_mode::current(cen::display_count().value()), cen::sdl_error);
}

TEST(DisplayMode, Desktop)
{
  const auto expected = get_sdl_desktop_display_mode(0);
  const auto desktop = cen::display_mode::desktop();
  verify(expected, desktop);
}

TEST(DisplayMode, Current)
{
  const auto expected = get_sdl_current_display_mode(0);
  const auto current = cen::display_mode::current();
  verify(expected, current);
}
