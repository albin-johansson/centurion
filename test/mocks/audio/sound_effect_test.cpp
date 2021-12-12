#include "audio/sound_effect.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"
#include "mixer_mocks.hpp"

using ms = cen::milliseconds<int>;

extern "C"
{
  FAKE_VOID_FUNC(Mix_FreeChunk, Mix_Chunk*)
  FAKE_VOID_FUNC(Mix_Pause, int)
  FAKE_VALUE_FUNC(int, Mix_PlayChannelTimed, int, Mix_Chunk*, int, int)
  FAKE_VALUE_FUNC(int, Mix_FadeInChannelTimed, int, Mix_Chunk*, int, int, int)
  FAKE_VALUE_FUNC(int, Mix_FadeOutChannel, int, int)
  FAKE_VALUE_FUNC(int, Mix_Playing, int)
  FAKE_VALUE_FUNC(int, Mix_VolumeChunk, Mix_Chunk*, int)
}

class SoundEffectTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_mixer();

    RESET_FAKE(Mix_FreeChunk)
    RESET_FAKE(Mix_Pause)
    RESET_FAKE(Mix_PlayChannelTimed)
    RESET_FAKE(Mix_FadeInChannelTimed)
    RESET_FAKE(Mix_FadeOutChannel)
    RESET_FAKE(Mix_Playing)
    RESET_FAKE(Mix_VolumeChunk)
  }

  cen::SoundEffectHandle sound{nullptr};
};

TEST_F(SoundEffectTest, Play)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_PlayChannelTimed, values.data(), cen::isize(values));

  ASSERT_FALSE(sound.Play());
  ASSERT_EQ(1u, Mix_PlayChannelTimed_fake.call_count);
  ASSERT_EQ(0, Mix_PlayChannelTimed_fake.arg2_val);

  ASSERT_TRUE(sound.Play(-2));
  ASSERT_EQ(2u, Mix_PlayChannelTimed_fake.call_count);
  ASSERT_EQ(-1, Mix_PlayChannelTimed_fake.arg2_val);

  ASSERT_TRUE(sound.Play(7));
  ASSERT_EQ(3u, Mix_PlayChannelTimed_fake.call_count);
  ASSERT_EQ(7, Mix_PlayChannelTimed_fake.arg2_val);
}

TEST_F(SoundEffectTest, Pause)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_Playing, values.data(), cen::isize(values));

  sound.Stop();  // Does not invoke Mix_Playing
  ASSERT_EQ(0u, Mix_Pause_fake.call_count);

  sound.set_channel(23);

  sound.Stop();
  ASSERT_EQ(0u, Mix_Pause_fake.call_count);

  sound.Stop();
  ASSERT_EQ(1u, Mix_Pause_fake.call_count);
}

TEST_F(SoundEffectTest, FadeIn)
{
  // Not playing
  sound.FadeIn(ms{5});
  ASSERT_EQ(1u, Mix_FadeInChannelTimed_fake.call_count);

  // Not playing but with an associated channel
  sound.set_channel(1);
  sound.FadeIn(ms{5});
  ASSERT_EQ(2u, Mix_FadeInChannelTimed_fake.call_count);

  // Already playing
  Mix_Playing_fake.return_val = 1;
  sound.FadeIn(ms{5});
  ASSERT_EQ(2u, Mix_FadeInChannelTimed_fake.call_count);
}

TEST_F(SoundEffectTest, FadeOut)
{
  // Not playing
  sound.FadeOut(ms{5});
  ASSERT_EQ(0u, Mix_FadeOutChannel_fake.call_count);

  // Not playing but with an associated channel
  sound.set_channel(7);
  sound.FadeOut(ms{5});
  ASSERT_EQ(0u, Mix_FadeOutChannel_fake.call_count);

  // Playing
  Mix_Playing_fake.return_val = 1;
  sound.FadeOut(ms{5});
  ASSERT_EQ(1u, Mix_FadeOutChannel_fake.call_count);
}

TEST_F(SoundEffectTest, SetVolume)
{
  sound.SetVolume(-1);
  ASSERT_EQ(0, Mix_VolumeChunk_fake.arg1_val);

  sound.SetVolume(cen::SoundEffect::GetMaxVolume() + 1);
  ASSERT_EQ(cen::SoundEffect::GetMaxVolume(), Mix_VolumeChunk_fake.arg1_val);

  sound.SetVolume(27);
  ASSERT_EQ(27, Mix_VolumeChunk_fake.arg1_val);
}

TEST_F(SoundEffectTest, IsAnyPlaying)
{
  const auto playing [[maybe_unused]] = cen::SoundEffect::IsAnyPlaying();
  ASSERT_EQ(1u, Mix_Playing_fake.call_count);
  ASSERT_EQ(-1, Mix_Playing_fake.arg0_val);
}

TEST_F(SoundEffectTest, Channel)
{
  ASSERT_FALSE(sound.GetChannel().has_value());

  sound.set_channel(7);
  ASSERT_EQ(7, sound.GetChannel());
}

TEST_F(SoundEffectTest, GetDecoder)
{
  const auto* name [[maybe_unused]] = cen::SoundEffect::GetDecoder(0);
  ASSERT_EQ(1u, Mix_GetChunkDecoder_fake.call_count);
}

TEST_F(SoundEffectTest, HasDecoder)
{
  std::array values{SDL_FALSE, SDL_TRUE};
  SET_RETURN_SEQ(Mix_HasChunkDecoder, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::SoundEffect::HasDecoder("foo"));
  ASSERT_TRUE(cen::SoundEffect::HasDecoder("foo"));
  ASSERT_EQ(2u, Mix_HasChunkDecoder_fake.call_count);
}

TEST_F(SoundEffectTest, GetDecoderCount)
{
  const auto count [[maybe_unused]] = cen::SoundEffect::GetDecoderCount();
  ASSERT_EQ(1u, Mix_GetNumChunkDecoders_fake.call_count);
}