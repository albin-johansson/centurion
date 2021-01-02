#include "sound_effect.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VOID_FUNC(Mix_FreeChunk, Mix_Chunk*)
FAKE_VALUE_FUNC(int, Mix_PlayChannelTimed, int, Mix_Chunk*, int, int)
}
// clang-format on

class SoundEffectTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(Mix_FreeChunk);
    RESET_FAKE(Mix_PlayChannelTimed);
  }

  cen::sound_effect m_sound;
};

TEST_F(SoundEffectTest, Play)
{
  m_sound.play();
  EXPECT_EQ(1, Mix_PlayChannelTimed_fake.call_count);
}
