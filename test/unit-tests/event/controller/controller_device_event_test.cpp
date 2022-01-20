#include <gtest/gtest.h>

#include "centurion/event.hpp"

TEST(ControllerDeviceEvent, Defaults)
{
  const cen::controller_device_event event;
  ASSERT_EQ(cen::event_type::controller_device_added, event.type());
}

TEST(ControllerDeviceEvent, SetWhich)
{
  cen::controller_device_event event;

  const cen::int32 which = 4;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(ControllerDeviceEvent, AsSDLEvent)
{
  const cen::controller_device_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.cdevice.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.cdevice.timestamp, event.timestamp().count());
}
