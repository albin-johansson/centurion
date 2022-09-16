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

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "centurion/system.hpp"
#include "core_mocks.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_OpenURL, const char*)
}

class OpenURLTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_OpenURL)
  }
};

TEST_F(OpenURLTest, OpenURL)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_OpenURL, values.data(), cen::isize(values));

  using namespace std::string_literals;
  const auto url = "https://www.google.com"s;

  ASSERT_FALSE(cen::open_url(url));
  ASSERT_TRUE(cen::open_url(url));

  ASSERT_EQ(2u, SDL_OpenURL_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
