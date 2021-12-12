#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "system/system.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(SDL_PowerState, SDL_GetPowerInfo, int*, int*)
}

namespace {

using signature_t = SDL_PowerState (*)(int*, int*);

inline constexpr cen::seconds<int> seconds{1'337};
inline constexpr auto percentage = 27;

auto power_delegate(int* outSeconds, int* outPercentage) -> SDL_PowerState
{
  if (outSeconds) {
    *outSeconds = seconds.count();
  }

  if (outPercentage) {
    *outPercentage = percentage;
  }

  return SDL_POWERSTATE_ON_BATTERY;
}

}  // namespace

class BatteryTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_GetPowerInfo)
  }
};

TEST_F(BatteryTest, SecondsLeft)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(seconds, cen::battery_seconds());
}

TEST_F(BatteryTest, BatteryMinutes)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(std::chrono::duration_cast<cen::minutes<int>>(seconds), cen::battery_minutes());
}

TEST_F(BatteryTest, BatteryPercentage)
{
  signature_t functions[] = {power_delegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(percentage, cen::battery_percentage());
}

TEST_F(BatteryTest, BatteryExists)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::battery_exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::battery_exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_TRUE(cen::battery_exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::battery_exists());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::battery_exists());
}

TEST_F(BatteryTest, BatteryCharging)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_FALSE(cen::battery_charging());
}

TEST_F(BatteryTest, BatteryCharged)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_FALSE(cen::battery_charged());
}

TEST_F(BatteryTest, BatteryAvailable)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_TRUE(cen::battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::battery_available());
}
