#include "filesystem/seek_mode.hpp"

#include <gtest/gtest.h>

#include <iostream>  // cout

#include "core/to_underlying.hpp"

TEST(SeekMode, Values)
{
  ASSERT_EQ(RW_SEEK_SET, cen::to_underlying(cen::seek_mode::from_beginning));
  ASSERT_EQ(RW_SEEK_CUR, cen::to_underlying(cen::seek_mode::relative_to_current));
  ASSERT_EQ(RW_SEEK_END, cen::to_underlying(cen::seek_mode::relative_to_end));
}

TEST(SeekMode, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::seek_mode>(3)), cen::cen_error);

  ASSERT_EQ("from_beginning", cen::to_string(cen::seek_mode::from_beginning));
  ASSERT_EQ("relative_to_current", cen::to_string(cen::seek_mode::relative_to_current));
  ASSERT_EQ("relative_to_end", cen::to_string(cen::seek_mode::relative_to_end));

  std::cout << "Seek mode example: " << cen::seek_mode::from_beginning << '\n';
}
