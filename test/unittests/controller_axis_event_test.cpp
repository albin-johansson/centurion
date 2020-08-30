#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("controller_axis_event constructors", "[controller_axis_event]")
{
  CHECK_NOTHROW(cen::controller_axis_event{});
  CHECK_NOTHROW(cen::controller_axis_event{{}});
}

TEST_CASE("controller_axis_event::set_which", "[controller_axis_event]")
{
  cen::controller_axis_event event;

  const SDL_JoystickID id = 53;
  event.set_which(id);

  CHECK(event.which() == id);
}

TEST_CASE("controller_axis_event::set_axis", "[controller_axis_event]")
{
  cen::controller_axis_event event;

  const auto axis = cen::controller_axis::trigger_right;
  event.set_axis(axis);

  CHECK(event.axis() == axis);
}

TEST_CASE("controller_axis_event::set_value", "[controller_axis_event]")
{
  cen::controller_axis_event event;

  const auto value = 4576;
  event.set_value(value);

  CHECK(event.value() == value);
}

TEST_CASE("controller_axis_event::which", "[controller_axis_event]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.which = 54;
  cen::controller_axis_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("controller_axis_event::axis", "[controller_axis_event]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.axis = SDL_CONTROLLER_AXIS_INVALID;
  cen::controller_axis_event event{sdlEvent};

  CHECK(event.axis() == static_cast<SDL_GameControllerAxis>(sdlEvent.axis));
}

TEST_CASE("controller_axis_event::value", "[controller_axis_event]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.value = 1234;
  cen::controller_axis_event event{sdlEvent};

  CHECK(event.value() == sdlEvent.value);
}
