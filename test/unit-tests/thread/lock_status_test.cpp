#include "thread/lock_status.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(LockStatus, Values)
{
  ASSERT_EQ(0, cen::to_underlying(cen::lock_status::success));
  ASSERT_EQ(SDL_MUTEX_TIMEDOUT, cen::to_underlying(cen::lock_status::timed_out));
  ASSERT_EQ(-1, cen::to_underlying(cen::lock_status::error));
}

TEST(LockStatus, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::lock_status>(2)), cen::cen_error);

  ASSERT_EQ("success", cen::to_string(cen::lock_status::success));
  ASSERT_EQ("timed_out", cen::to_string(cen::lock_status::timed_out));
  ASSERT_EQ("error", cen::to_string(cen::lock_status::error));

  std::cout << "Lock status example: " << cen::lock_status::timed_out << '\n';
}
