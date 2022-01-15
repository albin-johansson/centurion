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
  ASSERT_THROW(ToString(static_cast<Button>(SDL_CONTROLLER_BUTTON_MAX + 1)), cen::exception);

  ASSERT_EQ("Invalid", ToString(Button::Invalid));

  ASSERT_EQ("A", ToString(Button::A));
  ASSERT_EQ("B", ToString(Button::B));
  ASSERT_EQ("X", ToString(Button::X));
  ASSERT_EQ("Y", ToString(Button::Y));

  ASSERT_EQ("Back", ToString(Button::Back));
  ASSERT_EQ("Guide", ToString(Button::Guide));
  ASSERT_EQ("Start", ToString(Button::Start));

  ASSERT_EQ("LeftStick", ToString(Button::LeftStick));
  ASSERT_EQ("RightStick", ToString(Button::RightStick));

  ASSERT_EQ("LeftShoulder", ToString(Button::LeftShoulder));
  ASSERT_EQ("RightShoulder", ToString(Button::RightShoulder));

  ASSERT_EQ("DpadUp", ToString(Button::DpadUp));
  ASSERT_EQ("DpadDown", ToString(Button::DpadDown));
  ASSERT_EQ("DpadLeft", ToString(Button::DpadLeft));
  ASSERT_EQ("DpadRight", ToString(Button::DpadRight));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("Misc1", ToString(Button::Misc1));

  ASSERT_EQ("Paddle1", ToString(Button::Paddle1));
  ASSERT_EQ("Paddle2", ToString(Button::Paddle2));
  ASSERT_EQ("Paddle3", ToString(Button::Paddle3));
  ASSERT_EQ("Paddle4", ToString(Button::Paddle4));

  ASSERT_EQ("Touchpad", ToString(Button::Touchpad));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_EQ("Max", ToString(Button::Max));

  std::clog << "Controller Button example: " << Button::X << '\n';
}
