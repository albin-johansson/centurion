#include "video/window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "misc/log.hpp"
#include "video/screen.hpp"

class WindowTest : public testing::Test
{
 protected:
  [[maybe_unused]] static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
  }

  [[maybe_unused]] static void TearDownTestSuite()
  {
    m_window.reset();
  }

  inline static std::unique_ptr<cen::window> m_window;
};

TEST_F(WindowTest, Defaults)
{
  const cen::window window;
  EXPECT_EQ(cen::window::default_size(), window.size());
  EXPECT_EQ("Centurion window", window.title());
  EXPECT_FALSE(window.is_visible());
}

TEST_F(WindowTest, ConstructFromPointer)
{
  {  // window
    EXPECT_NO_THROW(
        cen::window{SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN)});

    SDL_Window* ptr{};
    EXPECT_THROW(cen::window{ptr}, cen::cen_error);
  }

  {  // window_handle
    EXPECT_NO_THROW(cen::window_handle{nullptr});
    cen::window_handle handle{m_window->get()};
    EXPECT_EQ(handle.get(), m_window->get());
  }
}

TEST_F(WindowTest, ContructorFromStringAndArea)
{
  using namespace std::string_literals;

  EXPECT_THROW(cen::window(""s, {0, 10}), cen::cen_error);
  EXPECT_THROW(cen::window(""s, {10, 0}), cen::cen_error);

  const auto width = 123;
  const auto height = 321;
  const auto title = "foobar"s;
  const cen::window window{title, {width, height}};

  EXPECT_EQ(title, window.title());
  EXPECT_EQ(width, window.width());
  EXPECT_EQ(height, window.height());
  EXPECT_FALSE(window.is_visible());
}

TEST_F(WindowTest, Get)
{
  EXPECT_TRUE(m_window->get());
}

TEST_F(WindowTest, BoolConversion)
{
  cen::window_handle handle{*m_window};
  EXPECT_TRUE(handle);
}

TEST_F(WindowTest, DefaultSize)
{
  constexpr auto size = cen::window::default_size();
  EXPECT_EQ(800, size.width);
  EXPECT_EQ(600, size.height);
}

TEST_F(WindowTest, PointerConversion)
{
  EXPECT_TRUE(m_window->operator SDL_Window*());
  EXPECT_TRUE(m_window->operator const SDL_Window*());
}

TEST_F(WindowTest, ToString)
{
  cen::log::put(cen::to_string(*m_window));
}

TEST_F(WindowTest, StreamOperator)
{
  std::cout << "COUT: " << *m_window << '\n';
}

TEST_F(WindowTest, WindowFlagsEnum)
{
  EXPECT_EQ(SDL_WINDOW_FULLSCREEN, cen::window::fullscreen);
  EXPECT_EQ(SDL_WINDOW_OPENGL, cen::window::opengl);
  EXPECT_EQ(SDL_WINDOW_SHOWN, cen::window::shown);
  EXPECT_EQ(SDL_WINDOW_HIDDEN, cen::window::hidden);
  EXPECT_EQ(SDL_WINDOW_BORDERLESS, cen::window::borderless);
  EXPECT_EQ(SDL_WINDOW_RESIZABLE, cen::window::resizable);
  EXPECT_EQ(SDL_WINDOW_MINIMIZED, cen::window::minimized);
  EXPECT_EQ(SDL_WINDOW_MAXIMIZED, cen::window::maximized);
  EXPECT_EQ(SDL_WINDOW_INPUT_GRABBED, cen::window::input_grabbed);
  EXPECT_EQ(SDL_WINDOW_INPUT_FOCUS, cen::window::input_focus);
  EXPECT_EQ(SDL_WINDOW_MOUSE_FOCUS, cen::window::mouse_focus);
  EXPECT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP, cen::window::fullscreen_desktop);
  EXPECT_EQ(SDL_WINDOW_FOREIGN, cen::window::foreign);
  EXPECT_EQ(SDL_WINDOW_ALLOW_HIGHDPI, cen::window::high_dpi);
  EXPECT_EQ(SDL_WINDOW_MOUSE_CAPTURE, cen::window::mouse_capture);
  EXPECT_EQ(SDL_WINDOW_ALWAYS_ON_TOP, cen::window::always_on_top);
  EXPECT_EQ(SDL_WINDOW_SKIP_TASKBAR, cen::window::skip_taskbar);
  EXPECT_EQ(SDL_WINDOW_UTILITY, cen::window::utility);
  EXPECT_EQ(SDL_WINDOW_TOOLTIP, cen::window::tooltip);
  EXPECT_EQ(SDL_WINDOW_POPUP_MENU, cen::window::popup_menu);
  EXPECT_EQ(SDL_WINDOW_VULKAN, cen::window::vulkan);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  EXPECT_EQ(SDL_WINDOW_METAL, cen::window::metal);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}