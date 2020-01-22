#include "catch.hpp"
#include "key_state.h"

using namespace centurion;

TEST_CASE("KeyState internal array bounds assertions", "[KeyState]") {
  KeyState state;

  // FIXME this requires assertions to be enabled for tests
  const auto maxScancode = static_cast<SDL_Scancode>(SDL_NUM_SCANCODES - 1);
  CHECK_NOFAIL(state.is_pressed(maxScancode));
  CHECK_NOFAIL(state.is_held(maxScancode));
  CHECK_NOFAIL(state.was_just_pressed(maxScancode));
  CHECK_NOFAIL(state.was_just_released(maxScancode));
}

TEST_CASE("KeyState::get_amount_of_keys", "[KeyState]") {
  KeyState state;
  CHECK(state.get_amount_of_keys() == static_cast<int>(SDL_NUM_SCANCODES));
}