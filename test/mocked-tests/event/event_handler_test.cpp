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

#include "centurion/events/event_handler.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_PumpEvents)
FAKE_VOID_FUNC(SDL_FlushEvents, Uint32, Uint32)
FAKE_VALUE_FUNC(int, SDL_PushEvent, SDL_Event*)
FAKE_VALUE_FUNC(int, SDL_PollEvent, SDL_Event*)
FAKE_VALUE_FUNC(int, SDL_PeepEvents, SDL_Event*, int, SDL_eventaction, Uint32, Uint32)
}

class EventTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_PumpEvents)
    RESET_FAKE(SDL_FlushEvents)
    RESET_FAKE(SDL_PushEvent)
    RESET_FAKE(SDL_PollEvent)
    RESET_FAKE(SDL_PeepEvents)
  }
};

TEST_F(EventTest, Update)
{
  cen::event_handler::update();
  ASSERT_EQ(1u, SDL_PumpEvents_fake.call_count);
}

TEST_F(EventTest, Flush)
{
  cen::event_handler::flush();
  ASSERT_EQ(1u, SDL_FlushEvents_fake.call_count);
  ASSERT_EQ(SDL_FIRSTEVENT, static_cast<SDL_EventType>(SDL_FlushEvents_fake.arg0_val));
  ASSERT_EQ(SDL_LASTEVENT, static_cast<SDL_EventType>(SDL_FlushEvents_fake.arg1_val));
}

TEST_F(EventTest, FlushAll)
{
  cen::event_handler::flush_all();
  ASSERT_EQ(1u, SDL_PumpEvents_fake.call_count);
  ASSERT_EQ(1u, SDL_FlushEvents_fake.call_count);
  ASSERT_EQ(SDL_FIRSTEVENT, static_cast<SDL_EventType>(SDL_FlushEvents_fake.arg0_val));
  ASSERT_EQ(SDL_LASTEVENT, static_cast<SDL_EventType>(SDL_FlushEvents_fake.arg1_val));
}

TEST_F(EventTest, Poll)
{
  cen::event_handler handler;
  handler.poll();

  ASSERT_EQ(1u, SDL_PollEvent_fake.call_count);
}

TEST_F(EventTest, QueueCount)
{
  const auto count [[maybe_unused]] = cen::event_handler::queue_count();
  ASSERT_EQ(1u, SDL_PeepEvents_fake.call_count);
  ASSERT_EQ(nullptr, SDL_PeepEvents_fake.arg0_val);
  ASSERT_EQ(0, SDL_PeepEvents_fake.arg1_val);
  ASSERT_EQ(SDL_PEEKEVENT, SDL_PeepEvents_fake.arg2_val);
  ASSERT_EQ(SDL_FIRSTEVENT, SDL_PeepEvents_fake.arg3_val);
  ASSERT_EQ(SDL_LASTEVENT, SDL_PeepEvents_fake.arg4_val);
}

TEST_F(EventTest, QueueCountSpecific)
{
  const auto count [[maybe_unused]] = cen::event_handler::queue_count(cen::event_type::quit);

  ASSERT_EQ(1u, SDL_PeepEvents_fake.call_count);
  ASSERT_EQ(nullptr, SDL_PeepEvents_fake.arg0_val);
  ASSERT_EQ(0, SDL_PeepEvents_fake.arg1_val);
  ASSERT_EQ(SDL_PEEKEVENT, SDL_PeepEvents_fake.arg2_val);
  ASSERT_EQ(static_cast<Uint32>(SDL_QUIT), SDL_PeepEvents_fake.arg3_val);
  ASSERT_EQ(static_cast<Uint32>(SDL_QUIT), SDL_PeepEvents_fake.arg4_val);
}