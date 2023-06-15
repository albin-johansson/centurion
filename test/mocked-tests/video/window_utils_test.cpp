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

#include "centurion/video/window.hpp"
#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(SDL_Window*, SDL_GetGrabbedWindow)
FAKE_VALUE_FUNC(SDL_Window*, SDL_GetMouseFocus)
FAKE_VALUE_FUNC(SDL_Window*, SDL_GetKeyboardFocus)
FAKE_VALUE_FUNC(SDL_Window*, SDL_GetWindowFromID, Uint32)
FAKE_VALUE_FUNC(SDL_Renderer*, SDL_GetRenderer, SDL_Window*)
}

class WindowUtilsTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetGrabbedWindow)
    RESET_FAKE(SDL_GetMouseFocus)
    RESET_FAKE(SDL_GetKeyboardFocus)
    RESET_FAKE(SDL_GetWindowFromID)
    RESET_FAKE(SDL_GetRenderer)
  }
};

TEST_F(WindowUtilsTest, GetGrabbedWindow)
{
  auto window [[maybe_unused]] = cen::get_grabbed_window();
  ASSERT_EQ(1u, SDL_GetGrabbedWindow_fake.call_count);
}

TEST_F(WindowUtilsTest, GetMouseFocusWindow)
{
  auto window [[maybe_unused]] = cen::get_mouse_focus_window();
  ASSERT_EQ(1u, SDL_GetMouseFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, GetKeyboardFocusWindow)
{
  auto window [[maybe_unused]] = cen::get_keyboard_focus_window();
  ASSERT_EQ(1u, SDL_GetKeyboardFocus_fake.call_count);
}

TEST_F(WindowUtilsTest, GetWindow)
{
  auto window [[maybe_unused]] = cen::get_window(0);
  ASSERT_EQ(1u, SDL_GetWindowFromID_fake.call_count);
}

TEST_F(WindowUtilsTest, GetRenderer)
{
  cen::window_handle window {nullptr};
  auto renderer [[maybe_unused]] = window.get_renderer();
  ASSERT_EQ(1u, SDL_GetRenderer_fake.call_count);
}
