#include "input/keyboard.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(const Uint8*, SDL_GetKeyboardState, int*)
FAKE_VALUE_FUNC(SDL_bool, SDL_HasScreenKeyboardSupport)
}
// clang-format on

TEST(Keyboard, Constructor)
{
  [[maybe_unused]] cen::keyboard state;
  ASSERT_EQ(1, SDL_GetKeyboardState_fake.call_count);
}

TEST(Keyboard, HasScreenKeyboard)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(SDL_HasScreenKeyboardSupport, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::has_screen_keyboard());
  ASSERT_TRUE(cen::has_screen_keyboard());
  ASSERT_EQ(2, SDL_HasScreenKeyboardSupport_fake.call_count);
}
