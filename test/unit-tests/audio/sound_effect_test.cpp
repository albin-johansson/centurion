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

#include <iostream>     // cout
#include <memory>       // unique_ptr
#include <type_traits>  // ...

#include "centurion/audio.hpp"

static_assert(std::is_final_v<cen::sound_effect>);
static_assert(!std::is_default_constructible_v<cen::sound_effect>);

static_assert(std::is_nothrow_move_constructible_v<cen::sound_effect>);
static_assert(std::is_nothrow_move_assignable_v<cen::sound_effect>);

static_assert(!std::is_copy_constructible_v<cen::sound_effect>);
static_assert(!std::is_copy_assignable_v<cen::sound_effect>);

inline constexpr auto path = "resources/click.wav";

class SoundEffect : public testing::Test {
 protected:
  static void SetUpTestSuite() { mSound = std::make_unique<cen::sound_effect>(path); }

  static void TearDownTestSuite() { mSound.reset(); }

  inline static std::unique_ptr<cen::sound_effect> mSound;
};

TEST_F(SoundEffect, Constructor)
{
  ASSERT_THROW(cen::sound_effect("foobar"), cen::mix_error);

  using namespace std::string_literals;
  ASSERT_THROW(cen::sound_effect("foobar"s), cen::mix_error);
}

TEST_F(SoundEffect, PlayAndStop)
{
  ASSERT_FALSE(mSound->is_playing());

  mSound->play();
  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();
  ASSERT_FALSE(mSound->is_playing());

  mSound->play(5);
  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();
}

TEST_F(SoundEffect, Looping)
{
  const auto oldVolume = mSound->volume();

  mSound->set_volume(1);

  mSound->play(10);
  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();

  ASSERT_LT(cen::sound_effect::forever, 0);
  ASSERT_NO_THROW(mSound->play(cen::sound_effect::forever));

  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();
  ASSERT_FALSE(mSound->is_playing());

  mSound->set_volume(oldVolume);
}

TEST_F(SoundEffect, FadeIn)
{
  mSound->stop();

  ASSERT_FALSE(mSound->is_fading());
  ASSERT_FALSE(mSound->is_playing());

  mSound->fade_in(cen::sound_effect::ms_type {100});
  ASSERT_TRUE(mSound->is_fading());
  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();
}

TEST_F(SoundEffect, FadeOut)
{
  ASSERT_FALSE(mSound->is_playing());

  mSound->play();
  mSound->fade_out(cen::sound_effect::ms_type {5});
  ASSERT_TRUE(mSound->is_fading());
  ASSERT_TRUE(mSound->is_playing());

  mSound->stop();
  ASSERT_FALSE(mSound->is_fading());
  ASSERT_FALSE(mSound->is_playing());
}

TEST_F(SoundEffect, SetVolume)
{
  const auto oldVolume = mSound->volume();

  {  // Valid volume
    const auto volume = 27;
    mSound->set_volume(volume);
    ASSERT_EQ(volume, mSound->volume());
  }

  {  // Volume underflow
    const auto volume = -1;
    mSound->set_volume(volume);
    ASSERT_EQ(0, mSound->volume());
  }

  {  // Volume overflow
    const auto volume = cen::sound_effect::max_volume() + 1;
    mSound->set_volume(volume);
    ASSERT_EQ(cen::sound_effect::max_volume(), mSound->volume());
  }

  mSound->set_volume(oldVolume);
}

TEST_F(SoundEffect, Volume)
{
  ASSERT_EQ(cen::sound_effect::max_volume(), mSound->volume());
  ASSERT_EQ(128, mSound->volume());  // because of the documentation guarantee
  ASSERT_EQ(MIX_MAX_VOLUME, cen::sound_effect::max_volume());
}

TEST_F(SoundEffect, Forever)
{
  ASSERT_EQ(-1, cen::sound_effect::forever);
}

TEST_F(SoundEffect, MaxVolume)
{
  ASSERT_EQ(MIX_MAX_VOLUME, cen::sound_effect::max_volume());
}

TEST_F(SoundEffect, StreamOperator)
{
  std::cout << "sound_effect == " << *mSound << '\n';
}