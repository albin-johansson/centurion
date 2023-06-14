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

#include "centurion/video/message_box.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, Values)
{
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,
            to_underlying(cen::message_box_button_order::left_to_right));
  ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
            to_underlying(cen::message_box_button_order::right_to_left));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST(MessageBoxButtonOrder, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::message_box_button_order>(1'000)), cen::exception);

  ASSERT_EQ("left_to_right", to_string(cen::message_box_button_order::left_to_right));
  ASSERT_EQ("right_to_left", to_string(cen::message_box_button_order::right_to_left));

  std::cout << "message_box_button_order::left_to_right == "
            << cen::message_box_button_order::left_to_right << '\n';
}