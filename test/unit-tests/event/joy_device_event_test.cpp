#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyDeviceEvent, Defaults)
{
  cen::joy_device_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::joystick_device_added, event.type());
}

TEST(JoyDeviceEvent, SetWhich)
{
  cen::joy_device_event event;

  constexpr auto which = 84;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(JoyDeviceEvent, Which)
{
  SDL_JoyDeviceEvent sdl;
  sdl.which = 27;

  const cen::joy_device_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(JoyDeviceEvent, AsSDLEvent)
{
  const cen::joy_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.jdevice.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.jdevice.timestamp, event.time());
}
