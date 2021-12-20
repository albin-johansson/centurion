#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(AudioDeviceEvent, Defaults)
{
  cen::AudioDeviceEvent event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::EventType::AudioDeviceAdded, event.type());
}

TEST(AudioDeviceEvent, Constructors)
{
  ASSERT_NO_THROW(cen::AudioDeviceEvent{});

  SDL_AudioDeviceEvent e;
  ASSERT_NO_THROW(cen::AudioDeviceEvent{e});
}

TEST(AudioDeviceEvent, SetWhich)
{
  cen::AudioDeviceEvent event;

  const Uint32 which = 7;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(AudioDeviceEvent, SetCapture)
{
  cen::AudioDeviceEvent event;

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

  cen::AudioDeviceEvent event{sdl};
  ASSERT_EQ(sdl.which, event.which());
}

TEST(AudioDeviceEvent, Output)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_FALSE;

  cen::AudioDeviceEvent event{sdl};
  ASSERT_TRUE(event.output());
  ASSERT_FALSE(event.capture());
}

TEST(AudioDeviceEvent, Capture)
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = SDL_TRUE;

  cen::AudioDeviceEvent event{sdl};
  ASSERT_TRUE(event.capture());
  ASSERT_FALSE(event.output());
}

TEST(AudioDeviceEvent, AsSDLEvent)
{
  const cen::AudioDeviceEvent event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.adevice.type, cen::ToUnderlying(event.type()));
  ASSERT_EQ(sdl.adevice.timestamp, event.time());
}
