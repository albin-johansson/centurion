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

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/power.hpp"

TEST(PowerState, Values)
{
  ASSERT_EQ(SDL_POWERSTATE_UNKNOWN, to_underlying(cen::power_state::unknown));
  ASSERT_EQ(SDL_POWERSTATE_ON_BATTERY, to_underlying(cen::power_state::on_battery));
  ASSERT_EQ(SDL_POWERSTATE_NO_BATTERY, to_underlying(cen::power_state::no_battery));
  ASSERT_EQ(SDL_POWERSTATE_CHARGING, to_underlying(cen::power_state::charging));
  ASSERT_EQ(SDL_POWERSTATE_CHARGED, to_underlying(cen::power_state::charged));
}

TEST(PowerState, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::power_state>(6)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::power_state::unknown));
  ASSERT_EQ("on_battery", to_string(cen::power_state::on_battery));
  ASSERT_EQ("no_battery", to_string(cen::power_state::no_battery));
  ASSERT_EQ("charging", to_string(cen::power_state::charging));
  ASSERT_EQ("charged", to_string(cen::power_state::charged));

  std::cout << "power_state::on_battery == " << cen::power_state::on_battery << '\n';
}
