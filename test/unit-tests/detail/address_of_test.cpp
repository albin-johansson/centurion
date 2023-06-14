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

#include <iostream>  // clog

#include "centurion/detail/stdlib.hpp"

TEST(AddressOf, Correctness)
{
  {  // Non-null pointer
    int i = 42;
    const auto str = cen::detail::address_of(&i);

    ASSERT_FALSE(str.empty());

#if CENTURION_HAS_FEATURE_CPP20
    ASSERT_TRUE(str.starts_with("0x"));
#endif  // CENTURION_HAS_FEATURE_CPP20

    std::cout << "detail::address_of output: " << str << '\n';
  }

  {  // Null pointer
    int* i {};
    ASSERT_NO_THROW(cen::detail::address_of(i));

    const auto str = cen::detail::address_of(i);
    ASSERT_TRUE(str.empty());
  }
}
