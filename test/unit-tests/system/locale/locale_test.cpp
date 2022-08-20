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

#include "centurion/locale.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(Locale, GetPreferred)
{
  /* We assume that the systems that run these tests have English as an available locale */
  if (auto locale = cen::locale::get_preferred()) {
    ASSERT_LT(0, locale.size());
    ASSERT_TRUE(locale.has_language("en"));
    ASSERT_FALSE(locale.has_language("se"));
    ASSERT_FALSE(locale.has_language("foo", "bar"));
  }
  else {
    std::cout << "Could not obtain preferred locale!\n";
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)