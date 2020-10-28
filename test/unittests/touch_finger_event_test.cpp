#include <catch.hpp>

#include "event.hpp"

TEST_CASE("touch_finger_event::set_touch_id", "[touch_finger_event]")
{
  cen::touch_finger_event event;

  const auto id = 8;
  event.set_touch_id(id);

  CHECK(event.touch_id() == id);
}

TEST_CASE("touch_finger_event::set_finger_id", "[touch_finger_event]")
{
  cen::touch_finger_event event;

  const auto id = 14;
  event.set_finger_id(id);

  CHECK(event.finger_id() == id);
}

TEST_CASE("touch_finger_event::set_window_id", "[touch_finger_event]")
{
  cen::touch_finger_event event;

  const auto id = 32;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("touch_finger_event::set_x", "[touch_finger_event]")
{
  cen::touch_finger_event event;

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

TEST_CASE("touch_finger_event::set_y", "[touch_finger_event]")
{
  cen::touch_finger_event event;

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

TEST_CASE("touch_finger_event::set_dx", "[touch_finger_event]")
{
  cen::touch_finger_event event;

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

TEST_CASE("touch_finger_event::set_dy", "[touch_finger_event]")
{
  cen::touch_finger_event event;

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

TEST_CASE("touch_finger_event::set_pressure", "[touch_finger_event]")
{
  cen::touch_finger_event event;

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

TEST_CASE("touch_finger_event::touch_id", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.touchId = 4;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.touch_id() == sdlEvent.touchId);
}

TEST_CASE("touch_finger_event::finger_id", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.fingerId = 18;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.finger_id() == sdlEvent.fingerId);
}

TEST_CASE("touch_finger_event::window_id", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.windowID = 7;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("touch_finger_event::x", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.x = 0.4f;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("touch_finger_event::y", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.y = 0.8f;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}

TEST_CASE("touch_finger_event::dx", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.dx = -0.9f;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.dx() == sdlEvent.dx);
}

TEST_CASE("touch_finger_event::dy", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.dy = 0.2f;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.dy() == sdlEvent.dy);
}

TEST_CASE("touch_finger_event::pressure", "[touch_finger_event]")
{
  SDL_TouchFingerEvent sdlEvent{};
  sdlEvent.pressure = 0.6f;
  cen::touch_finger_event event{sdlEvent};

  CHECK(event.pressure() == sdlEvent.pressure);
}

TEST_CASE("touch_finger_event()", "[touch_finger_event]")
{
  CHECK_NOTHROW(cen::touch_finger_event{{}});
}