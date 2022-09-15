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

#include "centurion/audio.hpp"
#include "core_mocks.hpp"
#include "mixer_mocks.hpp"

using music_finished_callback = void (*)();
using hook_music_callback = void (*)(void*, Uint8*, int);

extern "C"
{
  FAKE_VOID_FUNC(Mix_FreeMusic, Mix_Music*)
  FAKE_VOID_FUNC(Mix_ResumeMusic)
  FAKE_VOID_FUNC(Mix_PauseMusic)
  FAKE_VOID_FUNC(Mix_RewindMusic)
  FAKE_VOID_FUNC(Mix_HookMusicFinished, music_finished_callback)
  FAKE_VOID_FUNC(Mix_HookMusic, hook_music_callback, void*)
  FAKE_VALUE_FUNC(int, Mix_PlayMusic, Mix_Music*, int)
  FAKE_VALUE_FUNC(int, Mix_FadeInMusic, Mix_Music*, int, int)
  FAKE_VALUE_FUNC(int, Mix_FadeOutMusic, int)
  FAKE_VALUE_FUNC(int, Mix_VolumeMusic, int)
  FAKE_VALUE_FUNC(int, Mix_HaltMusic)
  FAKE_VALUE_FUNC(int, Mix_PlayingMusic)
  FAKE_VALUE_FUNC(int, Mix_PausedMusic)
  FAKE_VALUE_FUNC(void*, Mix_GetMusicHookData)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicDecoder, int)
  FAKE_VALUE_FUNC(SDL_bool, Mix_HasMusicDecoder, const char*)
  FAKE_VALUE_FUNC(int, Mix_GetNumMusicDecoders)
  FAKE_VALUE_FUNC(int, Mix_SetMusicPosition, double)
  FAKE_VALUE_FUNC(Mix_Fading, Mix_FadingMusic)
  FAKE_VALUE_FUNC(Mix_MusicType, Mix_GetMusicType, const Mix_Music*)

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicTitle, const Mix_Music*)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicTitleTag, const Mix_Music*)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicArtistTag, const Mix_Music*)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicAlbumTag, const Mix_Music*)
  FAKE_VALUE_FUNC(const char*, Mix_GetMusicCopyrightTag, const Mix_Music*)
  FAKE_VALUE_FUNC(double, Mix_GetMusicPosition, Mix_Music*)
  FAKE_VALUE_FUNC(double, Mix_MusicDuration, Mix_Music*)
  FAKE_VALUE_FUNC(double, Mix_GetMusicLoopStartTime, Mix_Music*)
  FAKE_VALUE_FUNC(double, Mix_GetMusicLoopEndTime, Mix_Music*)
  FAKE_VALUE_FUNC(double, Mix_GetMusicLoopLengthTime, Mix_Music*)
#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
}

class MusicTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_mixer();

    RESET_FAKE(Mix_FreeMusic)
    RESET_FAKE(Mix_ResumeMusic)
    RESET_FAKE(Mix_PauseMusic)
    RESET_FAKE(Mix_RewindMusic)
    RESET_FAKE(Mix_HookMusicFinished)
    RESET_FAKE(Mix_HookMusic)
    RESET_FAKE(Mix_PlayMusic)
    RESET_FAKE(Mix_FadeInMusic)
    RESET_FAKE(Mix_FadeOutMusic)
    RESET_FAKE(Mix_VolumeMusic)
    RESET_FAKE(Mix_HaltMusic)
    RESET_FAKE(Mix_PlayingMusic)
    RESET_FAKE(Mix_PausedMusic)
    RESET_FAKE(Mix_GetMusicHookData)
    RESET_FAKE(Mix_GetMusicDecoder)
    RESET_FAKE(Mix_HasMusicDecoder)
    RESET_FAKE(Mix_GetNumMusicDecoders)
    RESET_FAKE(Mix_SetMusicPosition)
    RESET_FAKE(Mix_FadingMusic)
    RESET_FAKE(Mix_GetMusicType)

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
    RESET_FAKE(Mix_GetMusicTitle)
    RESET_FAKE(Mix_GetMusicTitleTag)
    RESET_FAKE(Mix_GetMusicArtistTag)
    RESET_FAKE(Mix_GetMusicAlbumTag)
    RESET_FAKE(Mix_GetMusicCopyrightTag)
    RESET_FAKE(Mix_GetMusicPosition)
    RESET_FAKE(Mix_MusicDuration)
    RESET_FAKE(Mix_GetMusicLoopStartTime)
    RESET_FAKE(Mix_GetMusicLoopEndTime)
    RESET_FAKE(Mix_GetMusicLoopLengthTime)
#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
  }
};

TEST_F(MusicTest, Play)
{
  CEN_PREPARE_MOCK_TEST(Mix_PlayMusic, -1, 42)

  cen::music music;

  ASSERT_FALSE(music.play());
  ASSERT_EQ(1u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(0, Mix_PlayMusic_fake.arg1_val);

  ASSERT_EQ(42, music.play(7));
  ASSERT_EQ(2u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(7, Mix_PlayMusic_fake.arg1_val);

  ASSERT_EQ(42, music.play(cen::music::forever - 1));
  ASSERT_EQ(3u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(cen::music::forever, Mix_PlayMusic_fake.arg1_val);
}

TEST_F(MusicTest, Resume)
{
  cen::music::resume();
  ASSERT_EQ(1u, Mix_ResumeMusic_fake.call_count);
}

TEST_F(MusicTest, Halt)
{
  cen::music::halt();
  ASSERT_EQ(1u, Mix_HaltMusic_fake.call_count);
}

TEST_F(MusicTest, FadeIn)
{
  CEN_PREPARE_MOCK_TEST(Mix_FadeInMusic, -1, 0)

  cen::music music;

  ASSERT_FALSE(music.fade_in(cen::music::ms_type{5}));
  ASSERT_EQ(1u, Mix_FadeInMusic_fake.call_count);
  ASSERT_EQ(0, Mix_FadeInMusic_fake.arg1_val);

  ASSERT_TRUE(music.fade_in(cen::music::ms_type{5}, 4));
  ASSERT_EQ(2u, Mix_FadeInMusic_fake.call_count);
  ASSERT_EQ(4, Mix_FadeInMusic_fake.arg1_val);
}

TEST_F(MusicTest, FadeOut)
{
  CEN_PREPARE_MOCK_TEST(Mix_FadeOutMusic, 0, 1)

  ASSERT_FALSE(cen::music::fade_out(cen::music::ms_type{5}));
  ASSERT_EQ(1u, Mix_FadeOutMusic_fake.call_count);

  ASSERT_TRUE(cen::music::fade_out(cen::music::ms_type{3}));
  ASSERT_EQ(2u, Mix_FadeOutMusic_fake.call_count);

  // Should have no effect if already fading music
  Mix_FadingMusic_fake.return_val = MIX_FADING_IN;
  ASSERT_FALSE(cen::music::fade_out(cen::music::ms_type{3}));
  ASSERT_EQ(2u, Mix_FadeOutMusic_fake.call_count);
}

TEST_F(MusicTest, SetVolume)
{
  cen::music::set_volume(-1);
  ASSERT_EQ(0, Mix_VolumeMusic_fake.arg0_val);

  cen::music::set_volume(cen::music::max_volume() + 1);
  ASSERT_EQ(cen::music::max_volume(), Mix_VolumeMusic_fake.arg0_val);

  cen::music::set_volume(75);
  ASSERT_EQ(75, Mix_VolumeMusic_fake.arg0_val);
}

TEST_F(MusicTest, IsPlaying)
{
  const auto playing [[maybe_unused]] = cen::music::is_playing();
  ASSERT_EQ(1u, Mix_PlayingMusic_fake.call_count);
}

TEST_F(MusicTest, IsPaused)
{
  const auto paused [[maybe_unused]] = cen::music::is_paused();
  ASSERT_EQ(1u, Mix_PausedMusic_fake.call_count);
}

TEST_F(MusicTest, IsFading)
{
  const auto fading [[maybe_unused]] = cen::music::is_fading();
  ASSERT_EQ(1u, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, GetFadeStatus)
{
  const auto status [[maybe_unused]] = cen::music::get_fade_status();
  ASSERT_EQ(1u, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, Rewind)
{
  cen::music::rewind();
  ASSERT_EQ(1u, Mix_RewindMusic_fake.call_count);
}

TEST_F(MusicTest, SetPosition)
{
  CEN_PREPARE_MOCK_TEST(Mix_SetMusicPosition, -1, 0)

  ASSERT_EQ(cen::failure, cen::music::set_position(1));
  ASSERT_EQ(cen::success, cen::music::set_position(1));
  ASSERT_EQ(2u, Mix_SetMusicPosition_fake.call_count);
}

TEST_F(MusicTest, Type)
{
  cen::music music;
  const auto type [[maybe_unused]] = music.type();
  ASSERT_EQ(1u, Mix_GetMusicType_fake.call_count);
}

TEST_F(MusicTest, SetHook)
{
  cen::music::set_hook([](void*, Uint8*, int) {});

  ASSERT_EQ(1u, Mix_HookMusic_fake.call_count);
  ASSERT_NE(nullptr, Mix_HookMusic_fake.arg0_val);
}

TEST_F(MusicTest, ResetHook)
{
  cen::music::reset_hook();
  ASSERT_EQ(1u, Mix_HookMusic_fake.call_count);
  ASSERT_EQ(nullptr, Mix_HookMusic_fake.arg0_val);
}

TEST_F(MusicTest, HookData)
{
  auto* data [[maybe_unused]] = cen::music::hook_data();
  ASSERT_EQ(1u, Mix_GetMusicHookData_fake.call_count);
}

TEST_F(MusicTest, GetDecoder)
{
  const auto name [[maybe_unused]] = cen::music::get_decoder(0);
  ASSERT_EQ(1u, Mix_GetMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, HasDecoder)
{
  const auto has [[maybe_unused]] = cen::music::has_decoder("foo");
  ASSERT_EQ(1u, Mix_HasMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, DecoderCount)
{
  const auto count [[maybe_unused]] = cen::music::decoder_count();
  ASSERT_EQ(1u, Mix_GetNumMusicDecoders_fake.call_count);
}

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(MusicTest, CurrentTitle)
{
  const auto title [[maybe_unused]] = cen::music::current_title();
  ASSERT_EQ(nullptr, Mix_GetMusicTitle_fake.arg0_val);
  ASSERT_EQ(1u, Mix_GetMusicTitle_fake.call_count);
}

TEST_F(MusicTest, Title)
{
  const cen::music music;
  const auto title [[maybe_unused]] = music.title();
  ASSERT_EQ(1u, Mix_GetMusicTitle_fake.call_count);
}

TEST_F(MusicTest, TitleTag)
{
  const cen::music music;
  const auto title [[maybe_unused]] = music.title_tag();

  ASSERT_EQ(1u, Mix_GetMusicTitleTag_fake.call_count);
}

TEST_F(MusicTest, ArtistTag)
{
  const cen::music music;
  const auto artist [[maybe_unused]] = music.artist_tag();

  ASSERT_EQ(1u, Mix_GetMusicArtistTag_fake.call_count);
}

TEST_F(MusicTest, AlbumTag)
{
  const cen::music music;
  const auto album [[maybe_unused]] = music.album_tag();

  ASSERT_EQ(1u, Mix_GetMusicAlbumTag_fake.call_count);
}

TEST_F(MusicTest, CopyrightTag)
{
  const cen::music music;
  const auto copyright [[maybe_unused]] = music.copyright_tag();

  ASSERT_EQ(1u, Mix_GetMusicCopyrightTag_fake.call_count);
}

TEST_F(MusicTest, Position)
{
  CEN_PREPARE_MOCK_TEST(Mix_GetMusicPosition, -1.0, 0.4)

  const cen::music music;

  ASSERT_FALSE(music.position().has_value());
  ASSERT_EQ(0.4, music.position());

  ASSERT_EQ(2u, Mix_GetMusicPosition_fake.call_count);
}

TEST_F(MusicTest, Duration)
{
  CEN_PREPARE_MOCK_TEST(Mix_MusicDuration, -1.0, 32.0)

  const cen::music music;

  ASSERT_FALSE(music.duration().has_value());
  ASSERT_EQ(32.0, music.duration());

  ASSERT_EQ(2u, Mix_MusicDuration_fake.call_count);
}

TEST_F(MusicTest, LoopStartTime)
{
  CEN_PREPARE_MOCK_TEST(Mix_GetMusicLoopStartTime, -1.0, 7.0)

  const cen::music music;

  ASSERT_FALSE(music.loop_start_time().has_value());
  ASSERT_EQ(7.0, music.loop_start_time());

  ASSERT_EQ(2u, Mix_GetMusicLoopStartTime_fake.call_count);
}

TEST_F(MusicTest, LoopEndTime)
{
  CEN_PREPARE_MOCK_TEST(Mix_GetMusicLoopEndTime, -1.0, 4.0)

  const cen::music music;

  ASSERT_FALSE(music.loop_end_time().has_value());
  ASSERT_EQ(4.0, music.loop_end_time());

  ASSERT_EQ(2u, Mix_GetMusicLoopEndTime_fake.call_count);
}

TEST_F(MusicTest, LoopLength)
{
  CEN_PREPARE_MOCK_TEST(Mix_GetMusicLoopLengthTime, -1.0, 12.0)

  const cen::music music;

  ASSERT_FALSE(music.loop_length().has_value());
  ASSERT_EQ(12.0, music.loop_length());

  ASSERT_EQ(2u, Mix_GetMusicLoopLengthTime_fake.call_count);
}

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)