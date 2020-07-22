#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("multi_gesture_event::set_touch_id", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto id = 3;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("multi_gesture_event::set_delta_theta", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto dTheta = 65;
  event.set_delta_theta(dTheta);

  CHECK(event.delta_theta() == dTheta);
}

TEST_CASE("multi_gesture_event::set_delta_distance", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto dDistance = -79;
  event.set_delta_distance(dDistance);

  CHECK(event.delta_distance() == dDistance);
}

TEST_CASE("multi_gesture_event::set_center_x", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto centerX = 154;
  event.set_center_x(centerX);

  CHECK(event.center_x() == centerX);
}

TEST_CASE("multi_gesture_event::set_center_y", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto centerY = 867;
  event.set_center_y(centerY);

  CHECK(event.center_y() == centerY);
}

TEST_CASE("multi_gesture_event::set_fingers", "[multi_gesture_event]")
{
  ctn::multi_gesture_event event;

  const auto fingers = 3;
  event.set_fingers(fingers);

  CHECK(event.fingers() == fingers);
}

TEST_CASE("multi_gesture_event::touch_id", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.touchId = 54;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("multi_gesture_event::delta_theta", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.dTheta = 98;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.delta_theta() == sdlEvent.dTheta);
}

TEST_CASE("multi_gesture_event::delta_distance", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.dDist = -87;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.delta_distance() == sdlEvent.dDist);
}

TEST_CASE("multi_gesture_event::center_x", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.x = 564;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.center_x() == sdlEvent.x);
}

TEST_CASE("multi_gesture_event::center_y", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.y = 913;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.center_y() == sdlEvent.y);
}

TEST_CASE("multi_gesture_event::fingers", "[multi_gesture_event]")
{
  SDL_MultiGestureEvent sdlEvent;
  sdlEvent.numFingers = 2;
  ctn::multi_gesture_event event{sdlEvent};

  CHECK(event.fingers() == sdlEvent.numFingers);
}