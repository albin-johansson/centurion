#include "audio/sound_effect.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

using ms = cen::milliseconds<int>;

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
    mocks::reset_core();

    RESET_FAKE(Mix_FreeChunk);
    RESET_FAKE(Mix_Pause);
    RESET_FAKE(Mix_PlayChannelTimed);
    RESET_FAKE(Mix_FadeInChannelTimed);
    RESET_FAKE(Mix_FadeOutChannel);
    RESET_FAKE(Mix_Playing);
    RESET_FAKE(Mix_VolumeChunk);
  }

  cen::sound_effect_handle m_sound{nullptr};
};

TEST_F(SoundEffectTest, Play)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_PlayChannelTimed, values.data(), cen::isize(values));

  EXPECT_FALSE(m_sound.play());
  EXPECT_EQ(1, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(0, Mix_PlayChannelTimed_fake.arg2_val);

  EXPECT_TRUE(m_sound.play(-2));
  EXPECT_EQ(2, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(-1, Mix_PlayChannelTimed_fake.arg2_val);

  EXPECT_TRUE(m_sound.play(7));
  EXPECT_EQ(3, Mix_PlayChannelTimed_fake.call_count);
  EXPECT_EQ(7, Mix_PlayChannelTimed_fake.arg2_val);
}

TEST_F(SoundEffectTest, Pause)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_Playing, values.data(), cen::isize(values));

  m_sound.stop();  // Does not invoke Mix_Playing
  EXPECT_EQ(0, Mix_Pause_fake.call_count);

  m_sound.set_channel(23);

  m_sound.stop();
  EXPECT_EQ(0, Mix_Pause_fake.call_count);

  m_sound.stop();
  EXPECT_EQ(1, Mix_Pause_fake.call_count);
}

TEST_F(SoundEffectTest, FadeIn)
{
  // Not playing
  m_sound.fade_in(ms{5});
  EXPECT_EQ(1, Mix_FadeInChannelTimed_fake.call_count);

  // Not playing but with an associated channel
  m_sound.set_channel(1);
  m_sound.fade_in(ms{5});
  EXPECT_EQ(2, Mix_FadeInChannelTimed_fake.call_count);

  // Already playing
  Mix_Playing_fake.return_val = 1;
  m_sound.fade_in(ms{5});
  EXPECT_EQ(2, Mix_FadeInChannelTimed_fake.call_count);
}

TEST_F(SoundEffectTest, FadeOut)
{
  // Not playing
  m_sound.fade_out(ms{5});
  EXPECT_EQ(0, Mix_FadeOutChannel_fake.call_count);

  // Not playing but with an associated channel
  m_sound.set_channel(7);
  m_sound.fade_out(ms{5});
  EXPECT_EQ(0, Mix_FadeOutChannel_fake.call_count);

  // Playing
  Mix_Playing_fake.return_val = 1;
  m_sound.fade_out(ms{5});
  EXPECT_EQ(1, Mix_FadeOutChannel_fake.call_count);
}

TEST_F(SoundEffectTest, SetVolume)
{
  m_sound.set_volume(-1);
  EXPECT_EQ(0, Mix_VolumeChunk_fake.arg1_val);

  m_sound.set_volume(cen::sound_effect::max_volume() + 1);
  EXPECT_EQ(cen::sound_effect::max_volume(), Mix_VolumeChunk_fake.arg1_val);

  m_sound.set_volume(27);
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
  EXPECT_FALSE(m_sound.channel().has_value());

  m_sound.set_channel(7);
  EXPECT_EQ(7, m_sound.channel());
}

using SoundEffectDeathTest = SoundEffectTest;

TEST_F(SoundEffectDeathTest, FadeIn)
{
  EXPECT_DEBUG_DEATH(m_sound.fade_in(ms::zero()), "");
}

TEST_F(SoundEffectDeathTest, FadeOut)
{
  EXPECT_DEBUG_DEATH(m_sound.fade_out(ms::zero()), "");
}