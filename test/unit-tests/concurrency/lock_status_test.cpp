#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "concurrency.hpp"

TEST(LockStatus, Values)
{
  ASSERT_EQ(0, to_underlying(cen::lock_status::success));
  ASSERT_EQ(SDL_MUTEX_TIMEDOUT, to_underlying(cen::lock_status::timed_out));
  ASSERT_EQ(-1, to_underlying(cen::lock_status::error));
}

TEST(LockStatus, to_string)
{
  ASSERT_THROW(to_string(static_cast<cen::lock_status>(2)), cen::exception);

  ASSERT_EQ("success", to_string(cen::lock_status::success));
  ASSERT_EQ("timed_out", to_string(cen::lock_status::timed_out));
  ASSERT_EQ("error", to_string(cen::lock_status::error));

  std::cout << "lock_status::timed_out == " << cen::lock_status::timed_out << '\n';
}
