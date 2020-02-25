#include "key_state.h"

#include "catch.hpp"

using namespace centurion;
using namespace centurion::input;

TEST_CASE("KeyState smart pointer factory methods", "[KeyState]")
{
  CHECK(KeyState::unique());
  CHECK(KeyState::shared());
}

TEST_CASE("KeyState internal array bounds assertions", "[KeyState]")
{
  KeyState state;

  // Note, these tests are only useful when assertions are enabled
  const auto maxScancode = static_cast<SDL_Scancode>(SDL_NUM_SCANCODES - 1);
  CHECK_NOFAIL(state.is_pressed(maxScancode));
  CHECK_NOFAIL(state.is_held(maxScancode));
  CHECK_NOFAIL(state.was_just_pressed(maxScancode));
  CHECK_NOFAIL(state.was_just_released(maxScancode));
}

TEST_CASE("KeyState::get_amount_of_keys", "[KeyState]")
{
  KeyState state;
  CHECK(state.get_amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}