#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("AudioDeviceEvent constructors", "[AudioDeviceEvent]")
{
  CHECK_NOTHROW(audio_device_event{{}});

  SDL_AudioDeviceEvent e;
  CHECK_NOTHROW(audio_device_event{e});
}

TEST_CASE("AudioDeviceEvent::set_which", "[AudioDeviceEvent]")
{
  audio_device_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("AudioDeviceEvent::set_capture", "[AudioDeviceEvent]")
{
  audio_device_event event;

  event.set_capture(true);
  CHECK(event.capture());
  CHECK(!event.output());

  event.set_capture(false);
  CHECK(!event.capture());
  CHECK(event.output());
}

TEST_CASE("AudioDeviceEvent::which", "[AudioDeviceEvent]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.which = 23;
  audio_device_event event{sdl};

  CHECK(event.which() == sdl.which);
}

TEST_CASE("AudioDeviceEvent::output", "[AudioDeviceEvent]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = 0;
  audio_device_event event{sdl};

  CHECK(event.output());
}

TEST_CASE("AudioDeviceEvent::capture", "[AudioDeviceEvent]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = 1;
  audio_device_event event{sdl};

  CHECK(event.capture());
}