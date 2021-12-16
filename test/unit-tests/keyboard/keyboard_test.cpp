#include "keyboard.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <type_traits>

static_assert(std::is_final_v<cen::Keyboard>);

static_assert(std::is_default_constructible_v<cen::Keyboard>);
static_assert(std::is_nothrow_destructible_v<cen::Keyboard>);

static_assert(std::is_nothrow_move_constructible_v<cen::Keyboard>);
static_assert(std::is_nothrow_move_assignable_v<cen::Keyboard>);

static_assert(std::is_nothrow_copy_constructible_v<cen::Keyboard>);
static_assert(std::is_nothrow_copy_assignable_v<cen::Keyboard>);

TEST(Keyboard, Update)
{
  cen::Keyboard keyboard;
  ASSERT_NO_THROW(keyboard.Update());
}

TEST(Keyboard, IsPressed)
{
  cen::Keyboard keyboard;

  ASSERT_FALSE(keyboard.IsPressed(SDL_SCANCODE_A));
  ASSERT_FALSE(keyboard.IsPressed(SDLK_a));

  ASSERT_FALSE(keyboard.IsPressed(cen::ScanCode{-1}));
  ASSERT_FALSE(keyboard.IsPressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.IsPressed(cen::ScanCode{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsHeld)
{
  cen::Keyboard keyboard;

  ASSERT_FALSE(keyboard.IsHeld(SDL_SCANCODE_X));
  ASSERT_FALSE(keyboard.IsHeld(SDLK_x));

  ASSERT_FALSE(keyboard.IsHeld(cen::ScanCode{-1}));
  ASSERT_FALSE(keyboard.IsHeld(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.IsHeld(cen::ScanCode{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustPressed)
{
  cen::Keyboard keyboard;

  ASSERT_FALSE(keyboard.JustPressed(SDL_SCANCODE_V));
  ASSERT_FALSE(keyboard.JustPressed(SDLK_v));

  ASSERT_FALSE(keyboard.JustPressed(SDL_NUM_SCANCODES));
  ASSERT_FALSE(keyboard.JustPressed(cen::ScanCode{-1}));
  ASSERT_FALSE(keyboard.JustPressed(cen::ScanCode{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, JustReleased)
{
  cen::Keyboard keyboard;

  ASSERT_FALSE(keyboard.JustReleased(SDL_SCANCODE_U));
  ASSERT_FALSE(keyboard.JustReleased(SDLK_u));

  ASSERT_FALSE(keyboard.JustReleased(cen::ScanCode{-1}));
  ASSERT_FALSE(keyboard.JustReleased(cen::ScanCode{SDL_NUM_SCANCODES}));
  ASSERT_FALSE(keyboard.JustReleased(cen::ScanCode{SDL_NUM_SCANCODES + 1}));
}

TEST(Keyboard, IsActive)
{
  // If this test fails, make sure that CAPS isn't enabled on your computer :)
  cen::Keyboard keyboard;
  ASSERT_FALSE(keyboard.IsActive(cen::KeyMod::Caps));

  cen::SetModifiers(cen::KeyMod::Caps);
  ASSERT_TRUE(keyboard.IsActive(cen::KeyMod::Caps));
}

TEST(Keyboard, KeyCount)
{
  cen::Keyboard keyboard;
  ASSERT_EQ(SDL_NUM_SCANCODES, keyboard.GetNumKeys());
}

TEST(Keyboard, ToString)
{
  cen::Keyboard keyboard;

  ASSERT_EQ("Keyboard(#keys: " + std::to_string(keyboard.GetNumKeys()) + ")",
            cen::to_string(keyboard));

  std::clog << keyboard << '\n';
}
