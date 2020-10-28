#include <catch.hpp>

#include "event.hpp"

TEST_CASE("JoyDeviceEvent::set_which", "[JoyDeviceEvent]")
{
  cen::joy_device_event event;

  const auto which = 84;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("JoyDeviceEvent::which", "[JoyDeviceEvent]")
{
  SDL_JoyDeviceEvent sdlEvent;
  sdlEvent.which = 27;

  cen::joy_device_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}