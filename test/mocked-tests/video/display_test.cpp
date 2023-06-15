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

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/video.hpp"
#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_EnableScreenSaver)
FAKE_VOID_FUNC(SDL_DisableScreenSaver)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsScreenSaverEnabled)
FAKE_VALUE_FUNC(int, SDL_GetNumVideoDisplays)
FAKE_VALUE_FUNC(const char*, SDL_GetDisplayName, int)
FAKE_VALUE_FUNC(SDL_DisplayOrientation, SDL_GetDisplayOrientation, int)
FAKE_VALUE_FUNC(int, SDL_GetDisplayDPI, int, float*, float*, float*)
FAKE_VALUE_FUNC(int, SDL_GetDisplayBounds, int, SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_GetDisplayUsableBounds, int, SDL_Rect*)

#if SDL_VERSION_ATLEAST(2, 24, 0)
FAKE_VALUE_FUNC(int, SDL_GetPointDisplayIndex, const SDL_Point*)
FAKE_VALUE_FUNC(int, SDL_GetRectDisplayIndex, const SDL_Rect*)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
}

class DisplayTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_EnableScreenSaver)
    RESET_FAKE(SDL_DisableScreenSaver)
    RESET_FAKE(SDL_IsScreenSaverEnabled)
    RESET_FAKE(SDL_GetNumVideoDisplays)
    RESET_FAKE(SDL_GetDisplayName)
    RESET_FAKE(SDL_GetDisplayOrientation)
    RESET_FAKE(SDL_GetDisplayDPI)
    RESET_FAKE(SDL_GetDisplayBounds)
    RESET_FAKE(SDL_GetDisplayUsableBounds)

#if SDL_VERSION_ATLEAST(2, 24, 0)
    RESET_FAKE(SDL_GetPointDisplayIndex)
    RESET_FAKE(SDL_GetRectDisplayIndex)
#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
  }
};

TEST_F(DisplayTest, SetSreenSaverEnabled)
{
  cen::set_screen_saver_enabled(true);
  ASSERT_EQ(1u, SDL_EnableScreenSaver_fake.call_count);
  ASSERT_EQ(0u, SDL_DisableScreenSaver_fake.call_count);

  cen::set_screen_saver_enabled(false);
  ASSERT_EQ(1u, SDL_EnableScreenSaver_fake.call_count);
  ASSERT_EQ(1u, SDL_DisableScreenSaver_fake.call_count);
}

TEST_F(DisplayTest, IsScreenSaverEnabled)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_IsScreenSaverEnabled, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::is_screen_saver_enabled());
  ASSERT_TRUE(cen::is_screen_saver_enabled());

  ASSERT_EQ(2u, SDL_IsScreenSaverEnabled_fake.call_count);
}

TEST_F(DisplayTest, DisplayCount)
{
  std::array values {42};
  SET_RETURN_SEQ(SDL_GetNumVideoDisplays, values.data(), cen::isize(values));

  ASSERT_EQ(42, cen::display_count());

  ASSERT_EQ(1u, SDL_GetNumVideoDisplays_fake.call_count);
}

TEST_F(DisplayTest, DisplayName)
{
  std::array<const char*, 2> values {nullptr, "foo"};
  SET_RETURN_SEQ(SDL_GetDisplayName, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::display_name().has_value());
  ASSERT_EQ("foo", cen::display_name());

  ASSERT_EQ(2u, SDL_GetDisplayName_fake.call_count);
}

TEST_F(DisplayTest, DisplayOrientation)
{
  std::array values {SDL_ORIENTATION_UNKNOWN, SDL_ORIENTATION_LANDSCAPE};
  SET_RETURN_SEQ(SDL_GetDisplayOrientation, values.data(), cen::isize(values));

  ASSERT_EQ(cen::orientation::unknown, cen::display_orientation());
  ASSERT_EQ(cen::orientation::landscape, cen::display_orientation());

  ASSERT_EQ(2u, SDL_GetDisplayOrientation_fake.call_count);
}

TEST_F(DisplayTest, DisplayDPI)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GetDisplayDPI, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::display_dpi().has_value());
  ASSERT_TRUE(cen::display_dpi().has_value());

  ASSERT_EQ(2u, SDL_GetDisplayDPI_fake.call_count);
}

TEST_F(DisplayTest, DisplayBounds)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GetDisplayBounds, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::display_bounds().has_value());
  ASSERT_TRUE(cen::display_bounds().has_value());

  ASSERT_EQ(2u, SDL_GetDisplayBounds_fake.call_count);
}

TEST_F(DisplayTest, DisplayUsableBounds)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GetDisplayUsableBounds, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::display_usable_bounds().has_value());
  ASSERT_TRUE(cen::display_usable_bounds().has_value());

  ASSERT_EQ(2u, SDL_GetDisplayUsableBounds_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 24, 0)

TEST_F(DisplayTest, DisplayWithPoint)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GetPointDisplayIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::display_with({0, 0}).has_value());
  ASSERT_EQ(0, cen::display_with({0, 0}));

  ASSERT_EQ(2u, SDL_GetPointDisplayIndex_fake.call_count);
}

TEST_F(DisplayTest, DisplayWithRect)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_GetRectDisplayIndex, values.data(), cen::isize(values));

  const auto a = cen::display_with({0, 0, 10, 10});
  ASSERT_FALSE(a.has_value());

  const auto b = cen::display_with({0, 0, 10, 10});
  ASSERT_EQ(0, b);

  ASSERT_EQ(2u, SDL_GetRectDisplayIndex_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 24, 0)
