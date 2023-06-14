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

#include <iostream>     // clog
#include <memory>       // unique_ptr
#include <type_traits>  // ...

#include "centurion/audio.hpp"
#include "centurion/logging.hpp"

static_assert(std::is_final_v<cen::music>);

static_assert(!std::is_nothrow_copy_constructible_v<cen::music>);
static_assert(!std::is_nothrow_copy_assignable_v<cen::music>);

static_assert(std::is_nothrow_move_constructible_v<cen::music>);
static_assert(std::is_nothrow_move_assignable_v<cen::music>);

class MusicTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    music = std::make_unique<cen::music>("resources/hiddenPond.mp3");
  }

  static void TearDownTestSuite() { music.reset(); }

  inline static std::unique_ptr<cen::music> music;
};

TEST_F(MusicTest, Forever)
{
  ASSERT_EQ(-1, cen::music::forever);
}

TEST_F(MusicTest, Constructor)
{
  using namespace std::string_literals;
  ASSERT_THROW(cen::music {"foobar"s}, cen::mix_error);
}

TEST_F(MusicTest, Play)
{
  music->play();
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_paused());
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  cen::music::halt();

  music->play(cen::music::forever);
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_paused());
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());

  music->pause();
  cen::music::halt();
}

TEST_F(MusicTest, Resume)
{
  ASSERT_NO_THROW(cen::music::resume());

  music->play();
  ASSERT_NO_THROW(cen::music::resume());

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());

  cen::music::resume();
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();
  ASSERT_NO_THROW(cen::music::resume());
}

TEST_F(MusicTest, Pause)
{
  ASSERT_NO_THROW(cen::music::pause());

  music->play();

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());

  music->fade_in(cen::music::ms_type {100});

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, Halt)
{
  ASSERT_NO_THROW(cen::music::halt());

  music->play();
  cen::music::halt();

  ASSERT_FALSE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());

  music->fade_in(cen::music::ms_type {100});
  cen::music::halt();

  ASSERT_FALSE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_fading());
}

TEST_F(MusicTest, FadeIn)
{
  ASSERT_FALSE(cen::music::is_fading());

  cen::music::halt();

  music->fade_in(cen::music::ms_type {100});
  ASSERT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, FadeOut)
{
  ASSERT_FALSE(cen::music::is_fading());

  ASSERT_NO_THROW(cen::music::fade_out(cen::music::ms_type {100}));

  music->fade_in(cen::music::ms_type {100});
  ASSERT_TRUE(cen::music::is_fading());

  cen::music::halt();
}

TEST_F(MusicTest, SetVolume)
{
  const auto oldVolume = cen::music::volume();

  {  // Valid GetVolume
    const auto volume = 102;
    cen::music::set_volume(volume);
    ASSERT_EQ(volume, cen::music::volume());
  }

  {  // Volume underflow
    const auto volume = -1;
    cen::music::set_volume(volume);
    ASSERT_EQ(0, cen::music::volume());
  }

  {  // Volume overflow
    const auto volume = cen::music::max_volume() + 1;
    cen::music::set_volume(volume);
    ASSERT_EQ(cen::music::max_volume(), cen::music::volume());
  }

  cen::music::set_volume(oldVolume);
}

TEST_F(MusicTest, IsPlaying)
{
  ASSERT_FALSE(cen::music::is_playing());

  music->play();
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();

  music->fade_in(cen::music::ms_type {100});
  ASSERT_TRUE(cen::music::is_playing());

  cen::music::halt();
}

TEST_F(MusicTest, IsPaused)
{
  music->play();
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::pause();
  ASSERT_TRUE(cen::music::is_paused());
}

TEST_F(MusicTest, IsFading)
{
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_fading_in());
  ASSERT_FALSE(cen::music::is_fading_out());

  music->play();
  ASSERT_FALSE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_fading_in());
  ASSERT_FALSE(cen::music::is_fading_out());

  cen::music::halt();

  music->fade_in(cen::music::ms_type {200});
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_fading_in());
  ASSERT_FALSE(cen::music::is_fading_out());

  // This should have no effect, since the Music is fading in
  cen::music::fade_out(cen::music::ms_type {50});
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_fading_in());
  ASSERT_FALSE(cen::music::is_fading_out());

  cen::music::halt();

  music->play();
  cen::music::fade_out(cen::music::ms_type {50});
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_FALSE(cen::music::is_fading_in());
  ASSERT_TRUE(cen::music::is_fading_out());

  cen::music::halt();
}

TEST_F(MusicTest, Volume)
{
  ASSERT_EQ(cen::music::max_volume(), cen::music::volume());

  const auto volume = 47;
  cen::music::set_volume(volume);

  ASSERT_EQ(volume, cen::music::volume());
}

TEST_F(MusicTest, FadeStatus)
{
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());
  ASSERT_FALSE(cen::music::is_fading());

  music->fade_in(cen::music::ms_type {100});
  ASSERT_EQ(cen::fade_status::in, cen::music::get_fade_status());
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::halt();

  music->play();
  cen::music::fade_out(cen::music::ms_type {100});
  ASSERT_EQ(cen::fade_status::out, cen::music::get_fade_status());
  ASSERT_TRUE(cen::music::is_fading());
  ASSERT_TRUE(cen::music::is_playing());
  ASSERT_FALSE(cen::music::is_paused());

  cen::music::halt();
  ASSERT_EQ(cen::fade_status::none, cen::music::get_fade_status());
}

TEST_F(MusicTest, Type)
{
  ASSERT_EQ(cen::music_type::mp3, music->type());
}

TEST_F(MusicTest, StreamOperator)
{
  std::cout << "music == " << *music << '\n';
}