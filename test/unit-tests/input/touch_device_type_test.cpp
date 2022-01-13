#include "input/touch_device_type.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(TouchDeviceType, Values)
{
  ASSERT_EQ(cen::touch_device_type::invalid, SDL_TOUCH_DEVICE_INVALID);
  ASSERT_EQ(cen::touch_device_type::direct, SDL_TOUCH_DEVICE_DIRECT);
  ASSERT_EQ(cen::touch_device_type::indirect_absolute, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  ASSERT_EQ(cen::touch_device_type::indirect_relative, SDL_TOUCH_DEVICE_INDIRECT_RELATIVE);

  ASSERT_EQ(SDL_TOUCH_DEVICE_INVALID, cen::touch_device_type::invalid);
  ASSERT_EQ(SDL_TOUCH_DEVICE_DIRECT, cen::touch_device_type::direct);
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, cen::touch_device_type::indirect_absolute);
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE, cen::touch_device_type ::indirect_relative);

  ASSERT_NE(cen::touch_device_type::invalid, SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE);
  ASSERT_NE(SDL_TOUCH_DEVICE_DIRECT, cen::touch_device_type::invalid);
}

TEST(TouchDeviceType, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::touch_device_type>(4)), cen::Error);

  ASSERT_EQ("invalid", cen::ToString(cen::touch_device_type::invalid));
  ASSERT_EQ("direct", cen::ToString(cen::touch_device_type::direct));
  ASSERT_EQ("indirect_absolute", cen::ToString(cen::touch_device_type::indirect_absolute));
  ASSERT_EQ("indirect_relative", cen::ToString(cen::touch_device_type::indirect_relative));

  std::clog << "Touch device type: " << cen::touch_device_type::direct << '\n';
}
