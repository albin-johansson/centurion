#include <gtest/gtest.h>

#include "event.hpp"

TEST(MouseMotionEvent, Defaults)
{
  const cen::MouseMotionEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::MouseMotion, event.GetType());
}

TEST(MouseMotionEvent, SetWindowID)
{
  cen::MouseMotionEvent event;

  event.SetWindowID(8);
  ASSERT_EQ(8u, event.GetWindowID());
}

TEST(MouseMotionEvent, SetWhich)
{
  cen::MouseMotionEvent event;

  event.SetWhich(65);
  ASSERT_EQ(65u, event.GetWhich());
}

TEST(MouseMotionEvent, SetState)
{
  cen::MouseMotionEvent event;

  event.SetState(SDL_BUTTON_LMASK | SDL_BUTTON_MMASK);
  ASSERT_EQ(Uint32{SDL_BUTTON_LMASK | SDL_BUTTON_MMASK}, event.GetState());

  ASSERT_TRUE(event.IsPressed(cen::MouseButton::Left));
  ASSERT_TRUE(event.IsPressed(cen::MouseButton::Middle));

  ASSERT_FALSE(event.IsPressed(cen::MouseButton::Right));
  ASSERT_FALSE(event.IsPressed(cen::MouseButton::X1));
  ASSERT_FALSE(event.IsPressed(cen::MouseButton::X2));
}

TEST(MouseMotionEvent, SetX)
{
  cen::MouseMotionEvent event;

  event.SetX(745);
  ASSERT_EQ(745, event.GetX());
}

TEST(MouseMotionEvent, SetY)
{
  cen::MouseMotionEvent event;

  event.SetY(123);
  ASSERT_EQ(123, event.GetY());
}

TEST(MouseMotionEvent, SetDeltaX)
{
  cen::MouseMotionEvent event;

  event.SetDeltaX(-456);
  ASSERT_EQ(-456, event.GetDeltaX());
}

TEST(MouseMotionEvent, SetDeltaY)
{
  cen::MouseMotionEvent event;

  event.SetDeltaY(835);
  ASSERT_EQ(835, event.GetDeltaY());
}

TEST(MouseMotionEvent, AsSDLEvent)
{
  const cen::MouseMotionEvent event;
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.motion.type, cen::to_underlying(event.GetType()));
  ASSERT_EQ(sdl.motion.timestamp, event.GetTimestamp());
}
