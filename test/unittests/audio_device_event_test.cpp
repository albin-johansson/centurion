#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("audio_device_event constructors", "[audio_device_event]")
{
  CHECK_NOTHROW(ctn::audio_device_event{{}});

  SDL_AudioDeviceEvent e;
  CHECK_NOTHROW(ctn::audio_device_event{e});
}

TEST_CASE("audio_device_event::set_which", "[audio_device_event]")
{
  ctn::audio_device_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("audio_device_event::set_capture", "[audio_device_event]")
{
  ctn::audio_device_event event;

  event.set_capture(true);
  CHECK(event.capture());
  CHECK(!event.output());

  event.set_capture(false);
  CHECK(!event.capture());
  CHECK(event.output());
}

TEST_CASE("audio_device_event::which", "[audio_device_event]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.which = 23;

  ctn::audio_device_event event{sdl};

  CHECK(event.which() == sdl.which);
}

TEST_CASE("audio_device_event::output", "[audio_device_event]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = 0;

  ctn::audio_device_event event{sdl};

  CHECK(event.output());
}

TEST_CASE("audio_device_event::capture", "[audio_device_event]")
{
  SDL_AudioDeviceEvent sdl;
  sdl.iscapture = 1;

  ctn::audio_device_event event{sdl};

  CHECK(event.capture());
}