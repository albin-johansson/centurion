#include "input/joystick.hpp"

#include <gtest/gtest.h>

TEST(Joystick, PointerConstructor)
{
  ASSERT_THROW(cen::joystick{nullptr}, cen::cen_error);
}

TEST(Joystick, IndexConstructor)
{
  ASSERT_THROW(cen::joystick{0}, cen::sdl_error);
}

TEST(Joystick, AxisMax)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MAX, cen::joystick::axis_max());
}

TEST(Joystick, AxisMin)
{
  ASSERT_EQ(SDL_JOYSTICK_AXIS_MIN, cen::joystick::axis_min());
}

TEST(Joystick, HatStateEnum)
{
  using state = cen::hat_state;

  ASSERT_EQ(static_cast<state>(SDL_HAT_CENTERED), state::centered);
  ASSERT_EQ(static_cast<state>(SDL_HAT_UP), state::up);
  ASSERT_EQ(static_cast<state>(SDL_HAT_RIGHT), state::right);
  ASSERT_EQ(static_cast<state>(SDL_HAT_DOWN), state::down);
  ASSERT_EQ(static_cast<state>(SDL_HAT_LEFT), state::left);
  ASSERT_EQ(static_cast<state>(SDL_HAT_RIGHTUP), state::right_up);
  ASSERT_EQ(static_cast<state>(SDL_HAT_RIGHTDOWN), state::right_down);
  ASSERT_EQ(static_cast<state>(SDL_HAT_LEFTUP), state::left_up);
  ASSERT_EQ(static_cast<state>(SDL_HAT_LEFTDOWN), state::left_down);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Joystick, VirtualAPI)
{
  const auto type = cen::joystick_type::game_controller;
  const auto nAxes = 2;
  const auto nButtons = 3;
  const auto nHats = 4;

  const auto index = cen::joystick::attach_virtual(type, nAxes, nButtons, nHats);
  ASSERT_TRUE(index);
  ASSERT_TRUE(cen::joystick::is_virtual(*index));

  cen::joystick joystick{*index};
  ASSERT_EQ(type, joystick.type());
  ASSERT_EQ(nAxes, joystick.axis_count());
  ASSERT_EQ(nButtons, joystick.button_count());
  ASSERT_EQ(nHats, joystick.hat_count());

  ASSERT_TRUE(joystick.set_virtual_axis(0, 123));
  ASSERT_TRUE(joystick.set_virtual_button(0, cen::button_state::pressed));
  ASSERT_TRUE(joystick.set_virtual_hat(0, cen::hat_state::centered));

  ASSERT_TRUE(cen::joystick::detach_virtual(*index));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)