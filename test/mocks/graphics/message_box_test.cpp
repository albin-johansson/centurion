#include "message_box.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(int, SDL_ShowSimpleMessageBox, Uint32, const char*, const char*, SDL_Window*)
FAKE_VALUE_FUNC(int, SDL_ShowMessageBox, const SDL_MessageBoxData*, int*)
}
// clang-format on

class MessageBoxTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_DestroyWindow);
    RESET_FAKE(SDL_CreateWindow);
    RESET_FAKE(SDL_ShowSimpleMessageBox);
    RESET_FAKE(SDL_ShowMessageBox);
  }
};

TEST_F(MessageBoxTest, ShowStatic)
{
  const std::string title{"foo"};
  const std::string message{"bar"};

  {  // With defaults
    cen::message_box::show(title, message);
    EXPECT_EQ(1, SDL_ShowSimpleMessageBox_fake.call_count);

    EXPECT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_INFORMATION,
              SDL_ShowSimpleMessageBox_fake.arg0_val);
    EXPECT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    EXPECT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    EXPECT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type
    cen::message_box::show(title, message, cen::message_box::type::error);
    EXPECT_EQ(2, SDL_ShowSimpleMessageBox_fake.call_count);

    EXPECT_EQ(SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_ERROR,
              SDL_ShowSimpleMessageBox_fake.arg0_val);
    EXPECT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    EXPECT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    EXPECT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }

  {  // With custom type and button order
    cen::message_box::show(title,
                           message,
                           cen::message_box::type::error,
                           cen::message_box::button_order::right_to_left);
    EXPECT_EQ(3, SDL_ShowSimpleMessageBox_fake.call_count);

    EXPECT_EQ(SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT | SDL_MESSAGEBOX_ERROR,
              SDL_ShowSimpleMessageBox_fake.arg0_val);
    EXPECT_STREQ(title.c_str(), SDL_ShowSimpleMessageBox_fake.arg1_val);
    EXPECT_STREQ(message.c_str(), SDL_ShowSimpleMessageBox_fake.arg2_val);
    EXPECT_EQ(nullptr, SDL_ShowSimpleMessageBox_fake.arg3_val);
  }
}

TEST_F(MessageBoxTest, Show)
{
  cen::message_box mb;

  mb.show();
  EXPECT_EQ(1, SDL_ShowMessageBox_fake.call_count);

  cen::window_handle window{nullptr};
  mb.show(window);
  EXPECT_EQ(2, SDL_ShowMessageBox_fake.call_count);
}