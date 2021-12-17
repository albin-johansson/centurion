#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(ControllerAxisEvent, Defaults)
{
  cen::controller_axis_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::controller_axis_motion, event.type());
}

TEST(ControllerAxisEvent, Constructors)
{
  ASSERT_NO_THROW(cen::controller_axis_event{});

  SDL_ControllerAxisEvent e;
  ASSERT_NO_THROW(cen::controller_axis_event{e});
}

TEST(ControllerAxisEvent, SetWhich)
{
  cen::controller_axis_event event;

  const SDL_JoystickID id = 53;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(ControllerAxisEvent, SetAxis)
{
  cen::controller_axis_event event;

  const auto axis = cen::ControllerAxis::TriggerRight;
  event.set_axis(axis);

  ASSERT_EQ(axis, event.axis());
}

TEST(ControllerAxisEvent, SetValue)
{
  cen::controller_axis_event event;

  const auto value = 4576;
  event.set_value(value);

  ASSERT_EQ(value, event.value());
}

TEST(ControllerAxisEvent, Which)
{
  SDL_ControllerAxisEvent sdl;
  sdl.which = 54;

  cen::controller_axis_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(ControllerAxisEvent, Axis)
{
  SDL_ControllerAxisEvent sdl;
  sdl.axis = static_cast<Uint8>(SDL_CONTROLLER_AXIS_INVALID);

  cen::controller_axis_event event{sdl};
  ASSERT_EQ(sdl.axis, static_cast<Uint8>(event.axis()));
}

TEST(ControllerAxisEvent, Value)
{
  SDL_ControllerAxisEvent sdl;
  sdl.value = 1234;

  cen::controller_axis_event event{sdl};
  ASSERT_EQ(sdl.value, event.value());
}

TEST(ControllerAxisEvent, AsSDLEvent)
{
  const cen::controller_axis_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.caxis.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.caxis.timestamp, event.time());
}