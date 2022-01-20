#include "window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "core/logging.hpp"
#include "video.hpp"

class WindowTest : public testing::Test {
 protected:
  [[maybe_unused]] static void SetUpTestSuite() { window = std::make_unique<cen::window>(); }

  [[maybe_unused]] static void TearDownTestSuite() { window.reset(); }

  inline static std::unique_ptr<cen::window> window;
};

TEST_F(WindowTest, Defaults)
{
  const cen::window window;

  ASSERT_EQ("Centurion", window.title());

  ASSERT_EQ(cen::window::default_size(), window.size());
  ASSERT_TRUE(window.check_flag(cen::window::default_flags()));

  ASSERT_FALSE(window.is_visible());
}

TEST_F(WindowTest, ConstructFromPointer)
{
  {
    ASSERT_NO_THROW(cen::window{SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN)});

    SDL_Window* ptr{};
    ASSERT_THROW(cen::window{ptr}, cen::exception);
  }

  {
    ASSERT_NO_THROW(cen::window_handle{nullptr});
    cen::window_handle handle{window->get()};
    ASSERT_EQ(handle.get(), window->get());
  }
}

TEST_F(WindowTest, ContructorFromStringAndArea)
{
  using namespace std::string_literals;

  ASSERT_THROW(cen::window(""s, {0, 10}), cen::exception);
  ASSERT_THROW(cen::window(""s, {10, 0}), cen::exception);

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
  ASSERT_TRUE(window->get());
}

TEST_F(WindowTest, BoolConversion)
{
  cen::window_handle handle{*window};
  ASSERT_TRUE(handle);
}

TEST_F(WindowTest, DefaultSize)
{
  constexpr auto size = cen::window::default_size();
  ASSERT_EQ(800, size.width);
  ASSERT_EQ(600, size.height);
}

TEST_F(WindowTest, ToString)
{
  cen::log_info_raw(cen::to_string(*window));
}

TEST_F(WindowTest, StreamOperator)
{
  std::clog << *window << '\n';
}
