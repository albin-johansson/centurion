#include "battery.hpp"

#include <fff.h>
#include <gtest/gtest.h>

extern "C" {
FAKE_VALUE_FUNC(SDL_PowerState, SDL_GetPowerInfo, int*, int*)
}

class BatteryTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_GetPowerInfo);
  }
};

TEST_F(BatteryTest, Exists)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  EXPECT_FALSE(cen::battery::exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  EXPECT_FALSE(cen::battery::exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  EXPECT_TRUE(cen::battery::exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  EXPECT_TRUE(cen::battery::exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  EXPECT_TRUE(cen::battery::exists());
}

TEST_F(BatteryTest, IsCharging)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  EXPECT_TRUE(cen::battery::is_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  EXPECT_FALSE(cen::battery::is_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  EXPECT_FALSE(cen::battery::is_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  EXPECT_FALSE(cen::battery::is_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  EXPECT_FALSE(cen::battery::is_charging());
}

TEST_F(BatteryTest, IsCharged)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  EXPECT_TRUE(cen::battery::is_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  EXPECT_FALSE(cen::battery::is_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  EXPECT_FALSE(cen::battery::is_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  EXPECT_FALSE(cen::battery::is_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  EXPECT_FALSE(cen::battery::is_charged());
}

TEST_F(BatteryTest, IsAvailable)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  EXPECT_TRUE(cen::battery::is_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  EXPECT_TRUE(cen::battery::is_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  EXPECT_TRUE(cen::battery::is_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  EXPECT_FALSE(cen::battery::is_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  EXPECT_FALSE(cen::battery::is_available());
}
