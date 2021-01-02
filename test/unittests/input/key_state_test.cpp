#include "key_state.hpp"

#include <gtest/gtest.h>

#include <type_traits>

#include "key_code.hpp"
#include "scan_code.hpp"

// TODO mock: update

static_assert(std::is_final_v<cen::key_state>);

static_assert(std::is_default_constructible_v<cen::key_state>);
static_assert(std::is_nothrow_destructible_v<cen::key_state>);

static_assert(std::is_nothrow_move_constructible_v<cen::key_state>);
static_assert(std::is_nothrow_move_assignable_v<cen::key_state>);

static_assert(std::is_nothrow_copy_constructible_v<cen::key_state>);
static_assert(std::is_nothrow_copy_assignable_v<cen::key_state>);

TEST(KeyState, IsPressed)
{
  cen::key_state state;

  EXPECT_FALSE(state.is_pressed(SDL_SCANCODE_A));
  EXPECT_FALSE(state.is_pressed(SDLK_a));

  EXPECT_FALSE(state.is_pressed(cen::scan_code{-1}));
  EXPECT_FALSE(state.is_pressed(SDL_NUM_SCANCODES));  // TODO scan_code::count?
  EXPECT_FALSE(state.is_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(KeyState, IsHeld)
{
  cen::key_state state;

  EXPECT_FALSE(state.is_held(SDL_SCANCODE_X));
  EXPECT_FALSE(state.is_held(SDLK_x));

  EXPECT_FALSE(state.is_held(cen::scan_code{-1}));
  EXPECT_FALSE(state.is_held(SDL_NUM_SCANCODES));
  EXPECT_FALSE(state.is_held(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(KeyState, WasJustPressed)
{
  cen::key_state state;

  EXPECT_FALSE(state.was_just_pressed(SDL_SCANCODE_V));
  EXPECT_FALSE(state.was_just_pressed(SDLK_v));

  EXPECT_FALSE(state.was_just_pressed(SDL_NUM_SCANCODES));
  EXPECT_FALSE(state.was_just_pressed(cen::scan_code{-1}));
  EXPECT_FALSE(state.was_just_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(KeyState, WasJustReleased)
{
  cen::key_state state;

  EXPECT_FALSE(state.was_just_released(SDL_SCANCODE_U));
  EXPECT_FALSE(state.was_just_released(SDLK_u));

  EXPECT_FALSE(state.was_just_released(cen::scan_code{-1}));
  EXPECT_FALSE(state.was_just_released(cen::scan_code{SDL_NUM_SCANCODES}));
  EXPECT_FALSE(state.was_just_released(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(KeyState, ModifierActive)
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  cen::key_state state;
  EXPECT_FALSE(state.modifier_active(cen::key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);
  EXPECT_TRUE(state.modifier_active(cen::key_modifier::caps));
}

TEST(KeyState, AmountOfkeys)
{
  cen::key_state state;
  EXPECT_EQ(static_cast<int>(SDL_NUM_SCANCODES), state.amount_of_keys());
}
