#include "system/platform.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(Platform, IsWindows)
{
  EXPECT_EQ(cen::current_platform() == cen::platform_id::windows,
            cen::is_windows());

  constexpr auto isWindows = cen::ifdef_win32() || cen::ifdef_win64();
  EXPECT_EQ(cen::is_windows(), isWindows);

  // Check that win64 -> win32
  EXPECT_TRUE(!cen::ifdef_win64() ||
              (cen::ifdef_win64() && cen::ifdef_win32()));
}

TEST(Platform, IsMacOSX)
{
  EXPECT_EQ(cen::current_platform() == cen::platform_id::mac_osx,
            cen::is_mac_osx());

  constexpr auto isApple = cen::ifdef_apple();
  EXPECT_EQ(cen::is_mac_osx(), isApple);
}

TEST(Platform, IsLinux)
{
  EXPECT_EQ(cen::current_platform() == cen::platform_id::linux_os,
            cen::is_linux());

  constexpr auto isLinux = cen::ifdef_linux();
  EXPECT_EQ(cen::is_linux(), isLinux);
}

TEST(Platform, IsIOS)
{
  EXPECT_EQ(cen::current_platform() == cen::platform_id::ios, cen::is_ios());

  // Check that iOS -> Apple
  EXPECT_TRUE(!cen::is_ios() || (cen::is_ios() && cen::ifdef_apple()));
}

TEST(Platform, IsAndroid)
{
  EXPECT_EQ(cen::current_platform() == cen::platform_id::android,
            cen::is_android());

  constexpr auto isAndroid = cen::ifdef_android();
  EXPECT_EQ(cen::is_android(), isAndroid);
}

TEST(Platform, PlatformName)
{
  EXPECT_EQ(std::string{SDL_GetPlatform()}, *cen::platform_name());
}

TEST(Platform, IsTablet)
{
  EXPECT_EQ(SDL_IsTablet(), cen::is_tablet());
}
