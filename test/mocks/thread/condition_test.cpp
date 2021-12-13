#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "system/concurrency.hpp"
#include "thread_mocks.hpp"

class ConditionTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    mocks::reset_thread();
  }
};

TEST_F(ConditionTest, Constructor)
{
  ASSERT_THROW(cen::Condition{}, cen::SDLError);
}
