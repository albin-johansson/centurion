#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("ControllerDeviceEvent::set_which", "[ControllerDeviceEvent]")
{
  ControllerDeviceEvent event;

  const auto which = 7;
  event.set_which(which);

  CHECK(which == event.which());
}

TEST_CASE("ControllerDeviceEvent::which", "[ControllerDeviceEvent]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.which = 11;
  ControllerDeviceEvent event{sdlEvent};

  CHECK(event.which() == 11);
}

TEST_CASE("ControllerDeviceEvent()", "[ControllerDeviceEvent]")
{
  CHECK_NOTHROW(ControllerDeviceEvent{{}});
}