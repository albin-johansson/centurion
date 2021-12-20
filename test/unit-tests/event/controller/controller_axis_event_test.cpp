#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(ControllerAxisEvent, Defaults)
{
  const cen::ControllerAxisEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::ControllerAxisMotion, event.GetType());
}

TEST(ControllerAxisEvent, SetWhich)
{
  cen::ControllerAxisEvent event;

  const SDL_JoystickID id = 53;
  event.SetWhich(id);

  ASSERT_EQ(id, event.GetWhich());
}

TEST(ControllerAxisEvent, SetAxis)
{
  cen::ControllerAxisEvent event;

  const auto axis = cen::ControllerAxis::TriggerRight;
  event.SetAxis(axis);

  ASSERT_EQ(axis, event.GetAxis());
}

TEST(ControllerAxisEvent, SetValue)
{
  cen::ControllerAxisEvent event;

  const auto value = 4576;
  event.SetValue(value);

  ASSERT_EQ(value, event.GetValue());
}

TEST(ControllerAxisEvent, AsSDLEvent)
{
  const cen::ControllerAxisEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.caxis.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.caxis.timestamp, event.GetTimestamp());
}