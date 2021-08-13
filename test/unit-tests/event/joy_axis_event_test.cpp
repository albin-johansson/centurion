#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyAxisEvent, Defaults)
{
  cen::joy_axis_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::joystick_axis_motion, event.type());
}

TEST(JoyAxisEvent, SetWhich)
{
  cen::joy_axis_event event;

  constexpr auto which = 3;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(JoyAxisEvent, SetAxis)
{
  cen::joy_axis_event event;

  constexpr auto axis = 7;
  event.set_axis(axis);

  ASSERT_EQ(axis, event.axis());
}

TEST(JoyAxisEvent, SetValue)
{
  cen::joy_axis_event event;

  constexpr auto value = 4'234;
  event.set_value(value);

  ASSERT_EQ(value, event.value());
}

TEST(JoyAxisEvent, Which)
{
  SDL_JoyAxisEvent sdl;
  sdl.which = 23;

  const cen::joy_axis_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(JoyAxisEvent, Axis)
{
  SDL_JoyAxisEvent sdl;
  sdl.axis = 5;

  const cen::joy_axis_event event{sdl};
  ASSERT_EQ(sdl.axis, event.axis());
}

TEST(JoyAxisEvent, Value)
{
  SDL_JoyAxisEvent sdl;
  sdl.value = 1'864;

  const cen::joy_axis_event event{sdl};
  ASSERT_EQ(sdl.value, event.value());
}

TEST(JoyAxisEvent, AsSDLEvent)
{
  const cen::joy_axis_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jaxis.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jaxis.timestamp, event.time());
}
