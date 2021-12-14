#include <fff.h>
#include <gtest/gtest.h>

#include "core_mocks.hpp"
#include "filesystem.hpp"

extern "C"
{
  FAKE_VALUE_FUNC(char*, SDL_GetPrefPath, const char*, const char*)
}

class PreferredPathTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_GetPrefPath)
  }
};

TEST_F(PreferredPathTest, FunctionCall)
{
  const auto path [[maybe_unused]] = cen::GetPreferredPath("centurion", "tests");
  ASSERT_EQ(1u, SDL_GetPrefPath_fake.call_count);
}
