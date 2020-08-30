#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("mouse_wheel_direction operator==", "[mouse_wheel_direction]")
{
  CHECK(cen::mouse_wheel_direction::normal == SDL_MOUSEWHEEL_NORMAL);
  CHECK(cen::mouse_wheel_direction::flipped == SDL_MOUSEWHEEL_FLIPPED);

  CHECK(SDL_MOUSEWHEEL_NORMAL == cen::mouse_wheel_direction::normal);
  CHECK(SDL_MOUSEWHEEL_FLIPPED == cen::mouse_wheel_direction::flipped);

  CHECK_FALSE(cen::mouse_wheel_direction::normal == SDL_MOUSEWHEEL_FLIPPED);
}

TEST_CASE("mouse_wheel_direction operator!=", "[mouse_wheel_direction]")
{
  CHECK(cen::mouse_wheel_direction::normal != SDL_MOUSEWHEEL_FLIPPED);
  CHECK(cen::mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_NORMAL);

  CHECK(SDL_MOUSEWHEEL_NORMAL != cen::mouse_wheel_direction::flipped);
  CHECK(SDL_MOUSEWHEEL_FLIPPED != cen::mouse_wheel_direction::normal);

  CHECK_FALSE(cen::mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_FLIPPED);
}

TEST_CASE("mouse_wheel_event::set_window_id", "[mouse_wheel_event]")
{
  cen::mouse_wheel_event event;

  const auto id = 32;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("mouse_wheel_event::set_which", "[mouse_wheel_event]")
{
  cen::mouse_wheel_event event;

  const auto which = 32;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("mouse_wheel_event::set_x_scroll", "[mouse_wheel_event]")
{
  cen::mouse_wheel_event event;

  const auto xScroll = -545;
  event.set_x_scroll(xScroll);

  CHECK(event.x_scroll() == xScroll);
}

TEST_CASE("mouse_wheel_event::set_y_scroll", "[mouse_wheel_event]")
{
  cen::mouse_wheel_event event;

  const auto yScroll = 725;
  event.set_y_scroll(yScroll);

  CHECK(event.y_scroll() == yScroll);
}

TEST_CASE("mouse_wheel_event::set_direction", "[mouse_wheel_event]")
{
  cen::mouse_wheel_event event;

  const auto direction = cen::mouse_wheel_direction::flipped;
  event.set_direction(direction);

  CHECK(event.direction() == direction);
}

TEST_CASE("mouse_wheel_event::window_id", "[mouse_wheel_event]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  cen::mouse_wheel_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("mouse_wheel_event::which", "[mouse_wheel_event]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  cen::mouse_wheel_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("mouse_wheel_event::x_scroll", "[mouse_wheel_event]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.x = 455;

  cen::mouse_wheel_event event{sdlEvent};

  CHECK(event.x_scroll() == sdlEvent.x);
}

TEST_CASE("mouse_wheel_event::y_scroll", "[mouse_wheel_event]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.y = -123;

  cen::mouse_wheel_event event{sdlEvent};

  CHECK(event.y_scroll() == sdlEvent.y);
}

TEST_CASE("mouse_wheel_event::direction", "[mouse_wheel_event]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.direction = SDL_MOUSEWHEEL_NORMAL;

  cen::mouse_wheel_event event{sdlEvent};

  CHECK(event.direction() == cen::mouse_wheel_direction::normal);
}