#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyDeviceEvent, Defaults)
{
  cen::joy_device_event event;
  EXPECT_GT(event.time(), 0);
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
