#include "key_state.h"

#include <catch.hpp>

using namespace centurion;
using namespace centurion::input;

TEST_CASE("KeyState smart pointer factory methods", "[KeyState]")
{
  CHECK(KeyState::unique());
  CHECK(KeyState::shared());
}

TEST_CASE("KeyState::update", "[KeyState]")
{
  KeyState state;
  CHECK_NOTHROW(state.update());
}

TEST_CASE("KeyState::is_pressed", "[KeyState]")
{
  KeyState state;
  CHECK(!state.is_pressed(SDL_SCANCODE_A));
  CHECK(!state.is_pressed(-1));
  CHECK(!state.is_pressed(SDL_NUM_SCANCODES));
  CHECK(!state.is_pressed(SDL_NUM_SCANCODES + 1));
}

TEST_CASE("KeyState::is_held", "[KeyState]")
{
  KeyState state;
  CHECK(!state.is_held(SDLK_x));
  CHECK(!state.is_held(-1));
  CHECK(!state.is_held(SDL_NUM_SCANCODES));
  CHECK(!state.is_held(SDL_NUM_SCANCODES + 1));
}

TEST_CASE("KeyState::was_just_pressed", "[KeyState]")
{
  KeyState state;
  CHECK(!state.was_just_pressed(SDL_SCANCODE_V));
  CHECK(!state.was_just_pressed(-1));
  CHECK(!state.was_just_pressed(SDL_NUM_SCANCODES));
  CHECK(!state.was_just_pressed(SDL_NUM_SCANCODES + 1));
}

TEST_CASE("KeyState::was_just_released", "[KeyState]")
{
  KeyState state;
  CHECK(!state.was_just_released(SDLK_u));
  CHECK(!state.was_just_released(-1));
  CHECK(!state.was_just_released(SDL_NUM_SCANCODES));
  CHECK(!state.was_just_released(SDL_NUM_SCANCODES + 1));
}

TEST_CASE("KeyState::amount_of_keys", "[KeyState]")
{
  KeyState state;
  CHECK(state.amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}
