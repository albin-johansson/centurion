#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerDeviceEvent, Defaults)
{
  cen::controller_device_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::controller_device_added, event.type());
}

TEST(ControllerDeviceEvent, Constructors)
{
  EXPECT_NO_THROW(cen::controller_device_event{});

  SDL_ControllerDeviceEvent e;
  EXPECT_NO_THROW(cen::controller_device_event{e});
}

TEST(ControllerDeviceEvent, SetWhich)
{
  cen::controller_device_event event;

  constexpr auto which = 4;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(ControllerDeviceEvent, Which)
{
  SDL_ControllerDeviceEvent sdl;
  sdl.which = 11;

  const cen::controller_device_event event{sdl};
  EXPECT_EQ(11, event.which());
}

TEST(ControllerDeviceEvent, AsSDLEvent)
{
  const cen::controller_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.cdevice.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.cdevice.timestamp, event.time());
}
