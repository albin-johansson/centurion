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

#include "centurion/video.hpp"
#include "core_mocks.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(SDL_BlendMode,
                  SDL_ComposeCustomBlendMode,
                  SDL_BlendFactor,
                  SDL_BlendFactor,
                  SDL_BlendOperation,
                  SDL_BlendFactor,
                  SDL_BlendFactor,
                  SDL_BlendOperation);
}

class BlendModeTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_ComposeCustomBlendMode)
  }
};

TEST_F(BlendModeTest, ComposeBlendMode)
{
  const cen::blend_task color = {cen::blend_factor::src_color,
                                 cen::blend_factor::dst_color,
                                 cen::blend_op::add};
  const cen::blend_task alpha = {cen::blend_factor::src_alpha,
                                 cen::blend_factor::one_minus_dst_alpha,
                                 cen::blend_op::sub};
  const auto mode [[maybe_unused]] = cen::compose_blend_mode(color, alpha);

  ASSERT_EQ(1u, SDL_ComposeCustomBlendMode_fake.call_count);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_COLOR, SDL_ComposeCustomBlendMode_fake.arg0_val);
  ASSERT_EQ(SDL_BLENDFACTOR_DST_COLOR, SDL_ComposeCustomBlendMode_fake.arg1_val);
  ASSERT_EQ(SDL_BLENDOPERATION_ADD, SDL_ComposeCustomBlendMode_fake.arg2_val);

  ASSERT_EQ(SDL_BLENDFACTOR_SRC_ALPHA, SDL_ComposeCustomBlendMode_fake.arg3_val);
  ASSERT_EQ(SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_ComposeCustomBlendMode_fake.arg4_val);
  ASSERT_EQ(SDL_BLENDOPERATION_SUBTRACT, SDL_ComposeCustomBlendMode_fake.arg5_val);
}
