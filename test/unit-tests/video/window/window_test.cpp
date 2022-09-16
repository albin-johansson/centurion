/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#include "centurion/window.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

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

TEST_F(WindowTest, StreamOperator)
{
  std::cout << *window << '\n';
}
