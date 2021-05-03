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

TEST(Joystick, PowerEnum)
{
  ASSERT_EQ(cen::joystick_power::unknown, SDL_JOYSTICK_POWER_UNKNOWN);
  ASSERT_EQ(cen::joystick_power::empty, SDL_JOYSTICK_POWER_EMPTY);
  ASSERT_EQ(cen::joystick_power::low, SDL_JOYSTICK_POWER_LOW);
  ASSERT_EQ(cen::joystick_power::medium, SDL_JOYSTICK_POWER_MEDIUM);
  ASSERT_EQ(cen::joystick_power::full, SDL_JOYSTICK_POWER_FULL);
  ASSERT_EQ(cen::joystick_power::wired, SDL_JOYSTICK_POWER_WIRED);
  ASSERT_EQ(cen::joystick_power::max, SDL_JOYSTICK_POWER_MAX);

  ASSERT_EQ(SDL_JOYSTICK_POWER_UNKNOWN, cen::joystick_power::unknown);
  ASSERT_EQ(SDL_JOYSTICK_POWER_EMPTY, cen::joystick_power::empty);
  ASSERT_EQ(SDL_JOYSTICK_POWER_LOW, cen::joystick_power::low);
  ASSERT_EQ(SDL_JOYSTICK_POWER_MEDIUM, cen::joystick_power::medium);
  ASSERT_EQ(SDL_JOYSTICK_POWER_FULL, cen::joystick_power::full);
  ASSERT_EQ(SDL_JOYSTICK_POWER_WIRED, cen::joystick_power::wired);
  ASSERT_EQ(SDL_JOYSTICK_POWER_MAX, cen::joystick_power::max);

  ASSERT_NE(cen::joystick_power::max, SDL_JOYSTICK_POWER_WIRED);
  ASSERT_NE(SDL_JOYSTICK_POWER_MEDIUM, cen::joystick_power::low);
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

TEST(Joystick, TypeEnum)
{
  using type = cen::joystick_type;

  ASSERT_EQ(type::unknown, SDL_JOYSTICK_TYPE_UNKNOWN);
  ASSERT_EQ(type::game_controller, SDL_JOYSTICK_TYPE_GAMECONTROLLER);
  ASSERT_EQ(type::wheel, SDL_JOYSTICK_TYPE_WHEEL);
  ASSERT_EQ(type::arcade_stick, SDL_JOYSTICK_TYPE_ARCADE_STICK);
  ASSERT_EQ(type::flight_stick, SDL_JOYSTICK_TYPE_FLIGHT_STICK);
  ASSERT_EQ(type::dance_pad, SDL_JOYSTICK_TYPE_DANCE_PAD);
  ASSERT_EQ(type::guitar, SDL_JOYSTICK_TYPE_GUITAR);
  ASSERT_EQ(type::drum_kit, SDL_JOYSTICK_TYPE_DRUM_KIT);
  ASSERT_EQ(type::arcade_pad, SDL_JOYSTICK_TYPE_ARCADE_PAD);
  ASSERT_EQ(type::throttle, SDL_JOYSTICK_TYPE_THROTTLE);

  ASSERT_EQ(SDL_JOYSTICK_TYPE_UNKNOWN, type::unknown);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GAMECONTROLLER, type::game_controller);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_WHEEL, type::wheel);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_STICK, type::arcade_stick);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_FLIGHT_STICK, type::flight_stick);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DANCE_PAD, type::dance_pad);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_GUITAR, type::guitar);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_DRUM_KIT, type::drum_kit);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_ARCADE_PAD, type::arcade_pad);
  ASSERT_EQ(SDL_JOYSTICK_TYPE_THROTTLE, type::throttle);
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