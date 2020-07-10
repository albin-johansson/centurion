#include "key_state.hpp"

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
  CHECK(!state.is_pressed(Key{SDL_SCANCODE_A}));
  CHECK(!state.is_pressed(Key{-1}));
  CHECK(!state.is_pressed(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.is_pressed(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("KeyState::is_held", "[KeyState]")
{
  KeyState state;
  CHECK(!state.is_held(Key{SDLK_x}));
  CHECK(!state.is_held(Key{-1}));
  CHECK(!state.is_held(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.is_held(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("KeyState::was_just_pressed", "[KeyState]")
{
  KeyState state;
  CHECK(!state.was_just_pressed(Key{SDL_SCANCODE_V}));
  CHECK(!state.was_just_pressed(Key{-1}));
  CHECK(!state.was_just_pressed(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.was_just_pressed(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("KeyState::was_just_released", "[KeyState]")
{
  KeyState state;
  CHECK(!state.was_just_released(Key{SDLK_u}));
  CHECK(!state.was_just_released(Key{-1}));
  CHECK(!state.was_just_released(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.was_just_released(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("KeyState::modifier_active", "[KeyState]")
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  KeyState state;
  CHECK(!state.modifier_active(key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);

  CHECK(state.modifier_active(key_modifier::caps));
}

TEST_CASE("KeyState::amount_of_keys", "[KeyState]")
{
  KeyState state;
  CHECK(state.amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}
