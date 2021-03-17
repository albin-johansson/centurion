#include "input/key_state.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(const Uint8*, SDL_GetKeyboardState, int*)
}
// clang-format on

TEST(KeyCode, Constructor)
{
  [[maybe_unused]] cen::key_state state;
  EXPECT_EQ(1, SDL_GetKeyboardState_fake.call_count);
}
