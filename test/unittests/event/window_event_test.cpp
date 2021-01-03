#include <gtest/gtest.h>

#include "event.hpp"

TEST(WindowEvent, EventId)
{
  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_FOCUS_GAINED;

  const cen::window_event event{sdl};
  EXPECT_EQ(cen::window_event_id::focus_gained, event.event_id());
}

TEST(WindowEvent, Data1)
{
  constexpr auto width = 75;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data1 = width;

  const cen::window_event event{sdl};
  EXPECT_EQ(width, event.data_1());
}

TEST(WindowEvent, Data2)
{
  constexpr auto height = 54;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data2 = height;

  const cen::window_event event{sdl};
  EXPECT_EQ(height, event.data_2());
}
