#include <gtest/gtest.h>

#include <iostream>  // cout

#include "common.hpp"
#include "filesystem.hpp"

TEST(SeekMode, Values)
{
  ASSERT_EQ(RW_SEEK_SET, to_underlying(cen::seek_mode::from_beginning));
  ASSERT_EQ(RW_SEEK_CUR, to_underlying(cen::seek_mode::relative_to_current));
  ASSERT_EQ(RW_SEEK_END, to_underlying(cen::seek_mode::relative_to_end));
}

TEST(SeekMode, ToString)
{
  ASSERT_EQ("from_beginning", to_string(cen::seek_mode::from_beginning));
  ASSERT_EQ("relative_to_current", to_string(cen::seek_mode::relative_to_current));
  ASSERT_EQ("relative_to_end", to_string(cen::seek_mode::relative_to_end));

  std::cout << "seek_mode::from_beginning == " << cen::seek_mode::from_beginning << '\n';
}
