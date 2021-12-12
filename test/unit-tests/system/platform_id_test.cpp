#include <gtest/gtest.h>

#include <iostream>  // clog

#include "system/platform.hpp"

TEST(PlatformID, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::platform_id>(7)), cen::Error);

  ASSERT_EQ("unknown", cen::to_string(cen::platform_id::unknown));
  ASSERT_EQ("windows", cen::to_string(cen::platform_id::windows));
  ASSERT_EQ("mac_osx", cen::to_string(cen::platform_id::mac_osx));
  ASSERT_EQ("linux_os", cen::to_string(cen::platform_id::linux_os));
  ASSERT_EQ("ios", cen::to_string(cen::platform_id::ios));
  ASSERT_EQ("android", cen::to_string(cen::platform_id::android));

  std::clog << "Platform ID example: " << cen::platform_id::windows << '\n';
}
