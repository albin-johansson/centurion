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

#include "centurion/message_box.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_ShowSimpleMessageBox, Uint32, const char*, const char*, SDL_Window*)
  FAKE_VALUE_FUNC(int, SDL_ShowMessageBox, const SDL_MessageBoxData*, int*)
}

class MessageBoxTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_DestroyWindow)
    RESET_FAKE(SDL_CreateWindow)
    RESET_FAKE(SDL_ShowSimpleMessageBox)
    RESET_FAKE(SDL_ShowMessageBox)
  }
};

TEST_F(MessageBoxTest, ShowStatic)
{
  const std::string title{"foo"};
  const std::string message{"bar"};

  {  // With defaults
    cen::message_box::show(title, message);
    ASSERT_EQ(1u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_INFORMATION,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type
    cen::message_box::show(title, message, cen::message_box_type::error);
    ASSERT_EQ(2u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_ERROR,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type and button order
    cen::message_box::show(title,
                           message,
                           cen::message_box_type::error,
                           cen::message_box_button_order::right_to_left);
    ASSERT_EQ(3u, SDL_ShowSimpleMessageBox_fake.call_count);

#if SDL_VERSION_ATLEAST(2, 0, 12)
    ASSERT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT | SDL_MESSAGEBOX_ERROR,
              static_cast<int>(SDL_ShowSimpleMessageBox_fake.arg0_val));
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    ASSERT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    ASSERT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    ASSERT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }
}

TEST_F(MessageBoxTest, Show)
{
  cen::message_box mb;

  mb.show();
  ASSERT_EQ(1u, SDL_ShowMessageBox_fake.call_count);

  cen::window_handle window{nullptr};
  mb.show(window);
  ASSERT_EQ(2u, SDL_ShowMessageBox_fake.call_count);
}