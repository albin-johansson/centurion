#include <gtest/gtest.h>

#include <iostream>  // cout

#include "filesystem.hpp"

TEST(FileMode, ToString)
{
  ASSERT_EQ("r", to_string(cen::file_mode::r));
  ASSERT_EQ("rb", to_string(cen::file_mode::rb));

  ASSERT_EQ("w", to_string(cen::file_mode::w));
  ASSERT_EQ("wb", to_string(cen::file_mode::wb));

  ASSERT_EQ("a", to_string(cen::file_mode::a));
  ASSERT_EQ("ab", to_string(cen::file_mode::ab));

  ASSERT_EQ("rx", to_string(cen::file_mode::rx));
  ASSERT_EQ("rbx", to_string(cen::file_mode::rbx));

  ASSERT_EQ("wx", to_string(cen::file_mode::wx));
  ASSERT_EQ("wbx", to_string(cen::file_mode::wbx));

  ASSERT_EQ("ax", to_string(cen::file_mode::ax));
  ASSERT_EQ("abx", to_string(cen::file_mode::abx));

  std::cout << "file_mode::rb == " << cen::file_mode::rb << '\n';
}