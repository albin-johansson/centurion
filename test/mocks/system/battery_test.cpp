#include "system/battery.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(SDL_PowerState, SDL_GetPowerInfo, int*, int*)
}

namespace {

using signature_t = SDL_PowerState (*)(int*, int*);

inline constexpr cen::seconds<int> seconds{1'337};
inline constexpr auto percentage = 27;

auto power_delegate(int* outSeconds, int* outPercentage) -> SDL_PowerState
{
  if (outSeconds)
  {
    *outSeconds = seconds.count();
  }

  if (outPercentage)
  {
    *outPercentage = percentage;
  }

  return SDL_POWERSTATE_ON_BATTERY;
}

}  // namespace

class BatteryTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetPowerInfo);
  }
};

TEST_F(BatteryTest, SecondsLeft)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  EXPECT_EQ(seconds, cen::battery::seconds_left());
}

TEST_F(BatteryTest, MinutesLeft)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  EXPECT_EQ(std::chrono::duration_cast<cen::minutes<int>>(seconds),
            cen::battery::minutes_left());
}

TEST_F(BatteryTest, Percentage)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  EXPECT_EQ(percentage, cen::battery::percentage());
}

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
