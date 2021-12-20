#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(ControllerDeviceEvent, Defaults)
{
  const cen::ControllerDeviceEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::ControllerDeviceAdded, event.GetType());
}

TEST(ControllerDeviceEvent, SetWhich)
{
  cen::ControllerDeviceEvent event;

  constexpr auto which = 4;
  event.SetWhich(which);

  ASSERT_EQ(which, event.GetWhich());
}

TEST(ControllerDeviceEvent, AsSDLEvent)
{
  const cen::ControllerDeviceEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.cdevice.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.cdevice.timestamp, event.GetTimestamp());
}
