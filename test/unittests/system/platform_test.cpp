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

  // Check that win64 -> win32
  EXPECT_TRUE(!cen::platform::ifdef_win64() ||
              (cen::platform::ifdef_win64() && cen::platform::ifdef_win32()));
}

TEST(Platform, IsMacOSX)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::mac_osx,
            cen::platform::is_mac_osx());

  constexpr auto isApple = cen::platform::ifdef_apple();
  EXPECT_EQ(cen::platform::is_mac_osx(), isApple);
}

TEST(Platform, IsLinux)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::linuxx,
            cen::platform::is_linux());

  constexpr auto isLinux = cen::platform::ifdef_linux();
  EXPECT_EQ(cen::platform::is_linux(), isLinux);
}

TEST(Platform, IsIOS)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::ios,
            cen::platform::is_ios());

  constexpr auto isApple = cen::platform::ifdef_apple();
  EXPECT_EQ(cen::platform::is_ios(), isApple);
}

TEST(Platform, IsAndroid)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::android,
            cen::platform::is_android());

  constexpr auto isAndroid = cen::platform::ifdef_android();
  EXPECT_EQ(cen::platform::is_android(), isAndroid);
}

TEST(Platform, Name)
{
  EXPECT_EQ(std::string{SDL_GetPlatform()}, *cen::platform::name());
}

TEST(Platform, IsTablet)
{
  EXPECT_EQ(SDL_IsTablet(), cen::platform::is_tablet());
}
