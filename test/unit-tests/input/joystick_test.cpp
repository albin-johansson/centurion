#include "input/joystick.hpp"

#include <gtest/gtest.h>

TEST(Joystick, PointerConstructor)
{
  ASSERT_THROW(cen::Joystick{nullptr}, cen::Error);
}

TEST(Joystick, IndexConstructor)
{
  ASSERT_THROW(cen::Joystick{0}, cen::SDLError);
}

TEST(Joystick, GetAxisMax)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MAX, cen::Joystick::GetAxisMax());
}

TEST(Joystick, GetAxisMin)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MIN, cen::Joystick::GetAxisMin());
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Joystick, VirtualAPI)
{
  const auto type = cen::JoystickType::GameController;
  const auto nAxes = 2;
  const auto nButtons = 3;
  const auto nHats = 4;

  const auto index = cen::Joystick::AttachVirtual(type, nAxes, nButtons, nHats);
  ASSERT_TRUE(index);
  ASSERT_TRUE(cen::Joystick::IsVirtual(*index));

  cen::Joystick joystick{*index};
  ASSERT_EQ(type, joystick.GetType());
  ASSERT_EQ(nAxes, joystick.GetAxes());
  ASSERT_EQ(nButtons, joystick.GetButtons());
  ASSERT_EQ(nHats, joystick.GetHats());

  ASSERT_TRUE(joystick.SetVirtualAxis(0, 123));
  ASSERT_TRUE(joystick.SetVirtualButton(0, cen::button_state::pressed));
  ASSERT_TRUE(joystick.SetVirtualHat(0, cen::HatState::Centered));

  ASSERT_TRUE(cen::Joystick::DetachVirtual(*index));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)