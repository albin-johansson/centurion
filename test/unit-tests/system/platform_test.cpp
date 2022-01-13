#include <gtest/gtest.h>

#include <iostream>  // clog
#include <string>    // string

#include "system.hpp"

TEST(Platform, PlatformEnum)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::Platform>(7)), cen::Error);

  ASSERT_EQ("Unknown", cen::ToString(cen::Platform::Unknown));
  ASSERT_EQ("Windows", cen::ToString(cen::Platform::Windows));
  ASSERT_EQ("MacOS", cen::ToString(cen::Platform::MacOS));
  ASSERT_EQ("Linux", cen::ToString(cen::Platform::Linux));
  ASSERT_EQ("IOS", cen::ToString(cen::Platform::IOS));
  ASSERT_EQ("Android", cen::ToString(cen::Platform::Android));

  std::clog << "Platform ID example: " << cen::Platform::Windows << '\n';
}

TEST(Platform, IsWindows)
{
  ASSERT_EQ(cen::GetCurrentPlatform() == cen::Platform::Windows, cen::IsWindows());
  ASSERT_EQ(cen::on_windows, cen::IsWindows());
  ASSERT_EQ(cen::on_win32 || cen::on_win64, cen::IsWindows());

  /* win64 implies win32 */
  ASSERT_TRUE(!cen::on_win64 || (cen::on_win64 && cen::on_win32));
}

TEST(Platform, IsMacOS)
{
  ASSERT_EQ(cen::GetCurrentPlatform() == cen::Platform::MacOS, cen::IsMacOS());
  ASSERT_EQ(cen::on_apple, cen::IsMacOS());
}

TEST(Platform, IsLinux)
{
  ASSERT_EQ(cen::GetCurrentPlatform() == cen::Platform::Linux, cen::IsLinux());
  ASSERT_EQ(cen::on_linux, cen::IsLinux());
}

TEST(Platform, IsIOS)
{
  ASSERT_EQ(cen::GetCurrentPlatform() == cen::Platform::IOS, cen::IsIOS());

  /* iOS implies Apple */
  ASSERT_TRUE(!cen::IsIOS() || (cen::IsIOS() && cen::on_apple));
}

TEST(Platform, IsAndroid)
{
  ASSERT_EQ(cen::GetCurrentPlatform() == cen::Platform::Android, cen::IsAndroid());
  ASSERT_EQ(cen::on_android, cen::IsAndroid());
}

TEST(Platform, GetPlatformName)
{
  ASSERT_EQ(std::string{SDL_GetPlatform()}, cen::GetPlatformName().value());
}

TEST(Platform, IsTablet)
{
  ASSERT_EQ(SDL_IsTablet(), cen::IsTablet());
}
