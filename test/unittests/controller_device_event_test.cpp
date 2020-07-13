#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("ControllerDeviceEvent::set_which", "[ControllerDeviceEvent]")
{
  controller_device_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(which == event.which());
}

TEST_CASE("ControllerDeviceEvent::which", "[ControllerDeviceEvent]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.which = 11;
  controller_device_event event{sdlEvent};

  CHECK(event.which() == 11);
}

TEST_CASE("ControllerDeviceEvent()", "[ControllerDeviceEvent]")
{
  CHECK_NOTHROW(controller_device_event{{}});
}