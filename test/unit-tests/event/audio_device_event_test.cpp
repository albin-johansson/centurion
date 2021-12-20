#include <gtest/gtest.h>

#include "event.hpp"

TEST(AudioDeviceEvent, Defaults)
{
  const cen::AudioDeviceEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::AudioDeviceAdded, event.GetType());
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::AudioDeviceEvent event;

  const Uint32 which = 7;
  event.SetWhich(which);

  ASSERT_EQ(which, event.GetWhich());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::AudioDeviceEvent event;

  event.SetCapture(true);
  ASSERT_TRUE(event.IsCapture());
  ASSERT_FALSE(event.IsOutput());

  event.SetCapture(false);
  ASSERT_FALSE(event.IsCapture());
  ASSERT_TRUE(event.IsOutput());
}

TEST(AudioDeviceEvent, AsSDLEvent)
{
  const cen::AudioDeviceEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.adevice.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.adevice.timestamp, event.GetTimestamp());
}
