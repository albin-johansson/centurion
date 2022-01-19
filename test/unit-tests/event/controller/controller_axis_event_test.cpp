#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerAxisEvent, Defaults)
{
  const cen::controller_axis_event event;
  ASSERT_EQ(cen::event_type::controller_axis_motion, event.type());
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

  const cen::int16 value = 4576;
  event.set_value(value);

  ASSERT_EQ(value, event.value());
}

TEST(ControllerAxisEvent, AsSDLEvent)
{
  const cen::controller_axis_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.caxis.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.caxis.timestamp, event.timestamp().count());
}