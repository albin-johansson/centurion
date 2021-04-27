#include "input/joystick.hpp"

#include <gtest/gtest.h>

TEST(Joystick, PointerConstructor)
{
  EXPECT_THROW(cen::joystick{nullptr}, cen::cen_error);
}

TEST(Joystick, IndexConstructor)
{
  EXPECT_THROW(cen::joystick{0}, cen::sdl_error);
}

TEST(Joystick, AxisMax)
{
  EXPECT_EQ(SDL_JOYSTICK_AXIS_MAX, cen::joystick::axis_max());
}

TEST(Joystick, AxisMin)
{
  EXPECT_EQ(SDL_JOYSTICK_AXIS_MIN, cen::joystick::axis_min());
}

TEST(Joystick, PowerEnum)
{
  EXPECT_EQ(cen::joystick_power::unknown, SDL_JOYSTICK_POWER_UNKNOWN);
  EXPECT_EQ(cen::joystick_power::empty, SDL_JOYSTICK_POWER_EMPTY);
  EXPECT_EQ(cen::joystick_power::low, SDL_JOYSTICK_POWER_LOW);
  EXPECT_EQ(cen::joystick_power::medium, SDL_JOYSTICK_POWER_MEDIUM);
  EXPECT_EQ(cen::joystick_power::full, SDL_JOYSTICK_POWER_FULL);
  EXPECT_EQ(cen::joystick_power::wired, SDL_JOYSTICK_POWER_WIRED);
  EXPECT_EQ(cen::joystick_power::max, SDL_JOYSTICK_POWER_MAX);

  EXPECT_EQ(SDL_JOYSTICK_POWER_UNKNOWN, cen::joystick_power::unknown);
  EXPECT_EQ(SDL_JOYSTICK_POWER_EMPTY, cen::joystick_power::empty);
  EXPECT_EQ(SDL_JOYSTICK_POWER_LOW, cen::joystick_power::low);
  EXPECT_EQ(SDL_JOYSTICK_POWER_MEDIUM, cen::joystick_power::medium);
  EXPECT_EQ(SDL_JOYSTICK_POWER_FULL, cen::joystick_power::full);
  EXPECT_EQ(SDL_JOYSTICK_POWER_WIRED, cen::joystick_power::wired);
  EXPECT_EQ(SDL_JOYSTICK_POWER_MAX, cen::joystick_power::max);

  EXPECT_NE(cen::joystick_power::max, SDL_JOYSTICK_POWER_WIRED);
  EXPECT_NE(SDL_JOYSTICK_POWER_MEDIUM, cen::joystick_power::low);
}

TEST(Joystick, HatStateEnum)
{
  using state = cen::hat_state;

  EXPECT_EQ(static_cast<state>(SDL_HAT_CENTERED), state::centered);
  EXPECT_EQ(static_cast<state>(SDL_HAT_UP), state::up);
  EXPECT_EQ(static_cast<state>(SDL_HAT_RIGHT), state::right);
  EXPECT_EQ(static_cast<state>(SDL_HAT_DOWN), state::down);
  EXPECT_EQ(static_cast<state>(SDL_HAT_LEFT), state::left);
  EXPECT_EQ(static_cast<state>(SDL_HAT_RIGHTUP), state::right_up);
  EXPECT_EQ(static_cast<state>(SDL_HAT_RIGHTDOWN), state::right_down);
  EXPECT_EQ(static_cast<state>(SDL_HAT_LEFTUP), state::left_up);
  EXPECT_EQ(static_cast<state>(SDL_HAT_LEFTDOWN), state::left_down);
}

TEST(Joystick, TypeEnum)
{
  using type = cen::joystick_type;

  EXPECT_EQ(type::unknown, SDL_JOYSTICK_TYPE_UNKNOWN);
  EXPECT_EQ(type::game_controller, SDL_JOYSTICK_TYPE_GAMECONTROLLER);
  EXPECT_EQ(type::wheel, SDL_JOYSTICK_TYPE_WHEEL);
  EXPECT_EQ(type::arcade_stick, SDL_JOYSTICK_TYPE_ARCADE_STICK);
  EXPECT_EQ(type::flight_stick, SDL_JOYSTICK_TYPE_FLIGHT_STICK);
  EXPECT_EQ(type::dance_pad, SDL_JOYSTICK_TYPE_DANCE_PAD);
  EXPECT_EQ(type::guitar, SDL_JOYSTICK_TYPE_GUITAR);
  EXPECT_EQ(type::drum_kit, SDL_JOYSTICK_TYPE_DRUM_KIT);
  EXPECT_EQ(type::arcade_pad, SDL_JOYSTICK_TYPE_ARCADE_PAD);
  EXPECT_EQ(type::throttle, SDL_JOYSTICK_TYPE_THROTTLE);

  EXPECT_EQ(SDL_JOYSTICK_TYPE_UNKNOWN, type::unknown);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_GAMECONTROLLER, type::game_controller);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_WHEEL, type::wheel);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_ARCADE_STICK, type::arcade_stick);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_FLIGHT_STICK, type::flight_stick);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_DANCE_PAD, type::dance_pad);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_GUITAR, type::guitar);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_DRUM_KIT, type::drum_kit);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_ARCADE_PAD, type::arcade_pad);
  EXPECT_EQ(SDL_JOYSTICK_TYPE_THROTTLE, type::throttle);
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
  EXPECT_EQ(type, joystick.type());
  EXPECT_EQ(nAxes, joystick.axis_count());
  EXPECT_EQ(nButtons, joystick.button_count());
  EXPECT_EQ(nHats, joystick.hat_count());

  EXPECT_TRUE(joystick.set_virtual_axis(0, 123));
  EXPECT_TRUE(joystick.set_virtual_button(0, cen::button_state::pressed));
  EXPECT_TRUE(joystick.set_virtual_hat(0, cen::hat_state::centered));

  EXPECT_TRUE(cen::joystick::detach_virtual(*index));
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)