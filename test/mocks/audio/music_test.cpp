#include "audio/music.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

using music_finished_callback = void(SDLCALL*)(void);

// clang-format off
extern "C" {
FAKE_VOID_FUNC(Mix_FreeMusic, Mix_Music*)
FAKE_VOID_FUNC(Mix_ResumeMusic)
FAKE_VOID_FUNC(Mix_PauseMusic)
FAKE_VOID_FUNC(Mix_RewindMusic)
FAKE_VOID_FUNC(Mix_HookMusicFinished, music_finished_callback)
FAKE_VALUE_FUNC(int, Mix_PlayMusic, Mix_Music*, int)
FAKE_VALUE_FUNC(int, Mix_FadeInMusic, Mix_Music*, int, int)
FAKE_VALUE_FUNC(int, Mix_FadeOutMusic, int)
FAKE_VALUE_FUNC(int, Mix_VolumeMusic, int)
FAKE_VALUE_FUNC(int, Mix_HaltMusic)
FAKE_VALUE_FUNC(int, Mix_PlayingMusic)
FAKE_VALUE_FUNC(int, Mix_PausedMusic)
FAKE_VALUE_FUNC(const char*, Mix_GetMusicDecoder, int)
FAKE_VALUE_FUNC(SDL_bool, Mix_HasMusicDecoder, const char*)
FAKE_VALUE_FUNC(int, Mix_GetNumMusicDecoders)
FAKE_VALUE_FUNC(int, Mix_SetMusicPosition, double)
FAKE_VALUE_FUNC(Mix_Fading, Mix_FadingMusic)
FAKE_VALUE_FUNC(Mix_MusicType, Mix_GetMusicType, const Mix_Music*)
}
// clang-format on

class MusicTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(Mix_FreeMusic)
    RESET_FAKE(Mix_ResumeMusic)
    RESET_FAKE(Mix_PauseMusic)
    RESET_FAKE(Mix_RewindMusic)
    RESET_FAKE(Mix_HookMusicFinished)
    RESET_FAKE(Mix_PlayMusic)
    RESET_FAKE(Mix_FadeInMusic)
    RESET_FAKE(Mix_FadeOutMusic)
    RESET_FAKE(Mix_VolumeMusic)
    RESET_FAKE(Mix_HaltMusic)
    RESET_FAKE(Mix_PlayingMusic)
    RESET_FAKE(Mix_PausedMusic)
    RESET_FAKE(Mix_GetMusicDecoder)
    RESET_FAKE(Mix_HasMusicDecoder)
    RESET_FAKE(Mix_GetNumMusicDecoders)
    RESET_FAKE(Mix_SetMusicPosition)
    RESET_FAKE(Mix_FadingMusic)
    RESET_FAKE(Mix_GetMusicType)
  }
};

TEST_F(MusicTest, Play)
{
  cen::music music;

  music.play();
  EXPECT_EQ(1, Mix_PlayMusic_fake.call_count);
  EXPECT_EQ(0, Mix_PlayMusic_fake.arg1_val);

  music.play(7);
  EXPECT_EQ(2, Mix_PlayMusic_fake.call_count);
  EXPECT_EQ(7, Mix_PlayMusic_fake.arg1_val);

  music.play(cen::music::forever - 1);
  EXPECT_EQ(3, Mix_PlayMusic_fake.call_count);
  EXPECT_EQ(cen::music::forever, Mix_PlayMusic_fake.arg1_val);
}

TEST_F(MusicTest, Resume)
{
  cen::music::resume();
  EXPECT_EQ(1, Mix_ResumeMusic_fake.call_count);
}

TEST_F(MusicTest, Halt)
{
  cen::music::halt();
  EXPECT_EQ(1, Mix_HaltMusic_fake.call_count);
}

TEST_F(MusicTest, FadeIn)
{
  cen::music music;

  music.fade_in(cen::milliseconds<int>{5});
  EXPECT_EQ(1, Mix_FadeInMusic_fake.call_count);
  EXPECT_EQ(0, Mix_FadeInMusic_fake.arg1_val);

  music.fade_in(cen::milliseconds<int>{5}, 4);
  EXPECT_EQ(2, Mix_FadeInMusic_fake.call_count);
  EXPECT_EQ(4, Mix_FadeInMusic_fake.arg1_val);
}

TEST_F(MusicTest, FadeOut)
{
  cen::music::fade_out(cen::milliseconds<int>{5});
  EXPECT_EQ(1, Mix_FadeOutMusic_fake.call_count);

  cen::music::fade_out(cen::milliseconds<int>{3});
  EXPECT_EQ(2, Mix_FadeOutMusic_fake.call_count);

  // Should have no effect if already fading music
  Mix_FadingMusic_fake.return_val = MIX_FADING_IN;
  cen::music::fade_out(cen::milliseconds<int>{3});
  EXPECT_EQ(2, Mix_FadeOutMusic_fake.call_count);
}

TEST_F(MusicTest, SetVolume)
{
  cen::music::set_volume(-1);
  EXPECT_EQ(0, Mix_VolumeMusic_fake.arg0_val);

  cen::music::set_volume(cen::music::max_volume() + 1);
  EXPECT_EQ(cen::music::max_volume(), Mix_VolumeMusic_fake.arg0_val);

  cen::music::set_volume(75);
  EXPECT_EQ(75, Mix_VolumeMusic_fake.arg0_val);
}

TEST_F(MusicTest, IsPlaying)
{
  const auto playing [[maybe_unused]] = cen::music::is_playing();
  EXPECT_EQ(1, Mix_PlayingMusic_fake.call_count);
}

TEST_F(MusicTest, IsPaused)
{
  const auto paused [[maybe_unused]] = cen::music::is_paused();
  EXPECT_EQ(1, Mix_PausedMusic_fake.call_count);
}

TEST_F(MusicTest, IsFading)
{
  const auto fading [[maybe_unused]] = cen::music::is_fading();
  EXPECT_EQ(1, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, GetFadeStatus)
{
  const auto status [[maybe_unused]] = cen::music::get_fade_status();
  EXPECT_EQ(1, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, Rewind)
{
  cen::music::rewind();
  EXPECT_EQ(1, Mix_RewindMusic_fake.call_count);
}

TEST_F(MusicTest, SetPosition)
{
  cen::music::set_position(1);
  EXPECT_EQ(1, Mix_SetMusicPosition_fake.call_count);
}

TEST_F(MusicTest, Type)
{
  cen::music music;
  const auto type [[maybe_unused]] = music.type();
  EXPECT_EQ(1, Mix_GetMusicType_fake.call_count);
}

TEST_F(MusicTest, GetDecoder)
{
  const auto name [[maybe_unused]] = cen::music::get_decoder(0);
  EXPECT_EQ(1, Mix_GetMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, HasDecoder)
{
  const auto has [[maybe_unused]] = cen::music::has_decoder("foo");
  EXPECT_EQ(1, Mix_HasMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, DecoderCount)
{
  const auto count [[maybe_unused]] = cen::music::decoder_count();
  EXPECT_EQ(1, Mix_GetNumMusicDecoders_fake.call_count);
}

TEST_F(MusicTest, OnMusicFinished)
{
  cen::on_music_finished([]() noexcept {
  });
  EXPECT_EQ(1, Mix_HookMusicFinished_fake.call_count);
}

using MusicDeathTest = MusicTest;

TEST_F(MusicDeathTest, FadeIn)
{
  cen::music music;
  EXPECT_DEBUG_DEATH(music.fade_in(cen::milliseconds<int>::zero()), "");
}

TEST_F(MusicDeathTest, FadeOut)
{
  cen::music music;
  EXPECT_DEBUG_DEATH(music.fade_out(cen::milliseconds<int>::zero()), "");
}