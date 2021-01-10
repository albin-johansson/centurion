#include "sound_effect.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VOID_FUNC(Mix_FreeChunk, Mix_Chunk*)
FAKE_VOID_FUNC(Mix_Pause, int)
FAKE_VALUE_FUNC(int, Mix_PlayChannelTimed, int, Mix_Chunk*, int, int)
FAKE_VALUE_FUNC(int, Mix_FadeInChannelTimed, int, Mix_Chunk*, int, int, int)
FAKE_VALUE_FUNC(int, Mix_FadeOutChannel, int, int)
FAKE_VALUE_FUNC(int, Mix_Playing, int)
FAKE_VALUE_FUNC(int, Mix_VolumeChunk, Mix_Chunk*, int)
}
// clang-format on

class SoundEffectTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(Mix_FreeChunk);
    RESET_FAKE(Mix_Pause);
    RESET_FAKE(Mix_PlayChannelTimed);
    RESET_FAKE(Mix_FadeInChannelTimed);
    RESET_FAKE(Mix_FadeOutChannel);
    RESET_FAKE(Mix_Playing);
    RESET_FAKE(Mix_VolumeChunk);
  }
};

TEST_F(SoundEffectTest, Play)
{
  cen::sound_effect sound;

  sound.play();
  EXPECT_EQ(1, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(0, Mix_PlayChannelTimed_fake.arg2_val);

  sound.play(-2);
  EXPECT_EQ(2, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(-1, Mix_PlayChannelTimed_fake.arg2_val);

  sound.play(7);
  EXPECT_EQ(3, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(7, Mix_PlayChannelTimed_fake.arg2_val);
}

TEST_F(SoundEffectTest, Pause)
{
  cen::sound_effect sound;

  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_Playing, values.data(), static_cast<int>(values.size()));

  sound.stop();  // Does not invoke Mix_Playing
  EXPECT_EQ(0, Mix_Pause_fake.call_count);

  sound.set_channel(23);

  sound.stop();
  EXPECT_EQ(0, Mix_Pause_fake.call_count);

  sound.stop();
  EXPECT_EQ(1, Mix_Pause_fake.call_count);
}

TEST_F(SoundEffectTest, FadeIn)
{
  cen::sound_effect sound;

  // Not playing
  sound.fade_in(cen::milliseconds<int>{5});
  EXPECT_EQ(1, Mix_FadeInChannelTimed_fake.call_count);

  // Not playing but with an associated channel
  sound.set_channel(1);
  sound.fade_in(cen::milliseconds<int>{5});
  EXPECT_EQ(2, Mix_FadeInChannelTimed_fake.call_count);

  // Already playing
  Mix_Playing_fake.return_val = 1;
  sound.fade_in(cen::milliseconds<int>{5});
  EXPECT_EQ(2, Mix_FadeInChannelTimed_fake.call_count);
}

TEST_F(SoundEffectTest, FadeOut)
{
  cen::sound_effect sound;

  // Not playing
  sound.fade_out(cen::milliseconds<int>{5});
  EXPECT_EQ(0, Mix_FadeOutChannel_fake.call_count);

  // Not playing but with an associated channel
  sound.set_channel(7);
  sound.fade_out(cen::milliseconds<int>{5});
  EXPECT_EQ(0, Mix_FadeOutChannel_fake.call_count);

  // Playing
  Mix_Playing_fake.return_val = 1;
  sound.fade_out(cen::milliseconds<int>{5});
  EXPECT_EQ(1, Mix_FadeOutChannel_fake.call_count);
}

TEST_F(SoundEffectTest, SetVolume)
{
  cen::sound_effect sound;

  sound.set_volume(-1);
  EXPECT_EQ(0, Mix_VolumeChunk_fake.arg1_val);

  sound.set_volume(cen::sound_effect::max_volume() + 1);
  EXPECT_EQ(cen::sound_effect::max_volume(), Mix_VolumeChunk_fake.arg1_val);

  sound.set_volume(27);
  EXPECT_EQ(27, Mix_VolumeChunk_fake.arg1_val);
}

TEST_F(SoundEffectTest, IsAnyPlaying)
{
  const auto playing [[maybe_unused]] = cen::sound_effect::is_any_playing();
  EXPECT_EQ(1, Mix_Playing_fake.call_count);
  EXPECT_EQ(-1, Mix_Playing_fake.arg0_val);
}

TEST_F(SoundEffectTest, Channel)
{
  cen::sound_effect sound;
  EXPECT_FALSE(sound.channel().has_value());

  sound.set_channel(7);
  EXPECT_EQ(7, sound.channel());
}

using SoundEffectDeathTest = SoundEffectTest;

TEST_F(SoundEffectDeathTest, FadeIn)
{
  cen::sound_effect sound;
  EXPECT_DEBUG_DEATH(sound.fade_in(cen::milliseconds<int>::zero()), "");
}

TEST_F(SoundEffectDeathTest, FadeOut)
{
  cen::sound_effect sound;
  EXPECT_DEBUG_DEATH(sound.fade_out(cen::milliseconds<int>::zero()), "");
}