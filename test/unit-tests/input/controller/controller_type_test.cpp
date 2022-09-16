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

#include "centurion/controller.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 12)

using type = cen::controller_type;

TEST(ControllerType, Values)
{
  ASSERT_EQ(SDL_CONTROLLER_TYPE_UNKNOWN, to_underlying(type::unknown));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_XBOX360, to_underlying(type::xbox_360));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_XBOXONE, to_underlying(type::xbox_one));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS3, to_underlying(type::ps3));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS4, to_underlying(type::ps4));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO, to_underlying(type::nintendo_switch_pro));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(SDL_CONTROLLER_TYPE_PS5, to_underlying(type::ps5));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_VIRTUAL, to_underlying(type::virt));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ(SDL_CONTROLLER_TYPE_AMAZON_LUNA, to_underlying(type::amazon_luna));
  ASSERT_EQ(SDL_CONTROLLER_TYPE_GOOGLE_STADIA, to_underlying(type::google_stadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)
}

TEST(ControllerType, ToString)
{
  ASSERT_THROW(to_string(static_cast<type>(10)), cen::exception);

  ASSERT_EQ("unknown", to_string(type::unknown));
  ASSERT_EQ("nintendo_switch_pro", to_string(type::nintendo_switch_pro));
  ASSERT_EQ("xbox_360", to_string(type::xbox_360));
  ASSERT_EQ("xbox_one", to_string(type::xbox_one));
  ASSERT_EQ("ps3", to_string(type::ps3));
  ASSERT_EQ("ps4", to_string(type::ps4));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("ps5", to_string(type::ps5));
  ASSERT_EQ("virt", to_string(type::virt));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

#if SDL_VERSION_ATLEAST(2, 0, 16)
  ASSERT_EQ("amazon_luna", to_string(type::amazon_luna));
  ASSERT_EQ("google_stadia", to_string(type::google_stadia));
#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  std::cout << "controller_type::ps4 == " << type::ps4 << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
