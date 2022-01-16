#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "filesystem.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(char*, SDL_GetBasePath)
}

class BasePathTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_GetBasePath)
  }
};

TEST_F(BasePathTest, FunctionCall)
{
  const auto path [[maybe_unused]] = cen::base_path();
  ASSERT_EQ(1u, SDL_GetBasePath_fake.call_count);
}
