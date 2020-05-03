#include "common_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("CommonEvent::time", "[CommonEvent]")
{
  const auto time = 735;

  SDL_QuitEvent quitEvent;
  quitEvent.timestamp = time;

  CommonEvent<SDL_QuitEvent> event{quitEvent};

  CHECK(event.time() == time);
}

TEST_CASE("AudioDeviceEvent::type", "[AudioDeviceEvent]")
{
  SDL_QuitEvent quitEvent;
  quitEvent.type = SDL_MOUSEMOTION;

  CommonEvent<SDL_QuitEvent> event{quitEvent};

  CHECK(event.type() == EventType::MouseMotion);
}