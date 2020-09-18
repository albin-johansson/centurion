#include <catch.hpp>

#include "event.hpp"

TEST_CASE("text_editing_event::set_window_id", "[text_editing_event]")
{
  cen::text_editing_event event{};

  const auto id = 8;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("text_editing_event::set_start", "[text_editing_event]")
{
  cen::text_editing_event event{};

  const auto start = 4;
  event.set_start(start);

  CHECK(event.start() == start);
}

TEST_CASE("text_editing_event::set_length", "[text_editing_event]")
{
  cen::text_editing_event event{};

  const auto length = 9;
  event.set_length(length);

  CHECK(event.length() == length);

  SECTION("Value less than 0")
  {
    event.set_length(-1);
    CHECK(event.length() == 0);
  }

  SECTION("Value greater than 32")
  {
    event.set_length(33);
    CHECK(event.length() == 32);
  }
}

TEST_CASE("text_editing_event::window_id", "[text_editing_event]")
{
  SDL_TextEditingEvent sdlEvent{};
  sdlEvent.windowID = 7;
  cen::text_editing_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("text_editing_event::start", "[text_editing_event]")
{
  SDL_TextEditingEvent sdlEvent{};
  sdlEvent.start = 4;
  cen::text_editing_event event{sdlEvent};

  CHECK(event.start() == sdlEvent.start);
}

TEST_CASE("text_editing_event::length", "[text_editing_event]")
{
  SECTION("Good length")
  {
    SDL_TextEditingEvent sdlEvent{};
    sdlEvent.length = 4;
    cen::text_editing_event event{sdlEvent};

    CHECK(event.length() == sdlEvent.length);
  }

  SECTION("Underflow length")
  {
    SDL_TextEditingEvent sdlEvent{};
    sdlEvent.length = -1;
    cen::text_editing_event event{sdlEvent};

    CHECK(event.length() == 0);
  }

  SECTION("Overflow length")
  {
    SDL_TextEditingEvent sdlEvent{};
    sdlEvent.length = 33;
    cen::text_editing_event event{sdlEvent};

    CHECK(event.length() == 32);
  }
}

TEST_CASE("text_editing_event()", "[text_editing_event]")
{
  CHECK_NOTHROW(cen::text_editing_event{{}});
}