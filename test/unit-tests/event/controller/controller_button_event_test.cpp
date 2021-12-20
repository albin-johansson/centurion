#include <gtest/gtest.h>

#include "event.hpp"

TEST(ControllerButtonEvent, Defaults)
{
  const cen::ControllerButtonEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::ControllerButtonDown, event.GetType());
}

TEST(ControllerButtonEvent, SetButton)
{
  cen::ControllerButtonEvent event;

  event.SetButton(cen::ControllerButton::A);
  ASSERT_EQ(cen::ControllerButton::A, event.GetButton());
}

TEST(ControllerButtonEvent, SetState)
{
  cen::ControllerButtonEvent event;

  event.SetState(cen::ButtonState::Pressed);

  ASSERT_EQ(cen::ButtonState::Pressed, event.GetState());
  ASSERT_TRUE(event.IsPressed());
  ASSERT_FALSE(event.IsReleased());

  event.SetState(cen::ButtonState::Released);

  ASSERT_EQ(cen::ButtonState::Released, event.GetState());
  ASSERT_TRUE(event.IsReleased());
  ASSERT_FALSE(event.IsPressed());
}

TEST(ControllerButtonEvent, SetWhich)
{
  cen::ControllerButtonEvent event;

  event.SetWhich(7);
  ASSERT_EQ(7, event.GetWhich());
}

TEST(ControllerButtonEvent, AsSDLEvent)
{
  const cen::ControllerButtonEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.cbutton.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.cbutton.timestamp, event.GetTimestamp());
}