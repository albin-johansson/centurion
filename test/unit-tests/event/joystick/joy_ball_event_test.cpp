#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(JoyBallEvent, Defaults)
{
  const cen::JoyBallEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyBallMotion, event.GetType());
}

TEST(JoyBallEvent, SetWhich)
{
  cen::JoyBallEvent event;

  event.SetWhich(3);
  ASSERT_EQ(3, event.GetWhich());
}

TEST(JoyBallEvent, SetBall)
{
  cen::JoyBallEvent event;

  event.SetBall(7);
  ASSERT_EQ(7, event.GetBall());
}

TEST(JoyBallEvent, SetDeltaX)
{
  cen::JoyBallEvent event;

  event.SetDeltaX(173);
  ASSERT_EQ(173, event.GetDeltaX());
}

TEST(JoyBallEvent, SetDeltaY)
{
  cen::JoyBallEvent event;

  event.SetDeltaY(-57);
  ASSERT_EQ(-57, event.GetDeltaY());
}

TEST(JoyBallEvent, AsSDLEvent)
{
  const cen::JoyBallEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.jball.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.jball.timestamp, event.GetTimestamp());
}
