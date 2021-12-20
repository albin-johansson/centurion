#include <gtest/gtest.h>

#include "event.hpp"

TEST(JoyButtonEvent, Defaults)
{
  const cen::JoyButtonEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::JoyButtonDown, event.GetType());
}

TEST(JoyButtonEvent, SetWhich)
{
  cen::JoyButtonEvent event;

  event.SetWhich(92);
  ASSERT_EQ(92, event.GetWhich());
}

TEST(JoyButtonEvent, SetButton)
{
  cen::JoyButtonEvent event;

  event.SetButton(44);
  ASSERT_EQ(44, event.GetButton());
}

TEST(JoyButtonEvent, SetState)
{
  cen::JoyButtonEvent event;

  event.SetState(cen::ButtonState::Pressed);

  ASSERT_EQ(cen::ButtonState::Pressed, event.GetState());
  ASSERT_TRUE(event.IsPressed());
  ASSERT_FALSE(event.IsReleased());

  event.SetState(cen::ButtonState::Released);

  ASSERT_EQ(cen::ButtonState::Released, event.GetState());
  ASSERT_TRUE(event.IsReleased());
  ASSERT_FALSE(event.IsPressed());
}

TEST(JoyButtonEvent, AsSDLEvent)
{
  const cen::JoyButtonEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.jbutton.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(sdl.jbutton.timestamp, event.GetTimestamp());
}
