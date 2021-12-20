#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "input/controller.hpp"

using Button = cen::ControllerButton;

TEST(ControllerButton, Values)
{
  ASSERT_EQ(ToUnderlying(Button::Invalid), SDL_CONTROLLER_BUTTON_INVALID);

  ASSERT_EQ(ToUnderlying(Button::A), SDL_CONTROLLER_BUTTON_A);
  ASSERT_EQ(ToUnderlying(Button::B), SDL_CONTROLLER_BUTTON_B);
  ASSERT_EQ(ToUnderlying(Button::X), SDL_CONTROLLER_BUTTON_X);
  ASSERT_EQ(ToUnderlying(Button::Y), SDL_CONTROLLER_BUTTON_Y);

  ASSERT_EQ(ToUnderlying(Button::Back), SDL_CONTROLLER_BUTTON_BACK);
  ASSERT_EQ(ToUnderlying(Button::Guide), SDL_CONTROLLER_BUTTON_GUIDE);
  ASSERT_EQ(ToUnderlying(Button::Start), SDL_CONTROLLER_BUTTON_START);

  ASSERT_EQ(ToUnderlying(Button::LeftStick), SDL_CONTROLLER_BUTTON_LEFTSTICK);
  ASSERT_EQ(ToUnderlying(Button::RightStick), SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  ASSERT_EQ(ToUnderlying(Button::LeftShoulder), SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  ASSERT_EQ(ToUnderlying(Button::RightShoulder), SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

  ASSERT_EQ(ToUnderlying(Button::DpadUp), SDL_CONTROLLER_BUTTON_DPAD_UP);
  ASSERT_EQ(ToUnderlying(Button::DpadDown), SDL_CONTROLLER_BUTTON_DPAD_DOWN);
  ASSERT_EQ(ToUnderlying(Button::DpadRight), SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
  ASSERT_EQ(ToUnderlying(Button::DpadLeft), SDL_CONTROLLER_BUTTON_DPAD_LEFT);
  ASSERT_EQ(ToUnderlying(Button::Max), SDL_CONTROLLER_BUTTON_MAX);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(ToUnderlying(Button::Misc1), SDL_CONTROLLER_BUTTON_MISC1);
  ASSERT_EQ(ToUnderlying(Button::Paddle1), SDL_CONTROLLER_BUTTON_PADDLE1);
  ASSERT_EQ(ToUnderlying(Button::Paddle2), SDL_CONTROLLER_BUTTON_PADDLE2);
  ASSERT_EQ(ToUnderlying(Button::Paddle3), SDL_CONTROLLER_BUTTON_PADDLE3);
  ASSERT_EQ(ToUnderlying(Button::Paddle4), SDL_CONTROLLER_BUTTON_PADDLE4);
  ASSERT_EQ(ToUnderlying(Button::Touchpad), SDL_CONTROLLER_BUTTON_TOUCHPAD);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(ControllerButton, ToString)
{
  ASSERT_THROW(to_string(static_cast<Button>(SDL_CONTROLLER_BUTTON_MAX + 1)), cen::Error);

  ASSERT_EQ("Invalid", to_string(Button::Invalid));

  ASSERT_EQ("A", to_string(Button::A));
  ASSERT_EQ("B", to_string(Button::B));
  ASSERT_EQ("X", to_string(Button::X));
  ASSERT_EQ("Y", to_string(Button::Y));

  ASSERT_EQ("Back", to_string(Button::Back));
  ASSERT_EQ("Guide", to_string(Button::Guide));
  ASSERT_EQ("Start", to_string(Button::Start));

  ASSERT_EQ("LeftStick", to_string(Button::LeftStick));
  ASSERT_EQ("RightStick", to_string(Button::RightStick));

  ASSERT_EQ("LeftShoulder", to_string(Button::LeftShoulder));
  ASSERT_EQ("RightShoulder", to_string(Button::RightShoulder));

  ASSERT_EQ("DpadUp", to_string(Button::DpadUp));
  ASSERT_EQ("DpadDown", to_string(Button::DpadDown));
  ASSERT_EQ("DpadLeft", to_string(Button::DpadLeft));
  ASSERT_EQ("DpadRight", to_string(Button::DpadRight));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("Misc1", to_string(Button::Misc1));

  ASSERT_EQ("Paddle1", to_string(Button::Paddle1));
  ASSERT_EQ("Paddle2", to_string(Button::Paddle2));
  ASSERT_EQ("Paddle3", to_string(Button::Paddle3));
  ASSERT_EQ("Paddle4", to_string(Button::Paddle4));

  ASSERT_EQ("Touchpad", to_string(Button::Touchpad));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("Max", to_string(Button::Max));

  std::clog << "Controller Button example: " << Button::X << '\n';
}
