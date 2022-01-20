#include <gtest/gtest.h>

#include "centurion/window_events.hpp"

TEST(window_event, Defaults)
{
  const cen::window_event event;
  ASSERT_EQ(cen::event_type::window, event.type());
  ASSERT_EQ(cen::window_event_id::none, event.event_id());
}

TEST(WindowEvent, SetEventID)
{
  cen::window_event event;

  event.set_event_id(cen::window_event_id::focus_gained);
  ASSERT_EQ(cen::window_event_id::focus_gained, event.event_id());
}

TEST(WindowEvent, SetData1)
{
  cen::window_event event;
  event.set_event_id(cen::window_event_id::resized);

  const cen::int32 data = 75;
  event.set_data1(data);

  ASSERT_EQ(cen::window_event_id::resized, event.event_id());
  ASSERT_EQ(data, event.data1());
  ASSERT_EQ(0, event.data2());
}

TEST(WindowEvent, SetData2)
{
  cen::window_event event;
  event.set_event_id(cen::window_event_id::resized);

  const cen::int32 data = 54;
  event.set_data2(data);

  ASSERT_EQ(cen::window_event_id::resized, event.event_id());
  ASSERT_EQ(0, event.data1());
  ASSERT_EQ(data, event.data2());
}

TEST(WindowEvent, AsSDLEvent)
{
  const cen::window_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.window.type, to_underlying(event.type()));
  ASSERT_EQ(underlying.window.timestamp, event.timestamp().count());
}
