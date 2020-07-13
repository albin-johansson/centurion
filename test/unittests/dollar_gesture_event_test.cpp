#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("DollarGestureEvent::set_touch_id", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto id = 4;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("DollarGestureEvent::set_gesture_id", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto id = 81;
  event.set_gesture_id(id);

  CHECK(event.gesture_id() == id);
}

TEST_CASE("DollarGestureEvent::set_fingers", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto fingers = 2;
  event.set_fingers(fingers);

  CHECK(event.fingers() == fingers);
}

TEST_CASE("DollarGestureEvent::set_error", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto error = 5.1f;
  event.set_error(error);

  CHECK(event.error() == error);
}

TEST_CASE("DollarGestureEvent::set_x", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto x = 24.8f;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("DollarGestureEvent::set_y", "[DollarGestureEvent]")
{
  dollar_gesture_event event;

  const auto y = -12.9f;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("DollarGestureEvent::touch_id", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.touchId = 9;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("DollarGestureEvent::gesture_id", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.gestureId = 1;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.gesture_id() == sdlEvent.gestureId);
}

TEST_CASE("DollarGestureEvent::fingers", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.numFingers = 3;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.fingers() == sdlEvent.numFingers);
}

TEST_CASE("DollarGestureEvent::error", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.error = 7.4f;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.error() == sdlEvent.error);
}

TEST_CASE("DollarGestureEvent::x", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.x = 56.8f;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("DollarGestureEvent::y", "[DollarGestureEvent]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.y = 92.3f;
  dollar_gesture_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}