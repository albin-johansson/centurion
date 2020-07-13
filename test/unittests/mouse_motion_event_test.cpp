#include <catch.hpp>

#include "event.hpp"

using namespace centurion;
using namespace centurion;

TEST_CASE("MouseMotionEvent::set_window_id", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto id = 8;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("MouseMotionEvent::set_which", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto which = 65;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("MouseMotionEvent::set_state", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto state = SDL_BUTTON_LMASK | SDL_BUTTON_RMASK;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("MouseMotionEvent::set_x", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto x = 745;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("MouseMotionEvent::set_y", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto y = 123;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("MouseMotionEvent::set_dx", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto dx = -456;
  event.set_dx(dx);

  CHECK(event.dx() == dx);
}

TEST_CASE("MouseMotionEvent::set_dy", "[MouseMotionEvent]")
{
  mouse_motion_event event;

  const auto dy = 835;
  event.set_dy(dy);

  CHECK(event.dy() == dy);
}

TEST_CASE("MouseMotionEvent::pressed", "[MouseMotionEvent]")
{
  mouse_motion_event event;
  event.set_state(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);

  CHECK(event.pressed(mouse_button::left));
  CHECK(event.pressed(mouse_button::middle));

  CHECK(!event.pressed(mouse_button::right));
  CHECK(!event.pressed(mouse_button::x1));
  CHECK(!event.pressed(mouse_button::x2));
}

TEST_CASE("MouseMotionEvent::window_id", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.windowID = 45;
  mouse_motion_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseMotionEvent::which", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.which = 77;
  mouse_motion_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("MouseMotionEvent::state", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.state = SDL_BUTTON_LMASK;
  mouse_motion_event event{sdlEvent};

  CHECK(event.state() == sdlEvent.state);
}

TEST_CASE("MouseMotionEvent::x", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.x = 1867;
  mouse_motion_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("MouseMotionEvent::y", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.y = 454;
  mouse_motion_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}

TEST_CASE("MouseMotionEvent::dx", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.xrel = 78;
  mouse_motion_event event{sdlEvent};

  CHECK(event.dx() == sdlEvent.xrel);
}

TEST_CASE("MouseMotionEvent::dy", "[MouseMotionEvent]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.yrel = -564;
  mouse_motion_event event{sdlEvent};

  CHECK(event.dy() == sdlEvent.yrel);
}
