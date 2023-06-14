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

#include <string>  // string

#include "centurion/system.hpp"

TEST(Platform, IsWindows)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::windows, cen::is_windows());
  ASSERT_EQ(cen::on_windows, cen::is_windows());
  ASSERT_EQ(cen::on_win32 || cen::on_win64, cen::is_windows());

  /* win64 implies win32 */
  ASSERT_TRUE(!cen::on_win64 || (cen::on_win64 && cen::on_win32));
}

TEST(Platform, IsMacOS)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::macos, cen::is_macos());
  ASSERT_EQ(cen::on_apple, cen::is_macos());
}

TEST(Platform, IsLinux)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::linux_os, cen::is_linux());
  ASSERT_EQ(cen::on_linux, cen::is_linux());
}

TEST(Platform, IsIOS)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::ios, cen::is_ios());

  /* iOS implies Apple */
  ASSERT_TRUE(!cen::is_ios() || (cen::is_ios() && cen::on_apple));
}

TEST(Platform, IsAndroid)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::android, cen::is_android());
  ASSERT_EQ(cen::on_android, cen::is_android());
}

TEST(Platform, IsTablet)
{
  ASSERT_EQ(SDL_IsTablet(), cen::is_tablet());
}

TEST(Platform, PlatformName)
{
  ASSERT_EQ(std::string {SDL_GetPlatform()}, cen::platform_name().value());
}
