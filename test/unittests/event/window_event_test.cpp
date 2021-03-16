#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(WindowEvent, Defaults)
{
  cen::window_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::window, event.type());
}

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

TEST(WindowEvent, AsSDLEvent)
{
  const cen::window_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.window.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.window.timestamp, event.time());
}
