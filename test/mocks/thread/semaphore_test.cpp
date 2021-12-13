#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "concurrency.hpp"
#include "thread_mocks.hpp"

class SemaphoreTest : public testing::Test {
 public:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(SemaphoreTest, Constructor)
{
  ASSERT_THROW(cen::Semaphore{0}, cen::SDLError);
}
