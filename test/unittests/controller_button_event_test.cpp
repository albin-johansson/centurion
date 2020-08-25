#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("controller_button_event::set_button", "[controller_button_event]")
{
  ctn::controller_button_event event;

  const auto button = ctn::gamepad_button::a;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("controller_button_event::set_state", "[controller_button_event]")
{
  ctn::controller_button_event event;

  const auto state = ctn::button_state::pressed;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("controller_button_event::set_which", "[controller_button_event]")
{
  ctn::controller_button_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("controller_button_event::button", "[controller_button_event]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.button = SDL_CONTROLLER_BUTTON_A;

  ctn::controller_button_event event{sdlEvent};
  CHECK(event.button() == ctn::gamepad_button::a);
}

TEST_CASE("controller_button_event::state", "[controller_button_event]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  ctn::controller_button_event event{sdlEvent};
  CHECK(event.state() == ctn::button_state::released);
}

TEST_CASE("controller_button_event::which", "[controller_button_event]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.which = 16;

  ctn::controller_button_event event{sdlEvent};
  CHECK(event.which() == 16);
}

TEST_CASE("controller_button_event()", "[controller_button_event]")
{
  CHECK_NOTHROW(ctn::controller_button_event{{}});
}