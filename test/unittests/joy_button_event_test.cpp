#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("joy_button_event::set_which", "[joy_button_event]")
{
  ctn::joy_button_event event;

  const auto which = 92;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("joy_button_event::set_button", "[joy_button_event]")
{
  ctn::joy_button_event event;

  const auto button = 44;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("joy_button_event::set_state", "[joy_button_event]")
{
  ctn::joy_button_event event;

  const auto state = ctn::button_state::pressed;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("joy_button_event::which", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.which = 27;

  ctn::joy_button_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("joy_button_event::button", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.button = 99;

  ctn::joy_button_event event{sdlEvent};

  CHECK(event.button() == sdlEvent.button);
}

TEST_CASE("joy_button_event::state", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  ctn::joy_button_event event{sdlEvent};

  CHECK(event.state() == ctn::button_state::released);
}