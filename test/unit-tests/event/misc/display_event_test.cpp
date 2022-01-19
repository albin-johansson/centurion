#include <gtest/gtest.h>

#include "misc_events.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(DisplayEvent, Defaults)
{
  const cen::display_event event;
  ASSERT_EQ(cen::event_type::display, event.type());
  ASSERT_EQ(cen::display_event_id::none, event.event_id());
  ASSERT_EQ(0u, event.index());
  ASSERT_EQ(0, event.data1());
}

TEST(DisplayEvent, SetEventID)
{
  cen::display_event event;

  event.set_event_id(cen::display_event_id::orientation);
  ASSERT_EQ(cen::display_event_id::orientation, event.event_id());

  event.set_event_id(cen::display_event_id::connected);
  ASSERT_EQ(cen::display_event_id::connected, event.event_id());

  event.set_event_id(cen::display_event_id::disconnected);
  ASSERT_EQ(cen::display_event_id::disconnected, event.event_id());
}

TEST(DisplayEvent, SetIndex)
{
  cen::display_event event;

  const cen::uint32 index = 42;
  event.set_index(index);

  ASSERT_EQ(index, event.index());
}

TEST(DisplayEvent, SetData1)
{
  cen::display_event event;

  event.set_data1(SDL_ORIENTATION_LANDSCAPE);
  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, event.data1());
}

TEST(DisplayEvent, AsSdlEvent)
{
  cen::display_event event;
  event.set_index(123u);
  event.set_event_id(cen::display_event_id::connected);
  event.set_data1(5);

  const auto converted = cen::as_sdl_event(event);
  ASSERT_EQ(SDL_DISPLAYEVENT, static_cast<SDL_EventType>(converted.display.type));
  ASSERT_EQ(123u, converted.display.display);
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, converted.display.event);
  ASSERT_EQ(5, converted.display.data1);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)