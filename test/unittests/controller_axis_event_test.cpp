#include "controller_axis_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("GameControllerAxis operator==", "[GameControllerAxis]")
{
  using GCA = GameControllerAxis;

  CHECK(SDL_CONTROLLER_AXIS_INVALID == GCA::Invalid);
  CHECK(SDL_CONTROLLER_AXIS_LEFTX == GCA::LeftX);
  CHECK(SDL_CONTROLLER_AXIS_LEFTY == GCA::LeftY);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTX == GCA::RightX);
  CHECK(SDL_CONTROLLER_AXIS_RIGHTY == GCA::RightY);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT == GCA::TriggerLeft);
  CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT == GCA::TriggerRight);
  CHECK(SDL_CONTROLLER_AXIS_MAX == GCA::Max);

  CHECK(GCA::Invalid == SDL_CONTROLLER_AXIS_INVALID);
  CHECK(GCA::LeftX == SDL_CONTROLLER_AXIS_LEFTX);
  CHECK(GCA::LeftY == SDL_CONTROLLER_AXIS_LEFTY);
  CHECK(GCA::RightX == SDL_CONTROLLER_AXIS_RIGHTX);
  CHECK(GCA::RightY == SDL_CONTROLLER_AXIS_RIGHTY);
  CHECK(GCA::TriggerLeft == SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  CHECK(GCA::TriggerRight == SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  CHECK(GCA::Max == SDL_CONTROLLER_AXIS_MAX);
}

TEST_CASE("GameControllerAxis operator!=", "[GameControllerAxis]")
{
  CHECK(SDL_CONTROLLER_AXIS_INVALID != GameControllerAxis::RightX);
  CHECK(GameControllerAxis::Max != SDL_CONTROLLER_AXIS_LEFTX);

  CHECK(
      !(SDL_CONTROLLER_AXIS_TRIGGERRIGHT != GameControllerAxis::TriggerRight));
}

TEST_CASE("ControllerAxisEvent constructors", "[ControllerAxisEvent]")
{
  CHECK_NOTHROW(ControllerAxisEvent{});
  CHECK_NOTHROW(ControllerAxisEvent{{}});
}

TEST_CASE("ControllerAxisEvent::set_which", "[ControllerAxisEvent]")
{
  ControllerAxisEvent event;

  const JoystickID id = 53;
  event.set_which(id);

  CHECK(event.which() == id);
}

TEST_CASE("ControllerAxisEvent::set_axis", "[ControllerAxisEvent]")
{
  ControllerAxisEvent event;

  const auto axis = GameControllerAxis::TriggerRight;
  event.set_axis(axis);

  CHECK(event.axis() == axis);
}

TEST_CASE("ControllerAxisEvent::set_value", "[ControllerAxisEvent]")
{
  ControllerAxisEvent event;

  const auto value = 4576;
  event.set_value(value);

  CHECK(event.value() == value);
}

TEST_CASE("ControllerAxisEvent::which", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.which = 54;
  ControllerAxisEvent event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("ControllerAxisEvent::axis", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.axis = SDL_CONTROLLER_AXIS_INVALID;
  ControllerAxisEvent event{sdlEvent};

  CHECK(event.axis() == static_cast<SDL_GameControllerAxis>(sdlEvent.axis));
}

TEST_CASE("ControllerAxisEvent::value", "[ControllerAxisEvent]")
{
  SDL_ControllerAxisEvent sdlEvent;
  sdlEvent.value = 1234;
  ControllerAxisEvent event{sdlEvent};

  CHECK(event.value() == sdlEvent.value);
}
