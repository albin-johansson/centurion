#include <catch.hpp>

#include "event.hpp"

using namespace centurion;
using namespace centurion;

TEST_CASE("ControllerButtonEvent::set_button", "[ControllerButtonEvent]")
{
  controller_button_event event;

  const auto button = game_controller_button::a;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("ControllerButtonEvent::set_state", "[ControllerButtonEvent]")
{
  controller_button_event event;

  const auto state = button_state::pressed;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("ControllerButtonEvent::set_which", "[ControllerButtonEvent]")
{
  controller_button_event event;

  const auto which = 7;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("ControllerButtonEvent::button", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.button = SDL_CONTROLLER_BUTTON_A;

  controller_button_event event{sdlEvent};
  CHECK(event.button() == game_controller_button::a);
}

TEST_CASE("ControllerButtonEvent::state", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  controller_button_event event{sdlEvent};
  CHECK(event.state() == button_state::released);
}

TEST_CASE("ControllerButtonEvent::which", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.which = 16;

  controller_button_event event{sdlEvent};
  CHECK(event.which() == 16);
}

TEST_CASE("ControllerButtonEvent()", "[ControllerButtonEvent]")
{
  CHECK_NOTHROW(controller_button_event{{}});
}