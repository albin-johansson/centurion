#include <gtest/gtest.h>

#include "events/event.hpp"

using sdl_event = SDL_QuitEvent;  // A simple SDL event type for testing
using common_event = cen::quit_event;

TEST(CommonEvent, SetTime)
{
  common_event event;

  constexpr Uint32 time = 8'934;
  event.SetTimestamp(time);

  ASSERT_EQ(time, event.GetTimestamp());
}

TEST(CommonEvent, SetType)
{
  common_event event;

  const auto type = cen::EventType::AppLowMemory;
  event.SetType(type);

  ASSERT_EQ(type, event.GetType());
}

TEST(CommonEvent, Time)
{
  constexpr Uint32 time = 8'321;

  sdl_event sdl;
  sdl.timestamp = time;

  const common_event event{sdl};
  ASSERT_EQ(time, event.GetTimestamp());
}

TEST(CommonEvent, Type)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  ASSERT_EQ(cen::EventType::MouseMotion, event.GetType());
}

TEST(CommonEvent, Get)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  const auto& internal = event.get();

  ASSERT_EQ(sdl.type, internal.type);
}
