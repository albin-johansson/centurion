#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyAxisEvent, Defaults)
{
  const cen::JoyAxisEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyAxisMotion, event.GetType());
}

TEST(JoyAxisEvent, SetWhich)
{
  cen::JoyAxisEvent event;

  event.SetWhich(3);
  ASSERT_EQ(3, event.GetWhich());
}

TEST(JoyAxisEvent, SetAxis)
{
  cen::JoyAxisEvent event;

  event.SetAxis(7);
  ASSERT_EQ(7, event.GetAxis());
}

TEST(JoyAxisEvent, SetValue)
{
  cen::JoyAxisEvent event;

  event.SetValue(4'234);
  ASSERT_EQ(4'234, event.GetValue());
}

TEST(JoyAxisEvent, AsSDLEvent)
{
  const cen::JoyAxisEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.jaxis.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.jaxis.timestamp, event.GetTimestamp());
}
