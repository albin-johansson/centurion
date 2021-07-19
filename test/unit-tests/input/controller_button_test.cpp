#include "input/controller_button.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

using button = cen::controller_button;

TEST(ControllerButton, Values)
{
  ASSERT_EQ(button::invalid, SDL_CONTROLLER_BUTTON_INVALID);
  ASSERT_EQ(button::a, SDL_CONTROLLER_BUTTON_A);
  ASSERT_EQ(button::b, SDL_CONTROLLER_BUTTON_B);
  ASSERT_EQ(button::x, SDL_CONTROLLER_BUTTON_X);
  ASSERT_EQ(button::y, SDL_CONTROLLER_BUTTON_Y);
  ASSERT_EQ(button::back, SDL_CONTROLLER_BUTTON_BACK);
  ASSERT_EQ(button::guide, SDL_CONTROLLER_BUTTON_GUIDE);
  ASSERT_EQ(button::start, SDL_CONTROLLER_BUTTON_START);
  ASSERT_EQ(button::left_stick, SDL_CONTROLLER_BUTTON_LEFTSTICK);
  ASSERT_EQ(button::right_stick, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  ASSERT_EQ(button::left_shoulder, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  ASSERT_EQ(button::right_shoulder, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
  ASSERT_EQ(button::dpad_up, SDL_CONTROLLER_BUTTON_DPAD_UP);
  ASSERT_EQ(button::dpad_down, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
  ASSERT_EQ(button::dpad_right, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
  ASSERT_EQ(button::dpad_left, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
  ASSERT_EQ(button::max, SDL_CONTROLLER_BUTTON_MAX);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(button::misc1, SDL_CONTROLLER_BUTTON_MISC1);
  ASSERT_EQ(button::paddle1, SDL_CONTROLLER_BUTTON_PADDLE1);
  ASSERT_EQ(button::paddle2, SDL_CONTROLLER_BUTTON_PADDLE2);
  ASSERT_EQ(button::paddle3, SDL_CONTROLLER_BUTTON_PADDLE3);
  ASSERT_EQ(button::paddle4, SDL_CONTROLLER_BUTTON_PADDLE4);
  ASSERT_EQ(button::touchpad, SDL_CONTROLLER_BUTTON_TOUCHPAD);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_NE(button::right_stick, SDL_CONTROLLER_BUTTON_DPAD_UP);
  ASSERT_NE(SDL_CONTROLLER_BUTTON_B, button::guide);
}

TEST(ControllerButton, ToString)
{
  ASSERT_EQ("invalid", cen::to_string(button::invalid));

  ASSERT_EQ("a", cen::to_string(button::a));
  ASSERT_EQ("b", cen::to_string(button::b));
  ASSERT_EQ("x", cen::to_string(button::x));
  ASSERT_EQ("y", cen::to_string(button::y));

  ASSERT_EQ("back", cen::to_string(button::back));
  ASSERT_EQ("guide", cen::to_string(button::guide));
  ASSERT_EQ("start", cen::to_string(button::start));

  ASSERT_EQ("left_stick", cen::to_string(button::left_stick));
  ASSERT_EQ("right_stick", cen::to_string(button::right_stick));

  ASSERT_EQ("left_shoulder", cen::to_string(button::left_shoulder));
  ASSERT_EQ("right_shoulder", cen::to_string(button::right_shoulder));

  ASSERT_EQ("dpad_up", cen::to_string(button::dpad_up));
  ASSERT_EQ("dpad_down", cen::to_string(button::dpad_down));
  ASSERT_EQ("dpad_left", cen::to_string(button::dpad_left));
  ASSERT_EQ("dpad_right", cen::to_string(button::dpad_right));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("misc1", cen::to_string(button::misc1));

  ASSERT_EQ("paddle1", cen::to_string(button::paddle1));
  ASSERT_EQ("paddle2", cen::to_string(button::paddle2));
  ASSERT_EQ("paddle3", cen::to_string(button::paddle3));
  ASSERT_EQ("paddle4", cen::to_string(button::paddle4));

  ASSERT_EQ("touchpad", cen::to_string(button::touchpad));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("max", cen::to_string(button::max));

  std::cout << "Controller button example: " << button::x << '\n';
}
