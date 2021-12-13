#include <gtest/gtest.h>

#include "concurrency.hpp"
#include "core_mocks.hpp"
#include "thread_mocks.hpp"

class MutexTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(MutexTest, Constructor)
{
  ASSERT_THROW(cen::Mutex{}, cen::SDLError);
  ASSERT_EQ(1u, SDL_CreateMutex_fake.call_count);
}
