#include "platform.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(Platform, IsWindows)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::windows,
            cen::platform::is_windows());

  constexpr auto isWindows =
      cen::platform::ifdef_win32() || cen::platform::ifdef_win64();
  EXPECT_EQ(cen::platform::is_windows(), isWindows);
}

TEST(Platform, IsMacOSX)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::mac_osx,
            cen::platform::is_mac_osx());
}

TEST(Platform, IsLinux)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::linuxx,
            cen::platform::is_linux());
}

TEST(Platform, IsIOS)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::ios,
            cen::platform::is_ios());
}

TEST(Platform, IsAndroid)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::android,
            cen::platform::is_android());
}

TEST(Platform, Name)
{
  EXPECT_EQ(std::string{SDL_GetPlatform()}, *cen::platform::name());
}

TEST(Platform, IsTablet)
{
  EXPECT_EQ(SDL_IsTablet(), cen::platform::is_tablet());
}
