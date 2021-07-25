#include "filesystem/file_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

TEST(FileMode, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::file_mode>(13)), cen::cen_error);

  ASSERT_EQ("read_existing", cen::to_string(cen::file_mode::read_existing));
  ASSERT_EQ("read_existing_binary", cen::to_string(cen::file_mode::read_existing_binary));

  ASSERT_EQ("write", cen::to_string(cen::file_mode::write));
  ASSERT_EQ("write_binary", cen::to_string(cen::file_mode::write_binary));

  ASSERT_EQ("append_or_create", cen::to_string(cen::file_mode::append_or_create));
  ASSERT_EQ("append_or_create_binary",
            cen::to_string(cen::file_mode::append_or_create_binary));

  ASSERT_EQ("read_write_existing", cen::to_string(cen::file_mode::read_write_existing));
  ASSERT_EQ("read_write_existing_binary",
            cen::to_string(cen::file_mode::read_write_existing_binary));

  ASSERT_EQ("read_write_replace", cen::to_string(cen::file_mode::read_write_replace));
  ASSERT_EQ("read_write_replace_binary",
            cen::to_string(cen::file_mode::read_write_replace_binary));

  ASSERT_EQ("read_append", cen::to_string(cen::file_mode::read_append));
  ASSERT_EQ("read_append_binary", cen::to_string(cen::file_mode::read_append_binary));

  std::cout << "File mode example: " << cen::file_mode::write << '\n';
}
