#include "quit_event.hpp"

#include <catch.hpp>

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

TEST_CASE("QuitEvent(SDL_QuitEvent&&)", "[QuitEvent]")
{
  CHECK_NOTHROW(QuitEvent{{}});
}