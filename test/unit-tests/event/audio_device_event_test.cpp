#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(AudioDeviceEvent, Defaults)
{
  cen::audio_device_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::audio_device_added, event.type());
}

TEST(AudioDeviceEvent, Constructors)
{
  ASSERT_NO_THROW(cen::audio_device_event{});

  SDL_AudioDeviceEvent e;
  ASSERT_NO_THROW(cen::audio_device_event{e});
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::audio_device_event event;

  const auto which = 7;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::audio_device_event event;

  event.set_capture(true);
  ASSERT_TRUE(event.capture());
  ASSERT_FALSE(event.output());

  event.set_capture(false);
  ASSERT_FALSE(event.capture());
  ASSERT_TRUE(event.output());
}

TEST(AudioDeviceEvent, Which)
{
  SDL_AudioDeviceEvent sdl;
  sdl.which = 23;

  cen::audio_device_event event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(AudioDeviceEvent, Output)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_FALSE;

  cen::audio_device_event event{sdl};
  ASSERT_TRUE(event.output());
  ASSERT_FALSE(event.capture());
}

TEST(AudioDeviceEvent, Capture)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_TRUE;

  cen::audio_device_event event{sdl};
  ASSERT_TRUE(event.capture());
  ASSERT_FALSE(event.output());
}

TEST(AudioDeviceEvent, AsSDLEvent)
{
  const cen::audio_device_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.adevice.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.adevice.timestamp, event.time());
}
