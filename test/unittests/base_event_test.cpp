#include "base_event.h"

#include <SDL.h>

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("BaseEvent::time", "[BaseEvent]")
{
  const auto time = 735;
  SDL_QuitEvent quitEvent{0, time};
  BaseEvent<SDL_QuitEvent> event{quitEvent};

  CHECK(event.time() == time);
}
