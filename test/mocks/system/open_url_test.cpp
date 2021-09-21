#include "system/open_url.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>  // array

#include "core/integers.hpp"
#include "core_mocks.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

extern "C"
{
  FAKE_VALUE_FUNC(int, SDL_OpenURL, const char*)
}  // extern "C"

class OpenURLTest : public testing::Test
{
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

  ASSERT_FALSE(cen::open_url(url));
  ASSERT_TRUE(cen::open_url(url));

  ASSERT_EQ(2u, SDL_OpenURL_fake.call_count);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
