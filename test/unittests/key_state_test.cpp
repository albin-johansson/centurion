#include "key_state.hpp"

#include <catch.hpp>

#include "key_code.hpp"
#include "scan_code.hpp"

TEST_CASE("key_state::update", "[key_state]")
{
  cen::key_state state;
  CHECK_NOTHROW(state.update());
}

TEST_CASE("key_state::is_pressed", "[key_state]")
{
  cen::key_state state;

  CHECK(!state.is_pressed(SDL_SCANCODE_A));
  CHECK(!state.is_pressed(SDLK_a));

  CHECK(!state.is_pressed(cen::scan_code{-1}));
  CHECK(!state.is_pressed(SDL_NUM_SCANCODES));
  CHECK(!state.is_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::is_held", "[key_state]")
{
  cen::key_state state;

  CHECK(!state.is_held(SDL_SCANCODE_X));
  CHECK(!state.is_held(SDLK_x));

  CHECK(!state.is_held(cen::scan_code{-1}));
  CHECK(!state.is_held(SDL_NUM_SCANCODES));
  CHECK(!state.is_held(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::was_just_pressed", "[key_state]")
{
  cen::key_state state;

  CHECK(!state.was_just_pressed(SDL_SCANCODE_V));
  CHECK(!state.was_just_pressed(SDLK_v));

  CHECK(!state.was_just_pressed(SDL_NUM_SCANCODES));
  CHECK(!state.was_just_pressed(cen::scan_code{-1}));
  CHECK(!state.was_just_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::was_just_released", "[key_state]")
{
  cen::key_state state;

  CHECK(!state.was_just_released(SDL_SCANCODE_U));
  CHECK(!state.was_just_released(SDLK_u));

  CHECK(!state.was_just_released(cen::scan_code{-1}));
  CHECK(!state.was_just_released(cen::scan_code{SDL_NUM_SCANCODES}));
  CHECK(!state.was_just_released(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST_CASE("key_state::modifier_active", "[key_state]")
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  cen::key_state state;
  CHECK(!state.modifier_active(cen::key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);

  CHECK(state.modifier_active(cen::key_modifier::caps));
}

TEST_CASE("key_state::amount_of_keys", "[key_state]")
{
  cen::key_state state;
  CHECK(state.amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}
