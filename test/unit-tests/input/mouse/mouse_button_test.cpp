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

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/input/mouse.hpp"

TEST(MouseButton, Values)
{
  ASSERT_EQ(SDL_BUTTON_LEFT, to_underlying(cen::mouse_button::left));
  ASSERT_EQ(SDL_BUTTON_MIDDLE, to_underlying(cen::mouse_button::middle));
  ASSERT_EQ(SDL_BUTTON_RIGHT, to_underlying(cen::mouse_button::right));
  ASSERT_EQ(SDL_BUTTON_X1, to_underlying(cen::mouse_button::x1));
  ASSERT_EQ(SDL_BUTTON_X2, to_underlying(cen::mouse_button::x2));
}

TEST(MouseButton, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::mouse_button>(6)), cen::exception);

  ASSERT_EQ("left", to_string(cen::mouse_button::left));
  ASSERT_EQ("middle", to_string(cen::mouse_button::middle));
  ASSERT_EQ("right", to_string(cen::mouse_button::right));
  ASSERT_EQ("x1", to_string(cen::mouse_button::x1));
  ASSERT_EQ("x2", to_string(cen::mouse_button::x2));

  std::cout << "moues_button::middle == " << cen::mouse_button::middle << '\n';
}
