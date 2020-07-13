#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("JoyAxisEvent::set_which", "[JoyAxisEvent]")
{
  joy_axis_event event;

  const auto which = 3;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("JoyAxisEvent::set_axis", "[JoyAxisEvent]")
{
  joy_axis_event event;

  const auto axis = 7;
  event.set_axis(axis);

  CHECK(event.axis() == axis);
}

TEST_CASE("JoyAxisEvent::set_value", "[JoyAxisEvent]")
{
  joy_axis_event event;

  const auto value = 4'234;
  event.set_value(value);

  CHECK(event.value() == value);
}

TEST_CASE("JoyAxisEvent::which", "[JoyAxisEvent]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.which = 23;

  joy_axis_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("JoyAxisEvent::axis", "[JoyAxisEvent]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.axis = 5;

  joy_axis_event event{sdlEvent};

  CHECK(event.axis() == sdlEvent.axis);
}

TEST_CASE("JoyAxisEvent::value", "[JoyAxisEvent]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.value = 1864;

  joy_axis_event event{sdlEvent};

  CHECK(event.value() == sdlEvent.value);
}
