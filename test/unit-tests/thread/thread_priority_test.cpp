#include "thread/thread_priority.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

TEST(ThreadPriority, Values)
{
  ASSERT_EQ(cen::thread_priority::low, SDL_THREAD_PRIORITY_LOW);
  ASSERT_EQ(cen::thread_priority::normal, SDL_THREAD_PRIORITY_NORMAL);
  ASSERT_EQ(cen::thread_priority::high, SDL_THREAD_PRIORITY_HIGH);
  ASSERT_EQ(cen::thread_priority::critical, SDL_THREAD_PRIORITY_TIME_CRITICAL);

  ASSERT_EQ(SDL_THREAD_PRIORITY_LOW, cen::thread_priority::low);
  ASSERT_EQ(SDL_THREAD_PRIORITY_NORMAL, cen::thread_priority::normal);
  ASSERT_EQ(SDL_THREAD_PRIORITY_HIGH, cen::thread_priority::high);
  ASSERT_EQ(SDL_THREAD_PRIORITY_TIME_CRITICAL, cen::thread_priority::critical);

  ASSERT_NE(cen::thread_priority::high, SDL_THREAD_PRIORITY_TIME_CRITICAL);
  ASSERT_NE(SDL_THREAD_PRIORITY_LOW, cen::thread_priority::normal);
}

TEST(ThreadPriority, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::thread_priority>(5)), cen::Error);

  ASSERT_EQ("low", cen::to_string(cen::thread_priority::low));
  ASSERT_EQ("normal", cen::to_string(cen::thread_priority::normal));
  ASSERT_EQ("high", cen::to_string(cen::thread_priority::high));
  ASSERT_EQ("critical", cen::to_string(cen::thread_priority::critical));

  std::clog << "Thread priority example: " << cen::thread_priority::high << '\n';
}
