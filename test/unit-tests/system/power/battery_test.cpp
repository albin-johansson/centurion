/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#include <gtest/gtest.h>

#include "centurion/system/power.hpp"

TEST(Battery, BatteryPercentage)
{
  ASSERT_NO_THROW(cen::battery_percentage());

  const auto percentage = cen::battery_percentage();
  ASSERT_EQ(percentage.has_value(), cen::is_battery_available());

  if (percentage) {
    int actual = -1;
    SDL_GetPowerInfo(nullptr, &actual);

    ASSERT_EQ(actual, percentage);
  }
}

TEST(Battery, BatterySeconds)
{
  ASSERT_NO_THROW(cen::battery_seconds());

  int actual = -1;
  SDL_GetPowerInfo(&actual, nullptr);

  if (const auto secs = cen::battery_seconds()) {
    ASSERT_EQ(cen::seconds<int> {actual}, secs.value());
  }
}

TEST(Battery, BatteryMinutes)
{
  ASSERT_NO_THROW(cen::battery_minutes());

  if (const auto minutes = cen::battery_minutes()) {
    int actual = -1;
    SDL_GetPowerInfo(&actual, nullptr);

    const cen::seconds<int> s {actual};
    ASSERT_EQ(std::chrono::duration_cast<cen::minutes<int>>(s), minutes.value());
  }
}

TEST(Battery, QueryBattery)
{
  ASSERT_NO_THROW(cen::query_battery());

  const auto state = cen::query_battery();
  const auto actual = SDL_GetPowerInfo(nullptr, nullptr);

  ASSERT_EQ(actual, static_cast<SDL_PowerState>(state));
}

TEST(Battery, IsBatteryAvailable)
{
  const auto state = cen::query_battery();
  const auto exists = state == cen::power_state::on_battery ||
                      state == cen::power_state::charged ||
                      state == cen::power_state::charging;
  ASSERT_EQ(exists, cen::is_battery_available());
}

TEST(Battery, IsBatteryCharging)
{
  ASSERT_EQ(cen::query_battery() == cen::power_state::charging, cen::is_battery_charging());
}

TEST(Battery, IsBatteryCharged)
{
  ASSERT_EQ(cen::query_battery() == cen::power_state::charged, cen::is_battery_charged());
}
