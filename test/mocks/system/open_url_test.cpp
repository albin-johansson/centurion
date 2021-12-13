#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/common.hpp"
#include "core_mocks.hpp"
#include "system/system.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_OpenURL, const char*)
}

class OpenURLTest : public testing::Test {
 protected:
  void SetUp() override
  {
    mocks::reset_core();

    RESET_FAKE(SDL_OpenURL)
  }
};

TEST_F(OpenURLTest, OpenURL)
{
  std::array values{-1, 0};
  SET_RETURN_SEQ(SDL_OpenURL, values.data(), cen::isize(values));

  using namespace std::string_literals;
  const auto url = "https://www.google.com"s;

  ASSERT_FALSE(cen::OpenURL(url));
  ASSERT_TRUE(cen::OpenURL(url));

  ASSERT_EQ(2u, SDL_OpenURL_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
