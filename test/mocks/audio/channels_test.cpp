#include "audio/channels.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core_mocks.hpp"

using namespace cen::literals;

extern "C" {

using channel_finished_callback = void(SDLCALL*)(int);

FAKE_VOID_FUNC(Mix_ChannelFinished, channel_finished_callback)
FAKE_VALUE_FUNC(int, Mix_AllocateChannels, int)
FAKE_VALUE_FUNC(int, Mix_ReserveChannels, int)
FAKE_VALUE_FUNC(int, Mix_ExpireChannel, int, int)
FAKE_VALUE_FUNC(int, Mix_GroupChannel, int, int)
}

class ChannelsTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(Mix_AllocateChannels)
    RESET_FAKE(Mix_ReserveChannels)
    RESET_FAKE(Mix_ExpireChannel)
    RESET_FAKE(Mix_GroupChannel)
    RESET_FAKE(Mix_ChannelFinished)
  }
};

TEST_F(ChannelsTest, OnFinished)
{
  cen::channels::on_finished([](cen::channel_index channel) noexcept {
  });

  ASSERT_EQ(1, Mix_ChannelFinished_fake.call_count);
}

TEST_F(ChannelsTest, Allocate)
{
  cen::channels::allocate(42);
  ASSERT_EQ(1, Mix_AllocateChannels_fake.call_count);
}

TEST_F(ChannelsTest, Reserve)
{
  cen::channels::reserve(42);
  ASSERT_EQ(1, Mix_ReserveChannels_fake.call_count);
}

TEST_F(ChannelsTest, Expire)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_ExpireChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::channels::expire(7, 25_ms));
  ASSERT_EQ(cen::success, cen::channels::expire(7, 25_ms));
  ASSERT_EQ(2, Mix_ExpireChannel_fake.call_count);
}

TEST_F(ChannelsTest, RemoveExpiration)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_ExpireChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::channels::remove_expiration(7));
  ASSERT_EQ(cen::success, cen::channels::remove_expiration(7));
  ASSERT_EQ(-1, Mix_ExpireChannel_fake.arg1_val);
  ASSERT_EQ(2, Mix_ExpireChannel_fake.call_count);
}

TEST_F(ChannelsTest, SetGroup)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_GroupChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::channels::set_group(7, 42));
  ASSERT_EQ(cen::success, cen::channels::set_group(7, 42));
  ASSERT_EQ(2, Mix_GroupChannel_fake.call_count);
}

TEST_F(ChannelsTest, ResetGroup)
{
  std::array values{0, 1};
  SET_RETURN_SEQ(Mix_GroupChannel, values.data(), cen::isize(values));

  ASSERT_EQ(cen::failure, cen::channels::reset_group(7));
  ASSERT_EQ(cen::success, cen::channels::reset_group(7));
  ASSERT_EQ(-1, Mix_GroupChannel_fake.arg1_val);
  ASSERT_EQ(2, Mix_GroupChannel_fake.call_count);
}
