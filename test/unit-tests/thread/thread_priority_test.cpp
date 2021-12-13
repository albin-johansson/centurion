#include <gtest/gtest.h>

#include <iostream>  // clog

#include "concurrency.hpp"
#include "core/common.hpp"

TEST(ThreadPriority, Values)
{
  ASSERT_EQ(cen::to_underlying(cen::ThreadPriority::Low), SDL_THREAD_PRIORITY_LOW);
  ASSERT_EQ(cen::to_underlying(cen::ThreadPriority::Normal), SDL_THREAD_PRIORITY_NORMAL);
  ASSERT_EQ(cen::to_underlying(cen::ThreadPriority::High), SDL_THREAD_PRIORITY_HIGH);
  ASSERT_EQ(cen::to_underlying(cen::ThreadPriority::Critical),
            SDL_THREAD_PRIORITY_TIME_CRITICAL);
}

TEST(ThreadPriority, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::ThreadPriority>(5)), cen::Error);

  ASSERT_EQ("Low", cen::to_string(cen::ThreadPriority::Low));
  ASSERT_EQ("Normal", cen::to_string(cen::ThreadPriority::Normal));
  ASSERT_EQ("High", cen::to_string(cen::ThreadPriority::High));
  ASSERT_EQ("Critical", cen::to_string(cen::ThreadPriority::Critical));

  std::clog << "Thread priority example: " << cen::ThreadPriority::High << '\n';
}
