#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("mouse_motion_event::set_window_id", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto id = 8;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("mouse_motion_event::set_which", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto which = 65;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("mouse_motion_event::set_state", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto state = SDL_BUTTON_LMASK | SDL_BUTTON_RMASK;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("mouse_motion_event::set_x", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto x = 745;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("mouse_motion_event::set_y", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto y = 123;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("mouse_motion_event::set_dx", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto dx = -456;
  event.set_dx(dx);

  CHECK(event.dx() == dx);
}

TEST_CASE("mouse_motion_event::set_dy", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;

  const auto dy = 835;
  event.set_dy(dy);

  CHECK(event.dy() == dy);
}

TEST_CASE("mouse_motion_event::pressed", "[mouse_motion_event]")
{
  cen::mouse_motion_event event;
  event.set_state(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);

  CHECK(event.pressed(cen::mouse_button::left));
  CHECK(event.pressed(cen::mouse_button::middle));

  CHECK(!event.pressed(cen::mouse_button::right));
  CHECK(!event.pressed(cen::mouse_button::x1));
  CHECK(!event.pressed(cen::mouse_button::x2));
}

TEST_CASE("mouse_motion_event::window_id", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.windowID = 45;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("mouse_motion_event::which", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.which = 77;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("mouse_motion_event::state", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.state = SDL_BUTTON_LMASK;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.state() == sdlEvent.state);
}

TEST_CASE("mouse_motion_event::x", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.x = 1867;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("mouse_motion_event::y", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.y = 454;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}

TEST_CASE("mouse_motion_event::dx", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.xrel = 78;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.dx() == sdlEvent.xrel);
}

TEST_CASE("mouse_motion_event::dy", "[mouse_motion_event]")
{
  SDL_MouseMotionEvent sdlEvent;
  sdlEvent.yrel = -564;
  cen::mouse_motion_event event{sdlEvent};

  CHECK(event.dy() == sdlEvent.yrel);
}
