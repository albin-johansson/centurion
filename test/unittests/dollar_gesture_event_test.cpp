#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"

TEST_CASE("dollar_gesture_event::set_touch_id", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto id = 4;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("dollar_gesture_event::set_gesture_id", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto id = 81;
  event.set_gesture_id(id);

  CHECK(event.gesture_id() == id);
}

TEST_CASE("dollar_gesture_event::set_fingers", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto fingers = 2;
  event.set_fingers(fingers);

  CHECK(event.fingers() == fingers);
}

TEST_CASE("dollar_gesture_event::set_error", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto error = 5.1f;
  event.set_error(error);

  CHECK(event.error() == error);
}

TEST_CASE("dollar_gesture_event::set_x", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto x = 24.8f;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("dollar_gesture_event::set_y", "[dollar_gesture_event]")
{
  ctn::dollar_gesture_event event;

  const auto y = -12.9f;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("dollar_gesture_event::touch_id", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.touchId = 9;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("dollar_gesture_event::gesture_id", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.gestureId = 1;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.gesture_id() == sdlEvent.gestureId);
}

TEST_CASE("dollar_gesture_event::fingers", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.numFingers = 3;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.fingers() == sdlEvent.numFingers);
}

TEST_CASE("dollar_gesture_event::error", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.error = 7.4f;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.error() == sdlEvent.error);
}

TEST_CASE("dollar_gesture_event::x", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.x = 56.8f;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("dollar_gesture_event::y", "[dollar_gesture_event]")
{
  SDL_DollarGestureEvent sdlEvent;
  sdlEvent.y = 92.3f;
  ctn::dollar_gesture_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}