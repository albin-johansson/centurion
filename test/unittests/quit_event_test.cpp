#include <catch.hpp>

#include "event.hpp"

using namespace centurion::event;

TEST_CASE("QuitEvent()", "[QuitEvent]")
{
  CHECK_NOTHROW(QuitEvent{});
}

TEST_CASE("QuitEvent(const SDL_QuitEvent&)", "[QuitEvent]")
{
  SDL_QuitEvent qEvent;
  CHECK_NOTHROW(QuitEvent{qEvent});
}
