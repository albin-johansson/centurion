#include "shared_object.hpp"

#include <gtest/gtest.h>

#include "core_mocks.hpp"

extern "C" {
FAKE_VOID_FUNC(SDL_UnloadObject, void*)
FAKE_VALUE_FUNC(void*, SDL_LoadObject, const char*)
FAKE_VALUE_FUNC(void*, SDL_LoadFunction, void*, const char*)
}

class SharedObjectTest : public testing::Test
{
 public:
  void SetUp() override
  {
    mocks::reset_core();
    RESET_FAKE(SDL_UnloadObject);
    RESET_FAKE(SDL_LoadObject);
    RESET_FAKE(SDL_LoadFunction);
  }

  cen::shared_object m_object;
};

TEST_F(SharedObjectTest, LoadFunction)
{
  auto* ptr [[maybe_unused]] = m_object.load_function<void(int, float)>("foo");

  EXPECT_EQ(1, SDL_LoadFunction_fake.call_count);
  EXPECT_STREQ("foo", SDL_LoadFunction_fake.arg1_val);
}
