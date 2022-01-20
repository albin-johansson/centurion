#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/system.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(const char*, SDL_GetPlatform)
  FAKE_VALUE_FUNC(SDL_bool, SDL_IsTablet)
}

class PlatformTest : public testing::Test {
 public:

 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetPlatform)
    RESET_FAKE(SDL_IsTablet)
  }
};

TEST_F(PlatformTest, CurrentPlatform)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ(cen::platform_id::windows, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ(cen::platform_id::macos, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ(cen::platform_id::linux_os, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ(cen::platform_id::ios, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ(cen::platform_id::android, cen::current_platform());

  SDL_GetPlatform_fake.return_val = "Unknown";
  ASSERT_EQ(cen::platform_id::unknown, cen::current_platform());
}

TEST_F(PlatformTest, IsWindows)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_TRUE(cen::is_windows());
}

TEST_F(PlatformTest, IsMacOS)
{
  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_TRUE(cen::is_macos());
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

TEST_F(PlatformTest, IsTablet)
{
  const auto isTablet [[maybe_unused]] = cen::is_tablet();
  ASSERT_EQ(1u, SDL_IsTablet_fake.call_count);
}

TEST_F(PlatformTest, PlatformName)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ("Windows", cen::platform_name());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ("Mac OS X", cen::platform_name());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ("Linux", cen::platform_name());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ("iOS", cen::platform_name());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ("Android", cen::platform_name());

  SDL_GetPlatform_fake.return_val = "Unknown";
  ASSERT_FALSE(cen::platform_name().has_value());
}
