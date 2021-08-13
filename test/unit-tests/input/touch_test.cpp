#include "input/touch.hpp"

#include <gtest/gtest.h>

TEST(Touch, TouchMouseId)
{
  ASSERT_EQ(SDL_TOUCH_MOUSEID, cen::touch::touch_mouse_id());
}

TEST(Touch, MouseTouchId)
{
  ASSERT_EQ(SDL_MOUSE_TOUCHID, cen::touch::mouse_touch_id());
}
