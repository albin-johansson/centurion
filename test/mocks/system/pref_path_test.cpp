#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "filesystem/preferred_path.hpp"

extern "C" {
FAKE_VALUE_FUNC(char*, SDL_GetPrefPath, const char*, const char*)
}

class PrefPathTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_GetPrefPath);
  }
};

TEST_F(PrefPathTest, FunctionCall)
{
  const auto path [[maybe_unused]] = cen::preferred_path("centurion", "tests");
  EXPECT_EQ(1, SDL_GetPrefPath_fake.call_count);
}
