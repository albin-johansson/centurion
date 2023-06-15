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

#include <fff.h>
#include <gtest/gtest.h>

#include "centurion/audio.hpp"
#include "core_mocks.hpp"
#include "mixer_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(Mix_FreeChunk, Mix_Chunk*)
FAKE_VOID_FUNC(Mix_Pause, int)
FAKE_VALUE_FUNC(int, Mix_PlayChannelTimed, int, Mix_Chunk*, int, int)
FAKE_VALUE_FUNC(int, Mix_FadeInChannelTimed, int, Mix_Chunk*, int, int, int)
FAKE_VALUE_FUNC(int, Mix_FadeOutChannel, int, int)
FAKE_VALUE_FUNC(int, Mix_Playing, int)
FAKE_VALUE_FUNC(int, Mix_VolumeChunk, Mix_Chunk*, int)

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
FAKE_VALUE_FUNC(int, Mix_PlayChannel, int, Mix_Chunk*, int)
FAKE_VALUE_FUNC(int, Mix_FadeInChannel, int, Mix_Chunk*, int, int)
FAKE_VALUE_FUNC(int, Mix_MasterVolume, int)
#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
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

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
    RESET_FAKE(Mix_PlayChannel)
    RESET_FAKE(Mix_FadeInChannel)
    RESET_FAKE(Mix_MasterVolume)
#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
  }

  cen::sound_effect_handle mSound {nullptr};
};

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(SoundEffectTest, Play)
{
  CEN_PREPARE_MOCK_TEST(Mix_PlayChannel, -1, 0)

  ASSERT_FALSE(mSound.play());
  ASSERT_EQ(1u, Mix_PlayChannel_fake.call_count);
  ASSERT_EQ(0, Mix_PlayChannel_fake.arg2_val);

  ASSERT_TRUE(mSound.play(-2));
  ASSERT_EQ(2u, Mix_PlayChannel_fake.call_count);
  ASSERT_EQ(-1, Mix_PlayChannel_fake.arg2_val);

  ASSERT_TRUE(mSound.play(7));
  ASSERT_EQ(3u, Mix_PlayChannel_fake.call_count);
  ASSERT_EQ(7, Mix_PlayChannel_fake.arg2_val);
}

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(SoundEffectTest, Pause)
{
  CEN_PREPARE_MOCK_TEST(Mix_Playing, 0, 1)

  mSound.stop();  // Does not invoke Mix_Playing
  ASSERT_EQ(0u, Mix_Pause_fake.call_count);

  mSound.set_channel(23);

  mSound.stop();
  ASSERT_EQ(0u, Mix_Pause_fake.call_count);

  mSound.stop();
  ASSERT_EQ(1u, Mix_Pause_fake.call_count);
}

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(SoundEffectTest, FadeIn)
{
  // Not playing
  mSound.fade_in(cen::sound_effect::ms_type {5});
  ASSERT_EQ(1u, Mix_FadeInChannel_fake.call_count);

  // Not playing but with an associated channel
  mSound.set_channel(1);
  mSound.fade_in(cen::sound_effect::ms_type {5});
  ASSERT_EQ(2u, Mix_FadeInChannel_fake.call_count);

  // Already playing
  Mix_Playing_fake.return_val = 1;
  mSound.fade_in(cen::sound_effect::ms_type {5});
  ASSERT_EQ(2u, Mix_FadeInChannel_fake.call_count);
}

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(SoundEffectTest, FadeOut)
{
  // Not playing
  mSound.fade_out(cen::sound_effect::ms_type {5});
  ASSERT_EQ(0u, Mix_FadeOutChannel_fake.call_count);

  // Not playing but with an associated channel
  mSound.set_channel(7);
  mSound.fade_out(cen::sound_effect::ms_type {5});
  ASSERT_EQ(0u, Mix_FadeOutChannel_fake.call_count);

  // Playing
  Mix_Playing_fake.return_val = 1;
  mSound.fade_out(cen::sound_effect::ms_type {5});
  ASSERT_EQ(1u, Mix_FadeOutChannel_fake.call_count);
}

TEST_F(SoundEffectTest, SetVolume)
{
  mSound.set_volume(-1);
  ASSERT_EQ(0, Mix_VolumeChunk_fake.arg1_val);

  mSound.set_volume(cen::sound_effect::max_volume() + 1);
  ASSERT_EQ(cen::sound_effect::max_volume(), Mix_VolumeChunk_fake.arg1_val);

  mSound.set_volume(27);
  ASSERT_EQ(27, Mix_VolumeChunk_fake.arg1_val);
}

TEST_F(SoundEffectTest, IsAnyPlaying)
{
  const auto playing [[maybe_unused]] = cen::sound_effect::is_any_playing();
  ASSERT_EQ(1u, Mix_Playing_fake.call_count);
  ASSERT_EQ(-1, Mix_Playing_fake.arg0_val);
}

TEST_F(SoundEffectTest, Channel)
{
  ASSERT_FALSE(mSound.channel().has_value());

  mSound.set_channel(7);
  ASSERT_EQ(7, mSound.channel());
}

TEST_F(SoundEffectTest, GetDecoder)
{
  const auto* name [[maybe_unused]] = cen::sound_effect::get_decoder(0);
  ASSERT_EQ(1u, Mix_GetChunkDecoder_fake.call_count);
}

TEST_F(SoundEffectTest, HasDecoder)
{
  CEN_PREPARE_MOCK_TEST(Mix_HasChunkDecoder, SDL_FALSE, SDL_TRUE)

  ASSERT_FALSE(cen::sound_effect::has_decoder("foo"));
  ASSERT_TRUE(cen::sound_effect::has_decoder("foo"));

  ASSERT_EQ(2u, Mix_HasChunkDecoder_fake.call_count);
}

TEST_F(SoundEffectTest, DecoderCount)
{
  const auto count [[maybe_unused]] = cen::sound_effect::decoder_count();
  ASSERT_EQ(1u, Mix_GetNumChunkDecoders_fake.call_count);
}

#if SDL_MIXER_VERSION_ATLEAST(2, 6, 0)

TEST_F(SoundEffectTest, SetMasterVolume)
{
  cen::sound_effect::set_master_volume(53);
  ASSERT_EQ(53, Mix_MasterVolume_fake.arg0_val);
  ASSERT_EQ(1u, Mix_MasterVolume_fake.call_count);
}

TEST_F(SoundEffectTest, MasterVolume)
{
  const auto volume [[maybe_unused]] = cen::sound_effect::master_volume();
  ASSERT_EQ(-1, Mix_MasterVolume_fake.arg0_val);
  ASSERT_EQ(1u, Mix_MasterVolume_fake.call_count);
}

#endif  // SDL_MIXER_VERSION_ATLEAST(2, 6, 0)
