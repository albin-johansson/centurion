#include "thread/mutex.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "thread_mocks.hpp"

class MutexTest : public testing::Test
{
 public:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(MutexTest, Constructor)
{
  EXPECT_THROW(cen::mutex{}, cen::sdl_error);
  EXPECT_EQ(1, SDL_CreateMutex_fake.call_count);
}
