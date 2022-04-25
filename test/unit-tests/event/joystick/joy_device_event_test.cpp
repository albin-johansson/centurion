#include <gtest/gtest.h>

#include "centurion/joystick_events.hpp"

TEST(JoyDeviceEvent, Defaults)
{
  const cen::joy_device_event event;
  ASSERT_EQ(cen::event_type::joy_device_added, event.type());
}

TEST(JoyDeviceEvent, SetWhich)
{
  cen::joy_device_event event;

  const cen::int32 which = 84;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(JoyDeviceEvent, AsSDLEvent)
{
  const cen::joy_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jdevice.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.jdevice.timestamp, event.timestamp().count());
}
