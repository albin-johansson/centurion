#include <catch.hpp>

#include "event.hpp"

using namespace centurion;
using namespace centurion::event;

TEST_CASE("ControllerButtonEvent::set_button", "[ControllerButtonEvent]")
{
  ControllerButtonEvent event;

  const auto button = GameControllerButton::A;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("ControllerButtonEvent::set_state", "[ControllerButtonEvent]")
{
  ControllerButtonEvent event;

  const auto state = ButtonState::Pressed;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("ControllerButtonEvent::set_which", "[ControllerButtonEvent]")
{
  ControllerButtonEvent event;

  const auto which = 7;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("ControllerButtonEvent::button", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.button = SDL_CONTROLLER_BUTTON_A;

  ControllerButtonEvent event{sdlEvent};
  CHECK(event.button() == GameControllerButton::A);
}

TEST_CASE("ControllerButtonEvent::state", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;

  ControllerButtonEvent event{sdlEvent};
  CHECK(event.state() == ButtonState::Released);
}

TEST_CASE("ControllerButtonEvent::which", "[ControllerButtonEvent]")
{
  SDL_ControllerButtonEvent sdlEvent;
  sdlEvent.which = 16;

  ControllerButtonEvent event{sdlEvent};
  CHECK(event.which() == 16);
}

TEST_CASE("ControllerButtonEvent()", "[ControllerButtonEvent]")
{
  CHECK_NOTHROW(ControllerButtonEvent{{}});
}