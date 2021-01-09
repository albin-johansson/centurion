#include "window.hpp"

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
FAKE_VALUE_FUNC(Uint32, SDL_GetWindowFlags, SDL_Window*)
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
}

class WindowTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_FreeSurface);
    RESET_FAKE(SDL_ShowWindow);
    RESET_FAKE(SDL_HideWindow);
    RESET_FAKE(SDL_SetWindowPosition);
    RESET_FAKE(SDL_RaiseWindow);
    RESET_FAKE(SDL_MaximizeWindow);
    RESET_FAKE(SDL_MinimizeWindow);
    RESET_FAKE(SDL_SetWindowBordered);
    RESET_FAKE(SDL_SetWindowResizable);
    RESET_FAKE(SDL_SetWindowGrab);
    RESET_FAKE(SDL_SetWindowSize);
    RESET_FAKE(SDL_GetWindowSize);
    RESET_FAKE(SDL_SetWindowIcon);
    RESET_FAKE(SDL_SetWindowTitle);
    RESET_FAKE(SDL_SetWindowMinimumSize);
    RESET_FAKE(SDL_SetWindowMaximumSize);
    RESET_FAKE(SDL_GetWindowMinimumSize);
    RESET_FAKE(SDL_GetWindowMaximumSize);
    RESET_FAKE(SDL_GetWindowPosition);
    RESET_FAKE(SDL_SetWindowPosition);
    RESET_FAKE(SDL_GetWindowGrab);
    RESET_FAKE(SDL_GetWindowFlags);
    RESET_FAKE(SDL_GetWindowID);
    RESET_FAKE(SDL_GetWindowPixelFormat);
    RESET_FAKE(SDL_GetWindowSurface);
    RESET_FAKE(SDL_GetWindowTitle);
    RESET_FAKE(SDL_CaptureMouse);
    RESET_FAKE(SDL_UpdateWindowSurface);
    RESET_FAKE(SDL_GetWindowDisplayIndex);
    RESET_FAKE(SDL_SetWindowFullscreen);
    RESET_FAKE(SDL_SetWindowBrightness);
    RESET_FAKE(SDL_SetWindowOpacity);
    RESET_FAKE(SDL_GetWindowOpacity);
    RESET_FAKE(SDL_GetWindowBrightness);
  }

  cen::window_handle m_window{nullptr};
};

TEST_F(WindowTest, Show)
{
  m_window.show();
  EXPECT_EQ(1, SDL_ShowWindow_fake.call_count);
}

TEST_F(WindowTest, Hide)
{
  m_window.hide();
  EXPECT_EQ(1, SDL_HideWindow_fake.call_count);
}

TEST_F(WindowTest, Center)
{
  m_window.center();
  EXPECT_EQ(1, SDL_SetWindowPosition_fake.call_count);
  EXPECT_EQ(SDL_WINDOWPOS_CENTERED, SDL_SetWindowPosition_fake.arg1_val);
  EXPECT_EQ(SDL_WINDOWPOS_CENTERED, SDL_SetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, Raise)
{
  m_window.raise();
  EXPECT_EQ(1, SDL_RaiseWindow_fake.call_count);
}

TEST_F(WindowTest, Maximize)
{
  m_window.maximize();
  EXPECT_EQ(1, SDL_MaximizeWindow_fake.call_count);
}

TEST_F(WindowTest, Minimize)
{
  m_window.minimize();
  EXPECT_EQ(1, SDL_MinimizeWindow_fake.call_count);
}

TEST_F(WindowTest, UpdateSurface)
{
  m_window.update_surface();
  EXPECT_EQ(1, SDL_UpdateWindowSurface_fake.call_count);
}

TEST_F(WindowTest, SetFullscreen)
{
  m_window.set_fullscreen(true);
  EXPECT_EQ(1, SDL_SetWindowFullscreen_fake.call_count);
  EXPECT_EQ(SDL_WINDOW_FULLSCREEN, SDL_SetWindowFullscreen_fake.arg1_val);

  m_window.set_fullscreen(false);
  EXPECT_EQ(2, SDL_SetWindowFullscreen_fake.call_count);
  EXPECT_EQ(0, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetFullscreenDesktop)
{
  m_window.set_fullscreen_desktop(true);
  EXPECT_EQ(1, SDL_SetWindowFullscreen_fake.call_count);
  EXPECT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP,
            SDL_SetWindowFullscreen_fake.arg1_val);

  m_window.set_fullscreen_desktop(false);
  EXPECT_EQ(2, SDL_SetWindowFullscreen_fake.call_count);
  EXPECT_EQ(0, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetDecorated)
{
  m_window.set_decorated(true);
  EXPECT_EQ(1, SDL_SetWindowBordered_fake.call_count);
  EXPECT_EQ(SDL_TRUE, SDL_SetWindowBordered_fake.arg1_val);

  m_window.set_decorated(false);
  EXPECT_EQ(2, SDL_SetWindowBordered_fake.call_count);
  EXPECT_EQ(SDL_FALSE, SDL_SetWindowBordered_fake.arg1_val);
}

TEST_F(WindowTest, SetResizable)
{
  m_window.set_resizable(true);
  EXPECT_EQ(1, SDL_SetWindowResizable_fake.call_count);
  EXPECT_EQ(SDL_TRUE, SDL_SetWindowResizable_fake.arg1_val);

  m_window.set_resizable(false);
  EXPECT_EQ(2, SDL_SetWindowResizable_fake.call_count);
  EXPECT_EQ(SDL_FALSE, SDL_SetWindowResizable_fake.arg1_val);
}

TEST_F(WindowTest, SetWidth)
{
  m_window.set_width(123);
  EXPECT_EQ(1, SDL_SetWindowSize_fake.call_count);
  EXPECT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
}

TEST_F(WindowTest, SetHeight)
{
  m_window.set_height(789);
  EXPECT_EQ(1, SDL_SetWindowSize_fake.call_count);
  EXPECT_EQ(789, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetSize)
{
  m_window.set_size({123, 456});
  EXPECT_EQ(1, SDL_SetWindowSize_fake.call_count);
  EXPECT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
  EXPECT_EQ(456, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetIcon)
{
  const cen::surface icon;
  m_window.set_icon(icon);
  EXPECT_EQ(1, SDL_SetWindowIcon_fake.call_count);
}

TEST_F(WindowTest, SetTitle)
{
  m_window.set_title("foobar");
  EXPECT_EQ(1, SDL_SetWindowTitle_fake.call_count);
  EXPECT_STREQ("foobar", SDL_SetWindowTitle_fake.arg1_val);
}

TEST_F(WindowTest, SetOpacity)
{
  m_window.set_opacity(0.8f);
  EXPECT_EQ(1, SDL_SetWindowOpacity_fake.call_count);
  EXPECT_EQ(0.8f, SDL_SetWindowOpacity_fake.arg1_val);
}

TEST_F(WindowTest, SetMinSize)
{
  m_window.set_min_size({12, 34});
  EXPECT_EQ(1, SDL_SetWindowMinimumSize_fake.call_count);
  EXPECT_EQ(12, SDL_SetWindowMinimumSize_fake.arg1_val);
  EXPECT_EQ(34, SDL_SetWindowMinimumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetMaxSize)
{
  m_window.set_max_size({56, 78});
  EXPECT_EQ(1, SDL_SetWindowMaximumSize_fake.call_count);
  EXPECT_EQ(56, SDL_SetWindowMaximumSize_fake.arg1_val);
  EXPECT_EQ(78, SDL_SetWindowMaximumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetPosition)
{
  m_window.set_position({123, 456});
  EXPECT_EQ(1, SDL_SetWindowPosition_fake.call_count);
  EXPECT_EQ(123, SDL_SetWindowPosition_fake.arg1_val);
  EXPECT_EQ(456, SDL_SetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, SetGrabMouse)
{
  m_window.set_grab_mouse(true);
  EXPECT_EQ(1, SDL_SetWindowGrab_fake.call_count);
  EXPECT_EQ(SDL_TRUE, SDL_SetWindowGrab_fake.arg1_val);

  m_window.set_grab_mouse(false);
  EXPECT_EQ(2, SDL_SetWindowGrab_fake.call_count);
  EXPECT_EQ(SDL_FALSE, SDL_SetWindowGrab_fake.arg1_val);
}

TEST_F(WindowTest, SetBrightness)
{
  std::array values{-1, -1, 0};
  SET_RETURN_SEQ(SDL_SetWindowBrightness,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.set_brightness(-0.1f));
  EXPECT_EQ(1, SDL_SetWindowBrightness_fake.call_count);
  EXPECT_EQ(0, SDL_SetWindowBrightness_fake.arg1_val);

  EXPECT_FALSE(m_window.set_brightness(1.1f));
  EXPECT_EQ(2, SDL_SetWindowBrightness_fake.call_count);
  EXPECT_EQ(1, SDL_SetWindowBrightness_fake.arg1_val);

  EXPECT_TRUE(m_window.set_brightness(0.4f));
  EXPECT_EQ(3, SDL_SetWindowBrightness_fake.call_count);
  EXPECT_EQ(0.4f, SDL_SetWindowBrightness_fake.arg1_val);
}

TEST_F(WindowTest, SetCapturingMouse)
{
  cen::window::set_capturing_mouse(true);
  EXPECT_EQ(1, SDL_CaptureMouse_fake.call_count);
  EXPECT_EQ(SDL_TRUE, SDL_CaptureMouse_fake.arg0_val);

  cen::window::set_capturing_mouse(false);
  EXPECT_EQ(2, SDL_CaptureMouse_fake.call_count);
  EXPECT_EQ(SDL_FALSE, SDL_CaptureMouse_fake.arg0_val);
}

TEST_F(WindowTest, GrabbingMouse)
{
  const auto grabbing [[maybe_unused]] = m_window.grabbing_mouse();
  EXPECT_EQ(1, SDL_GetWindowGrab_fake.call_count);
}

TEST_F(WindowTest, HasInputFocus)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_MOUSE_FOCUS),
                    static_cast<cen::u32>(SDL_WINDOW_INPUT_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.has_input_focus());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.has_input_focus());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, HasMouseFocus)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_FULLSCREEN),
                    static_cast<cen::u32>(SDL_WINDOW_MOUSE_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.has_mouse_focus());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.has_mouse_focus());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsDecorated)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_FULLSCREEN_DESKTOP),
                    static_cast<cen::u32>(SDL_WINDOW_BORDERLESS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_TRUE(m_window.is_decorated());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_FALSE(m_window.is_decorated());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsResizable)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_OPENGL),
                    static_cast<cen::u32>(SDL_WINDOW_RESIZABLE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_resizable());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_resizable());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreen)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_OPENGL),
                    static_cast<cen::u32>(SDL_WINDOW_FULLSCREEN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_fullscreen());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_fullscreen());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreenDesktop)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_OPENGL),
                    static_cast<cen::u32>(SDL_WINDOW_FULLSCREEN_DESKTOP)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_fullscreen_desktop());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_fullscreen_desktop());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVisible)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_OPENGL),
                    static_cast<cen::u32>(SDL_WINDOW_SHOWN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_visible());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_visible());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsOpenGL)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_HIDDEN),
                    static_cast<cen::u32>(SDL_WINDOW_OPENGL)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_opengl());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_opengl());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVulkan)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_SHOWN),
                    static_cast<cen::u32>(SDL_WINDOW_VULKAN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_vulkan());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_vulkan());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsForeign)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_SHOWN),
                    static_cast<cen::u32>(SDL_WINDOW_FOREIGN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_foreign());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_foreign());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsCapturingMouse)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_VULKAN),
                    static_cast<cen::u32>(SDL_WINDOW_MOUSE_CAPTURE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_capturing_mouse());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_capturing_mouse());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMinimized)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_OPENGL),
                    static_cast<cen::u32>(SDL_WINDOW_MINIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_minimized());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_minimized());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMaximized)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_HIDDEN),
                    static_cast<cen::u32>(SDL_WINDOW_MAXIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.is_maximized());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.is_maximized());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, AlwaysOnTop)
{
  std::array values{static_cast<cen::u32>(SDL_WINDOW_FULLSCREEN),
                    static_cast<cen::u32>(SDL_WINDOW_ALWAYS_ON_TOP)};
  SET_RETURN_SEQ(SDL_GetWindowFlags,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.always_on_top());
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);

  EXPECT_TRUE(m_window.always_on_top());
  EXPECT_EQ(2, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, Brightness)
{
  const auto brightness [[maybe_unused]] = m_window.brightness();
  EXPECT_EQ(1, SDL_GetWindowBrightness_fake.call_count);
}

TEST_F(WindowTest, Opacity)
{
  const auto opacity [[maybe_unused]] = m_window.opacity();
  EXPECT_EQ(1, SDL_GetWindowOpacity_fake.call_count);
}

TEST_F(WindowTest, X)
{
  const auto x [[maybe_unused]] = m_window.x();
  EXPECT_EQ(1, SDL_GetWindowPosition_fake.call_count);
  EXPECT_NE(nullptr, SDL_GetWindowPosition_fake.arg1_val);
  EXPECT_EQ(nullptr, SDL_GetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, Y)
{
  const auto y [[maybe_unused]] = m_window.y();
  EXPECT_EQ(1, SDL_GetWindowPosition_fake.call_count);
  EXPECT_EQ(nullptr, SDL_GetWindowPosition_fake.arg1_val);
  EXPECT_NE(nullptr, SDL_GetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, Id)
{
  const auto id [[maybe_unused]] = m_window.id();
  EXPECT_EQ(1, SDL_GetWindowID_fake.call_count);
}

TEST_F(WindowTest, DisplayIndex)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_GetWindowDisplayIndex,
                 values.data(),
                 static_cast<int>(values.size()));

  EXPECT_FALSE(m_window.display_index().has_value());
  EXPECT_EQ(1, SDL_GetWindowDisplayIndex_fake.call_count);

  EXPECT_EQ(7, m_window.display_index());
  EXPECT_EQ(2, SDL_GetWindowDisplayIndex_fake.call_count);
}

TEST_F(WindowTest, Position)
{
  const auto pos [[maybe_unused]] = m_window.position();
  EXPECT_EQ(1, SDL_GetWindowPosition_fake.call_count);
}

TEST_F(WindowTest, MinSize)
{
  const auto size [[maybe_unused]] = m_window.min_size();
  EXPECT_EQ(1, SDL_GetWindowMinimumSize_fake.call_count);
}

TEST_F(WindowTest, MaxSize)
{
  const auto size [[maybe_unused]] = m_window.max_size();
  EXPECT_EQ(1, SDL_GetWindowMaximumSize_fake.call_count);
}

TEST_F(WindowTest, Width)
{
  const auto width [[maybe_unused]] = m_window.width();
  EXPECT_EQ(1, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Height)
{
  const auto height [[maybe_unused]] = m_window.height();
  EXPECT_EQ(1, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Size)
{
  const auto size [[maybe_unused]] = m_window.size();
  EXPECT_EQ(1, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, CheckFlag)
{
  const auto full [[maybe_unused]] = m_window.check_flag(SDL_WINDOW_FULLSCREEN);
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, Flags)
{
  const auto flags [[maybe_unused]] = m_window.flags();
  EXPECT_EQ(1, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, GetPixelFormat)
{
  const auto format [[maybe_unused]] = m_window.get_pixel_format();
  EXPECT_EQ(1, SDL_GetWindowPixelFormat_fake.call_count);
}

TEST_F(WindowTest, GetSurface)
{
  const auto surface [[maybe_unused]] = m_window.get_surface();
  EXPECT_EQ(1, SDL_GetWindowSurface_fake.call_count);
}

TEST_F(WindowTest, Title)
{
  SDL_GetWindowTitle_fake.return_val = "";
  const auto title [[maybe_unused]] = m_window.title();
  EXPECT_EQ(1, SDL_GetWindowTitle_fake.call_count);
}
