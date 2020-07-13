#include <catch.hpp>

#include "event.hpp"

using namespace centurion;
using namespace centurion;

TEST_CASE("ControllerAxisEvent constructors", "[ControllerAxisEvent]")
{
  CHECK_NOTHROW(controller_axis_event{});
  CHECK_NOTHROW(controller_axis_event{{}});
}

TEST_CASE("ControllerAxisEvent::set_which", "[ControllerAxisEvent]")
{
  controller_axis_event event;

  const SDL_JoystickID id = 53;
  event.set_which(id);

  CHECK(event.which() == id);
}

TEST_CASE("ControllerAxisEvent::set_axis", "[ControllerAxisEvent]")
{
  controller_axis_event event;

  const auto axis = game_controller_axis::trigger_right;
  event.set_axis(axis);

  CHECK(event.axis() == axis);
}

TEST_CASE("ControllerAxisEvent::set_value", "[ControllerAxisEvent]")
{
  controller_axis_event event;

  const auto value = 4576;
  event.set_value(value);

  CHECK(event.value() == value);
}

TEST_CASE("ControllerAxisEvent::which", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.which = 54;
  controller_axis_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("ControllerAxisEvent::axis", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.axis = SDL_CONTROLLER_AXIS_INVALID;
  controller_axis_event event{sdlEvent};

  CHECK(event.axis() == static_cast<SDL_GameControllerAxis>(sdlEvent.axis));
}

TEST_CASE("ControllerAxisEvent::value", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.value = 1234;
  controller_axis_event event{sdlEvent};

  CHECK(event.value() == sdlEvent.value);
}
