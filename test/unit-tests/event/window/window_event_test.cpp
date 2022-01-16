#include <gtest/gtest.h>

#include "event.hpp"

TEST(WindowEvent, Defaults)
{
  const cen::WindowEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::Window, event.GetType());
  ASSERT_EQ(cen::WindowEventID::None, event.GetEventID());
}

TEST(WindowEvent, SetEventID)
{
  cen::WindowEvent event;

  event.SetEventID(cen::WindowEventID::FocusGained);
  ASSERT_EQ(cen::WindowEventID::FocusGained, event.GetEventID());
}

TEST(WindowEvent, SetData1)
{
  cen::WindowEvent event;
  event.SetEventID(cen::WindowEventID::Resized);
  event.SetData1(75);

  ASSERT_EQ(cen::WindowEventID::Resized, event.GetEventID());
  ASSERT_EQ(75, event.GetData1());
  ASSERT_EQ(0, event.GetData2());
}

TEST(WindowEvent, Data2)
{
  cen::WindowEvent event;
  event.SetEventID(cen::WindowEventID::Resized);
  event.SetData2(54);

  ASSERT_EQ(cen::WindowEventID::Resized, event.GetEventID());
  ASSERT_EQ(0, event.GetData1());
  ASSERT_EQ(54, event.GetData2());
}

TEST(WindowEvent, AsSDLEvent)
{
  const cen::WindowEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.window.type, to_underlying(event.GetType()));
  ASSERT_EQ(underlying.window.timestamp, event.GetTimestamp());
}
