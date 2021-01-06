#include <gtest/gtest.h>

#include "event.hpp"

TEST(TextEditingEvent, Defaults)
{
  cen::text_editing_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::text_editing, event.type());
}

TEST(TextEditingEvent, SetWindowId)
{
  cen::text_editing_event event;

  constexpr auto id = 8;
  event.set_window_id(id);

  EXPECT_EQ(id, event.window_id());
}

TEST(TextEditingEvent, SetStart)
{
  cen::text_editing_event event;

  constexpr auto start = 4;
  event.set_start(start);

  EXPECT_EQ(start, event.start());
}

TEST(TextEditingEvent, SetLength)
{
  cen::text_editing_event event;

  constexpr auto length = 9;
  event.set_length(length);

  EXPECT_EQ(length, event.length());

  event.set_length(-1);
  EXPECT_EQ(0, event.length());

  event.set_length(33);
  EXPECT_EQ(32, event.length());
}

TEST(TextEditingEvent, WindowId)
{
  SDL_TextEditingEvent sdl{};
  sdl.windowID = 7;

  const cen::text_editing_event event{sdl};
  EXPECT_EQ(sdl.windowID, event.window_id());
}

TEST(TextEditingEvent, Start)
{
  SDL_TextEditingEvent sdl{};
  sdl.start = 4;

  const cen::text_editing_event event{sdl};
  EXPECT_EQ(sdl.start, event.start());
}

TEST(TextEditingEvent, Length)
{
  {  // Good length
    SDL_TextEditingEvent sdl{};
    sdl.length = 4;

    const cen::text_editing_event event{sdl};
    EXPECT_EQ(sdl.length, event.length());
  }

  {  // Underflow length
    SDL_TextEditingEvent sdl{};
    sdl.length = -1;

    const cen::text_editing_event event{sdl};
    EXPECT_EQ(0, event.length());
  }

  {  // Overflow length
    SDL_TextEditingEvent sdl{};
    sdl.length = 33;

    const cen::text_editing_event event{sdl};
    EXPECT_EQ(32, event.length());
  }
}
