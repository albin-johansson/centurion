#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyAxisEvent, Defaults)
{
  cen::joy_axis_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::joystick_axis_motion, event.type());
}

TEST(JoyAxisEvent, SetWhich)
{
  cen::joy_axis_event event;

  constexpr auto which = 3;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(JoyAxisEvent, SetAxis)
{
  cen::joy_axis_event event;

  constexpr auto axis = 7;
  event.set_axis(axis);

  EXPECT_EQ(axis, event.axis());
}

TEST(JoyAxisEvent, SetValue)
{
  cen::joy_axis_event event;

  constexpr auto value = 4'234;
  event.set_value(value);

  EXPECT_EQ(value, event.value());
}

TEST(JoyAxisEvent, Which)
{
  SDL_JoyAxisEvent sdl;
  sdl.which = 23;

  const cen::joy_axis_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(JoyAxisEvent, Axis)
{
  SDL_JoyAxisEvent sdl;
  sdl.axis = 5;

  const cen::joy_axis_event event{sdl};
  EXPECT_EQ(sdl.axis, event.axis());
}

TEST(JoyAxisEvent, Value)
{
  SDL_JoyAxisEvent sdl;
  sdl.value = 1'864;

  const cen::joy_axis_event event{sdl};
  EXPECT_EQ(sdl.value, event.value());
}
