#include <catch.hpp>

#include "event.hpp"

using namespace centurion;
using namespace centurion;

TEST_CASE("MouseButtonEvent::set_window_id", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto id = 64;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("MouseButtonEvent::set_which", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto which = 17;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("MouseButtonEvent::set_button", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto button = MouseButton::Right;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("MouseButtonEvent::set_state", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto state = button_state::released;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("MouseButtonEvent::set_clicks", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto clicks = 2;
  event.set_clicks(clicks);

  CHECK(event.clicks() == clicks);
}

TEST_CASE("MouseButtonEvent::set_x", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto x = 645;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("MouseButtonEvent::set_y", "[MouseButtonEvent]")
{
  MouseButtonEvent event;

  const auto y = 177;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("MouseButtonEvent::window_id", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.windowID = 75;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("MouseButtonEvent::which", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.which = 23;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("MouseButtonEvent::button", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.button = SDL_BUTTON_X1;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.button() == static_cast<MouseButton>(sdlEvent.button));
}

TEST_CASE("MouseButtonEvent::state", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.state = SDL_PRESSED;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.state() == static_cast<button_state>(sdlEvent.state));
}

TEST_CASE("MouseButtonEvent::clicks", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.clicks = 2;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.clicks() == sdlEvent.clicks);
}

TEST_CASE("MouseButtonEvent::x", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.x = 467;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("MouseButtonEvent::y", "[MouseButtonEvent]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.y = 887;
  MouseButtonEvent event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}
