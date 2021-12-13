#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "system.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(SDL_PowerState, SDL_GetPowerInfo, int*, int*)
}

namespace {

using signature_t = SDL_PowerState (*)(int*, int*);

inline constexpr cen::seconds<int> seconds{1'337};
inline constexpr auto percentage = 27;

auto PowerDelegate(int* outSeconds, int* outPercentage) -> SDL_PowerState
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

TEST_F(BatteryTest, GetBatterySeconds)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(seconds, cen::GetBatterySeconds());
}

TEST_F(BatteryTest, GetBatteryMinutes)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(std::chrono::duration_cast<cen::minutes<int>>(seconds), cen::GetBatteryMinutes());
}

TEST_F(BatteryTest, GetBatteryPercentage)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(percentage, cen::GetBatteryPercentage());
}

TEST_F(BatteryTest, IsBatteryAvailable)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::IsBatteryAvailable());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::IsBatteryAvailable());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_TRUE(cen::IsBatteryAvailable());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::IsBatteryAvailable());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::IsBatteryAvailable());
}

TEST_F(BatteryTest, IsBatteryCharging)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::IsBatteryCharging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::IsBatteryCharging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::IsBatteryCharging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::IsBatteryCharging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_FALSE(cen::IsBatteryCharging());
}

TEST_F(BatteryTest, IsBatteryCharged)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::IsBatteryCharged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::IsBatteryCharged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::IsBatteryCharged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::IsBatteryCharged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_FALSE(cen::IsBatteryCharged());
}
