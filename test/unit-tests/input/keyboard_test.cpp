#include "input/keyboard.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

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
  ASSERT_NO_THROW(keyboard.update());
}

TEST(Keyboard, IsPressed)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.is_pressed(SDL_SCANCODE_A));
  ASSERT_FALSE(keyboard.is_pressed(SDLK_a));

  ASSERT_FALSE(keyboard.is_pressed(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.is_pressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.is_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsHeld)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.is_held(SDL_SCANCODE_X));
  ASSERT_FALSE(keyboard.is_held(SDLK_x));

  ASSERT_FALSE(keyboard.is_held(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.is_held(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.is_held(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustPressed)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.just_pressed(SDL_SCANCODE_V));
  ASSERT_FALSE(keyboard.just_pressed(SDLK_v));

  ASSERT_FALSE(keyboard.just_pressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.just_pressed(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.just_pressed(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustReleased)
{
  cen::keyboard keyboard;

  ASSERT_FALSE(keyboard.just_released(SDL_SCANCODE_U));
  ASSERT_FALSE(keyboard.just_released(SDLK_u));

  ASSERT_FALSE(keyboard.just_released(cen::scan_code{-1}));
  ASSERT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES}));
  ASSERT_FALSE(keyboard.just_released(cen::scan_code{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsActive)
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  cen::keyboard keyboard;
  ASSERT_FALSE(keyboard.is_active(cen::key_modifier::caps));

  SDL_SetModState(SDL_Keymod::KMOD_CAPS);
  ASSERT_TRUE(keyboard.is_active(cen::key_modifier::caps));
}

TEST(Keyboard, KeyCount)
{
  cen::keyboard keyboard;
  ASSERT_EQ(static_cast<int>(SDL_NUM_SCANCODES), keyboard.key_count());
}

TEST(Keyboard, ToString)
{
  cen::keyboard keyboard;

  ASSERT_EQ("keyboard{#keys: " + std::to_string(keyboard.key_count()) + "}",
            cen::to_string(keyboard));

  std::cout << keyboard;
}
