#include <gtest/gtest.h>

#include <iostream>  // clog

#include "concurrency.hpp"
#include "common.hpp"

TEST(ThreadPriority, Values)
{
  ASSERT_EQ(cen::ToUnderlying(cen::ThreadPriority::Low), SDL_THREAD_PRIORITY_LOW);
  ASSERT_EQ(cen::ToUnderlying(cen::ThreadPriority::Normal), SDL_THREAD_PRIORITY_NORMAL);
  ASSERT_EQ(cen::ToUnderlying(cen::ThreadPriority::High), SDL_THREAD_PRIORITY_HIGH);
  ASSERT_EQ(cen::ToUnderlying(cen::ThreadPriority::Critical),
            SDL_THREAD_PRIORITY_TIME_CRITICAL);
}

TEST(ThreadPriority, ToString)
{
  ASSERT_THROW(cen::ToString(static_cast<cen::ThreadPriority>(5)), cen::Error);

  ASSERT_EQ("Low", cen::ToString(cen::ThreadPriority::Low));
  ASSERT_EQ("Normal", cen::ToString(cen::ThreadPriority::Normal));
  ASSERT_EQ("High", cen::ToString(cen::ThreadPriority::High));
  ASSERT_EQ("Critical", cen::ToString(cen::ThreadPriority::Critical));

  std::clog << "Thread priority example: " << cen::ThreadPriority::High << '\n';
}
