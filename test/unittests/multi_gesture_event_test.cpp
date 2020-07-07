#include <catch.hpp>

#include "event.hpp"

using namespace centurion::event;

TEST_CASE("MultiGestureEvent::set_touch_id", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto id = 3;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("MultiGestureEvent::set_delta_theta", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto dTheta = 65;
  event.set_delta_theta(dTheta);

  CHECK(event.delta_theta() == dTheta);
}

TEST_CASE("MultiGestureEvent::set_delta_distance", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto dDistance = -79;
  event.set_delta_distance(dDistance);

  CHECK(event.delta_distance() == dDistance);
}

TEST_CASE("MultiGestureEvent::set_center_x", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto centerX = 154;
  event.set_center_x(centerX);

  CHECK(event.center_x() == centerX);
}

TEST_CASE("MultiGestureEvent::set_center_y", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto centerY = 867;
  event.set_center_y(centerY);

  CHECK(event.center_y() == centerY);
}

TEST_CASE("MultiGestureEvent::set_fingers", "[MultiGestureEvent]")
{
  MultiGestureEvent event;

  const auto fingers = 3;
  event.set_fingers(fingers);

  CHECK(event.fingers() == fingers);
}

TEST_CASE("MultiGestureEvent::touch_id", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.touchId = 54;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("MultiGestureEvent::delta_theta", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.dTheta = 98;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.delta_theta() == sdlEvent.dTheta);
}

TEST_CASE("MultiGestureEvent::delta_distance", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.dDist = -87;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.delta_distance() == sdlEvent.dDist);
}

TEST_CASE("MultiGestureEvent::center_x", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.x = 564;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.center_x() == sdlEvent.x);
}

TEST_CASE("MultiGestureEvent::center_y", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.y = 913;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.center_y() == sdlEvent.y);
}

TEST_CASE("MultiGestureEvent::fingers", "[MultiGestureEvent]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.numFingers = 2;
  MultiGestureEvent event{sdlEvent};

  CHECK(event.fingers() == sdlEvent.numFingers);
}