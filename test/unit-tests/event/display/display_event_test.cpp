#include <gtest/gtest.h>

#include "event.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(DisplayEvent, Defaults)
{
  const cen::DisplayEvent event;
  ASSERT_EQ(cen::EventType::Display, event.GetType());
  ASSERT_EQ(cen::DisplayEventID::None, event.GetEventID());
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(0u, event.GetIndex());
  ASSERT_EQ(0, event.GetData1());
}

TEST(DisplayEvent, SetEventID)
{
  cen::DisplayEvent event;

  event.SetEventID(cen::DisplayEventID::Orientation);
  ASSERT_EQ(cen::DisplayEventID::Orientation, event.GetEventID());

  event.SetEventID(cen::DisplayEventID::Connected);
  ASSERT_EQ(cen::DisplayEventID::Connected, event.GetEventID());

  event.SetEventID(cen::DisplayEventID::Disconnected);
  ASSERT_EQ(cen::DisplayEventID::Disconnected, event.GetEventID());
}

TEST(DisplayEvent, SetIndex)
{
  cen::DisplayEvent event;

  event.SetIndex(42u);
  ASSERT_EQ(42u, event.GetIndex());
}

TEST(DisplayEvent, SetData1)
{
  cen::DisplayEvent event;

  event.SetData1(SDL_ORIENTATION_LANDSCAPE);
  ASSERT_EQ(SDL_ORIENTATION_LANDSCAPE, event.GetData1());
}

TEST(DisplayEvent, AsSdlEvent)
{
  cen::DisplayEvent event;
  event.SetTimestamp(1'337u);
  event.SetIndex(123u);
  event.SetEventID(cen::DisplayEventID::Connected);
  event.SetData1(5);

  const auto converted = cen::AsSDLEvent(event);
  ASSERT_EQ(SDL_DISPLAYEVENT, static_cast<SDL_EventType>(converted.display.type));
  ASSERT_EQ(1'337u, converted.display.timestamp);
  ASSERT_EQ(123u, converted.display.display);
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, converted.display.event);
  ASSERT_EQ(5, converted.display.data1);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)