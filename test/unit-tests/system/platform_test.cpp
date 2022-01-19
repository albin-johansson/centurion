#include <gtest/gtest.h>

#include <string>  // string

#include "system.hpp"

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
  ASSERT_EQ(std::string{SDL_GetPlatform()}, cen::platform_name().value());
}
