#include "key_state.hpp"

#include <catch.hpp>

using namespace centurion;
using namespace centurion::input;

TEST_CASE("key_state smart pointer factory methods", "[key_state]")
{
  CHECK(key_state::unique());
  CHECK(key_state::shared());
}

TEST_CASE("key_state::update", "[key_state]")
{
  key_state state;
  CHECK_NOTHROW(state.update());
}

TEST_CASE("key_state::is_pressed", "[key_state]")
{
  key_state state;
  CHECK(!state.is_pressed(Key{SDL_SCANCODE_A}));
  CHECK(!state.is_pressed(Key{-1}));
  CHECK(!state.is_pressed(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.is_pressed(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::is_held", "[key_state]")
{
  key_state state;
  CHECK(!state.is_held(Key{SDLK_x}));
  CHECK(!state.is_held(Key{-1}));
  CHECK(!state.is_held(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.is_held(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::was_just_pressed", "[key_state]")
{
  key_state state;
  CHECK(!state.was_just_pressed(Key{SDL_SCANCODE_V}));
  CHECK(!state.was_just_pressed(Key{-1}));
  CHECK(!state.was_just_pressed(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.was_just_pressed(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::was_just_released", "[key_state]")
{
  key_state state;
  CHECK(!state.was_just_released(Key{SDLK_u}));
  CHECK(!state.was_just_released(Key{-1}));
  CHECK(!state.was_just_released(Key{SDL_NUM_SCANCODES}));
  CHECK(!state.was_just_released(Key{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::modifier_active", "[key_state]")
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  key_state state;
  CHECK(!state.modifier_active(key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);

  CHECK(state.modifier_active(key_modifier::caps));
}

TEST_CASE("key_state::amount_of_keys", "[key_state]")
{
  key_state state;
  CHECK(state.amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}
