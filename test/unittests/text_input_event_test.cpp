#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("TextInputEvent::set_window_id", "[TextInputEvent]")
{
  TextInputEvent event;

  const auto id = 23;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("TextInputEvent::window_id", "[TextInputEvent]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 0, 8};
  TextInputEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("TextInputEvent::text", "[TextInputEvent]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 1, 1, "hello"};
  TextInputEvent event{sdlEvent};
  CHECK_THAT(event.text(), Catch::Equals("hello"));
}

TEST_CASE("TextInputEvent()", "[TextInputEvent]")
{
  CHECK_NOTHROW(TextInputEvent{{}});
}
