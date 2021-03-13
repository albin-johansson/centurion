#include "window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "log.hpp"
#include "screen.hpp"

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
    EXPECT_THROW(cen::window{ptr}, cen::exception);
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

  EXPECT_THROW(cen::window(""s, {0, 10}), cen::exception);
  EXPECT_THROW(cen::window(""s, {10, 0}), cen::exception);

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
