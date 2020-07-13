#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("MouseWheelDirection operator==", "[MouseWheelDirection]")
{
  CHECK(mouse_wheel_direction::normal == SDL_MOUSEWHEEL_NORMAL);
  CHECK(mouse_wheel_direction::flipped == SDL_MOUSEWHEEL_FLIPPED);

  CHECK(SDL_MOUSEWHEEL_NORMAL == mouse_wheel_direction::normal);
  CHECK(SDL_MOUSEWHEEL_FLIPPED == mouse_wheel_direction::flipped);

  CHECK(!(mouse_wheel_direction::normal == SDL_MOUSEWHEEL_FLIPPED));
}

TEST_CASE("MouseWheelDirection operator!=", "[MouseWheelDirection]")
{
  CHECK(mouse_wheel_direction::normal != SDL_MOUSEWHEEL_FLIPPED);
  CHECK(mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_NORMAL);

  CHECK(SDL_MOUSEWHEEL_NORMAL != mouse_wheel_direction::flipped);
  CHECK(SDL_MOUSEWHEEL_FLIPPED != mouse_wheel_direction::normal);

  CHECK(!(mouse_wheel_direction::flipped != SDL_MOUSEWHEEL_FLIPPED));
}

TEST_CASE("MouseWheelEvent::set_window_id", "[MouseWheelEvent]")
{
  mouse_wheel_event event;

  const auto id = 32;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("MouseWheelEvent::set_which", "[MouseWheelEvent]")
{
  mouse_wheel_event event;

  const auto which = 32;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("MouseWheelEvent::set_x_scroll", "[MouseWheelEvent]")
{
  mouse_wheel_event event;

  const auto xScroll = -545;
  event.set_x_scroll(xScroll);

  CHECK(event.x_scroll() == xScroll);
}

TEST_CASE("MouseWheelEvent::set_y_scroll", "[MouseWheelEvent]")
{
  mouse_wheel_event event;

  const auto yScroll = 725;
  event.set_y_scroll(yScroll);

  CHECK(event.y_scroll() == yScroll);
}

TEST_CASE("MouseWheelEvent::set_direction", "[MouseWheelEvent]")
{
  mouse_wheel_event event;

  const auto direction = mouse_wheel_direction::flipped;
  event.set_direction(direction);

  CHECK(event.direction() == direction);
}

TEST_CASE("MouseWheelEvent::window_id", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  mouse_wheel_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseWheelEvent::which", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  mouse_wheel_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseWheelEvent::x_scroll", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.x = 455;

  mouse_wheel_event event{sdlEvent};

  CHECK(event.x_scroll() == sdlEvent.x);
}

TEST_CASE("MouseWheelEvent::y_scroll", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.y = -123;

  mouse_wheel_event event{sdlEvent};

  CHECK(event.y_scroll() == sdlEvent.y);
}

TEST_CASE("MouseWheelEvent::direction", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.direction = SDL_MOUSEWHEEL_NORMAL;

  mouse_wheel_event event{sdlEvent};

  CHECK(event.direction() == mouse_wheel_direction::normal);
}