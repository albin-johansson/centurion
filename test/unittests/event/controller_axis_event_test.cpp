#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerAxisEvent, Defaults)
{
  cen::controller_axis_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::controller_axis_motion, event.type());
}

TEST(ControllerAxisEvent, Constructors)
{
  EXPECT_NO_THROW(cen::controller_axis_event{});

  SDL_ControllerAxisEvent e;
  EXPECT_NO_THROW(cen::controller_axis_event{e});
}

TEST(ControllerAxisEvent, SetWhich)
{
  cen::controller_axis_event event;

  const SDL_JoystickID id = 53;
  event.set_which(id);

  EXPECT_EQ(id, event.which());
}

TEST(ControllerAxisEvent, SetAxis)
{
  cen::controller_axis_event event;

  const auto axis = cen::controller_axis::trigger_right;
  event.set_axis(axis);

  EXPECT_EQ(axis, event.axis());
}

TEST(ControllerAxisEvent, SetValue)
{
  cen::controller_axis_event event;

  const auto value = 4576;
  event.set_value(value);

  EXPECT_EQ(value, event.value());
}

TEST(ControllerAxisEvent, Which)
{
  SDL_ControllerAxisEvent sdl;
  sdl.which = 54;

  cen::controller_axis_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(ControllerAxisEvent, Axis)
{
  SDL_ControllerAxisEvent sdl;
  sdl.axis = SDL_CONTROLLER_AXIS_INVALID;

  cen::controller_axis_event event{sdl};
  EXPECT_EQ(sdl.axis, static_cast<cen::u8>(event.axis()));
}

TEST(ControllerAxisEvent, Value)
{
  SDL_ControllerAxisEvent sdl;
  sdl.value = 1234;

  cen::controller_axis_event event{sdl};
  EXPECT_EQ(sdl.value, event.value());
}
