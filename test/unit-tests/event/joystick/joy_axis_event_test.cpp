#include <gtest/gtest.h>

#include "centurion/joystick_events.hpp"

TEST(JoyAxisEvent, Defaults)
{
  const cen::joy_axis_event event;
  ASSERT_EQ(cen::event_type::joy_axis_motion, event.type());
}

TEST(JoyAxisEvent, SetWhich)
{
  cen::joy_axis_event event;

  const SDL_JoystickID id = 3;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(JoyAxisEvent, SetAxis)
{
  cen::joy_axis_event event;

  const cen::uint8 axis = 42;
  event.set_axis(axis);

  ASSERT_EQ(axis, event.axis());
}

TEST(JoyAxisEvent, SetValue)
{
  cen::joy_axis_event event;

  const cen::int16 value = 4'234;
  event.set_value(value);

  ASSERT_EQ(value, event.value());
}

TEST(JoyAxisEvent, AsSDLEvent)
{
  const cen::joy_axis_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jaxis.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jaxis.timestamp, event.timestamp().count());
}
