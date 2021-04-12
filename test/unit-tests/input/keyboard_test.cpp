#include <gtest/gtest.h>

#include <type_traits>

#include "input/keyboard.hpp"

static_assert(std::is_final_v<cen::keyboard>);

static_assert(std::is_default_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_destructible_v<cen::keyboard>);

static_assert(std::is_nothrow_move_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_move_assignable_v<cen::keyboard>);

static_assert(std::is_nothrow_copy_constructible_v<cen::keyboard>);
static_assert(std::is_nothrow_copy_assignable_v<cen::keyboard>);

TEST(Keyboard, Update)
{
  cen::keyboard keyboard;
  EXPECT_NO_THROW(keyboard.update());
}

TEST(Keyboard, IsPressed)
{
  cen::keyboard keyboard;

  EXPECT_FALSE(keyboard.is_pressed(SDL_SCANCODE_A));
  EXPECT_FALSE(keyboard.is_pressed(SDLK_a));

  EXPECT_FALSE(keyboard.is_pressed(cen::scan_code{-1}));
  EXPECT_FALSE(keyboard.is_pressed(SDL_NUM_SCANCODES));
  EXPECT_FALSE(keyboard.is_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsHeld)
{
  cen::keyboard keyboard;

  EXPECT_FALSE(keyboard.is_held(SDL_SCANCODE_X));
  EXPECT_FALSE(keyboard.is_held(SDLK_x));

  EXPECT_FALSE(keyboard.is_held(cen::scan_code{-1}));
  EXPECT_FALSE(keyboard.is_held(SDL_NUM_SCANCODES));
  EXPECT_FALSE(keyboard.is_held(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustPressed)
{
  cen::keyboard keyboard;

  EXPECT_FALSE(keyboard.just_pressed(SDL_SCANCODE_V));
  EXPECT_FALSE(keyboard.just_pressed(SDLK_v));

  EXPECT_FALSE(keyboard.just_pressed(SDL_NUM_SCANCODES));
  EXPECT_FALSE(keyboard.just_pressed(cen::scan_code{-1}));
  EXPECT_FALSE(keyboard.just_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustReleased)
{
  cen::keyboard keyboard;

  EXPECT_FALSE(keyboard.just_released(SDL_SCANCODE_U));
  EXPECT_FALSE(keyboard.just_released(SDLK_u));

  EXPECT_FALSE(keyboard.just_released(cen::scan_code{-1}));
  EXPECT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES}));
  EXPECT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsActive)
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  cen::keyboard keyboard;
  EXPECT_FALSE(keyboard.is_active(cen::key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);
  EXPECT_TRUE(keyboard.is_active(cen::key_modifier::caps));
}

TEST(Keyboard, KeyCount)
{
  cen::keyboard state;
  EXPECT_EQ(static_cast<int>(SDL_NUM_SCANCODES), state.key_count());
}
