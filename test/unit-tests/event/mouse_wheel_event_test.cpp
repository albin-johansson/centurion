#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(MouseWheelEvent, Defaults)
{
  const cen::MouseWheelEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::MouseWheel, event.GetType());
}

TEST(MouseWheelEvent, SetWindowID)
{
  cen::MouseWheelEvent event;

  event.SetWindowID(32);
  ASSERT_EQ(32, event.GetWindowID());
}

TEST(MouseWheelEvent, SetWhich)
{
  cen::MouseWheelEvent event;

  event.SetWhich(32);
  ASSERT_EQ(32, event.GetWhich());
}

TEST(MouseWheelEvent, SetXScroll)
{
  cen::MouseWheelEvent event;

  event.SetXScroll(-545);
  ASSERT_EQ(-545, event.GetXScroll());
}

TEST(MouseWheelEvent, SetYScroll)
{
  cen::MouseWheelEvent event;

  event.SetYScroll(725);
  ASSERT_EQ(725, event.GetYScroll());
}

TEST(MouseWheelEvent, SetDirection)
{
  cen::MouseWheelEvent event;

  event.SetDirection(cen::MouseWheelDirection::Flipped);
  ASSERT_EQ(cen::MouseWheelDirection::Flipped, event.GetDirection());
}

TEST(MouseWheelEvent, AsSDLEvent)
{
  const cen::MouseWheelEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.wheel.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.wheel.timestamp, event.GetTimestamp());
}
