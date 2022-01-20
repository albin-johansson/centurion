#include <gtest/gtest.h>

#include "centurion/event.hpp"

TEST(AudioDeviceEvent, Defaults)
{
  const cen::audio_device_event event;
  ASSERT_EQ(cen::event_type::audio_device_added, event.type());
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::audio_device_event event;

  const Uint32 which = 7;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::audio_device_event event;

  event.set_capture(true);
  ASSERT_TRUE(event.is_capture());
  ASSERT_FALSE(event.is_output());

  event.set_capture(false);
  ASSERT_FALSE(event.is_capture());
  ASSERT_TRUE(event.is_output());
}

TEST(AudioDeviceEvent, AsSDLEvent)
{
  const cen::audio_device_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.adevice.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.adevice.timestamp, event.timestamp().count());
}
