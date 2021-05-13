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

TEST(Touch, DeviceTypeEnum)
{
  using type = cen::touch::device_type;

  ASSERT_EQ(type::invalid, SDL_TOUCH_DEVICE_INVALID);
  ASSERT_EQ(type::direct, SDL_TOUCH_DEVICE_DIRECT);
  ASSERT_EQ(type::indirect_absolute, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  ASSERT_EQ(type::indirect_relative, SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

  ASSERT_EQ(SDL_TOUCH_DEVICE_INVALID, type::invalid);
  ASSERT_EQ(SDL_TOUCH_DEVICE_DIRECT, type::direct);
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, type::indirect_absolute);
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE, type ::indirect_relative);

  ASSERT_FALSE(type::indirect_absolute == SDL_TOUCH_DEVICE_DIRECT);

  ASSERT_NE(type::invalid, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  ASSERT_NE(SDL_TOUCH_DEVICE_DIRECT, type::invalid);
}
