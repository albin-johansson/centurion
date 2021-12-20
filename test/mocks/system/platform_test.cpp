#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "common.hpp"
#include "core_mocks.hpp"
#include "system.hpp"

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

TEST_F(PlatformTest, GetCurrentPlatform)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ(cen::Platform::Windows, cen::GetCurrentPlatform());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ(cen::Platform::MacOS, cen::GetCurrentPlatform());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ(cen::Platform::Linux, cen::GetCurrentPlatform());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ(cen::Platform::IOS, cen::GetCurrentPlatform());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ(cen::Platform::Android, cen::GetCurrentPlatform());

  SDL_GetPlatform_fake.return_val = "Unknown";
  ASSERT_EQ(cen::Platform::Unknown, cen::GetCurrentPlatform());
}

TEST_F(PlatformTest, IsWindows)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_TRUE(cen::IsWindows());
}

TEST_F(PlatformTest, IsMacOS)
{
  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_TRUE(cen::IsMacOS());
}

TEST_F(PlatformTest, IsLinux)
{
  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_TRUE(cen::IsLinux());
}

TEST_F(PlatformTest, IsIOS)
{
  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_TRUE(cen::IsIOS());
}

TEST_F(PlatformTest, IsAndroid)
{
  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_TRUE(cen::IsAndroid());
}

TEST_F(PlatformTest, GetPlatformName)
{
  SDL_GetPlatform_fake.return_val = "Windows";
  ASSERT_EQ("Windows", cen::GetPlatformName());

  SDL_GetPlatform_fake.return_val = "Mac OS X";
  ASSERT_EQ("Mac OS X", cen::GetPlatformName());

  SDL_GetPlatform_fake.return_val = "Linux";
  ASSERT_EQ("Linux", cen::GetPlatformName());

  SDL_GetPlatform_fake.return_val = "iOS";
  ASSERT_EQ("iOS", cen::GetPlatformName());

  SDL_GetPlatform_fake.return_val = "Android";
  ASSERT_EQ("Android", cen::GetPlatformName());

  SDL_GetPlatform_fake.return_val = "Unknown";
  ASSERT_FALSE(cen::GetPlatformName().has_value());
}

TEST_F(PlatformTest, IsTablet)
{
  const auto isTablet [[maybe_unused]] = cen::IsTablet();
  ASSERT_EQ(1u, SDL_IsTablet_fake.call_count);
}
