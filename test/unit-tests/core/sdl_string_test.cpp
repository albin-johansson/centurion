#include "core/sdl_string.hpp"

#include <gtest/gtest.h>

TEST(SDLString, Constructor)
{
  ASSERT_NO_THROW(cen::sdl_string{nullptr});

  const cen::sdl_string str{nullptr};
  ASSERT_FALSE(str);
}

TEST(SDLString, Get)
{
  SDL_SetClipboardText("foo");
  const cen::sdl_string str{SDL_GetClipboardText()};
  ASSERT_STREQ(str.get(), "foo");
}

TEST(SDLString, Copy)
{
  {  // Valid string
    SDL_SetClipboardText("bar");
    const cen::sdl_string str{SDL_GetClipboardText()};
    const auto copy = str.copy();
    ASSERT_EQ("bar", copy);
  }

  {  // Empty string
    SDL_SetClipboardText(nullptr);
    const cen::sdl_string empty{SDL_GetClipboardText()};
    ASSERT_TRUE(empty.copy().empty());
  }

  {  // Null string
    const cen::sdl_string str{nullptr};
    ASSERT_EQ("", str.copy());
  }
}
