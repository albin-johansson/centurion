#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(ControllerDeviceEvent, Defaults)
{
  cen::controller_device_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::EventType::ControllerDeviceAdded, event.type());
}

TEST(ControllerDeviceEvent, Constructors)
{
  ASSERT_NO_THROW(cen::controller_device_event{});

  SDL_ControllerDeviceEvent e;
  ASSERT_NO_THROW(cen::controller_device_event{e});
}

TEST(ControllerDeviceEvent, SetWhich)
{
  cen::controller_device_event event;

  constexpr auto which = 4;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(ControllerDeviceEvent, Which)
{
  SDL_ControllerDeviceEvent sdl;
  sdl.which = 11;

  const cen::controller_device_event event{sdl};
  ASSERT_EQ(11, event.which());
}

TEST(ControllerDeviceEvent, AsSDLEvent)
{
  const cen::controller_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.cdevice.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.cdevice.timestamp, event.time());
}
