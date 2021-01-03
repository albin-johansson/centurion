#include <gtest/gtest.h>

#include "event.hpp"

TEST(TextInputEvent, SetWindowId)
{
  cen::text_input_event event;

  constexpr auto id = 23;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(TextInputEvent, WindowId)
{
  SDL_TextInputEvent sdl{};
  sdl.type = SDL_TEXTINPUT;
  sdl.windowID = 8;

  const cen::text_input_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(TextInputEvent, TextUtf8)
{
  const SDL_TextInputEvent sdl{SDL_TEXTINPUT, 1, 1, "hello"};
  const cen::text_input_event event{sdl};
  EXPECT_EQ("hello", event.text_utf8());
}
