#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/concurrency.hpp"

TEST(ThreadPriority, Values)
{
  ASSERT_EQ(SDL_THREAD_PRIORITY_LOW, to_underlying(cen::thread_priority::low));
  ASSERT_EQ(SDL_THREAD_PRIORITY_NORMAL, to_underlying(cen::thread_priority::normal));
  ASSERT_EQ(SDL_THREAD_PRIORITY_HIGH, to_underlying(cen::thread_priority::high));
  ASSERT_EQ(SDL_THREAD_PRIORITY_TIME_CRITICAL, to_underlying(cen::thread_priority::critical));
}

TEST(ThreadPriority, to_string)
{
  ASSERT_THROW(to_string(static_cast<cen::thread_priority>(5)), cen::exception);

  ASSERT_EQ("low", to_string(cen::thread_priority::low));
  ASSERT_EQ("normal", to_string(cen::thread_priority::normal));
  ASSERT_EQ("high", to_string(cen::thread_priority::high));
  ASSERT_EQ("critical", to_string(cen::thread_priority::critical));

  std::cout << "thread_priority::high == " << cen::thread_priority::high << '\n';
}
