#include <catch.hpp>

#include "cen.hpp"
#include "event.hpp"

TEST_CASE("mouse_button_event::set_window_id", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto id = 64;
  event.set_window_id(id);

  CHECK(event.window_id() == id);
}

TEST_CASE("mouse_button_event::set_which", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto which = 17;
  event.set_which(which);

  CHECK(event.which() == which);
}

TEST_CASE("mouse_button_event::set_button", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto button = cen::mouse_button::right;
  event.set_button(button);

  CHECK(event.button() == button);
}

TEST_CASE("mouse_button_event::set_state", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto state = cen::button_state::released;
  event.set_state(state);

  CHECK(event.state() == state);
}

TEST_CASE("mouse_button_event::set_clicks", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto clicks = 2;
  event.set_clicks(clicks);

  CHECK(event.clicks() == clicks);
}

TEST_CASE("mouse_button_event::set_x", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto x = 645;
  event.set_x(x);

  CHECK(event.x() == x);
}

TEST_CASE("mouse_button_event::set_y", "[mouse_button_event]")
{
  cen::mouse_button_event event;

  const auto y = 177;
  event.set_y(y);

  CHECK(event.y() == y);
}

TEST_CASE("mouse_button_event::window_id", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.windowID = 75;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.window_id() == sdlEvent.windowID);
}

TEST_CASE("mouse_button_event::which", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.which = 23;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.which() == sdlEvent.which);
}

TEST_CASE("mouse_button_event::button", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.button = SDL_BUTTON_X1;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.button() == static_cast<cen::mouse_button>(sdlEvent.button));
}

TEST_CASE("mouse_button_event::state", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.state = SDL_PRESSED;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.state() == static_cast<cen::button_state>(sdlEvent.state));
}

TEST_CASE("mouse_button_event::pressed", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.state = SDL_PRESSED;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.pressed());
}

TEST_CASE("mouse_button_event::released", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.state = SDL_RELEASED;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.released());
}

TEST_CASE("mouse_button_event::clicks", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.clicks = 2;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.clicks() == sdlEvent.clicks);
}

TEST_CASE("mouse_button_event::x", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.x = 467;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.x() == sdlEvent.x);
}

TEST_CASE("mouse_button_event::y", "[mouse_button_event]")
{
  SDL_MouseButtonEvent sdlEvent;
  sdlEvent.y = 887;
  cen::mouse_button_event event{sdlEvent};

  CHECK(event.y() == sdlEvent.y);
}
