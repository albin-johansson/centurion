#include "controller_device_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("ControllerDeviceEvent::set_type", "[ControllerDeviceEvent]")
{
  ControllerDeviceEvent event;

  const auto type = ControllerDeviceEventType::Added;
  event.set_type(type);

  CHECK(type == event.type());
}

TEST_CASE("ControllerDeviceEvent::set_which", "[ControllerDeviceEvent]")
{
  ControllerDeviceEvent event;

  const auto which = 7;
  event.set_which(which);

  CHECK(which == event.which());
}

TEST_CASE("ControllerDeviceEvent::type", "[ControllerDeviceEvent]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.type = SDL_CONTROLLERDEVICEREMAPPED;
  ControllerDeviceEvent event{sdlEvent};

  CHECK(event.type() == ControllerDeviceEventType::Remapped);
}

TEST_CASE("ControllerDeviceEvent::which", "[ControllerDeviceEvent]")
{
  SDL_ControllerDeviceEvent sdlEvent;
  sdlEvent.which = 11;
  ControllerDeviceEvent event{sdlEvent};

  CHECK(event.which() == 11);
}