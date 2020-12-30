#include "scoped_lock.hpp"

#include <gtest/gtest.h>

TEST(ScopedLock, Construction)
{
  cen::mutex mutex;
  EXPECT_NO_THROW(cen::scoped_lock{mutex});
}
