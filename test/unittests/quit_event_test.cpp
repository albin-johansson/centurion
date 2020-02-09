#include "catch.hpp"
#include "event.h"

using namespace centurion;
using namespace centurion::event;

TEST_CASE("QuitEvent(SDL_QuitEvent)", "[QuitEvent]") {
  SDL_QuitEvent sdlEvent{};
  CHECK_NOTHROW(QuitEvent{sdlEvent});
}

TEST_CASE("QuitEvent::get_time", "[QuitEvent]") {
  const auto time = 8191278U;
  const auto event = [time]() noexcept {
    SDL_QuitEvent sdlEvent{};
    sdlEvent.timestamp = time;
    return QuitEvent{sdlEvent};
  }();
  CHECK(event.get_time() == time);
}