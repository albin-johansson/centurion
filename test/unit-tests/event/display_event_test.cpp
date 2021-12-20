#include "events/display_event.hpp"

#include <gtest/gtest.h>

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(DisplayEvent, Defaults)
{
  const cen::display_event event;
  ASSERT_EQ(cen::EventType::Display, event.type());
  ASSERT_EQ(cen::display_event_id::none, event.event_id());
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(0u, event.index());
  ASSERT_EQ(0, event.data_1());
}

TEST(DisplayEvent, SetEventId)
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

  event.set_index(42u);
  ASSERT_EQ(42u, event.index());
}

TEST(DisplayEvent, SetData1)
{
  cen::display_event event;

  event.set_data_1(SDL_ORIENTATION_LANDSCAPE);
  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, event.data_1());
}

TEST(DisplayEvent, Data1)
{
  SDL_DisplayEvent source{};
  source.type = SDL_DISPLAYEVENT;
  source.timestamp = SDL_GetTicks();
  source.display = 42u;
  source.event = SDL_DISPLAYEVENT_ORIENTATION;
  source.data1 = SDL_ORIENTATION_LANDSCAPE;

  const cen::display_event event{source};
  ASSERT_EQ(42u, event.index());
  ASSERT_EQ(cen::display_event_id::orientation, event.event_id());
  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, event.data_1());
}

TEST(DisplayEvent, AsSdlEvent)
{
  cen::display_event event;
  event.set_time(1'337u);
  event.set_index(123u);
  event.set_event_id(cen::display_event_id::connected);
  event.set_data_1(5);

  const auto converted = cen::as_sdl_event(event);
  ASSERT_EQ(SDL_DISPLAYEVENT, static_cast<SDL_EventType>(converted.display.type));
  ASSERT_EQ(1'337u, converted.display.timestamp);
  ASSERT_EQ(123u, converted.display.display);
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, converted.display.event);
  ASSERT_EQ(5, converted.display.data1);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)