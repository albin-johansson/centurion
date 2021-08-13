#include "system/platform.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(Platform, IsWindows)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::windows, cen::is_windows());

  constexpr auto isWin32 = cen::ifdef_win32();
  constexpr auto isWin64 = cen::ifdef_win64();
  ASSERT_EQ(cen::is_windows(), isWin32 || isWin64);

  // Check that win64 -> win32
  ASSERT_TRUE(!isWin64 || (isWin64 && isWin32));
}

TEST(Platform, IsMacOSX)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::mac_osx, cen::is_mac_osx());

  constexpr auto isApple = cen::ifdef_apple();
  ASSERT_EQ(cen::is_mac_osx(), isApple);
}

TEST(Platform, IsLinux)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::linux_os, cen::is_linux());

  constexpr auto isLinux = cen::ifdef_linux();
  ASSERT_EQ(cen::is_linux(), isLinux);
}

TEST(Platform, IsIOS)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::ios, cen::is_ios());

  // Check that iOS -> Apple
  ASSERT_TRUE(!cen::is_ios() || (cen::is_ios() && cen::ifdef_apple()));
}

TEST(Platform, IsAndroid)
{
  ASSERT_EQ(cen::current_platform() == cen::platform_id::android, cen::is_android());

  constexpr auto isAndroid = cen::ifdef_android();
  ASSERT_EQ(cen::is_android(), isAndroid);
}

TEST(Platform, PlatformName)
{
  ASSERT_EQ(std::string{SDL_GetPlatform()}, *cen::platform_name());
}

TEST(Platform, IsTablet)
{
  ASSERT_EQ(SDL_IsTablet(), cen::is_tablet());
}
