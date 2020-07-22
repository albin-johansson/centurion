#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("joy_axis_event::set_which", "[joy_axis_event]")
{
  ctn::joy_axis_event event;

  const auto which = 3;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("joy_axis_event::set_axis", "[joy_axis_event]")
{
  ctn::joy_axis_event event;

  const auto axis = 7;
  event.set_axis(axis);

  CHECK(event.axis() == axis);
}

TEST_CASE("joy_axis_event::set_value", "[joy_axis_event]")
{
  ctn::joy_axis_event event;

  const auto value = 4'234;
  event.set_value(value);

  CHECK(event.value() == value);
}

TEST_CASE("joy_axis_event::which", "[joy_axis_event]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.which = 23;

  ctn::joy_axis_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("joy_axis_event::axis", "[joy_axis_event]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.axis = 5;

  ctn::joy_axis_event event{sdlEvent};

  CHECK(event.axis() == sdlEvent.axis);
}

TEST_CASE("joy_axis_event::value", "[joy_axis_event]")
{
  SDL_JoyAxisEvent sdlEvent;
  sdlEvent.value = 1864;

  ctn::joy_axis_event event{sdlEvent};

  CHECK(event.value() == sdlEvent.value);
}
