#include <gtest/gtest.h>

#include "event.hpp"

TEST(MouseButtonEvent, Defaults)
{
  const cen::MouseButtonEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::MouseButtonDown, event.GetType());
}

TEST(MouseButtonEvent, SetWindowID)
{
  cen::MouseButtonEvent event;

  event.SetWindowID(64);
  ASSERT_EQ(64, event.GetWindowID());
}

TEST(MouseButtonEvent, SetWhich)
{
  cen::MouseButtonEvent event;

  event.SetWhich(17);
  ASSERT_EQ(17, event.GetWhich());
}

TEST(MouseButtonEvent, SetButton)
{
  cen::MouseButtonEvent event;

  event.SetButton(cen::MouseButton::Right);
  ASSERT_EQ(cen::MouseButton::Right, event.GetButton());
}

TEST(MouseButtonEvent, SetState)
{
  cen::MouseButtonEvent event;

  event.SetState(cen::ButtonState::Pressed);

  ASSERT_EQ(cen::ButtonState::Pressed, event.GetState());
  ASSERT_TRUE(event.IsPressed());
  ASSERT_FALSE(event.IsReleased());

  event.SetState(cen::ButtonState::Released);

  ASSERT_EQ(cen::ButtonState::Released, event.GetState());
  ASSERT_TRUE(event.IsReleased());
  ASSERT_FALSE(event.IsPressed());
}

TEST(MouseButtonEvent, SetClicks)
{
  cen::MouseButtonEvent event;

  event.SetClicks(2);
  ASSERT_EQ(2, event.GetClicks());
}

TEST(MouseButtonEvent, SetX)
{
  cen::MouseButtonEvent event;

  event.SetX(645);
  ASSERT_EQ(645, event.GetX());
}

TEST(MouseButtonEvent, SetY)
{
  cen::MouseButtonEvent event;

  event.SetY(177);
  ASSERT_EQ(177, event.GetY());
}

TEST(MouseButtonEvent, AsSDLEvent)
{
  const cen::MouseButtonEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.button.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.button.timestamp, event.GetTimestamp());
}
