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

#include "centurion/video/window.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_ShowWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_HideWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_RaiseWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_MaximizeWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_MinimizeWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_RestoreWindow, SDL_Window*)
FAKE_VOID_FUNC(SDL_SetWindowBordered, SDL_Window*, SDL_bool)
FAKE_VOID_FUNC(SDL_SetWindowResizable, SDL_Window*, SDL_bool)
FAKE_VOID_FUNC(SDL_SetWindowGrab, SDL_Window*, SDL_bool)
FAKE_VOID_FUNC(SDL_SetWindowIcon, SDL_Window*, SDL_Surface*)
FAKE_VOID_FUNC(SDL_SetWindowPosition, SDL_Window*, int, int)
FAKE_VOID_FUNC(SDL_SetWindowSize, SDL_Window*, int, int)
FAKE_VOID_FUNC(SDL_GetWindowSize, SDL_Window*, int*, int*)
FAKE_VOID_FUNC(SDL_SetWindowTitle, SDL_Window*, const char*)
FAKE_VOID_FUNC(SDL_SetWindowMinimumSize, SDL_Window*, int, int)
FAKE_VOID_FUNC(SDL_SetWindowMaximumSize, SDL_Window*, int, int)
FAKE_VOID_FUNC(SDL_GetWindowMinimumSize, SDL_Window*, int*, int*)
FAKE_VOID_FUNC(SDL_GetWindowMaximumSize, SDL_Window*, int*, int*)
FAKE_VOID_FUNC(SDL_GetWindowPosition, SDL_Window*, int*, int*)
FAKE_VALUE_FUNC(SDL_bool, SDL_GetWindowGrab, SDL_Window*)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsScreenKeyboardShown, SDL_Window*)
FAKE_VALUE_FUNC(Uint32, SDL_GetWindowID, SDL_Window*)
FAKE_VALUE_FUNC(Uint32, SDL_GetWindowPixelFormat, SDL_Window*)
FAKE_VALUE_FUNC(SDL_Surface*, SDL_GetWindowSurface, SDL_Window*)
FAKE_VALUE_FUNC(const char*, SDL_GetWindowTitle, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_CaptureMouse, SDL_bool)
FAKE_VALUE_FUNC(int, SDL_UpdateWindowSurface, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_GetWindowDisplayIndex, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_SetWindowFullscreen, SDL_Window*, Uint32)
FAKE_VALUE_FUNC(int, SDL_SetWindowBrightness, SDL_Window*, float)
FAKE_VALUE_FUNC(int, SDL_SetWindowOpacity, SDL_Window*, float)
FAKE_VALUE_FUNC(int, SDL_GetWindowOpacity, SDL_Window*, float*)
FAKE_VALUE_FUNC(float, SDL_GetWindowBrightness, SDL_Window*)

#if SDL_VERSION_ATLEAST(2, 0, 16)

FAKE_VOID_FUNC(SDL_SetWindowAlwaysOnTop, SDL_Window*, SDL_bool)
FAKE_VOID_FUNC(SDL_SetWindowKeyboardGrab, SDL_Window*, SDL_bool)
FAKE_VALUE_FUNC(int, SDL_FlashWindow, SDL_Window*, SDL_FlashOperation)

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)

FAKE_VALUE_FUNC(int, SDL_SetWindowMouseRect, SDL_Window*, const SDL_Rect*)
FAKE_VALUE_FUNC(const SDL_Rect*, SDL_GetWindowMouseRect, SDL_Window*)

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 0, 22)

FAKE_VALUE_FUNC(SDL_Window*, SDL_RenderGetWindow, SDL_Renderer*)

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
}

class WindowTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_FreeSurface)
    RESET_FAKE(SDL_ShowWindow)
    RESET_FAKE(SDL_HideWindow)
    RESET_FAKE(SDL_SetWindowPosition)
    RESET_FAKE(SDL_RaiseWindow)
    RESET_FAKE(SDL_MaximizeWindow)
    RESET_FAKE(SDL_MinimizeWindow)
    RESET_FAKE(SDL_RestoreWindow)
    RESET_FAKE(SDL_SetWindowBordered)
    RESET_FAKE(SDL_SetWindowResizable)
    RESET_FAKE(SDL_SetWindowGrab)
    RESET_FAKE(SDL_IsScreenKeyboardShown)
    RESET_FAKE(SDL_SetWindowSize)
    RESET_FAKE(SDL_GetWindowSize)
    RESET_FAKE(SDL_SetWindowIcon)
    RESET_FAKE(SDL_SetWindowTitle)
    RESET_FAKE(SDL_SetWindowMinimumSize)
    RESET_FAKE(SDL_SetWindowMaximumSize)
    RESET_FAKE(SDL_GetWindowMinimumSize)
    RESET_FAKE(SDL_GetWindowMaximumSize)
    RESET_FAKE(SDL_GetWindowPosition)
    RESET_FAKE(SDL_SetWindowPosition)
    RESET_FAKE(SDL_GetWindowGrab)
    RESET_FAKE(SDL_GetWindowID)
    RESET_FAKE(SDL_GetWindowPixelFormat)
    RESET_FAKE(SDL_GetWindowSurface)
    RESET_FAKE(SDL_GetWindowTitle)
    RESET_FAKE(SDL_CaptureMouse)
    RESET_FAKE(SDL_UpdateWindowSurface)
    RESET_FAKE(SDL_GetWindowDisplayIndex)
    RESET_FAKE(SDL_SetWindowFullscreen)
    RESET_FAKE(SDL_SetWindowBrightness)
    RESET_FAKE(SDL_SetWindowOpacity)
    RESET_FAKE(SDL_GetWindowOpacity)
    RESET_FAKE(SDL_GetWindowBrightness)

#if SDL_VERSION_ATLEAST(2, 0, 16)

    RESET_FAKE(SDL_SetWindowAlwaysOnTop)
    RESET_FAKE(SDL_SetWindowKeyboardGrab)
    RESET_FAKE(SDL_FlashWindow)

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)

    RESET_FAKE(SDL_SetWindowMouseRect)
    RESET_FAKE(SDL_GetWindowMouseRect)

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 0, 22)

    RESET_FAKE(SDL_RenderGetWindow)

#endif  // SDL_VERSION_ATLEAST(2, 0, 2)
  }

  cen::window_handle mWindow {nullptr};
};

TEST_F(WindowTest, Constructor)
{
  ASSERT_THROW(cen::window {"foo"}, cen::sdl_error);
  ASSERT_EQ(1u, SDL_CreateWindow_fake.call_count);
}

TEST_F(WindowTest, Show)
{
  mWindow.show();
  ASSERT_EQ(1u, SDL_ShowWindow_fake.call_count);
}

TEST_F(WindowTest, Hide)
{
  mWindow.hide();
  ASSERT_EQ(1u, SDL_HideWindow_fake.call_count);
}

TEST_F(WindowTest, Center)
{
  mWindow.center();
  ASSERT_EQ(1u, SDL_SetWindowPosition_fake.call_count);
  ASSERT_EQ(SDL_WINDOWPOS_CENTERED,
            static_cast<unsigned>(SDL_SetWindowPosition_fake.arg1_val));
  ASSERT_EQ(SDL_WINDOWPOS_CENTERED,
            static_cast<unsigned>(SDL_SetWindowPosition_fake.arg2_val));
}

TEST_F(WindowTest, Raise)
{
  mWindow.raise();
  ASSERT_EQ(1u, SDL_RaiseWindow_fake.call_count);
}

TEST_F(WindowTest, Maximize)
{
  mWindow.maximize();
  ASSERT_EQ(1u, SDL_MaximizeWindow_fake.call_count);
}

TEST_F(WindowTest, Minimize)
{
  mWindow.minimize();
  ASSERT_EQ(1u, SDL_MinimizeWindow_fake.call_count);
}

TEST_F(WindowTest, Restore)
{
  mWindow.restore();
  ASSERT_EQ(1u, SDL_RestoreWindow_fake.call_count);
}

TEST_F(WindowTest, UpdateSurface)
{
  mWindow.update_surface();
  ASSERT_EQ(1u, SDL_UpdateWindowSurface_fake.call_count);
}

TEST_F(WindowTest, SetFullscreen)
{
  std::array values {0, 1};
  SET_RETURN_SEQ(SDL_SetWindowFullscreen, values.data(), cen::isize(values));

  ASSERT_TRUE(mWindow.set_fullscreen(true));
  ASSERT_EQ(1u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN,
            static_cast<SDL_WindowFlags>(SDL_SetWindowFullscreen_fake.arg1_val));

  ASSERT_FALSE(mWindow.set_fullscreen(false));
  ASSERT_EQ(2u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(0u, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetFullscreenDesktop)
{
  std::array values {0, 1};
  SET_RETURN_SEQ(SDL_SetWindowFullscreen, values.data(), cen::isize(values));

  ASSERT_TRUE(mWindow.set_fullscreen_desktop(true));
  ASSERT_EQ(1u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_SetWindowFullscreen_fake.arg1_val);

  ASSERT_FALSE(mWindow.set_fullscreen_desktop(false));
  ASSERT_EQ(2u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(0, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetDecorated)
{
  mWindow.set_decorated(true);
  ASSERT_EQ(1u, SDL_SetWindowBordered_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowBordered_fake.arg1_val);

  mWindow.set_decorated(false);
  ASSERT_EQ(2u, SDL_SetWindowBordered_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowBordered_fake.arg1_val);
}

TEST_F(WindowTest, SetResizable)
{
  mWindow.set_resizable(true);
  ASSERT_EQ(1u, SDL_SetWindowResizable_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowResizable_fake.arg1_val);

  mWindow.set_resizable(false);
  ASSERT_EQ(2u, SDL_SetWindowResizable_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowResizable_fake.arg1_val);
}

TEST_F(WindowTest, SetWidth)
{
  mWindow.set_width(123);
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
}

TEST_F(WindowTest, SetHeight)
{
  mWindow.set_height(789);
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(789, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetSize)
{
  mWindow.set_size({123, 456});
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
  ASSERT_EQ(456, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetIcon)
{
  const cen::surface icon;
  mWindow.set_icon(icon);
  ASSERT_EQ(1u, SDL_SetWindowIcon_fake.call_count);
}

TEST_F(WindowTest, SetTitle)
{
  using namespace std::string_literals;
  const auto title = "foobar"s;

  mWindow.set_title(title);
  ASSERT_EQ(1u, SDL_SetWindowTitle_fake.call_count);
  ASSERT_STREQ("foobar", SDL_SetWindowTitle_fake.arg1_val);
}

TEST_F(WindowTest, SetOpacity)
{
  std::array values {0, 1};
  SET_RETURN_SEQ(SDL_SetWindowOpacity, values.data(), cen::isize(values));

  ASSERT_TRUE(mWindow.set_opacity(0.8f));
  ASSERT_EQ(1u, SDL_SetWindowOpacity_fake.call_count);
  ASSERT_EQ(0.8f, SDL_SetWindowOpacity_fake.arg1_val);

  ASSERT_FALSE(mWindow.set_opacity(0.5f));
}

TEST_F(WindowTest, SetMinSize)
{
  mWindow.set_min_size({12, 34});
  ASSERT_EQ(1u, SDL_SetWindowMinimumSize_fake.call_count);
  ASSERT_EQ(12, SDL_SetWindowMinimumSize_fake.arg1_val);
  ASSERT_EQ(34, SDL_SetWindowMinimumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetMaxSize)
{
  mWindow.set_max_size({56, 78});
  ASSERT_EQ(1u, SDL_SetWindowMaximumSize_fake.call_count);
  ASSERT_EQ(56, SDL_SetWindowMaximumSize_fake.arg1_val);
  ASSERT_EQ(78, SDL_SetWindowMaximumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetPosition)
{
  mWindow.set_position({123, 456});
  ASSERT_EQ(1u, SDL_SetWindowPosition_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowPosition_fake.arg1_val);
  ASSERT_EQ(456, SDL_SetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, SetGrabMouse)
{
  mWindow.set_grab_mouse(true);
  ASSERT_EQ(1u, SDL_SetWindowGrab_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowGrab_fake.arg1_val);

  mWindow.set_grab_mouse(false);
  ASSERT_EQ(2u, SDL_SetWindowGrab_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowGrab_fake.arg1_val);
}

TEST_F(WindowTest, SetBrightness)
{
  std::array values {-1, -1, 0};
  SET_RETURN_SEQ(SDL_SetWindowBrightness, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.set_brightness(-0.1f));
  ASSERT_EQ(1u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(0, SDL_SetWindowBrightness_fake.arg1_val);

  ASSERT_FALSE(mWindow.set_brightness(1.1f));
  ASSERT_EQ(2u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(1, SDL_SetWindowBrightness_fake.arg1_val);

  ASSERT_TRUE(mWindow.set_brightness(0.4f));
  ASSERT_EQ(3u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(0.4f, SDL_SetWindowBrightness_fake.arg1_val);
}

TEST_F(WindowTest, SetCapturingMouse)
{
  std::array values {0, 1};
  SET_RETURN_SEQ(SDL_CaptureMouse, values.data(), cen::isize(values));

  ASSERT_TRUE(cen::window::set_capturing_mouse(true));
  ASSERT_EQ(1u, SDL_CaptureMouse_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_CaptureMouse_fake.arg0_val);

  ASSERT_FALSE(cen::window::set_capturing_mouse(false));
  ASSERT_EQ(2u, SDL_CaptureMouse_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_CaptureMouse_fake.arg0_val);
}

TEST_F(WindowTest, GrabbingMouse)
{
  const auto grabbing [[maybe_unused]] = mWindow.is_grabbing_mouse();
  ASSERT_EQ(1u, SDL_GetWindowGrab_fake.call_count);
}

TEST_F(WindowTest, IsScreenKeyboardShown)
{
  std::array values {SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_IsScreenKeyboardShown, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_screen_keyboard_shown());
  ASSERT_TRUE(mWindow.is_screen_keyboard_shown());
  ASSERT_EQ(2u, SDL_IsScreenKeyboardShown_fake.call_count);
}

TEST_F(WindowTest, HasInputFocus)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_MOUSE_FOCUS),
                     static_cast<Uint32>(SDL_WINDOW_INPUT_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.has_input_focus());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.has_input_focus());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, HasMouseFocus)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_FULLSCREEN),
                     static_cast<Uint32>(SDL_WINDOW_MOUSE_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.has_mouse_focus());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.has_mouse_focus());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsDecorated)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_FULLSCREEN_DESKTOP),
                     static_cast<Uint32>(SDL_WINDOW_BORDERLESS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_TRUE(mWindow.is_decorated());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_FALSE(mWindow.is_decorated());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsResizable)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_OPENGL),
                     static_cast<Uint32>(SDL_WINDOW_RESIZABLE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_resizable());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_resizable());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreen)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_OPENGL),
                     static_cast<Uint32>(SDL_WINDOW_FULLSCREEN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_fullscreen());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_fullscreen());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreenDesktop)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_OPENGL),
                     static_cast<Uint32>(SDL_WINDOW_FULLSCREEN_DESKTOP)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_fullscreen_desktop());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_fullscreen_desktop());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVisible)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_OPENGL),
                     static_cast<Uint32>(SDL_WINDOW_SHOWN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_visible());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_visible());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsOpenGL)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_HIDDEN),
                     static_cast<Uint32>(SDL_WINDOW_OPENGL)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_opengl());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_opengl());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVulkan)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_SHOWN),
                     static_cast<Uint32>(SDL_WINDOW_VULKAN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_vulkan());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_vulkan());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsForeign)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_SHOWN),
                     static_cast<Uint32>(SDL_WINDOW_FOREIGN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_foreign());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_foreign());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsCapturingMouse)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_VULKAN),
                     static_cast<Uint32>(SDL_WINDOW_MOUSE_CAPTURE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_capturing_mouse());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_capturing_mouse());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMinimized)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_OPENGL),
                     static_cast<Uint32>(SDL_WINDOW_MINIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_minimized());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_minimized());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMaximized)
{
  std::array values {static_cast<Uint32>(SDL_WINDOW_HIDDEN),
                     static_cast<Uint32>(SDL_WINDOW_MAXIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_maximized());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(mWindow.is_maximized());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsAlwaysOnTop)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::always_on_top}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_always_on_top());
  ASSERT_TRUE(mWindow.is_always_on_top());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, HasGrabbedInput)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::input_grabbed}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.has_grabbed_input());
  ASSERT_TRUE(mWindow.has_grabbed_input());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsHighDPI)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::allow_high_dpi}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_high_dpi());
  ASSERT_TRUE(mWindow.is_high_dpi());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsHidden)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::hidden}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_hidden());
  ASSERT_TRUE(mWindow.is_hidden());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsUtility)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::utility}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_utility());
  ASSERT_TRUE(mWindow.is_utility());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsTooltip)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::tooltip}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_tooltip());
  ASSERT_TRUE(mWindow.is_tooltip());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsPopupMenu)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::popup_menu}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_popup_menu());
  ASSERT_TRUE(mWindow.is_popup_menu());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsExcludedFromTaskbar)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::skip_taskbar}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_excluded_from_taskbar());
  ASSERT_TRUE(mWindow.is_excluded_from_taskbar());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(WindowTest, IsMetal)
{
  std::array values {Uint32 {cen::window::fullscreen}, Uint32 {cen::window::metal}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.is_metal());
  ASSERT_TRUE(mWindow.is_metal());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(WindowTest, GetBrightness)
{
  const auto brightness [[maybe_unused]] = mWindow.brightness();
  ASSERT_EQ(1u, SDL_GetWindowBrightness_fake.call_count);
}

TEST_F(WindowTest, GetOpacity)
{
  const auto opacity [[maybe_unused]] = mWindow.opacity();
  ASSERT_EQ(1u, SDL_GetWindowOpacity_fake.call_count);
}

TEST_F(WindowTest, X)
{
  const auto x [[maybe_unused]] = mWindow.x();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
  ASSERT_NE(nullptr, SDL_GetWindowPosition_fake.arg1_val);
}

TEST_F(WindowTest, Y)
{
  const auto y [[maybe_unused]] = mWindow.y();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
  ASSERT_NE(nullptr, SDL_GetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, GetID)
{
  const auto id [[maybe_unused]] = mWindow.id();
  ASSERT_EQ(1u, SDL_GetWindowID_fake.call_count);
}

TEST_F(WindowTest, GetDisplayIndex)
{
  std::array values {-1, 7};
  SET_RETURN_SEQ(SDL_GetWindowDisplayIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.display_index().has_value());
  ASSERT_EQ(1u, SDL_GetWindowDisplayIndex_fake.call_count);

  ASSERT_EQ(7, mWindow.display_index());
  ASSERT_EQ(2u, SDL_GetWindowDisplayIndex_fake.call_count);
}

TEST_F(WindowTest, Position)
{
  const auto pos [[maybe_unused]] = mWindow.position();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
}

TEST_F(WindowTest, GetMinSize)
{
  const auto size [[maybe_unused]] = mWindow.min_size();
  ASSERT_EQ(1u, SDL_GetWindowMinimumSize_fake.call_count);
}

TEST_F(WindowTest, GetMaxSize)
{
  const auto size [[maybe_unused]] = mWindow.max_size();
  ASSERT_EQ(1u, SDL_GetWindowMaximumSize_fake.call_count);
}

TEST_F(WindowTest, Width)
{
  const auto width [[maybe_unused]] = mWindow.width();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Height)
{
  const auto height [[maybe_unused]] = mWindow.height();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Size)
{
  const auto size [[maybe_unused]] = mWindow.size();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, CheckFlag)
{
  const auto a [[maybe_unused]] = mWindow.check_flag(cen::window_handle::fullscreen);
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, GetFlags)
{
  const auto flags [[maybe_unused]] = mWindow.flags();
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, GetPixelFormat)
{
  const auto format [[maybe_unused]] = mWindow.format();
  ASSERT_EQ(1u, SDL_GetWindowPixelFormat_fake.call_count);
}

TEST_F(WindowTest, GetSurface)
{
  const auto surface [[maybe_unused]] = mWindow.get_surface();
  ASSERT_EQ(1u, SDL_GetWindowSurface_fake.call_count);
}

TEST_F(WindowTest, GetTitle)
{
  SDL_GetWindowTitle_fake.return_val = "";
  const auto title [[maybe_unused]] = mWindow.title();
  ASSERT_EQ(1u, SDL_GetWindowTitle_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(WindowTest, SetAlwaysOnTop)
{
  mWindow.set_always_on_top(true);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowAlwaysOnTop_fake.arg1_val);

  mWindow.set_always_on_top(false);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowAlwaysOnTop_fake.arg1_val);
}

TEST_F(WindowTest, SetGrabKeyboard)
{
  mWindow.set_grab_keyboard(true);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowKeyboardGrab_fake.arg1_val);

  mWindow.set_grab_keyboard(false);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowKeyboardGrab_fake.arg1_val);
}

TEST_F(WindowTest, Flash)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_FlashWindow, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.flash());
  ASSERT_EQ(SDL_FLASH_BRIEFLY, SDL_FlashWindow_fake.arg1_val);

  ASSERT_TRUE(mWindow.flash(cen::flash_op::until_focused));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, SDL_FlashWindow_fake.arg1_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

#if SDL_VERSION_ATLEAST(2, 0, 18)

TEST_F(WindowTest, ResetMouseRect)
{
  mWindow.reset_mouse_rect();
  ASSERT_EQ(1u, SDL_SetWindowMouseRect_fake.call_count);
  ASSERT_EQ(nullptr, SDL_SetWindowMouseRect_fake.arg1_val);
}

TEST_F(WindowTest, SetMouseRect)
{
  std::array values {-1, 0};
  SET_RETURN_SEQ(SDL_SetWindowMouseRect, values.data(), cen::isize(values));

  const cen::irect region {12, 94, 150, 100};

  ASSERT_EQ(cen::failure, mWindow.set_mouse_rect(region));
  ASSERT_EQ(cen::success, mWindow.set_mouse_rect(region));

  ASSERT_EQ(2u, SDL_SetWindowMouseRect_fake.call_count);
}

TEST_F(WindowTest, MouseRect)
{
  const SDL_Rect region {75, 32, 83, 53};

  std::array<const SDL_Rect*, 2> values {nullptr, &region};
  SET_RETURN_SEQ(SDL_GetWindowMouseRect, values.data(), cen::isize(values));

  ASSERT_FALSE(mWindow.mouse_rect().has_value());
  ASSERT_EQ(cen::irect(75, 32, 83, 53), mWindow.mouse_rect());

  ASSERT_EQ(2u, SDL_GetWindowMouseRect_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

#if SDL_VERSION_ATLEAST(2, 0, 22)

TEST_F(WindowTest, GetWindowFromRenderer)
{
  cen::renderer_handle renderer {nullptr};
  auto window [[maybe_unused]] = cen::get_window(renderer);
  ASSERT_EQ(1u, SDL_RenderGetWindow_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 22)
