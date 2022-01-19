#include <gtest/gtest.h>

#include "event_base.hpp"
#include "misc_events.hpp"

using sdl_event = SDL_QuitEvent;  // A simple SDL event type for testing
using common_event = cen::quit_event;

using namespace cen::literals::time_literals;

TEST(EventBase, SetTimestamp)
{
  common_event event;

  const auto time = 8'934_ms;
  event.set_timestamp(time);

  ASSERT_EQ(time, event.timestamp());
}

TEST(EventBase, SetType)
{
  common_event event;

  const auto type = cen::event_type::app_low_memory;
  event.set_type(type);

  ASSERT_EQ(type, event.type());
}

TEST(EventBase, Timestamp)
{
  const auto time = 8'321_ms;

  sdl_event sdl;
  sdl.timestamp = time.count();

  const common_event event{sdl};
  ASSERT_EQ(time, event.timestamp());
}

TEST(EventBase, Type)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  ASSERT_EQ(cen::event_type::mouse_motion, event.type());
}

TEST(EventBase, Get)
{
  sdl_event sdl;
  sdl.type = SDL_MOUSEMOTION;

  const common_event event{sdl};
  const auto& internal = event.get();

  ASSERT_EQ(sdl.type, internal.type);
}
