#include "system/platform.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(const char*, SDL_GetPlatform)
FAKE_VALUE_FUNC(SDL_bool, SDL_IsTablet)
FAKE_VALUE_FUNC(int, SDL_OpenURL, const char*)
}

class PlatformTest : public testing::Test
{
 public:
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetPlatform)
    RESET_FAKE(SDL_IsTablet)
    RESET_FAKE(SDL_OpenURL)
  }
};

TEST_F(PlatformTest, CurrentPlatform)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ(cen::platform_id::windows, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ(cen::platform_id::mac_osx, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ(cen::platform_id::linux_os, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ(cen::platform_id::ios, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ(cen::platform_id::android, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "foobar";
  ASSERT_EQ(cen::platform_id::unknown, cen::current_platform());
}

TEST_F(PlatformTest, IsWindows)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_TRUE(cen::is_windows());
}

TEST_F(PlatformTest, IsMacOSX)
{
  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_TRUE(cen::is_mac_osx());
}

TEST_F(PlatformTest, IsLinux)
{
  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_TRUE(cen::is_linux());
}

TEST_F(PlatformTest, IsIOS)
{
  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_TRUE(cen::is_ios());
}

TEST_F(PlatformTest, IsAndroid)
{
  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_TRUE(cen::is_android());
}

TEST_F(PlatformTest, PlatformName)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ("Windows", cen::platform_name().value());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ("Mac OS X", cen::platform_name().value());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ("Linux", cen::platform_name().value());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ("iOS", cen::platform_name().value());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ("Android", cen::platform_name().value());

  SDL_GetPlatform_fake.return_val = "Unknown";
  ASSERT_FALSE(cen::platform_name().has_value());
}

TEST_F(PlatformTest, IsTablet)
{
  const auto isTablet [[maybe_unused]] = cen::is_tablet();
  ASSERT_EQ(1, SDL_IsTablet_fake.call_count);
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(PlatformTest, OpenURL)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_OpenURL, values.data(), cen::isize(values));

  using namespace std::string_literals;
  const auto url = "https://www.google.com"s;

  ASSERT_FALSE(cen::open_url(url));
  ASSERT_TRUE(cen::open_url(url));

  ASSERT_EQ(2, SDL_OpenURL_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
