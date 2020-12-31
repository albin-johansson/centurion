#include "scoped_lock.hpp"

#include <gtest/gtest.h>

#include <type_traits>

static_assert(!std::is_copy_constructible_v<cen::scoped_lock>);
static_assert(!std::is_copy_assignable_v<cen::scoped_lock>);

TEST(ScopedLock, Construction)
{
  cen::mutex mutex;
  EXPECT_NO_THROW(cen::scoped_lock{mutex});
}
