#include <gtest/gtest.h>

#include "events/event.hpp"

using sdl_event = SDL_QuitEvent;  // A simple SDL event type for testing
using common_event = cen::quit_event;

TEST(CommonEvent, SetTime)
{
  common_event event;

  constexpr Uint32 time = 8'934;
  event.set_time(time);

  ASSERT_EQ(time, event.time());
}

TEST(CommonEvent, SetType)
{
  common_event event;

  const auto type = cen::EventType::AppLowMemory;
  event.set_type(type);

  ASSERT_EQ(type, event.type());
}

TEST(CommonEvent, Time)
{
  constexpr Uint32 time = 8'321;

  sdl_event sdl;
  sdl.timestamp = time;

  const common_event event{sdl};
  ASSERT_EQ(time, event.time());
}

TEST(CommonEvent, Type)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  ASSERT_EQ(cen::EventType::MouseMotion, event.type());
}

TEST(CommonEvent, Get)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  const auto& internal = event.get();

  ASSERT_EQ(sdl.type, internal.type);
}
