#include "events/event.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_PumpEvents)
FAKE_VOID_FUNC(SDL_FlushEvents, Uint32, Uint32)
FAKE_VALUE_FUNC(int, SDL_PushEvent, SDL_Event*)
FAKE_VALUE_FUNC(int, SDL_PollEvent, SDL_Event*)
FAKE_VALUE_FUNC(int, SDL_PeepEvents, SDL_Event*, int, SDL_eventaction, Uint32, Uint32)
}
// clang-format on

class EventTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_PumpEvents);
    RESET_FAKE(SDL_FlushEvents);
    RESET_FAKE(SDL_PushEvent);
    RESET_FAKE(SDL_PollEvent);
    RESET_FAKE(SDL_PeepEvents);
  }
};

TEST_F(EventTest, Update)
{
  cen::event::update();
  ASSERT_EQ(1, SDL_PumpEvents_fake.call_count);
}

TEST_F(EventTest, Push)
{
  cen::event event;
  cen::event::push(event);
  ASSERT_EQ(1, SDL_PushEvent_fake.call_count);
}

TEST_F(EventTest, Flush)
{
  cen::event::flush();
  ASSERT_EQ(1, SDL_FlushEvents_fake.call_count);
  ASSERT_EQ(SDL_FIRSTEVENT, SDL_FlushEvents_fake.arg0_val);
  ASSERT_EQ(SDL_LASTEVENT, SDL_FlushEvents_fake.arg1_val);
}

TEST_F(EventTest, FlushAll)
{
  cen::event::flush_all();
  ASSERT_EQ(1, SDL_PumpEvents_fake.call_count);
  ASSERT_EQ(1, SDL_FlushEvents_fake.call_count);
  ASSERT_EQ(SDL_FIRSTEVENT, SDL_FlushEvents_fake.arg0_val);
  ASSERT_EQ(SDL_LASTEVENT, SDL_FlushEvents_fake.arg1_val);
}

TEST_F(EventTest, Poll)
{
  cen::event event;
  event.poll();

  ASSERT_EQ(1, SDL_PollEvent_fake.call_count);
}

TEST_F(EventTest, QueueCount)
{
  const auto count [[maybe_unused]] = cen::event::queue_count();
  ASSERT_EQ(1, SDL_PeepEvents_fake.call_count);
  ASSERT_EQ(nullptr, SDL_PeepEvents_fake.arg0_val);
  ASSERT_EQ(0, SDL_PeepEvents_fake.arg1_val);
  ASSERT_EQ(SDL_PEEKEVENT, SDL_PeepEvents_fake.arg2_val);
  ASSERT_EQ(SDL_FIRSTEVENT, SDL_PeepEvents_fake.arg3_val);
  ASSERT_EQ(SDL_LASTEVENT, SDL_PeepEvents_fake.arg4_val);
}

TEST_F(EventTest, QueueCountSpecific)
{
  const auto count [[maybe_unused]] = cen::event::queue_count(cen::event_type::quit);

  ASSERT_EQ(1, SDL_PeepEvents_fake.call_count);
  ASSERT_EQ(nullptr, SDL_PeepEvents_fake.arg0_val);
  ASSERT_EQ(0, SDL_PeepEvents_fake.arg1_val);
  ASSERT_EQ(SDL_PEEKEVENT, SDL_PeepEvents_fake.arg2_val);
  ASSERT_EQ(static_cast<Uint32>(SDL_QUIT), SDL_PeepEvents_fake.arg3_val);
  ASSERT_EQ(static_cast<Uint32>(SDL_QUIT), SDL_PeepEvents_fake.arg4_val);
}