#include <fff.h>
#include <gtest/gtest.h>

#include "input/keyboard.hpp"

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(const Uint8*, SDL_GetKeyboardState, int*)
}
// clang-format on

TEST(Keyboard, Constructor)
{
  [[maybe_unused]] cen::keyboard state;
  EXPECT_EQ(1, SDL_GetKeyboardState_fake.call_count);
}
