#include "thread/thread_priority.hpp"

#include <gtest/gtest.h>

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
