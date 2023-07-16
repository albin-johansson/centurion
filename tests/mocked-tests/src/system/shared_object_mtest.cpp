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

#include <centurion/system/shared_object.hpp>
#include <gtest/gtest.h>

#include "sdl_mocks.hpp"

CEN_MOCK_FIXTURE(SharedObjectFixture);

TEST_F(SharedObjectFixture, Constructor)
{
  EXPECT_THROW(cen::SharedObject {"dummy.dll"}, cen::SDLError);
  EXPECT_EQ(SDL_LoadObject_fake.call_count, 1);
  EXPECT_STREQ(SDL_LoadObject_fake.arg0_val, "dummy.dll");
}

TEST_F(SharedObjectFixture, Usage)
{
  void* so_handle = testing::make_ptr<void*>(123);
  SET_RETURN_SEQ(SDL_LoadObject, &so_handle, 1)

  {
    cen::SharedObject so {"dummy.dll"};
    EXPECT_EQ(SDL_LoadObject_fake.call_count, 1);

    auto* function [[maybe_unused]] = so.load_function<void()>("do_something");
    EXPECT_EQ(SDL_LoadFunction_fake.call_count, 1);
    EXPECT_EQ(SDL_LoadFunction_fake.arg0_val, so_handle);
    EXPECT_STREQ(SDL_LoadFunction_fake.arg1_val, "do_something");
  }

  EXPECT_EQ(SDL_UnloadObject_fake.call_count, 1);
  EXPECT_EQ(SDL_UnloadObject_fake.arg0_val, so_handle);
}
