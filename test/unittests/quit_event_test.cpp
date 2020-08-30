#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("quit_event()", "[quit_event]")
{
  CHECK_NOTHROW(cen::quit_event{});
}

TEST_CASE("quit_event(const SDL_QuitEvent&)", "[quit_event]")
{
  SDL_QuitEvent qEvent;
  CHECK_NOTHROW(cen::quit_event{qEvent});
}
