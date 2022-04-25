#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/system.hpp"

TEST(PlatformID, ToString)
{
  ASSERT_THROW(to_string(static_cast<cen::platform_id>(100)), cen::exception);

  ASSERT_EQ("unknown", to_string(cen::platform_id::unknown));
  ASSERT_EQ("windows", to_string(cen::platform_id::windows));
  ASSERT_EQ("macos", to_string(cen::platform_id::macos));
  ASSERT_EQ("linux_os", to_string(cen::platform_id::linux_os));
  ASSERT_EQ("ios", to_string(cen::platform_id::ios));
  ASSERT_EQ("android", to_string(cen::platform_id::android));

  std::cout << "platform_id::windows == " << cen::platform_id::windows << '\n';
}