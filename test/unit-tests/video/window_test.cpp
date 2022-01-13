#include "window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "core/logging.hpp"
#include "video.hpp"

class WindowTest : public testing::Test {
 protected:
  [[maybe_unused]] static void SetUpTestSuite() { window = std::make_unique<cen::Window>(); }

  [[maybe_unused]] static void TearDownTestSuite() { window.reset(); }

  inline static std::unique_ptr<cen::Window> window;
};

TEST_F(WindowTest, Defaults)
{
  const cen::Window window;

  ASSERT_EQ("Centurion", window.GetTitle());

  ASSERT_EQ(cen::Window::GetDefaultSize(), window.GetSize());
  ASSERT_TRUE(window.CheckFlag(cen::Window::GetDefaultFlags()));

  ASSERT_FALSE(window.IsVisible());
}

TEST_F(WindowTest, ConstructFromPointer)
{
  {
    ASSERT_NO_THROW(cen::Window{SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN)});

    SDL_Window* ptr{};
    ASSERT_THROW(cen::Window{ptr}, cen::Error);
  }

  {
    ASSERT_NO_THROW(cen::WindowHandle{nullptr});
    cen::WindowHandle handle{window->get()};
    ASSERT_EQ(handle.get(), window->get());
  }
}

TEST_F(WindowTest, ContructorFromStringAndArea)
{
  using namespace std::string_literals;

  ASSERT_THROW(cen::Window(""s, {0, 10}), cen::Error);
  ASSERT_THROW(cen::Window(""s, {10, 0}), cen::Error);

  const auto width = 123;
  const auto height = 321;
  const auto title = "foobar"s;
  const cen::Window window{title, {width, height}};

  ASSERT_EQ(title, window.GetTitle());
  ASSERT_EQ(width, window.GetWidth());
  ASSERT_EQ(height, window.GetHeight());
  ASSERT_FALSE(window.IsVisible());
}

TEST_F(WindowTest, Get)
{
  ASSERT_TRUE(window->get());
}

TEST_F(WindowTest, BoolConversion)
{
  cen::WindowHandle handle{*window};
  ASSERT_TRUE(handle);
}

TEST_F(WindowTest, DefaultSize)
{
  constexpr auto size = cen::Window::GetDefaultSize();
  ASSERT_EQ(800, size.width);
  ASSERT_EQ(600, size.height);
}

TEST_F(WindowTest, ToString)
{
  cen::log_info_raw(cen::ToString(*window));
}

TEST_F(WindowTest, StreamOperator)
{
  std::clog << *window << '\n';
}

TEST_F(WindowTest, WindowFlagsEnum)
{
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN, static_cast<SDL_WindowFlags>(cen::Window::Fullscreen));
  ASSERT_EQ(SDL_WINDOW_OPENGL, static_cast<SDL_WindowFlags>(cen::Window::OpenGL));
  ASSERT_EQ(SDL_WINDOW_SHOWN, static_cast<SDL_WindowFlags>(cen::Window::Shown));
  ASSERT_EQ(SDL_WINDOW_HIDDEN, static_cast<SDL_WindowFlags>(cen::Window::Hidden));
  ASSERT_EQ(SDL_WINDOW_BORDERLESS, static_cast<SDL_WindowFlags>(cen::Window::Borderless));
  ASSERT_EQ(SDL_WINDOW_RESIZABLE, static_cast<SDL_WindowFlags>(cen::Window::Resizable));
  ASSERT_EQ(SDL_WINDOW_MINIMIZED, static_cast<SDL_WindowFlags>(cen::Window::Minimized));
  ASSERT_EQ(SDL_WINDOW_MAXIMIZED, static_cast<SDL_WindowFlags>(cen::Window::Maximized));
  ASSERT_EQ(SDL_WINDOW_INPUT_GRABBED, static_cast<SDL_WindowFlags>(cen::Window::InputGrabbed));
  ASSERT_EQ(SDL_WINDOW_INPUT_FOCUS, static_cast<SDL_WindowFlags>(cen::Window::InputFocus));
  ASSERT_EQ(SDL_WINDOW_MOUSE_FOCUS, static_cast<SDL_WindowFlags>(cen::Window::MouseFocus));
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP,
            static_cast<SDL_WindowFlags>(cen::Window::FullscreenDesktop));
  ASSERT_EQ(SDL_WINDOW_FOREIGN, static_cast<SDL_WindowFlags>(cen::Window::Foreign));
  ASSERT_EQ(SDL_WINDOW_ALLOW_HIGHDPI, static_cast<SDL_WindowFlags>(cen::Window::AllowHighDPI));
  ASSERT_EQ(SDL_WINDOW_MOUSE_CAPTURE, static_cast<SDL_WindowFlags>(cen::Window::MouseCapture));
  ASSERT_EQ(SDL_WINDOW_ALWAYS_ON_TOP, static_cast<SDL_WindowFlags>(cen::Window::AlwaysOnTop));
  ASSERT_EQ(SDL_WINDOW_SKIP_TASKBAR, static_cast<SDL_WindowFlags>(cen::Window::SkipTaskbar));
  ASSERT_EQ(SDL_WINDOW_UTILITY, static_cast<SDL_WindowFlags>(cen::Window::Utility));
  ASSERT_EQ(SDL_WINDOW_TOOLTIP, static_cast<SDL_WindowFlags>(cen::Window::Tooltip));
  ASSERT_EQ(SDL_WINDOW_POPUP_MENU, static_cast<SDL_WindowFlags>(cen::Window::PopupMenu));
  ASSERT_EQ(SDL_WINDOW_VULKAN, static_cast<SDL_WindowFlags>(cen::Window::Vulkan));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_WINDOW_METAL, static_cast<SDL_WindowFlags>(cen::Window::Metal));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(WindowUtils, MakeWindowAndRenderer)
{
  ASSERT_NO_THROW(cen::MakeWindowAndRenderer());
}