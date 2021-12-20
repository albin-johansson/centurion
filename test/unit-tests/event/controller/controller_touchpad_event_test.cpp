#include <gtest/gtest.h>

#include "event.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(ControllerTouchpadEvent, Defaults)
{
  const cen::ControllerTouchpadEvent event;
  ASSERT_EQ(0, event.GetWhich());
  ASSERT_EQ(0, event.GetFingerIndex());
  ASSERT_EQ(0, event.GetX());
  ASSERT_EQ(0, event.GetY());
  ASSERT_EQ(0, event.GetPressure());
}

TEST(ControllerTouchpadEvent, SetWhich)
{
  cen::ControllerTouchpadEvent event;

  event.SetWhich(832);
  ASSERT_EQ(832, event.GetWhich());
}

TEST(ControllerTouchpadEvent, SetTouchpadIndex)
{
  cen::ControllerTouchpadEvent event;

  event.SetTouchpadIndex(32);
  ASSERT_EQ(32, event.GetTouchpadIndex());
}

TEST(ControllerTouchpadEvent, SetFingerIndex)
{
  cen::ControllerTouchpadEvent event;

  event.SetFingerIndex(27);
  ASSERT_EQ(27, event.GetFingerIndex());
}

TEST(ControllerTouchpadEvent, SetX)
{
  cen::ControllerTouchpadEvent event;

  event.SetX(0.4f);
  ASSERT_EQ(0.4f, event.GetX());

  event.SetX(-0.5f);
  ASSERT_EQ(0, event.GetX());

  event.SetX(1.2f);
  ASSERT_EQ(1.0f, event.GetX());
}

TEST(ControllerTouchpadEvent, SetY)
{
  cen::ControllerTouchpadEvent event;

  event.SetY(0.8f);
  ASSERT_EQ(0.8f, event.GetY());

  event.SetY(-0.1f);
  ASSERT_EQ(0, event.GetY());

  event.SetY(4.2f);
  ASSERT_EQ(1.0f, event.GetY());
}

TEST(ControllerTouchpadEvent, SetPressure)
{
  cen::ControllerTouchpadEvent event;

  event.SetPressure(0.1f);
  ASSERT_EQ(0.1f, event.GetPressure());

  event.SetPressure(-1.4f);
  ASSERT_EQ(0, event.GetPressure());

  event.SetPressure(5.3f);
  ASSERT_EQ(1.0f, event.GetPressure());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
