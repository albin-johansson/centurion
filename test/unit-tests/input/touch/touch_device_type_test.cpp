#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/touch.hpp"

using device_type = cen::touch_device_type;

TEST(TouchDeviceType, Values)
{
  ASSERT_EQ(SDL_TOUCH_DEVICE_INVALID, to_underlying(device_type::invalid));
  ASSERT_EQ(SDL_TOUCH_DEVICE_DIRECT, to_underlying(device_type::direct));
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE, to_underlying(device_type::indirect_absolute));
  ASSERT_EQ(SDL_TOUCH_DEVICE_INDIRECT_RELATIVE, to_underlying(device_type::indirect_relative));
}

TEST(TouchDeviceType, ToString)
{
  ASSERT_THROW(to_string(static_cast<device_type>(4)), cen::exception);

  ASSERT_EQ("invalid", to_string(device_type::invalid));
  ASSERT_EQ("direct", to_string(device_type::direct));
  ASSERT_EQ("indirect_absolute", to_string(device_type::indirect_absolute));
  ASSERT_EQ("indirect_relative", to_string(device_type::indirect_relative));

  std::cout << "touch_device_type::direct == " << device_type::direct << '\n';
}
