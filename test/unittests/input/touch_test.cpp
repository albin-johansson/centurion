#include "input/touch.hpp"

#include <gtest/gtest.h>

TEST(Touch, TouchMouseId)
{
  EXPECT_EQ(SDL_TOUCH_MOUSEID, cen::touch::touch_mouse_id());
}

TEST(Touch, MouseTouchId)
{
  EXPECT_EQ(SDL_MOUSE_TOUCHID, cen::touch::mouse_touch_id());
}

TEST(Touch, DeviceTypeEnum)
{
  using type = cen::touch::device_type;

  EXPECT_EQ(type::invalid, SDL_TOUCH_DEVICE_INVALID);
  EXPECT_EQ(type::direct, SDL_TOUCH_DEVICE_DIRECT);
  EXPECT_EQ(type::indirect_absolute, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  EXPECT_EQ(type::indirect_relative, SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

  EXPECT_EQ(SDL_TOUCH_DEVICE_INVALID, type::invalid);
  EXPECT_EQ(SDL_TOUCH_DEVICE_DIRECT, type::direct);
  EXPECT_EQ(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, type::indirect_absolute);
  EXPECT_EQ(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE, type ::indirect_relative);

  EXPECT_FALSE(type::indirect_absolute == SDL_TOUCH_DEVICE_DIRECT);

  EXPECT_NE(type::invalid, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  EXPECT_NE(SDL_TOUCH_DEVICE_DIRECT, type::invalid);
}
