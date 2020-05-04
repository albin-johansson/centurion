#include "text_editing_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("TextEditingEvent::set_window_id", "[TextEditingEvent]")
{
  TextEditingEvent event;

  const auto id = 8;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("TextEditingEvent::set_start", "[TextEditingEvent]")
{
  TextEditingEvent event;

  const auto start = 4;
  event.set_start(start);

  CHECK(event.start() == start);
}

TEST_CASE("TextEditingEvent::set_length", "[TextEditingEvent]")
{
  TextEditingEvent event;

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

TEST_CASE("TextEditingEvent::window_id", "[TextEditingEvent]")
{
  SDL_TextEditingEvent sdlEvent;
  sdlEvent.windowID = 7;
  TextEditingEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("TextEditingEvent::start", "[TextEditingEvent]")
{
  SDL_TextEditingEvent sdlEvent;
  sdlEvent.start = 4;
  TextEditingEvent event{sdlEvent};

  CHECK(event.start() == sdlEvent.start);
}

TEST_CASE("TextEditingEvent::length", "[TextEditingEvent]")
{
  SECTION("Good length")
  {
    SDL_TextEditingEvent sdlEvent;
    sdlEvent.length = 4;
    TextEditingEvent event{sdlEvent};

    CHECK(event.length() == sdlEvent.length);
  }

  SECTION("Underflow length")
  {
    SDL_TextEditingEvent sdlEvent;
    sdlEvent.length = -1;
    TextEditingEvent event{sdlEvent};

    CHECK(event.length() == 0);
  }

  SECTION("Overflow length")
  {
    SDL_TextEditingEvent sdlEvent;
    sdlEvent.length = 33;
    TextEditingEvent event{sdlEvent};

    CHECK(event.length() == 32);
  }
}