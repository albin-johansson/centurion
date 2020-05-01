#include "touch_finger_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("TouchFingerEvent::set_type", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  const auto type = TouchFingerEventType::Motion;
  event.set_type(type);

  CHECK(event.type() == type);
}

TEST_CASE("TouchFingerEvent::set_touch_id", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  const auto id = 8;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("TouchFingerEvent::set_finger_id", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  const auto id = 14;
  event.set_finger_id(id);

  CHECK(event.finger_id() == id);
}

TEST_CASE("TouchFingerEvent::set_window_id", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  const auto id = 32;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("TouchFingerEvent::set_x", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  SECTION("Overflow")
  {
    event.set_x(1.1f);
    CHECK(event.x() == 1);
  }

  SECTION("Underflow")
  {
    event.set_x(-0.1f);
    CHECK(event.x() == 0);
  }

  SECTION("Good value")
  {
    const auto x = 0.4f;
    event.set_x(x);
    CHECK(event.x() == x);
  }
}

TEST_CASE("TouchFingerEvent::set_y", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  SECTION("Overflow")
  {
    event.set_y(1.1f);
    CHECK(event.y() == 1);
  }

  SECTION("Underflow")
  {
    event.set_y(-0.1f);
    CHECK(event.y() == 0);
  }

  SECTION("Good value")
  {
    const auto y = 0.9f;
    event.set_y(y);
    CHECK(event.y() == y);
  }
}

TEST_CASE("TouchFingerEvent::set_dx", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  SECTION("Overflow")
  {
    event.set_dx(1.1f);
    CHECK(event.dx() == 1);
  }

  SECTION("Underflow")
  {
    event.set_dx(-1.1f);
    CHECK(event.dx() == -1);
  }

  SECTION("Good value")
  {
    const auto dx = -0.4f;
    event.set_dx(dx);
    CHECK(event.dx() == dx);
  }
}

TEST_CASE("TouchFingerEvent::set_dy", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  SECTION("Overflow")
  {
    event.set_dy(1.1f);
    CHECK(event.dy() == 1);
  }

  SECTION("Underflow")
  {
    event.set_dy(-1.1f);
    CHECK(event.dy() == -1);
  }

  SECTION("Good value")
  {
    const auto dy = 0.75f;
    event.set_dy(dy);
    CHECK(event.dy() == dy);
  }
}

TEST_CASE("TouchFingerEvent::set_pressure", "[TouchFingerEvent]")
{
  TouchFingerEvent event;

  SECTION("Overflow")
  {
    event.set_pressure(1.1f);
    CHECK(event.pressure() == 1);
  }

  SECTION("Underflow")
  {
    event.set_pressure(-0.1f);
    CHECK(event.pressure() == 0);
  }

  SECTION("Good value")
  {
    const auto pressure = 0.75f;
    event.set_pressure(pressure);
    CHECK(event.pressure() == pressure);
  }
}

TEST_CASE("TouchFingerEvent::type", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.type = SDL_FINGERUP;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.type() == TouchFingerEventType::Up);
}

TEST_CASE("TouchFingerEvent::touch_id", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.touchId = 4;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("TouchFingerEvent::finger_id", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.fingerId = 18;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.finger_id() == sdlEvent.fingerId);
}

TEST_CASE("TouchFingerEvent::window_id", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.windowID = 7;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("TouchFingerEvent::x", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.x = 0.4f;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("TouchFingerEvent::y", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.y = 0.8f;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}

TEST_CASE("TouchFingerEvent::dx", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.dx = -0.9f;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.dx() == sdlEvent.dx);
}

TEST_CASE("TouchFingerEvent::dy", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.dy = 0.2f;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.dy() == sdlEvent.dy);
}

TEST_CASE("TouchFingerEvent::pressure", "[TouchFingerEvent]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.pressure = 0.6f;
  TouchFingerEvent event{sdlEvent};

  CHECK(event.pressure() == sdlEvent.pressure);
}