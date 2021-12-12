#include "audio/music.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "mixer_mocks.hpp"

using music_finished_callback = void(SDLCALL*)(void);
using hook_music_callback = void(SDLCALL*)(void*, Uint8*, int);
using ms = cen::milliseconds<int>;

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
  }
};

TEST_F(MusicTest, Play)
{
  std::array values{-1, 42};
  SET_RETURN_SEQ(Mix_PlayMusic, values.data(), cen::isize(values));

  cen::Music music;

  ASSERT_FALSE(music.Play());
  ASSERT_EQ(1u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(0, Mix_PlayMusic_fake.arg1_val);

  ASSERT_EQ(42, music.Play(7));
  ASSERT_EQ(2u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(7, Mix_PlayMusic_fake.arg1_val);

  ASSERT_EQ(42, music.Play(cen::Music::forever - 1));
  ASSERT_EQ(3u, Mix_PlayMusic_fake.call_count);
  ASSERT_EQ(cen::Music::forever, Mix_PlayMusic_fake.arg1_val);
}

TEST_F(MusicTest, Resume)
{
  cen::Music::Resume();
  ASSERT_EQ(1u, Mix_ResumeMusic_fake.call_count);
}

TEST_F(MusicTest, Halt)
{
  cen::Music::Halt();
  ASSERT_EQ(1u, Mix_HaltMusic_fake.call_count);
}

TEST_F(MusicTest, FadeIn)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_FadeInMusic, values.data(), cen::isize(values));

  cen::Music music;

  ASSERT_FALSE(music.FadeIn(ms{5}));
  ASSERT_EQ(1u, Mix_FadeInMusic_fake.call_count);
  ASSERT_EQ(0, Mix_FadeInMusic_fake.arg1_val);

  ASSERT_TRUE(music.FadeIn(ms{5}, 4));
  ASSERT_EQ(2u, Mix_FadeInMusic_fake.call_count);
  ASSERT_EQ(4, Mix_FadeInMusic_fake.arg1_val);
}

TEST_F(MusicTest, FadeOut)
{
  std::array values{0, 1};  // Yes, this function has weird error codes
  SET_RETURN_SEQ(Mix_FadeOutMusic, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::Music::FadeOut(ms{5}));
  ASSERT_EQ(1u, Mix_FadeOutMusic_fake.call_count);

  ASSERT_TRUE(cen::Music::FadeOut(ms{3}));
  ASSERT_EQ(2u, Mix_FadeOutMusic_fake.call_count);

  // Should have no effect if already fading music
  Mix_FadingMusic_fake.return_val = MIX_FADING_IN;
  ASSERT_FALSE(cen::Music::FadeOut(ms{3}));
  ASSERT_EQ(2u, Mix_FadeOutMusic_fake.call_count);
}

TEST_F(MusicTest, SetVolume)
{
  cen::Music::SetVolume(-1);
  ASSERT_EQ(0, Mix_VolumeMusic_fake.arg0_val);

  cen::Music::SetVolume(cen::Music::GetMaxVolume() + 1);
  ASSERT_EQ(cen::Music::GetMaxVolume(), Mix_VolumeMusic_fake.arg0_val);

  cen::Music::SetVolume(75);
  ASSERT_EQ(75, Mix_VolumeMusic_fake.arg0_val);
}

TEST_F(MusicTest, IsPlaying)
{
  const auto playing [[maybe_unused]] = cen::Music::IsPlaying();
  ASSERT_EQ(1u, Mix_PlayingMusic_fake.call_count);
}

TEST_F(MusicTest, IsPaused)
{
  const auto paused [[maybe_unused]] = cen::Music::IsPaused();
  ASSERT_EQ(1u, Mix_PausedMusic_fake.call_count);
}

TEST_F(MusicTest, IsFading)
{
  const auto fading [[maybe_unused]] = cen::Music::IsFading();
  ASSERT_EQ(1u, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, GetFadeStatus)
{
  const auto status [[maybe_unused]] = cen::Music::GetFadeStatus();
  ASSERT_EQ(1u, Mix_FadingMusic_fake.call_count);
}

TEST_F(MusicTest, Rewind)
{
  cen::Music::Rewind();
  ASSERT_EQ(1u, Mix_RewindMusic_fake.call_count);
}

TEST_F(MusicTest, SetPosition)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_SetMusicPosition, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::Music::SetPosition(1));
  ASSERT_EQ(cen::success, cen::Music::SetPosition(1));
  ASSERT_EQ(2u, Mix_SetMusicPosition_fake.call_count);
}

TEST_F(MusicTest, GetType)
{
  cen::Music music;
  const auto type [[maybe_unused]] = music.GetType();
  ASSERT_EQ(1u, Mix_GetMusicType_fake.call_count);
}

TEST_F(MusicTest, SetHook)
{
  cen::Music::SetHook([](void*, Uint8*, int) {});

  ASSERT_EQ(1u, Mix_HookMusic_fake.call_count);
  ASSERT_NE(nullptr, Mix_HookMusic_fake.arg0_val);
}

TEST_F(MusicTest, ResetHook)
{
  cen::Music::ResetHook();
  ASSERT_EQ(1u, Mix_HookMusic_fake.call_count);
  ASSERT_EQ(nullptr, Mix_HookMusic_fake.arg0_val);
}

TEST_F(MusicTest, GetHookData)
{
  auto* data [[maybe_unused]] = cen::Music::GetHookData();
  ASSERT_EQ(1u, Mix_GetMusicHookData_fake.call_count);
}

TEST_F(MusicTest, GetDecoder)
{
  const auto name [[maybe_unused]] = cen::Music::GetDecoder(0);
  ASSERT_EQ(1u, Mix_GetMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, HasDecoder)
{
  const auto has [[maybe_unused]] = cen::Music::HasDecoder("foo");
  ASSERT_EQ(1u, Mix_HasMusicDecoder_fake.call_count);
}

TEST_F(MusicTest, GetDecoderCount)
{
  const auto count [[maybe_unused]] = cen::Music::GetDecoderCount();
  ASSERT_EQ(1u, Mix_GetNumMusicDecoders_fake.call_count);
}
