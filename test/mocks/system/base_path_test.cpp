#include "filesystem/base_path.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C" {
FAKE_VALUE_FUNC(char*, SDL_GetBasePath)
}

class BasePathTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_GetBasePath);
  }
};

TEST_F(BasePathTest, FunctionCall)
{
  const auto path [[maybe_unused]] = cen::get_base_path();
  EXPECT_EQ(1, SDL_GetBasePath_fake.call_count);
}
