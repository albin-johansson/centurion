#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(WindowEvent, Defaults)
{
  cen::window_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::window, event.type());
}

TEST(WindowEvent, EventId)
{
  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_FOCUS_GAINED;

  const cen::window_event event{sdl};
  ASSERT_EQ(cen::window_event_id::focus_gained, event.event_id());
}

TEST(WindowEvent, Data1)
{
  constexpr auto width = 75;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data1 = width;

  const cen::window_event event{sdl};
  ASSERT_EQ(width, event.data_1());
}

TEST(WindowEvent, Data2)
{
  constexpr auto height = 54;

  SDL_WindowEvent sdl{};
  sdl.event = SDL_WINDOWEVENT_RESIZED;
  sdl.data2 = height;

  const cen::window_event event{sdl};
  ASSERT_EQ(height, event.data_2());
}

TEST(WindowEvent, AsSDLEvent)
{
  const cen::window_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.window.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.window.timestamp, event.time());
}
