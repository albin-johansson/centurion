#include "audio/mixer.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

using namespace cen::literals;

extern "C" {
using each_sound_font = int(SDLCALL*)(const char*, void*);
using channel_finished_callback = void(SDLCALL*)(int);

FAKE_VALUE_FUNC(int, Mix_SetSoundFonts, const char*)
FAKE_VALUE_FUNC(const char*, Mix_GetSoundFonts)
FAKE_VALUE_FUNC(int, Mix_EachSoundFont, each_sound_font, void*)
FAKE_VALUE_FUNC(int, Mix_AllocateChannels, int)
FAKE_VALUE_FUNC(int, Mix_ReserveChannels, int)
FAKE_VALUE_FUNC(int, Mix_ExpireChannel, int, int)
FAKE_VALUE_FUNC(int, Mix_GroupChannel, int, int)

FAKE_VOID_FUNC(Mix_ChannelFinished, channel_finished_callback)
}

class MixerTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(Mix_SetSoundFonts)
    RESET_FAKE(Mix_GetSoundFonts)
    RESET_FAKE(Mix_EachSoundFont)
    RESET_FAKE(Mix_AllocateChannels)
    RESET_FAKE(Mix_ReserveChannels)
    RESET_FAKE(Mix_ExpireChannel)
    RESET_FAKE(Mix_GroupChannel)

    RESET_FAKE(Mix_ChannelFinished)
  }
};

TEST_F(MixerTest, SetSoundFonts)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_SetSoundFonts, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::set_sound_fonts("foo"));
  ASSERT_EQ(cen::success, cen::set_sound_fonts("foo"));

  ASSERT_EQ(2, Mix_SetSoundFonts_fake.call_count);
  ASSERT_STREQ("foo", Mix_SetSoundFonts_fake.arg0_val);
}

TEST_F(MixerTest, GetSoundFonts)
{
  const auto* fonts [[maybe_unused]] = cen::get_sound_fonts();
  ASSERT_EQ(1, Mix_GetSoundFonts_fake.call_count);
}

TEST_F(MixerTest, EachSoundFont)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_EachSoundFont, values.data(), cen::isize(values));

  const auto callable = [](cen::czstring font, void* data) noexcept {
    return 0;
  };

  ASSERT_EQ(cen::failure, cen::each_sound_font(callable));
  ASSERT_EQ(cen::success, cen::each_sound_font(callable));
  ASSERT_EQ(2, Mix_EachSoundFont_fake.call_count);
}

TEST_F(MixerTest, OnChannelFinished)
{
  cen::on_channel_finished([](int channel) noexcept {
  });

  ASSERT_EQ(1, Mix_ChannelFinished_fake.call_count);
}

TEST_F(MixerTest, AllocateChannels)
{
  cen::allocate_channels(42);
  ASSERT_EQ(1, Mix_AllocateChannels_fake.call_count);
}

TEST_F(MixerTest, ReserveChannels)
{
  cen::reserve_channels(42);
  ASSERT_EQ(1, Mix_ReserveChannels_fake.call_count);
}

TEST_F(MixerTest, ExpireChannel)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_ExpireChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::expire_channel(7, 25_ms));
  ASSERT_EQ(cen::success, cen::expire_channel(7, 25_ms));
  ASSERT_EQ(2, Mix_ExpireChannel_fake.call_count);
}

TEST_F(MixerTest, RemoveExpiration)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_ExpireChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::remove_expiration(7));
  ASSERT_EQ(cen::success, cen::remove_expiration(7));
  ASSERT_EQ(-1, Mix_ExpireChannel_fake.arg1_val);
  ASSERT_EQ(2, Mix_ExpireChannel_fake.call_count);
}

TEST_F(MixerTest, SetChannelGroup)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_GroupChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::set_channel_group(7, 42));
  ASSERT_EQ(cen::success, cen::set_channel_group(7, 42));
  ASSERT_EQ(2, Mix_GroupChannel_fake.call_count);
}

TEST_F(MixerTest, ResetChannelGroup)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_GroupChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::reset_channel_group(7));
  ASSERT_EQ(cen::success, cen::reset_channel_group(7));
  ASSERT_EQ(-1, Mix_GroupChannel_fake.arg1_val);
  ASSERT_EQ(2, Mix_GroupChannel_fake.call_count);
}
