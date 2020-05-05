#include "joy_device_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("JoyDeviceEvent move constructor", "[JoyDeviceEvent]")
{
  CHECK_NOTHROW(JoyDeviceEvent{{}});
}

TEST_CASE("JoyDeviceEvent::set_which", "[JoyDeviceEvent]")
{
  JoyDeviceEvent event;

  const auto which = 84;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("JoyDeviceEvent::which", "[JoyDeviceEvent]")
{
  SDL_JoyDeviceEvent sdlEvent;
  sdlEvent.which = 27;
  JoyDeviceEvent event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}