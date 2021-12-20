#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyDeviceEvent, Defaults)
{
  const cen::JoyDeviceEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyDeviceAdded, event.GetType());
}

TEST(JoyDeviceEvent, SetWhich)
{
  cen::JoyDeviceEvent event;

  event.SetWhich(84);
  ASSERT_EQ(84, event.GetWhich());
}

TEST(JoyDeviceEvent, AsSDLEvent)
{
  const cen::JoyDeviceEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.jdevice.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.jdevice.timestamp, event.GetTimestamp());
}
