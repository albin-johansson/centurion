#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyHatEvent, Defaults)
{
  const cen::JoyHatEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyHatMotion, event.GetType());
}

TEST(JoyHatEvent, SetHat)
{
  cen::JoyHatEvent event;

  event.SetHat(7);
  ASSERT_EQ(7, event.GetHat());
}

TEST(JoyHatEvent, SetPosition)
{
  cen::JoyHatEvent event;

  event.SetPosition(cen::JoyHatPosition::Right);
  ASSERT_EQ(cen::JoyHatPosition::Right, event.GetPosition());
}

TEST(JoyHatEvent, AsSDLEvent)
{
  const cen::JoyHatEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.jhat.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.jhat.timestamp, event.GetTimestamp());
}
