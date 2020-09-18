#include <catch.hpp>

#include "event.hpp"

TEST_CASE("controller_device_event::set_which", "[controller_device_event]")
{
  cen::controller_device_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(which == event.which());
}

TEST_CASE("controller_device_event::which", "[controller_device_event]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.which = 11;
  cen::controller_device_event event{sdlEvent};

  CHECK(event.which() == 11);
}

TEST_CASE("controller_device_event()", "[controller_device_event]")
{
  CHECK_NOTHROW(cen::controller_device_event{{}});
}