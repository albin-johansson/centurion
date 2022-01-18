#include "window.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C"
{
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
  }

  cen::WindowHandle m_window{nullptr};
};

TEST_F(WindowTest, Constructor)
{
  ASSERT_THROW(cen::Window{"foo"}, cen::sdl_error);
  ASSERT_EQ(1u, SDL_CreateWindow_fake.call_count);
}

TEST_F(WindowTest, Show)
{
  m_window.Show();
  ASSERT_EQ(1u, SDL_ShowWindow_fake.call_count);
}

TEST_F(WindowTest, Hide)
{
  m_window.Hide();
  ASSERT_EQ(1u, SDL_HideWindow_fake.call_count);
}

TEST_F(WindowTest, Center)
{
  m_window.Center();
  ASSERT_EQ(1u, SDL_SetWindowPosition_fake.call_count);
  ASSERT_EQ(SDL_WINDOWPOS_CENTERED,
            static_cast<unsigned>(SDL_SetWindowPosition_fake.arg1_val));
  ASSERT_EQ(SDL_WINDOWPOS_CENTERED,
            static_cast<unsigned>(SDL_SetWindowPosition_fake.arg2_val));
}

TEST_F(WindowTest, Raise)
{
  m_window.Raise();
  ASSERT_EQ(1u, SDL_RaiseWindow_fake.call_count);
}

TEST_F(WindowTest, Maximize)
{
  m_window.Maximize();
  ASSERT_EQ(1u, SDL_MaximizeWindow_fake.call_count);
}

TEST_F(WindowTest, Minimize)
{
  m_window.Minimize();
  ASSERT_EQ(1u, SDL_MinimizeWindow_fake.call_count);
}

TEST_F(WindowTest, Restore)
{
  m_window.Restore();
  ASSERT_EQ(1u, SDL_RestoreWindow_fake.call_count);
}

TEST_F(WindowTest, UpdateSurface)
{
  m_window.UpdateSurface();
  ASSERT_EQ(1u, SDL_UpdateWindowSurface_fake.call_count);
}

TEST_F(WindowTest, SetFullscreen)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(SDL_SetWindowFullscreen, values.data(), cen::isize(values));

  ASSERT_TRUE(m_window.SetFullscreen(true));
  ASSERT_EQ(1u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN,
            static_cast<SDL_WindowFlags>(SDL_SetWindowFullscreen_fake.arg1_val));

  ASSERT_FALSE(m_window.SetFullscreen(false));
  ASSERT_EQ(2u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(0u, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetFullscreenDesktop)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(SDL_SetWindowFullscreen, values.data(), cen::isize(values));

  ASSERT_TRUE(m_window.SetFullscreenDesktop(true));
  ASSERT_EQ(1u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_SetWindowFullscreen_fake.arg1_val);

  ASSERT_FALSE(m_window.SetFullscreenDesktop(false));
  ASSERT_EQ(2u, SDL_SetWindowFullscreen_fake.call_count);
  ASSERT_EQ(0, SDL_SetWindowFullscreen_fake.arg1_val);
}

TEST_F(WindowTest, SetDecorated)
{
  m_window.SetDecorated(true);
  ASSERT_EQ(1u, SDL_SetWindowBordered_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowBordered_fake.arg1_val);

  m_window.SetDecorated(false);
  ASSERT_EQ(2u, SDL_SetWindowBordered_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowBordered_fake.arg1_val);
}

TEST_F(WindowTest, SetResizable)
{
  m_window.SetResizable(true);
  ASSERT_EQ(1u, SDL_SetWindowResizable_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowResizable_fake.arg1_val);

  m_window.SetResizable(false);
  ASSERT_EQ(2u, SDL_SetWindowResizable_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowResizable_fake.arg1_val);
}

TEST_F(WindowTest, SetWidth)
{
  m_window.SetWidth(123);
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
}

TEST_F(WindowTest, SetHeight)
{
  m_window.SetHeight(789);
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(789, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetSize)
{
  m_window.SetSize({123, 456});
  ASSERT_EQ(1u, SDL_SetWindowSize_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowSize_fake.arg1_val);
  ASSERT_EQ(456, SDL_SetWindowSize_fake.arg2_val);
}

TEST_F(WindowTest, SetIcon)
{
  const cen::surface icon;
  m_window.SetIcon(icon);
  ASSERT_EQ(1u, SDL_SetWindowIcon_fake.call_count);
}

TEST_F(WindowTest, SetTitle)
{
  using namespace std::string_literals;
  const auto title = "foobar"s;

  m_window.SetTitle(title);
  ASSERT_EQ(1u, SDL_SetWindowTitle_fake.call_count);
  ASSERT_STREQ("foobar", SDL_SetWindowTitle_fake.arg1_val);
}

TEST_F(WindowTest, SetOpacity)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(SDL_SetWindowOpacity, values.data(), cen::isize(values));

  ASSERT_TRUE(m_window.SetOpacity(0.8f));
  ASSERT_EQ(1u, SDL_SetWindowOpacity_fake.call_count);
  ASSERT_EQ(0.8f, SDL_SetWindowOpacity_fake.arg1_val);

  ASSERT_FALSE(m_window.SetOpacity(0.5f));
}

TEST_F(WindowTest, SetMinSize)
{
  m_window.SetMinSize({12, 34});
  ASSERT_EQ(1u, SDL_SetWindowMinimumSize_fake.call_count);
  ASSERT_EQ(12, SDL_SetWindowMinimumSize_fake.arg1_val);
  ASSERT_EQ(34, SDL_SetWindowMinimumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetMaxSize)
{
  m_window.SetMaxSize({56, 78});
  ASSERT_EQ(1u, SDL_SetWindowMaximumSize_fake.call_count);
  ASSERT_EQ(56, SDL_SetWindowMaximumSize_fake.arg1_val);
  ASSERT_EQ(78, SDL_SetWindowMaximumSize_fake.arg2_val);
}

TEST_F(WindowTest, SetPosition)
{
  m_window.SetPosition({123, 456});
  ASSERT_EQ(1u, SDL_SetWindowPosition_fake.call_count);
  ASSERT_EQ(123, SDL_SetWindowPosition_fake.arg1_val);
  ASSERT_EQ(456, SDL_SetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, SetGrabMouse)
{
  m_window.SetGrabMouse(true);
  ASSERT_EQ(1u, SDL_SetWindowGrab_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowGrab_fake.arg1_val);

  m_window.SetGrabMouse(false);
  ASSERT_EQ(2u, SDL_SetWindowGrab_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowGrab_fake.arg1_val);
}

TEST_F(WindowTest, SetBrightness)
{
  std::array values{-1, -1, 0};
  SET_RETURN_SEQ(SDL_SetWindowBrightness, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.SetBrightness(-0.1f));
  ASSERT_EQ(1u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(0, SDL_SetWindowBrightness_fake.arg1_val);

  ASSERT_FALSE(m_window.SetBrightness(1.1f));
  ASSERT_EQ(2u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(1, SDL_SetWindowBrightness_fake.arg1_val);

  ASSERT_TRUE(m_window.SetBrightness(0.4f));
  ASSERT_EQ(3u, SDL_SetWindowBrightness_fake.call_count);
  ASSERT_EQ(0.4f, SDL_SetWindowBrightness_fake.arg1_val);
}

TEST_F(WindowTest, SetCapturingMouse)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(SDL_CaptureMouse, values.data(), cen::isize(values));

  ASSERT_TRUE(cen::Window::SetCapturingMouse(true));
  ASSERT_EQ(1u, SDL_CaptureMouse_fake.call_count);
  ASSERT_EQ(SDL_TRUE, SDL_CaptureMouse_fake.arg0_val);

  ASSERT_FALSE(cen::Window::SetCapturingMouse(false));
  ASSERT_EQ(2u, SDL_CaptureMouse_fake.call_count);
  ASSERT_EQ(SDL_FALSE, SDL_CaptureMouse_fake.arg0_val);
}

TEST_F(WindowTest, GrabbingMouse)
{
  const auto grabbing [[maybe_unused]] = m_window.IsGrabbingMouse();
  ASSERT_EQ(1u, SDL_GetWindowGrab_fake.call_count);
}

TEST_F(WindowTest, IsScreenKeyboardShown)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_IsScreenKeyboardShown, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsScreenKeyboardShown());
  ASSERT_TRUE(m_window.IsScreenKeyboardShown());
  ASSERT_EQ(2u, SDL_IsScreenKeyboardShown_fake.call_count);
}

TEST_F(WindowTest, HasInputFocus)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_MOUSE_FOCUS),
                    static_cast<Uint32>(SDL_WINDOW_INPUT_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.HasInputFocus());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.HasInputFocus());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, HasMouseFocus)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_FULLSCREEN),
                    static_cast<Uint32>(SDL_WINDOW_MOUSE_FOCUS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.HasMouseFocus());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.HasMouseFocus());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsDecorated)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_FULLSCREEN_DESKTOP),
                    static_cast<Uint32>(SDL_WINDOW_BORDERLESS)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_TRUE(m_window.IsDecorated());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_FALSE(m_window.IsDecorated());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsResizable)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_OPENGL),
                    static_cast<Uint32>(SDL_WINDOW_RESIZABLE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsResizable());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsResizable());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreen)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_OPENGL),
                    static_cast<Uint32>(SDL_WINDOW_FULLSCREEN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsFullscreen());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsFullscreen());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsFullscreenDesktop)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_OPENGL),
                    static_cast<Uint32>(SDL_WINDOW_FULLSCREEN_DESKTOP)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsFullscreenDesktop());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsFullscreenDesktop());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVisible)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_OPENGL),
                    static_cast<Uint32>(SDL_WINDOW_SHOWN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsVisible());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsVisible());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsOpenGL)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_HIDDEN),
                    static_cast<Uint32>(SDL_WINDOW_OPENGL)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsOpenGL());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsOpenGL());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsVulkan)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_SHOWN),
                    static_cast<Uint32>(SDL_WINDOW_VULKAN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsVulkan());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsVulkan());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsForeign)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_SHOWN),
                    static_cast<Uint32>(SDL_WINDOW_FOREIGN)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsForeign());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsForeign());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsCapturingMouse)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_VULKAN),
                    static_cast<Uint32>(SDL_WINDOW_MOUSE_CAPTURE)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsCapturingMouse());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsCapturingMouse());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMinimized)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_OPENGL),
                    static_cast<Uint32>(SDL_WINDOW_MINIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsMinimized());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsMinimized());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsMaximized)
{
  std::array values{static_cast<Uint32>(SDL_WINDOW_HIDDEN),
                    static_cast<Uint32>(SDL_WINDOW_MAXIMIZED)};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsMaximized());
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);

  ASSERT_TRUE(m_window.IsMaximized());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsAlwaysOnTop)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::AlwaysOnTop}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsAlwaysOnTop());
  ASSERT_TRUE(m_window.IsAlwaysOnTop());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, HasGrabbedInput)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::InputGrabbed}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.HasGrabbedInput());
  ASSERT_TRUE(m_window.HasGrabbedInput());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsHighDPI)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::AllowHighDPI}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsHighDPI());
  ASSERT_TRUE(m_window.IsHighDPI());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsHidden)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::Hidden}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsHidden());
  ASSERT_TRUE(m_window.IsHidden());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsUtility)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::Utility}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsUtility());
  ASSERT_TRUE(m_window.IsUtility());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsTooltip)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::Tooltip}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsTooltip());
  ASSERT_TRUE(m_window.IsTooltip());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsPopupMenu)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::PopupMenu}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsPopupMenu());
  ASSERT_TRUE(m_window.IsPopupMenu());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, IsExcludedFromTaskbar)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::SkipTaskbar}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsExcludedFromTaskbar());
  ASSERT_TRUE(m_window.IsExcludedFromTaskbar());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(WindowTest, IsMetal)
{
  std::array values{Uint32{cen::Window::Fullscreen}, Uint32{cen::Window::Metal}};
  SET_RETURN_SEQ(SDL_GetWindowFlags, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.IsMetal());
  ASSERT_TRUE(m_window.IsMetal());
  ASSERT_EQ(2u, SDL_GetWindowFlags_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(WindowTest, GetBrightness)
{
  const auto brightness [[maybe_unused]] = m_window.GetBrightness();
  ASSERT_EQ(1u, SDL_GetWindowBrightness_fake.call_count);
}

TEST_F(WindowTest, GetOpacity)
{
  const auto opacity [[maybe_unused]] = m_window.GetOpacity();
  ASSERT_EQ(1u, SDL_GetWindowOpacity_fake.call_count);
}

TEST_F(WindowTest, X)
{
  const auto x [[maybe_unused]] = m_window.x();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
  ASSERT_NE(nullptr, SDL_GetWindowPosition_fake.arg1_val);
}

TEST_F(WindowTest, Y)
{
  const auto y [[maybe_unused]] = m_window.y();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
  ASSERT_NE(nullptr, SDL_GetWindowPosition_fake.arg2_val);
}

TEST_F(WindowTest, GetID)
{
  const auto id [[maybe_unused]] = m_window.GetID();
  ASSERT_EQ(1u, SDL_GetWindowID_fake.call_count);
}

TEST_F(WindowTest, GetDisplayIndex)
{
  std::array values{-1, 7};
  SET_RETURN_SEQ(SDL_GetWindowDisplayIndex, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.GetDisplayIndex().has_value());
  ASSERT_EQ(1u, SDL_GetWindowDisplayIndex_fake.call_count);

  ASSERT_EQ(7, m_window.GetDisplayIndex());
  ASSERT_EQ(2u, SDL_GetWindowDisplayIndex_fake.call_count);
}

TEST_F(WindowTest, Position)
{
  const auto pos [[maybe_unused]] = m_window.position();
  ASSERT_EQ(1u, SDL_GetWindowPosition_fake.call_count);
}

TEST_F(WindowTest, GetMinSize)
{
  const auto size [[maybe_unused]] = m_window.GetMinSize();
  ASSERT_EQ(1u, SDL_GetWindowMinimumSize_fake.call_count);
}

TEST_F(WindowTest, GetMaxSize)
{
  const auto size [[maybe_unused]] = m_window.GetMaxSize();
  ASSERT_EQ(1u, SDL_GetWindowMaximumSize_fake.call_count);
}

TEST_F(WindowTest, Width)
{
  const auto width [[maybe_unused]] = m_window.width();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Height)
{
  const auto height [[maybe_unused]] = m_window.height();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, Size)
{
  const auto size [[maybe_unused]] = m_window.size();
  ASSERT_EQ(1u, SDL_GetWindowSize_fake.call_count);
}

TEST_F(WindowTest, CheckFlag)
{
  const auto a [[maybe_unused]] = m_window.CheckFlag(cen::WindowHandle::Fullscreen);
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, GetFlags)
{
  const auto flags [[maybe_unused]] = m_window.GetFlags();
  ASSERT_EQ(1u, SDL_GetWindowFlags_fake.call_count);
}

TEST_F(WindowTest, GetPixelFormat)
{
  const auto format [[maybe_unused]] = m_window.GetPixelFormat();
  ASSERT_EQ(1u, SDL_GetWindowPixelFormat_fake.call_count);
}

TEST_F(WindowTest, GetSurface)
{
  const auto surface [[maybe_unused]] = m_window.GetSurface();
  ASSERT_EQ(1u, SDL_GetWindowSurface_fake.call_count);
}

TEST_F(WindowTest, GetTitle)
{
  SDL_GetWindowTitle_fake.return_val = "";
  const auto title [[maybe_unused]] = m_window.GetTitle();
  ASSERT_EQ(1u, SDL_GetWindowTitle_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 16)

TEST_F(WindowTest, SetAlwaysOnTop)
{
  m_window.SetAlwaysOnTop(true);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowAlwaysOnTop_fake.arg1_val);

  m_window.SetAlwaysOnTop(false);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowAlwaysOnTop_fake.arg1_val);
}

TEST_F(WindowTest, SetGrabKeyboard)
{
  m_window.SetGrabKeyboard(true);
  ASSERT_EQ(SDL_TRUE, SDL_SetWindowKeyboardGrab_fake.arg1_val);

  m_window.SetGrabKeyboard(false);
  ASSERT_EQ(SDL_FALSE, SDL_SetWindowKeyboardGrab_fake.arg1_val);
}

TEST_F(WindowTest, Flash)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_FlashWindow, values.data(), cen::isize(values));

  ASSERT_FALSE(m_window.Flash());
  ASSERT_EQ(SDL_FLASH_BRIEFLY, SDL_FlashWindow_fake.arg1_val);

  ASSERT_TRUE(m_window.Flash(cen::FlashOp::UntilFocused));
  ASSERT_EQ(SDL_FLASH_UNTIL_FOCUSED, SDL_FlashWindow_fake.arg1_val);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
