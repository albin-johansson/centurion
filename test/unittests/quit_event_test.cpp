#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("QuitEvent()", "[QuitEvent]")
{
  CHECK_NOTHROW(quit_event{});
}

TEST_CASE("QuitEvent(const SDL_QuitEvent&)", "[QuitEvent]")
{
  SDL_QuitEvent qEvent;
  CHECK_NOTHROW(quit_event{qEvent});
}
