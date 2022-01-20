#include "touch.hpp"

#include <gtest/gtest.h>

TEST(Touch, TouchMouseId)
{
  ASSERT_EQ(SDL_TOUCH_MOUSEID, cen::touch_mouse_id());
}

TEST(Touch, MouseTouchId)
{
  ASSERT_EQ(SDL_MOUSE_TOUCHID, cen::mouse_touch_id());
}

TEST(Touch, TouchDeviceCount)
{
  ASSERT_EQ(SDL_GetNumTouchDevices(), cen::touch_device_count());
}
