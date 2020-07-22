#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("text_input_event::set_window_id", "[text_input_event]")
{
  ctn::text_input_event event;

  const auto id = 23;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("text_input_event::window_id", "[text_input_event]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 0, 8};
  ctn::text_input_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("text_input_event::text_utf8", "[text_input_event]")
{
  SDL_TextInputEvent sdlEvent{SDL_TEXTINPUT, 1, 1, "hello"};
  ctn::text_input_event event{sdlEvent};
  CHECK_THAT(event.text_utf8().data(), Catch::Equals("hello"));
}

TEST_CASE("text_input_event()", "[text_input_event]")
{
  CHECK_NOTHROW(ctn::text_input_event{{}});
}
