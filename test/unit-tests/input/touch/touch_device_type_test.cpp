/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
