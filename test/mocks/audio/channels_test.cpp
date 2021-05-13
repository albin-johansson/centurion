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
FAKE_VALUE_FUNC(int, Mix_GroupCount, int)
FAKE_VALUE_FUNC(int, Mix_GroupAvailable, int)
FAKE_VALUE_FUNC(int, Mix_GroupNewer, int)
FAKE_VALUE_FUNC(int, Mix_GroupOldest, int)
}

class ChannelsTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(Mix_ChannelFinished)
    RESET_FAKE(Mix_AllocateChannels)
    RESET_FAKE(Mix_ReserveChannels)
    RESET_FAKE(Mix_ExpireChannel)
    RESET_FAKE(Mix_GroupChannel)
    RESET_FAKE(Mix_GroupCount)
    RESET_FAKE(Mix_GroupAvailable)
    RESET_FAKE(Mix_GroupNewer)
    RESET_FAKE(Mix_GroupOldest)
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

TEST_F(ChannelsTest, GroupCount)
{
  const auto all [[maybe_unused]] = cen::channels::group_count();
  ASSERT_EQ(-1, Mix_GroupCount_fake.arg0_val);

  const auto count [[maybe_unused]] = cen::channels::group_count(123);
  ASSERT_EQ(123, Mix_GroupCount_fake.arg0_val);
  ASSERT_EQ(2, Mix_GroupCount_fake.call_count);
}

TEST_F(ChannelsTest, FirstAvailable)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_GroupAvailable, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::channels::first_available(42));
  ASSERT_TRUE(cen::channels::first_available(42));
  ASSERT_EQ(2, Mix_GroupAvailable_fake.call_count);
}

TEST_F(ChannelsTest, MostRecent)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_GroupNewer, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::channels::most_recent(42));
  ASSERT_TRUE(cen::channels::most_recent(42));
  ASSERT_EQ(2, Mix_GroupNewer_fake.call_count);
}

TEST_F(ChannelsTest, Oldest)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(Mix_GroupOldest, values.data(), cen::isize(values));

  ASSERT_FALSE(cen::channels::oldest(42));
  ASSERT_TRUE(cen::channels::oldest(42));
  ASSERT_EQ(2, Mix_GroupOldest_fake.call_count);
}
