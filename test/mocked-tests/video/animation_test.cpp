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

#include "centurion/video/animation.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

#if SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)

extern "C" {
FAKE_VALUE_FUNC(IMG_Animation*, IMG_LoadAnimation, const char*)
FAKE_VOID_FUNC(IMG_FreeAnimation, IMG_Animation*)
}

struct AnimationTest : testing::Test {
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(IMG_LoadAnimation)
    RESET_FAKE(IMG_FreeAnimation)
  }
};

TEST_F(AnimationTest, InvalidConstruction)
{
  ASSERT_THROW(cen::animation {nullptr}, cen::exception);
  ASSERT_THROW(cen::animation::load("foo.gif"), cen::img_error);
}

TEST_F(AnimationTest, Usage)
{
  int delays[] = {10, 20};
  SDL_Surface* frames[] = {nullptr, nullptr};

  IMG_Animation src {
      .w = 123,
      .h = 169,
      .count = 2,
      .frames = frames,
      .delays = delays,
  };

  CEN_PREPARE_MOCK_TEST(IMG_LoadAnimation, &src)

  cen::animation animation {"foo.gif"};

  ASSERT_EQ(src.w, animation.width());
  ASSERT_EQ(src.h, animation.height());
  ASSERT_EQ(cen::iarea {src.w, src.h}, animation.size());

  ASSERT_EQ(src.count, animation.count());
  ASSERT_TRUE(animation.get());

  ASSERT_NO_THROW(animation.at(0));
  ASSERT_NO_THROW(animation.at(1));
  ASSERT_THROW(animation.at(2), cen::exception);

  ASSERT_NO_THROW(animation[0]);
  ASSERT_NO_THROW(animation[1]);
  ASSERT_THROW(animation[2], cen::exception);

  ASSERT_EQ(src.delays[0], animation.delay(0));
  ASSERT_EQ(src.delays[1], animation.delay(1));
  ASSERT_THROW(animation.delay(2), cen::exception);
}

#endif  // SDL_IMAGE_VERSION_ATLEAST(2, 6, 0)
