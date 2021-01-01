#include "sdl_string.hpp"

#include <gtest/gtest.h>

#include "types.hpp"

TEST(SDLString, Constructor)
{
  EXPECT_NO_THROW(cen::sdl_string{nullptr});

  const cen::sdl_string str{nullptr};
  EXPECT_FALSE(str);
}

TEST(SDLString, Get)
{
  SDL_SetClipboardText("foo");
  const cen::sdl_string str{SDL_GetClipboardText()};
  EXPECT_STREQ(str.get(), "foo");
}

TEST(SDLString, Copy)
{
  {  // Valid string
    SDL_SetClipboardText("bar");
    const cen::sdl_string str{SDL_GetClipboardText()};
    const auto copy = str.copy();
    EXPECT_EQ("bar", copy);
  }

  {  // Empty string
    SDL_SetClipboardText(nullptr);
    const cen::sdl_string empty{SDL_GetClipboardText()};
    EXPECT_TRUE(empty.copy().empty());
  }
}
