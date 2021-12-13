#include <gtest/gtest.h>

#include <type_traits>

#include "system/concurrency.hpp"

static_assert(!std::is_copy_constructible_v<cen::ScopedLock>);
static_assert(!std::is_copy_assignable_v<cen::ScopedLock>);

TEST(ScopedLock, Construction)
{
  cen::Mutex mutex;
  ASSERT_NO_THROW(cen::ScopedLock{mutex});
}
