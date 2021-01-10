#include "scoped_lock.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "thread_mocks.hpp"

class ScopedLockTest : public testing::Test
{
 public:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(ScopedLockTest, ConstructorFailsToLockMutex)
{
  cen::mutex mutex{0};  // Dummy parameter for mock-friendly constructor

  SDL_LockMutex_fake.return_val = -1;
  EXPECT_THROW(cen::scoped_lock{mutex}, cen::sdl_error);
}
