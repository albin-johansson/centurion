#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("TextInputEvent::set_window_id", "[TextInputEvent]")
{
  text_input_event event;

  const auto id = 23;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("TextInputEvent::window_id", "[TextInputEvent]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 0, 8};
  text_input_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("TextInputEvent::text", "[TextInputEvent]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 1, 1, "hello"};
  text_input_event event{sdlEvent};
  CHECK_THAT(event.text().data(), Catch::Equals("hello"));
}

TEST_CASE("TextInputEvent()", "[TextInputEvent]")
{
  CHECK_NOTHROW(text_input_event{{}});
}
