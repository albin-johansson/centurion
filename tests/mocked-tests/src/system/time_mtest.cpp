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

#include <centurion/system/time.hpp>
#include <gtest/gtest.h>

#include "sdl_mocks.hpp"

CEN_MOCK_FIXTURE(TimeFixture);

TEST_F(TimeFixture, Frequency)
{
  const Uint64 frequency = 4'238'912;

  Uint64 frequency_arr[] = {frequency};
  SET_RETURN_SEQ(SDL_GetPerformanceFrequency, frequency_arr, std::size(frequency_arr))

  EXPECT_EQ(cen::Time::frequency(), frequency);
  EXPECT_EQ(SDL_GetPerformanceFrequency_fake.call_count, 1);
}

TEST_F(TimeFixture, SinceInit)
{
  const Uint64 ticks_ms = 8'235;
  const Uint64 ticks_ns = 732'153;

  Uint64 ticks_ms_arr[] = {ticks_ms};
  Uint64 ticks_ns_arr[] = {ticks_ns};
  SET_RETURN_SEQ(SDL_GetTicks, ticks_ms_arr, std::size(ticks_ms_arr))
  SET_RETURN_SEQ(SDL_GetTicksNS, ticks_ns_arr, std::size(ticks_ns_arr))

  EXPECT_EQ(cen::Time::since_init_ns().count(), ticks_ns);
  EXPECT_EQ(cen::Time::since_init_us().count(), ticks_ns / Uint64 {1'000});
  EXPECT_EQ(SDL_GetTicksNS_fake.call_count, 2);

  EXPECT_EQ(cen::Time::since_init_ms().count(), ticks_ms);
  EXPECT_EQ(SDL_GetTicks_fake.call_count, 1);
}

TEST_F(TimeFixture, Now)
{
  const Uint64 counter = 123'456'789;
  const Uint64 frequency = 1'234;

  Uint64 counter_arr[] = {counter};
  Uint64 frequency_arr[] = {frequency};
  SET_RETURN_SEQ(SDL_GetPerformanceCounter, counter_arr, std::size(counter_arr))
  SET_RETURN_SEQ(SDL_GetPerformanceFrequency, frequency_arr, std::size(frequency_arr))

  auto convert = [=](const double factor) {
    const auto ratio = static_cast<double>(counter) / static_cast<double>(frequency);
    return static_cast<Uint64>(ratio * factor);
  };

  EXPECT_EQ(cen::Time::now(), counter);
  EXPECT_EQ(cen::Time::now_s().count(), convert(1));
  EXPECT_EQ(cen::Time::now_ms().count(), convert(1'000));
  EXPECT_EQ(cen::Time::now_us().count(), convert(1'000'000));
  EXPECT_EQ(cen::Time::now_ns().count(), convert(1'000'000'000));

  EXPECT_EQ(SDL_GetPerformanceCounter_fake.call_count, 5);
}
