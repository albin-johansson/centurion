#include <gtest/gtest.h>

#include "event.hpp"

using sdl_event = SDL_QuitEvent;  // A simple SDL event type for testing
using common_event = cen::common_event<sdl_event>;

TEST(CommonEvent, SetTime)
{
  common_event event;

  constexpr auto time = 8'934;
  event.set_time(time);

  EXPECT_EQ(time, event.time());
}

TEST(CommonEvent, SetType)
{
  common_event event;

  const auto type = cen::event_type::app_low_memory;
  event.set_type(type);

  EXPECT_EQ(type, event.type());
}

TEST(CommonEvent, Time)
{
  constexpr auto time = 8'321;

  sdl_event sdl;
  sdl.timestamp = time;

  const common_event event{sdl};
  EXPECT_EQ(time, event.time());
}

TEST(CommonEvent, Type)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  EXPECT_EQ(cen::event_type::mouse_motion, event.type());
}

TEST(CommonEvent, Get)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  const auto& internal = event.get();

  EXPECT_EQ(sdl.type, internal.type);
}
