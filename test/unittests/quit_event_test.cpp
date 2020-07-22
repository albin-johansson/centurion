#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("quit_event()", "[quit_event]")
{
  CHECK_NOTHROW(ctn::quit_event{});
}

TEST_CASE("quit_event(const SDL_QuitEvent&)", "[quit_event]")
{
  SDL_QuitEvent qEvent;
  CHECK_NOTHROW(ctn::quit_event{qEvent});
}
