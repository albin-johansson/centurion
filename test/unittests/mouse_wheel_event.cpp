#include "mouse_wheel_event.h"

#include <catch.hpp>

using namespace centurion::event;

TEST_CASE("MouseWheelDirection operator==", "[MouseWheelDirection]")
{
  CHECK(MouseWheelDirection::Normal == SDL_MOUSEWHEEL_NORMAL);
  CHECK(MouseWheelDirection::Flipped == SDL_MOUSEWHEEL_FLIPPED);

  CHECK(SDL_MOUSEWHEEL_NORMAL == MouseWheelDirection::Normal);
  CHECK(SDL_MOUSEWHEEL_FLIPPED == MouseWheelDirection::Flipped);

  CHECK(!(MouseWheelDirection::Normal == SDL_MOUSEWHEEL_FLIPPED));
}

TEST_CASE("MouseWheelDirection operator!=", "[MouseWheelDirection]")
{
  CHECK(MouseWheelDirection::Normal != SDL_MOUSEWHEEL_FLIPPED);
  CHECK(MouseWheelDirection::Flipped != SDL_MOUSEWHEEL_NORMAL);

  CHECK(SDL_MOUSEWHEEL_NORMAL != MouseWheelDirection::Flipped);
  CHECK(SDL_MOUSEWHEEL_FLIPPED != MouseWheelDirection::Normal);

  CHECK(!(MouseWheelDirection::Flipped != SDL_MOUSEWHEEL_FLIPPED));
}

TEST_CASE("MouseWheelEvent::set_window_id", "[MouseWheelEvent]")
{
  MouseWheelEvent event;

  const auto id = 32;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("MouseWheelEvent::set_which", "[MouseWheelEvent]")
{
  MouseWheelEvent event;

  const auto which = 32;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("MouseWheelEvent::set_x_scroll", "[MouseWheelEvent]")
{
  MouseWheelEvent event;

  const auto xScroll = -545;
  event.set_x_scroll(xScroll);

  CHECK(event.x_scroll() == xScroll);
}

TEST_CASE("MouseWheelEvent::set_y_scroll", "[MouseWheelEvent]")
{
  MouseWheelEvent event;

  const auto yScroll = 725;
  event.set_y_scroll(yScroll);

  CHECK(event.y_scroll() == yScroll);
}

TEST_CASE("MouseWheelEvent::set_direction", "[MouseWheelEvent]")
{
  MouseWheelEvent event;

  const auto direction = MouseWheelDirection::Flipped;
  event.set_direction(direction);

  CHECK(event.direction() == direction);
}

TEST_CASE("MouseWheelEvent::window_id", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  MouseWheelEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseWheelEvent::which", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.windowID = 12;

  MouseWheelEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseWheelEvent::x_scroll", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.x = 455;

  MouseWheelEvent event{sdlEvent};

  CHECK(event.x_scroll() == sdlEvent.x);
}

TEST_CASE("MouseWheelEvent::y_scroll", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.y = -123;

  MouseWheelEvent event{sdlEvent};

  CHECK(event.y_scroll() == sdlEvent.y);
}

TEST_CASE("MouseWheelEvent::direction", "[MouseWheelEvent]")
{
  SDL_MouseWheelEvent sdlEvent;
  sdlEvent.direction = SDL_MOUSEWHEEL_NORMAL;

  MouseWheelEvent event{sdlEvent};

  CHECK(event.direction() == MouseWheelDirection::Normal);
}