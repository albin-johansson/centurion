#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("joy_button_event::set_which", "[joy_button_event]")
{
  cen::joy_button_event event;

  const auto which = 92;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("joy_button_event::set_button", "[joy_button_event]")
{
  cen::joy_button_event event;

  const auto button = 44;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("joy_button_event::set_state", "[joy_button_event]")
{
  cen::joy_button_event event;

  const auto state = cen::button_state::pressed;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("joy_button_event::which", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.which = 27;

  cen::joy_button_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("joy_button_event::button", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.button = 99;

  cen::joy_button_event event{sdlEvent};

  CHECK(event.button() == sdlEvent.button);
}

TEST_CASE("joy_button_event::state", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  cen::joy_button_event event{sdlEvent};

  CHECK(event.state() == cen::button_state::released);
}

TEST_CASE("joy_button_event::pressed", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.state = SDL_PRESSED;

  cen::joy_button_event event{sdlEvent};

  CHECK(event.pressed());
}

TEST_CASE("joy_button_event::released", "[joy_button_event]")
{
  SDL_JoyButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  cen::joy_button_event event{sdlEvent};

  CHECK(event.released());
}