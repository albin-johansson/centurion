#include <gtest/gtest.h>

#include "centurion/event.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(ControllerTouchpadEvent, Defaults)
{
  const cen::controller_touchpad_event event;
  ASSERT_EQ(0, event.which());
  ASSERT_EQ(0, event.finger_index());
  ASSERT_EQ(0, event.x());
  ASSERT_EQ(0, event.y());
  ASSERT_EQ(0, event.pressure());
}

TEST(ControllerTouchpadEvent, SetWhich)
{
  cen::controller_touchpad_event event;

  const SDL_JoystickID id = 832;
  event.set_which(id);

  ASSERT_EQ(id, event.which());
}

TEST(ControllerTouchpadEvent, SetTouchpadIndex)
{
  cen::controller_touchpad_event event;

  const cen::int32 index = 32;
  event.set_touchpad_index(index);

  ASSERT_EQ(index, event.touchpad_index());
}

TEST(ControllerTouchpadEvent, SetFingerIndex)
{
  cen::controller_touchpad_event event;

  const cen::int32 index = 27;
  event.set_finger_index(index);

  ASSERT_EQ(index, event.finger_index());
}

TEST(ControllerTouchpadEvent, SetX)
{
  cen::controller_touchpad_event event;

  event.set_x(0.4f);
  ASSERT_EQ(0.4f, event.x());

  event.set_x(-0.5f);
  ASSERT_EQ(0, event.x());

  event.set_x(1.2f);
  ASSERT_EQ(1.0f, event.x());
}

TEST(ControllerTouchpadEvent, SetY)
{
  cen::controller_touchpad_event event;

  event.set_y(0.8f);
  ASSERT_EQ(0.8f, event.y());

  event.set_y(-0.1f);
  ASSERT_EQ(0, event.y());

  event.set_y(4.2f);
  ASSERT_EQ(1.0f, event.y());
}

TEST(ControllerTouchpadEvent, SetPressure)
{
  cen::controller_touchpad_event event;

  event.set_pressure(0.1f);
  ASSERT_EQ(0.1f, event.pressure());

  event.set_pressure(-1.4f);
  ASSERT_EQ(0, event.pressure());

  event.set_pressure(5.3f);
  ASSERT_EQ(1.0f, event.pressure());
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
