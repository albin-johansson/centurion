#include "video/window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "core/log.hpp"
#include "video/screen.hpp"
#include "video/window_utils.hpp"

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
  ASSERT_EQ(cen::window::default_size(), window.size());
  ASSERT_EQ("Centurion window", window.title());
  ASSERT_FALSE(window.is_visible());
}

TEST_F(WindowTest, ConstructFromPointer)
{
  {  // window
    ASSERT_NO_THROW(cen::window{SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN)});

    SDL_Window* ptr{};
    ASSERT_THROW(cen::window{ptr}, cen::cen_error);
  }

  {  // window_handle
    ASSERT_NO_THROW(cen::window_handle{nullptr});
    cen::window_handle handle{m_window->get()};
    ASSERT_EQ(handle.get(), m_window->get());
  }
}

TEST_F(WindowTest, ContructorFromStringAndArea)
{
  using namespace std::string_literals;

  ASSERT_THROW(cen::window(""s, {0, 10}), cen::cen_error);
  ASSERT_THROW(cen::window(""s, {10, 0}), cen::cen_error);

  const auto width = 123;
  const auto height = 321;
  const auto title = "foobar"s;
  const cen::window window{title, {width, height}};

  ASSERT_EQ(title, window.title());
  ASSERT_EQ(width, window.width());
  ASSERT_EQ(height, window.height());
  ASSERT_FALSE(window.is_visible());
}

TEST_F(WindowTest, Get)
{
  ASSERT_TRUE(m_window->get());
}

TEST_F(WindowTest, BoolConversion)
{
  cen::window_handle handle{*m_window};
  ASSERT_TRUE(handle);
}

TEST_F(WindowTest, DefaultSize)
{
  constexpr auto size = cen::window::default_size();
  ASSERT_EQ(800, size.width);
  ASSERT_EQ(600, size.height);
}

TEST_F(WindowTest, PointerConversion)
{
  ASSERT_TRUE(m_window->operator SDL_Window*());
  ASSERT_TRUE(m_window->operator const SDL_Window*());
}

TEST_F(WindowTest, ToString)
{
  cen::log::put(cen::to_string(*m_window));
}

TEST_F(WindowTest, StreamOperator)
{
  std::clog << *m_window << '\n';
}

TEST_F(WindowTest, WindowFlagsEnum)
{
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN, static_cast<SDL_WindowFlags>(cen::window::fullscreen));
  ASSERT_EQ(SDL_WINDOW_OPENGL, static_cast<SDL_WindowFlags>(cen::window::opengl));
  ASSERT_EQ(SDL_WINDOW_SHOWN, static_cast<SDL_WindowFlags>(cen::window::shown));
  ASSERT_EQ(SDL_WINDOW_HIDDEN, static_cast<SDL_WindowFlags>(cen::window::hidden));
  ASSERT_EQ(SDL_WINDOW_BORDERLESS, static_cast<SDL_WindowFlags>(cen::window::borderless));
  ASSERT_EQ(SDL_WINDOW_RESIZABLE, static_cast<SDL_WindowFlags>(cen::window::resizable));
  ASSERT_EQ(SDL_WINDOW_MINIMIZED, static_cast<SDL_WindowFlags>(cen::window::minimized));
  ASSERT_EQ(SDL_WINDOW_MAXIMIZED, static_cast<SDL_WindowFlags>(cen::window::maximized));
  ASSERT_EQ(SDL_WINDOW_INPUT_GRABBED,
            static_cast<SDL_WindowFlags>(cen::window::input_grabbed));
  ASSERT_EQ(SDL_WINDOW_INPUT_FOCUS, static_cast<SDL_WindowFlags>(cen::window::input_focus));
  ASSERT_EQ(SDL_WINDOW_MOUSE_FOCUS, static_cast<SDL_WindowFlags>(cen::window::mouse_focus));
  ASSERT_EQ(SDL_WINDOW_FULLSCREEN_DESKTOP,
            static_cast<SDL_WindowFlags>(cen::window::fullscreen_desktop));
  ASSERT_EQ(SDL_WINDOW_FOREIGN, static_cast<SDL_WindowFlags>(cen::window::foreign));
  ASSERT_EQ(SDL_WINDOW_ALLOW_HIGHDPI, static_cast<SDL_WindowFlags>(cen::window::high_dpi));
  ASSERT_EQ(SDL_WINDOW_MOUSE_CAPTURE,
            static_cast<SDL_WindowFlags>(cen::window::mouse_capture));
  ASSERT_EQ(SDL_WINDOW_ALWAYS_ON_TOP,
            static_cast<SDL_WindowFlags>(cen::window::always_on_top));
  ASSERT_EQ(SDL_WINDOW_SKIP_TASKBAR, static_cast<SDL_WindowFlags>(cen::window::skip_taskbar));
  ASSERT_EQ(SDL_WINDOW_UTILITY, static_cast<SDL_WindowFlags>(cen::window::utility));
  ASSERT_EQ(SDL_WINDOW_TOOLTIP, static_cast<SDL_WindowFlags>(cen::window::tooltip));
  ASSERT_EQ(SDL_WINDOW_POPUP_MENU, static_cast<SDL_WindowFlags>(cen::window::popup_menu));
  ASSERT_EQ(SDL_WINDOW_VULKAN, static_cast<SDL_WindowFlags>(cen::window::vulkan));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_WINDOW_METAL, static_cast<SDL_WindowFlags>(cen::window::metal));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(WindowUtils, MakeWindowAndRenderer)
{
  ASSERT_NO_THROW(cen::make_window_and_renderer());
}