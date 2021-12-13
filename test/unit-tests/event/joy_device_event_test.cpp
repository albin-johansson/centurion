#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyDeviceEvent, Defaults)
{
  cen::joy_device_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::joystick_device_added, event.type());
}

TEST(JoyDeviceEvent, SetWhich)
{
  cen::joy_device_event event;

  constexpr auto which = 84;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(JoyDeviceEvent, Which)
{
  SDL_JoyDeviceEvent sdl;
  sdl.which = 27;

  const cen::joy_device_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(JoyDeviceEvent, AsSDLEvent)
{
  const cen::joy_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.jdevice.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.jdevice.timestamp, event.time());
}
