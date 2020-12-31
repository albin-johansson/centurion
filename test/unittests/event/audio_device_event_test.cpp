#include <gtest/gtest.h>

#include "event.hpp"

TEST(AudioDeviceEvent, Constructors)
{
  EXPECT_NO_THROW(cen::audio_device_event{});

  SDL_AudioDeviceEvent e;
  EXPECT_NO_THROW(cen::audio_device_event{e});
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::audio_device_event event;

  const auto which = 7;
  event.set_which(which);

  EXPECT_EQ(which, event.which());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::audio_device_event event;

  event.set_capture(true);
  EXPECT_TRUE(event.capture());
  EXPECT_FALSE(event.output());

  event.set_capture(false);
  EXPECT_FALSE(event.capture());
  EXPECT_TRUE(event.output());
}

TEST(AudioDeviceEvent, Which)
{
  SDL_AudioDeviceEvent sdl;
  sdl.which = 23;

  cen::audio_device_event event{sdl};
  EXPECT_EQ(sdl.which, event.which());
}

TEST(AudioDeviceEvent, Output)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_FALSE;

  cen::audio_device_event event{sdl};
  EXPECT_TRUE(event.output());
  EXPECT_FALSE(event.capture());
}

TEST(AudioDeviceEvent, Capture)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_TRUE;

  cen::audio_device_event event{sdl};
  EXPECT_TRUE(event.capture());
  EXPECT_FALSE(event.output());
}
