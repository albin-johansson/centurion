#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("controller_device_event::set_which", "[controller_device_event]")
{
  ctn::controller_device_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(which == event.which());
}

TEST_CASE("controller_device_event::which", "[controller_device_event]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.which = 11;
  ctn::controller_device_event event{sdlEvent};

  CHECK(event.which() == 11);
}

TEST_CASE("controller_device_event()", "[controller_device_event]")
{
  CHECK_NOTHROW(ctn::controller_device_event{{}});
}