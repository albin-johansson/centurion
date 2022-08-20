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

#include "centurion/initialization.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"

class InitializationTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    /* Sets up expected return values for OK initialization */
    SDL_Init_fake.return_val = cen::sdl_cfg{}.flags;
    IMG_Init_fake.return_val = cen::img_cfg{}.flags;
    Mix_Init_fake.return_val = cen::mix_cfg{}.flags;
    TTF_Init_fake.return_val = 0;

    Mix_OpenAudio_fake.return_val = 0;
  }
};

TEST_F(InitializationTest, CoreDefaultConfiguration)
{
  try {
    const cen::sdl sdl;
    ASSERT_EQ(1u, SDL_Init_fake.call_count);

    constexpr cen::sdl_cfg cfg;
    ASSERT_EQ(cfg.flags, SDL_Init_fake.arg0_val);
  }
  catch (...) {
    FAIL();
  }
}

TEST_F(InitializationTest, ImgDefaultConfiguration)
{
  try {
    const cen::img lib;
    ASSERT_EQ(1u, IMG_Init_fake.call_count);

    constexpr cen::img_cfg cfg;
    ASSERT_EQ(cfg.flags, IMG_Init_fake.arg0_val);
  }
  catch (...) {
    FAIL();
  }
}

TEST_F(InitializationTest, MixDefaultConfiguration)
{
  try {
    const cen::mix lib;
    ASSERT_EQ(1u, Mix_Init_fake.call_count);

    constexpr cen::mix_cfg cfg;
    ASSERT_EQ(cfg.frequency, Mix_OpenAudio_fake.arg0_val);
    ASSERT_EQ(cfg.format, Mix_OpenAudio_fake.arg1_val);
    ASSERT_EQ(cfg.channels, Mix_OpenAudio_fake.arg2_val);
    ASSERT_EQ(cfg.chunk_size, Mix_OpenAudio_fake.arg3_val);
  }
  catch (...) {
    FAIL();
  }
}

TEST_F(InitializationTest, TTFDefaultConfiguration)
{
  try {
    const cen::ttf lib;
    ASSERT_EQ(1u, TTF_Init_fake.call_count);
  }
  catch (...) {
    FAIL();
  }
}

TEST_F(InitializationTest, SDLCoreInitFailure)
{
  SDL_Init_fake.return_val = -1;
  ASSERT_THROW(cen::sdl{}, cen::sdl_error);
}

TEST_F(InitializationTest, SDLTTFInitFailure)
{
  TTF_Init_fake.return_val = -1;
  ASSERT_THROW(cen::ttf{}, cen::ttf_error);
}

TEST_F(InitializationTest, SDLImageInitFailure)
{
  IMG_Init_fake.return_val = 0;
  ASSERT_THROW(cen::img{}, cen::img_error);
}

TEST_F(InitializationTest, SDLMixInitFailure)
{
  Mix_Init_fake.return_val = 0;
  ASSERT_THROW(cen::mix{}, cen::mix_error);
}

TEST_F(InitializationTest, SDLMixOpenFailure)
{
  Mix_OpenAudio_fake.return_val = -1;
  ASSERT_THROW(cen::mix{}, cen::mix_error);
}
