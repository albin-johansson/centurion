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

#include <concepts>  // same_as

#include <centurion/system/time.hpp>
#include <gtest/gtest.h>

static_assert(std::same_as<cen::Time::ns_type::rep, Uint64>);
static_assert(std::same_as<cen::Time::us_type::rep, Uint64>);
static_assert(std::same_as<cen::Time::ms_type::rep, Uint64>);
static_assert(std::same_as<cen::Time::s_type::rep, Uint64>);

TEST(Time, SinceInit)
{
  EXPECT_GT(cen::Time::since_init_ns(), cen::Time::ns_type::zero());
  EXPECT_GT(cen::Time::since_init_us(), cen::Time::us_type::zero());
  EXPECT_GT(cen::Time::since_init_ms(), cen::Time::ms_type::zero());
}

TEST(Time, Now)
{
  EXPECT_GT(cen::Time::now(), 0);
  EXPECT_GT(cen::Time::now_ns(), cen::Time::ns_type::zero());
  EXPECT_GT(cen::Time::now_us(), cen::Time::us_type::zero());
  EXPECT_GT(cen::Time::now_ms(), cen::Time::ms_type::zero());
  EXPECT_GT(cen::Time::now_s(), cen::Time::s_type::zero());
}