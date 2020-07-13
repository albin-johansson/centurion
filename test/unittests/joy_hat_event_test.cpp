#include <catch.hpp>

#include "event.hpp"

using namespace centurion;

TEST_CASE("JoyHatValue enum values", "[JoyHatEvent]")
{
  CHECK(static_cast<u8>(joy_hat_position::left_up) == SDL_HAT_LEFTUP);
  CHECK(static_cast<u8>(joy_hat_position::left) == SDL_HAT_LEFT);
  CHECK(static_cast<u8>(joy_hat_position::left_down) == SDL_HAT_LEFTDOWN);
  CHECK(static_cast<u8>(joy_hat_position::up) == SDL_HAT_UP);
  CHECK(static_cast<u8>(joy_hat_position::centered) == SDL_HAT_CENTERED);
  CHECK(static_cast<u8>(joy_hat_position::down) == SDL_HAT_DOWN);
  CHECK(static_cast<u8>(joy_hat_position::right_up) == SDL_HAT_RIGHTUP);
  CHECK(static_cast<u8>(joy_hat_position::right) == SDL_HAT_RIGHT);
  CHECK(static_cast<u8>(joy_hat_position::right_down) == SDL_HAT_RIGHTDOWN);
}

TEST_CASE("JoyHatEvent::set_hat", "[JoyHatEvent]")
{
  joy_hat_event event;

  const auto hat = 7;
  event.set_hat(hat);

  CHECK(event.hat() == hat);
}

TEST_CASE("JoyHatEvent::set_position", "[JoyHatEvent]")
{
  joy_hat_event event;

  const auto position = joy_hat_position::right;
  event.set_position(position);

  CHECK(event.position() == position);
}

TEST_CASE("JoyHatEvent::hat", "[JoyHatEvent]")
{
  SDL_JoyHatEvent sdlEvent;
  sdlEvent.hat = 2;
  joy_hat_event event{sdlEvent};

  CHECK(event.hat() == sdlEvent.hat);
}

TEST_CASE("JoyHatEvent::position", "[JoyHatEvent]")
{
  SDL_JoyHatEvent sdlEvent;
  sdlEvent.value = SDL_HAT_LEFT;
  joy_hat_event event{sdlEvent};

  CHECK(event.position() == joy_hat_position::left);
}