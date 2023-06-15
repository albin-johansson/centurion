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

#include "centurion/common/primitives.hpp"
#include "centurion/common/utils.hpp"

using foo_type = cen::ulonglong;
using bar_type = char;

enum class foo : foo_type {
  a = 27,
  b = 42,
  c = 123
};

enum class bar : bar_type {
  a = 'a',
  b = '1',
  c = 'x'
};

static_assert(std::is_same_v<foo_type, decltype(cen::to_underlying(foo::a))>);
static_assert(std::is_same_v<bar_type, decltype(cen::to_underlying(bar::a))>);

TEST(to_underlying, to_underlying)
{
  ASSERT_EQ(27u, cen::to_underlying(foo::a));
  ASSERT_EQ(42u, cen::to_underlying(foo::b));
  ASSERT_EQ(123u, cen::to_underlying(foo::c));

  ASSERT_EQ('a', cen::to_underlying(bar::a));
  ASSERT_EQ('1', cen::to_underlying(bar::b));
  ASSERT_EQ('x', cen::to_underlying(bar::c));
}
