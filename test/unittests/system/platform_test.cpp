#include "platform.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(Platform, Id)
{
  EXPECT_NO_THROW(cen::platform::id());

#ifdef __WIN32
  EXPECT_EQ(cen::platform::platform_id::windows, cen::platform::id());
#elif __APPLE__
  EXPECT_EQ(cen::platform::platform_id::mac_osx, cen::platform::id());
#elif __linux__
  EXPECT_EQ(cen::platform::platform_id::linuxx, cen::platform::id());
#elif __ANDROID__
  EXPECT_EQ(cen::platform::platform_id::android, cen::platform::id());
#endif
}

TEST(Platform, IsWindows)
{
  EXPECT_EQ(cen::platform::id() == cen::platform::platform_id::windows,
            cen::platform::is_windows());
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
