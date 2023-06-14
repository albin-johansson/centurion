/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "centurion/power.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(SDL_PowerState, SDL_GetPowerInfo, int*, int*)
}

namespace {

using signature_t = SDL_PowerState (*)(int*, int*);

inline constexpr cen::seconds<int> seconds {1'337};
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

TEST_F(BatteryTest, BatterySeconds)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(seconds, cen::battery_seconds());
}

TEST_F(BatteryTest, BatteryMinutes)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(std::chrono::duration_cast<cen::minutes<int>>(seconds), cen::battery_minutes());
}

TEST_F(BatteryTest, BatteryPercentage)
{
  signature_t functions[] = {PowerDelegate};
  SET_CUSTOM_FAKE_SEQ(SDL_GetPowerInfo, functions, 1);

  ASSERT_EQ(percentage, cen::battery_percentage());
}

TEST_F(BatteryTest, IsBatteryAvailable)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::is_battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::is_battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_TRUE(cen::is_battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::is_battery_available());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::is_battery_available());
}

TEST_F(BatteryTest, IsBatteryCharging)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_TRUE(cen::is_battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::is_battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::is_battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::is_battery_charging());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_FALSE(cen::is_battery_charging());
}

TEST_F(BatteryTest, IsBatteryCharged)
{
  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGED;
  ASSERT_TRUE(cen::is_battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_UNKNOWN;
  ASSERT_FALSE(cen::is_battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_NO_BATTERY;
  ASSERT_FALSE(cen::is_battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_ON_BATTERY;
  ASSERT_FALSE(cen::is_battery_charged());

  SDL_GetPowerInfo_fake.return_val = SDL_POWERSTATE_CHARGING;
  ASSERT_FALSE(cen::is_battery_charged());
}
