#include <catch.hpp>

#include "event.hpp"

using namespace centurion::event;

TEST_CASE("JoyHatValue enum values", "[JoyHatEvent]")
{
  CHECK(static_cast<Uint8>(JoyHatPosition::LeftUp) == SDL_HAT_LEFTUP);
  CHECK(static_cast<Uint8>(JoyHatPosition::Left) == SDL_HAT_LEFT);
  CHECK(static_cast<Uint8>(JoyHatPosition::LeftDown) == SDL_HAT_LEFTDOWN);
  CHECK(static_cast<Uint8>(JoyHatPosition::Up) == SDL_HAT_UP);
  CHECK(static_cast<Uint8>(JoyHatPosition::Centered) == SDL_HAT_CENTERED);
  CHECK(static_cast<Uint8>(JoyHatPosition::Down) == SDL_HAT_DOWN);
  CHECK(static_cast<Uint8>(JoyHatPosition::RightUp) == SDL_HAT_RIGHTUP);
  CHECK(static_cast<Uint8>(JoyHatPosition::Right) == SDL_HAT_RIGHT);
  CHECK(static_cast<Uint8>(JoyHatPosition::RightDown) == SDL_HAT_RIGHTDOWN);
}

TEST_CASE("JoyHatEvent move constructor", "[JoyHatEvent]")
{
  CHECK_NOTHROW(JoyHatEvent{{}});
}

TEST_CASE("JoyHatEvent::set_hat", "[JoyHatEvent]")
{
  JoyHatEvent event;

  const auto hat = 7;
  event.set_hat(hat);

  CHECK(event.hat() == hat);
}

TEST_CASE("JoyHatEvent::set_position", "[JoyHatEvent]")
{
  JoyHatEvent event;

  const auto position = JoyHatPosition::Right;
  event.set_position(position);

  CHECK(event.position() == position);
}

TEST_CASE("JoyHatEvent::hat", "[JoyHatEvent]")
{
  SDL_JoyHatEvent sdlEvent;
  sdlEvent.hat = 2;
  JoyHatEvent event{sdlEvent};

  CHECK(event.hat() == sdlEvent.hat);
}

TEST_CASE("JoyHatEvent::position", "[JoyHatEvent]")
{
  SDL_JoyHatEvent sdlEvent;
  sdlEvent.value = SDL_HAT_LEFT;
  JoyHatEvent event{sdlEvent};

  CHECK(event.position() == JoyHatPosition::Left);
}